// Download by http://www.codefans.net
//对象居中
$jm.center = function (obj, parent) {
    if (!parent) parent = $(window.document);
    var bgWidth = parent.width();
    var bgHeight = parent.height();
    var popupHeight = $(obj).height();
    var popupWidth = $(obj).width();
    var t = (bgHeight - popupHeight) / 2 + parent.scrollTop();
    var l = (bgWidth - popupWidth) / 2;
    $(obj).css({
        "top": t > 0 ? t : 0,
        "left": l > 0 ? l : 0
    });
}

//获取鼠标坐标
$jm.getMouseLocation = function (ev, target) {
    if (!target) target = $(document.body);
    return {
        x: ev.clientX - target.offset().left,
        y: ev.clientY - target.offset().top//document.body.scrollTop
    };
}


//最大化对象
//@p为对象所在容器
//@w为需要最大化的对象
//@offset 需要处理的偏量
$jm.fullWin = function (w, p, offsetx, offsety) {
    if (!p) p = window;
    p = $(p);
    w = $(w);
    if (!offsetx) offsetx = 0;
    if (!offsety) offsety = 0;
    w.width(p.width() + offsetx);
    w.height(p.height() + offsety);
}

//通过ID获取窗口
$jm.getWinById = function (winid) {
    if (!winid) return;
    var wins = $jm.cache.get('jm_win_container'); //从缓存中获取窗体
    if (wins) {
        var len = wins.length;
        for (var i = 0; i < len; i++) {
            if (wins[i].id() == winid) return wins[i];
        }
    }
}
//通过标题查找窗口
$jm.getWinByTitle = function (title) {
    if (!title) return;
    var wins = $jm.cache.get('jm_win_container'); //从缓存中获取窗体
    if (wins) {
        var len = wins.length;
        for (var i = 0; i < len; i++) {
            if (wins[i].title == title) return wins[i];
        }
    }
}
//移除指定的窗口
$jm._removewin = function (winid) {
    var wins = $jm.cache.get('jm_win_container'); //从缓存中获取窗体
    if (wins) {
        wins = $.grep(wins, function (val, k) {
            return val.id() != winid;
        });
        $jm.cache.set('jm_win_container', wins);
    }
}
//关闭窗口通过ID
$jm.closeWinById = function (id) {
    var win = $jm.getWinById(id);
    if (!win) return;
    win.close();
}
//获取当前最顶层窗口的zindex
$jm.get_top_win = function () {
    var topwin;
    var wins = $jm.cache.get('jm_win_container'); //从缓存中获取窗体
    if (wins) {
        var len = wins.length;
        for (var i = 0; i < len; i++) {
            if (wins[i].winState == $jm.winState.min) continue;
            if (!topwin || wins[i].zindex() > topwin.zindex()) topwin = wins[i];
        }
    }
    return topwin;
}

//窗体状态枚举
$jm.winState = { normal: 0, min: 1, max: 2 };

//创建弹窗
//@params 为窗口参数
//button 为{ text: '', style: '', className: 'jm_win_button', click: function () { return false; } };
$jm.win = function (params) {
    if (!params) return;
    var windowIndex = function (index) {
        if (index) {
            $jm.cache.set('jm_win_index', index); //获取索引
        }
        else return $jm.cache.get('jm_win_index') || 0; //设置索引
    }
    //此窗体的索引
    this.Index = windowIndex() + 1;
    //索引递加一
    windowIndex(this.Index);

    //参数初始化
    var body = (params.body) ? (typeof (params.body) == "object" ? params.body : $("#" + params.body)) : ""; //body参数可以为对象或标签ID   

    this.jmwin = true; //标识为家猫对象
    var headheight = params.headheight || 22;
    var height = params.height || 300;
    var width = params.width || 420;
    var position = params.position || 'auto';
    var left = position == 'left' ? 0 : (params.left || '25%');
    var top = position == 'top' ? 0 : (params.top || 80);
    var style = params.style || "";
    var __title = params.title || params.name || '';
    var __id = params.id || 'jm_win_' + this.Index;

    this.params = params; //保存参数
    //设置默认图标
    this.params.ico = this.params.ico || 'css/default/images/ico.png';

    //窗体ID
    this.id = function () { return __id; }

    //是否为模式窗口
    this.modal = params.modal;
    //默认为正常状态
    this.__oldState = this.winState = $jm.isNull(params.state) ? $jm.winState.normal : params.state;

    //是否可以改变大小
    this.resizeable = params.resizeable != false;
    //窗口关闭回调
    this.closeCallback = params.closeCallback;
    this.focusCallback = params.focusCallback; //获得焦点回调
    this.subCallback = params.subCallback; //失去焦点回调
    //显示的内容
    this.content = params.content || '';

    //家猫弹窗    
    this.winBody;
    this.winHead = $('<div class="jm_win_head" jm_winid="' + this.id() + '"></div>');
    this.winTitle = $('<span class="jm_win_title" jm_winid="' + this.id() + '"></span>');
    this.winBottom = $('<div class="jm_win_bottom" jm_winid="' + this.id() + '"></div>');
    //窗口遮板
    if (params.iframe) {
        this.bodyModel = $('<div class="jm_win_body_model" jm_winid="' + this.id() + '"></div>');
    }
    this.win = $('<div class="jm_win" id="' + this.id() + '"></div>');

    this.bodyParent = null;
    this.parent = params.parent ? $(params.parent) : $jm.os.body.element;
    this.fullDiv = $('<div class="jm_win_full_div"></div>');

    this._zindex = $jm.os.config.appMinZIndex;
    //当前窗口的层叠顺序
    this.zindex = function (index) {
        if (index) {
            this.win.css('z-index', index + '');
            this._zindex = index;
        }
        else {
            return this._zindex;
        }
    };

    this.__actived = false;
    //激活
    this.actived = function (v) {
        if (v == true || v == false) {
            this.__actived = v;
            this.__showModelDiv(!v);
        }
        return this.__actived;
    }

    //显示和隐藏遮板
    this.__showModelDiv = function (v) {
        if (this.bodyModel) {
            if (v == true) {
                this.bodyModel.show();
            }
            else {
                this.bodyModel.hide()
            }
        }
    }

    //标题
    this.title = function (t) {
        if (typeof t != 'undefined') {
            __title = t;
            this.winTitle.html(t);
        }
        return __title;
    }

    //当前窗口的宽
    this.width = function (w) {
        if (!$jm.isNull(w)) {
            this.win.width(w);
            w = this.win.width();
            this.winBody.width(w - 4);
            this.resize();
        }
        else {
            return this.win.width();
        }
    }
    //当前窗口的高
    this.height = function (h) {
        if (!$jm.isNull(h)) {
            this.win.height(h);
            h = this.win.height();
            this.winBody.height(h - headheight - 6); //设置里面元素新高度
            this.resize();
        }
        else {
            return this.win.height();
        }
    }

    //大小改变
    this.resize = function () {
        if (this.resizeCallback) this.resizeCallback();
    }

    //左坐标
    this.left = function (l) {
        if (!$jm.isNull(l)) {
            //l = l < 0 ? 0 : l;
            this.win.css('left', l);
        }
        else
            return this.win.position().left;
    }
    //顶坐标
    this.top = function (t) {
        if (!$jm.isNull(t)) {
            // t = t < 0 ? 0 : t;
            this.win.css('top', t);
        }
        else
            return this.win.position().top;
    }

    this.__visible = false;
    //当前可见状态
    this.visible = function (v) {
        if (this.__visible && v == false) {
            this.__visible = false;
            this.sub();
            this.hide();
        }
        else if (!this.__visible && v == true) {
            this.win.show();
            this.changeState(this.__oldState); //恢复大小
            this.__visible = true;
        }
        else if (v == true && this.winState == $jm.winState.min) {
            this.changeState(this.__oldState); //恢复大小
            this.__visible = true;
        }
        return this.__visible;
    }

    //初始化按钮
    this.__initButtons = function (par) {
        if (!par) return;
        //窗口按钮初始化        
        var btn = $('<input type="button" class="' +
        (par.className ? par.className : 'jm_win_button') + '" value="' + par.text + '" />');

        //点击是按钮
        if (par.click) btn.click(function () {
            par.click();
        });

        btn.appendTo(this.winBottom);
    }
    //初始化主体窗口
    this.__initBody = function () {
        //窗口   
        //如果是加载外部窗口
        if (!$jm.isNull(body) && body != '') {
            this.winBody = body;
            if (this.winBody.css('display') == 'none') this.winBody.css('display', '');
            this.bodyParent = this.winBody[0].parentElement;
        } else {
            this.winBody = $('<div class="jm_win_body"></div>');
            this.winBody.parent = null;
        }
        if (style && style != '') this.winBody.attr('class', style);

        if (this.title != '') {
            var ico = $('<img src="' + this.params.ico + '" class="jm_win_ico"/>');
            ico.appendTo(this.winHead);
            this.winHead.css('height', headheight + 'px');

            this.title(this.title()); //设置标题
            this.winTitle.appendTo(this.winHead); //加入标题

            //功能区域
            //var cmdArea = $('<div class="jm_win_cmdarea"></div>');
            //添加关闭按钮
            var closebtn = $("<a class='cmdbtn close' onclick='javascript:$jm.closeWinById(\"" + this.id() + "\")' href='javascript:;'>X</a>");
            closebtn.appendTo(this.winHead);

            if (this.resizeable) {
                //最大化
                var maxbtn = $("<a class='cmdbtn max' onclick='javascript:$jm.getWinById(\"" + this.id() + "\").changeState();' href='javascript:;'>口</a>");
                maxbtn.appendTo(this.winHead);
            }

            //最小化
            var minbtn = $('<a class="cmdbtn min" onclick="javascript:$jm.getWinById(\'' + this.id() + '\').min();">一</a>');
            minbtn.appendTo(this.winHead);
            //cmdArea.appendTo(this.winHead);
            this.winHead.appendTo(this.win);
        }

        this.winBody.appendTo(this.win); //加入主体到窗口中

        this.winBody.html('<div class="jm_wait"></div>'); //显示等待

        this.win.css('left', left).css('top', top);
    }

    this.__initBody(); //初始化主体窗口

    //加载窗体内容
    this.loadContent = function () {
        this.winBody.html('');

        //如果应用为目录
        if (!$jm.isNull(this.content)) {
            if (this.content != '' && !this.params.folder) {
                this.winBody.html(this.content);
                //return;
            }
            else if (this.params.folder) {
                var app = $jm.os.getAppByHandle(this.params.handle);
                if (app && app.cleaLink) app.cleaLink(); //链接归0
                //为目录添加应用链接
                for (var p in this.params.content) {
                    var par = this.params.content[p];
                    if (typeof par == 'string') {
                        var app = $jm.os.getApp(par);
                        if (app) par = app.params; //得到参数
                        else continue;
                    }
                    par.container = this.winBody;
                    $jm.os.installApp(par); //添加应用到系统中
                    //添加快捷方式
                    $jm.os.addLinkItem(par.handle, this.params.handle);
                }
                //大小改变回调
                this.resizeCallback = function () {
                    var app = $jm.os.getAppByHandle(this.params.handle);
                    if (app)
                        app.positionLinks(); //重新定位快捷方式
                }
                //return;
            }
        }
        //如果为外链接
        if (!$jm.isNull(this.params.url)) {
            //如果是用帧显示
            if (this.params.iframe) {
                var fm = $('<iframe frameborder="0" width="100%" height="100%"></iframe>');
                fm.attr('src', this.params.url);
                //fm.bind('mousedown', function () { alert(1); });
                this.winBody.html('');
                fm.appendTo(this.winBody);
            }
            else {//否则加载内容
                var winid = this.id(); //当前窗体的ID
                $jm.load(this.params.url, function (html) {
                    var win = $jm.getWinById(winid); //得到窗体
                    if (win) {
                        win.content = html;
                        win.winBody.html(html);
                    }
                });
            }
        }

        //加入遮板
        if (this.bodyModel) this.bodyModel.appendTo(this.winBody);
    }

    //窗体手标按下事件
    this.__winmousedown = function (evt) {
        var winobj = $jm.getWinById(this.id || evt.id);
        if (winobj) {
            winobj.focus(); //获得焦点
        }
    };

    //标题栏双击事件
    this.__headdblclick = function () {
        var winid = $(this).attr('jm_winid');
        var win = $jm.getWinById(winid);
        if (win) {
            win.changeState();
        }
    }

    //显示窗口
    this.show = function (callback) {
        //如果加载回调返回false.则直接返回
        if (this.params.loading && !this.params.loading(this.id())) {
            return false;
        }

        if (this.visible()) {
            this.focus();
            return;
        }
        //this.close();
        //加入到集合中
        var wins = $jm.cache.get('jm_win_container'); //从缓存中获取窗体
        if (!wins) { wins = []; $jm.cache.set('jm_win_container', wins); }
        wins.push(this);

        //模式窗体
        if (this.modal) {
            this.fullDiv.appendTo(this.parent);
        }
        this.win.appendTo(this.parent);
        //添加按钮
        if (params.button) {
            this.winBottom.html('');
            for (var i in params.button)
                this.__initButtons(params.button[i]);

            this.winBottom.appendTo(this.win);
        }
        //如果归中
        if (params.position == 'center') $jm.center(this.win, this.parent);
        this.width(width);
        this.height(height);

        //保存原大小
        this.__oldSize = {w:width,h:height};

        this.win.unbind('mousedown', this.__winmousedown);
        this.win.bind('mousedown', this.__winmousedown);

        //注册移动事件
        var jmmvdrag = new $jm.objMove();
        jmmvdrag.Register(this);

        //如果可以改变大小
        if (this.resizeable) {
            var jmmddrag = new $jm.objResize();
            jmmddrag.Register(this); //注册大小改变对象

            //双击标题.最大化
            this.winHead.unbind('dblclick', this.__headdblclick);
            this.winHead.bind('dblclick', this.__headdblclick);
        }
        else {//改变指针
            this.win.css('cursor', 'default');
        }

        if (this.title != '') {
            //绑定标题栏菜单
            var headmenu = new $jm.menu(this.winHead,
            [
                {
                    text: '最大化',
                    tag: this.id(),
                    disabled: !this.resizeable, //是否可最大化
                    click: function () {
                        var winid = $(this).attr('tag');
                        var win = $jm.getWinById(winid);
                        if (win) win.max();
                    }
                },
                {
                    text: '最小化',
                    tag: this.id(),
                    click: function () {
                        var winid = $(this).attr('tag');
                        var win = $jm.getWinById(winid);
                        if (win) win.min();
                    }
                },
                {
                    text: '关闭', tag: this.id(), click: function () {
                        var winid = $(this).attr('tag');
                        $jm.closeWinById(winid); //关闭
                    }
                }
            ]);
        }

        this.zindex(this.zindex()); //先设置其层级

        //置顶
        this.focus();

        //状态为可见
        this.__visible = true;

        //if ($jm.isNull(this.content) || this.content == '') {
        //通过地址加载内容
        this.loadContent();
        //}

        //调用回调
        if (callback) callback();

        this.saveState(); //保存初始状态

        //如果已最大化启动
        if (this.winState == $jm.winState.max) {
            setTimeout('var win = $jm.getWinById("' + this.id() + '");if (win)win.max();', 500); //最大化
        }
    }

    //改变最大化状态
    this.changeState = function (state) {
        //if (!this.resizeable) return;
        //如果指定要改变到某状态..否则对其进行反转
        if (state == $jm.winState.normal ||
        ($jm.isNull(state) && this.winState == $jm.winState.max))
            this.normal(); //恢复正常大小
        else if (state == $jm.winState.max ||
        ($jm.isNull(state) && this.winState == $jm.winState.normal))
            this.max(); //最大化
        else if (state == $jm.winState.min)
            this.min(); //最小化
    }

    //隐藏
    this.hide = function () {
        this.win.hide();
    }

    //保存当前状态大小
    this.saveState = function () {
        if (this.winState == $jm.winState.min) return;

        if (this.winState != $jm.winState.max) {
            //原大小
            this.__oldSize = { w: this.width(), h: this.height() };
            //原位置
            this.__oldPosition = { x: this.left(), y: this.top() };
        }
        this.__oldState = this.winState;
    }

    //最小化
    this.min = function () {
        this.saveState(); //保存当前状态
        var winid = this.id();
        this.win.animate({ left: 0, top: 0, width: 0, height: 0 }, 500, function () {
            var win = $jm.getWinById(winid);
            //win.left(-1000);
            win.top(-1000);
            win.sub();
            var topwin = $jm.get_top_win(); //获取顶层窗口
            if (topwin) { topwin.focus(); }
        });

        this.winState = $jm.winState.min;
        //        this.__visible = false;

        //        this.top(-10000);
        //        this.sub();
        //        var topwin = $jm.get_top_win(); //获取顶层窗口
        //        if (topwin) { topwin.focus(); }
    }

    //最大化
    this.max = function () {
        //如果已经为最大化,则不处理
        if (!this.resizeable) return;

        this.saveState(); //保存当前状态

        this.winState = $jm.winState.max;


        var w = this.parent.width() - 10,
        h = this.parent.height() - 10;

        //        var winid = this.id();
        //        this.win.animate({ left: 0, top: 0, width: w, height: h }, function () {
        //            var win = $jm.getWinById(winid);
        //            win.width(w); win.height(h);
        //        });
        //设置位置为顶上
        this.left(0);
        this.top(0);

        this.width(w);
        this.height(h);
    }

    //恢复正常大小
    this.normal = function () {
        //如果已经是正常状态则返回
        //if (this.winState == $jm.winState.normal) return;

        this.winState = $jm.winState.normal;

        //        var winid = this.id();
        //        var w = this.__oldSize.w;
        //        var h = this.__oldSize.h;

        //        this.left(0);
        //        this.top(0);
        //        this.win.animate({ left: this.__oldPosition.x, top: this.__oldPosition.y, width: w, height: h }, function () {
        //            var win = $jm.getWinById(winid);
        //            win.width(w); win.height(h);
        //        });

        this.width(this.__oldSize.w);
        this.height(this.__oldSize.h);
        this.left(this.__oldPosition.x);
        this.top(this.__oldPosition.y);
    }

    //获得焦点
    this.focus = function () {
        //如果已激活则直接返回
        if (this.actived() == true) return;
        this.actived(true);

        var topwin = $jm.get_top_win(); //获取顶层窗口
        if (topwin) {

            //如果它比当前顶层小.则设置它大于顶层
            if (topwin.id() != this.id()) {
                var maxindex = topwin.zindex();
                if (this.zindex() <= maxindex) {
                    if (this.modal) {
                        this.fullDiv.css('z-index', maxindex + 1);
                        this.zindex(maxindex + 2);
                    }
                    else
                        this.zindex(maxindex + 1);
                }
                topwin.sub();
            }
        }
        //遮层底于当前窗口一层
        if (this.modal) this.fullDiv.css('z-index', this.zindex() - 1);
        this.win.removeClass('jm_win_sub'); //高度当前窗口

        if (this.focusCallback) this.focusCallback(this.params.handle); //回调

        this.visible(true); //显示出来
    }
    //失去焦点
    this.sub = function () {
        //如果本来就未激活则直接返回
        if (this.actived() == false) return;

        //去除样式灰度       
        this.win.addClass('jm_win_sub');
        this.actived(false);
        if (this.subCallback) this.subCallback(this.params.handle); //回调       
    }
    //关闭
    this.close = function (callback) {
        if (this.params.closing && this.params.closing() == false) return false;
        if (this.bodyParent) {
            this.winBody.css('display', 'none');
            this.winBody.appendTo(this.bodyParent);
            this.bodyParent = null;
        }
        this.fullDiv.remove();
        this.win.remove();
        $jm._removewin(this.id());
        var topwin = $jm.get_top_win(); //获取顶层窗口
        if (topwin) topwin.focus(); //激活最上层的窗口
        //状态为不可见
        this.__visible = false;

        this.actived(false);

        //调用回调
        if (this.closeCallback) {
            this.closeCallback(this.params.handle);
        }

        if (callback) callback(this.params.handle);
    }

    //原大小
    this.__oldSize = { w: this.width(), h: this.height() };
    //原位置
    this.__oldPosition = { x: this.left(), y: this.top() };
}

//对象移动插件
$jm.objMove = function () {
    //拖拽对象
    var _win;
    //拖动状态
    var _flag = false;
    //拖拽对象的当前位置
    var _objCurrentLocation;
    //鼠标最后位置
    var _mouseLastLocation;
    //鼠标按下
    var _mdHandler = function (evt) {
        //不在最大化状态下可以移动
        if ((evt.button == 0 || evt.button == 1) && _win && _win.winState != $jm.winState.max) {
            //显示遮板
            _win.__showModelDiv(true);

            evt = evt || window.event;
            //标记
            _flag = true;

            //拖拽对象位置初始化
            _objCurrentLocation = {
                x: _win.win.position().left, //.offset()
                y: _win.win.position().top
            };

            //鼠标最后位置初始化
            _mouseLastLocation = $jm.getMouseLocation(evt);

            //解决鼠标离开时事件丢失问题
            //注册事件(鼠标移动)
            $(document).unbind("mousemove", _mmHandler);
            $(document).bind("mousemove", _mmHandler);
            //$(document).bind("touchmove", _mmHandler);
            //注册事件(鼠标松开)
            $(document).unbind("mouseup", _muHandler);
            $(document).bind("mouseup", _muHandler);

            //取消事件的默认动作
            if (evt.preventDefault)
                evt.preventDefault();
            else
                evt.returnValue = false;
        }
    };

    //鼠标移动
    var _mmHandler = function (evt) {
        if (_flag) {
            evt = evt || window.event;
            //当前鼠标的x,y座标
            var _mouseCurrentLocation = $jm.getMouseLocation(evt);

            //拖拽对象座标更新(变量)
            _objCurrentLocation.x = _objCurrentLocation.x + (_mouseCurrentLocation.x - _mouseLastLocation.x);
            _objCurrentLocation.y = _objCurrentLocation.y + (_mouseCurrentLocation.y - _mouseLastLocation.y);

            //将鼠标最后位置赋值为当前位置
            _mouseLastLocation = _mouseCurrentLocation;

            //拖拽对象座标更新(位置)//并保证不出界
            if (_objCurrentLocation.x > 1)
                _win.win.css("left", _objCurrentLocation.x + "px");
            if (_objCurrentLocation.y > 1)
                _win.win.css("top", _objCurrentLocation.y + "px");
        }
    };

    //鼠标松开
    var _muHandler = function (evt) {
        if (_flag) {
            evt = evt || window.event;
            //注销鼠标事件
            _cleanHandlers();
            //标记
            _flag = false;
        }
    };

    //注销鼠标事件(mousemove mouseup)
    var _cleanHandlers = function () {
        if (_win) {
            $(document).unbind("mousemove", _mmHandler);
            //$(document).unbind("touchmove");
            $(document).unbind("mouseup", _muHandler);

            //隐藏遮板
            _win.__showModelDiv(false);
        }
    };
    //注册拖拽(参数为dom对象)
    this.Register = function (win) {
        //赋值
        _win = win;
        //注册事件(鼠标按下)
        _win.winHead.unbind("mousedown", _mdHandler);
        _win.winHead.bind("mousedown", _mdHandler);
    }
};
//对象大小修改事件
$jm.objResize = function () {
    var _win; //对象   
    var _flag = 0; //拖拉状态0=否，1=右;2=下;3表示右下
    var _curSize; //当前大小
    var _lastLocation; //最后位置
    var _resizeareawidth = 6; //可响应拉的宽度
    //鼠标按下
    var mdHandler = function (evt) {
        if (_win) {
            evt = evt || window.event;
            //拖拽对象位置初始化
            _curSize = {
                w: _win.width(),
                h: _win.height()
            };

            //鼠标最后位置初始化
            _lastLocation = $jm.getMouseLocation(evt);
            //标记
            var tmpflag = 0;
            if (_win.win.offset().top + _curSize.h < _lastLocation.y + _resizeareawidth) _flag = 2; //表示向下拉
            if (_win.win.offset().left + _curSize.w < _lastLocation.x + _resizeareawidth) tmpflag = 1; //向右拉

            if (_flag == 2 && tmpflag == 1) {
                _flag = 3; //表示为右下拉
                $(this).css('cursor', 'se-resize');
            }
            else if (tmpflag == 1) {
                _flag = tmpflag;
                $(this).css('cursor', 'e-resize');
            }
            else if (_flag == 2) {
                $(this).css('cursor', 's-resize');
            }
            else {
                $(this).css('cursor', 'default');
                return;
            }

            //显示遮板
            _win.__showModelDiv(true);

            //注册事件(鼠标移动)
            $(document).unbind("mousemove", mmHandler);
            $(document).bind("mousemove", mmHandler);
            //$(document).bind("touchmove", mmHandler);
            //_win.parent.bind("mousemove", mmHandler);
            //注册事件(鼠标松开)
            $(document).unbind("mouseup", muHandler);
            $(document).bind("mouseup", muHandler);
            //_win.parent.bind("mouseup", muHandler);

            //取消事件的默认动作
            if (evt.preventDefault)
                evt.preventDefault();
            else
                evt.returnValue = false;
        }
    };

    //鼠标移动
    var mmHandler = function (evt) {
        if (_flag != 0) {
            evt = evt || window.event;
            //当前鼠标的x,y座标
            var _mouseCurrentLocation = $jm.getMouseLocation(evt);
            //拖拽对象座标更新(变量)
            _curSize.w = _curSize.w + (_mouseCurrentLocation.x - _lastLocation.x);
            _curSize.h = _curSize.h + (_mouseCurrentLocation.y - _lastLocation.y);

            //将鼠标最后位置赋值为当前位置
            _lastLocation = _mouseCurrentLocation;

            //更新对象大小
            if (_flag == 1 || _flag == 3) _win.width(_curSize.w);
            if (_flag == 2 || _flag == 3) _win.height(_curSize.h);

            //取消事件的默认动作
            if (evt.preventDefault)
                evt.preventDefault();
            else
                evt.returnValue = false;
        }
    };

    //鼠标松开
    var muHandler = function (evt) {
        if (_flag != 0) {
            evt = evt || window.event;
            //注销鼠标事件(mousemove mouseup)
            cleanMouseHandlers();
            //标记
            _flag = 0;
            //隐藏遮板
            _win.__showModelDiv(false);
        }
    };

    //注销鼠标事件(mousemove mouseup)
    var cleanMouseHandlers = function () {
        if (_win) {
            _win.win.css('cursor', 'default');
            $(document).unbind("mousemove", mmHandler);
            //$(document).unbind("touchmove");
            $(document).unbind("mouseup", muHandler);
        }
    };
    //注册拖拽(参数为dom对象)
    this.Register = function (win) {
        //赋值
        _win = win;
        //注册事件(鼠标按下)
        _win.win.unbind("mousedown", mdHandler);
        _win.win.bind("mousedown", mdHandler);
    }
};

//窗体按钮
$jm.buttons = { OK: 1, YesOrNo: 2 };
//消息框
$jm.msgbox = function (pars) {
    var msg = pars.content;
    var title = pars.title || msg;
    var button = [];
    var _box;
    if (pars.button == $jm.buttons.YesOrNo) {
        button.push({
            text: pars.oktext || '是',
            click: function () {
                if (pars.ok) pars.ok();
                _box.close();
            }
        });
        button.push({
            text: pars.notext || '否',
            click: function () {
                if (pars.no) pars.no();
                _box.close();
            }
        });
    }
    else {
        button.push({
            text: pars.oktext || '确定',
            click: pars.ok
        });
    }
    _box = new $jm.win({ title: title,
        modal: true,
        content: msg,
        button: button,
        position: 'center'
    });
    //弹出
    this.show = function () { _box.show(); };
} 
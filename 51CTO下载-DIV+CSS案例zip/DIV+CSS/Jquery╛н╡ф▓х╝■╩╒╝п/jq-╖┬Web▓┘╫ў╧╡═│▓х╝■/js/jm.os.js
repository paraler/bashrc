//============================================
//基础服务
//============================================
// Download by http://www.codefans.net

//系统对象
//为一个单例
$jm.os = new (function () {
    //桌面
    this.body;
    //状态栏
    this.statusTool;
    //桌面菜单
    this.bodyMenu;

    //系统配置
    this.config = {
        skin: 'default', //当前皮肤

        //桌面配置
        desktop: {
            itemSize: { w: 60, h: 80 }, //图标大小

            desItems: [], //桌面快捷方式集
            itemIndex: 0, //快捷方式索引
            backGroundUrl: 'css/default/images/wallpaper.jpg', //背景图url

            //通过索引获取快捷方式
            getItemByIndex: function (index) {
                var len = $jm.os.config.desktop.desItems.length;
                for (var i = 0; i < len; i++) {
                    if ($jm.os.config.desktop.desItems[i].index == index) {
                        return $jm.os.config.desktop.desItems[i];
                    }
                }
            },
            //重新定位桌面快捷方式
            position: function (w, h) {
                var len = $jm.os.config.desktop.desItems.length;
                for (var i = 0; i < len; i++) {
                    $jm.os.config.desktop.desItems[i].position(w, h);
                }
            }
        },

        appMinZIndex: 100, //应用最小层叠
        winMinZIndex:1000,//窗口最小层叠
        handleIndex: 0, //应用程序句柄索引
        appLinks: [], //初始化应用连接
        apps: [] //系统中的应用集
    };

    //应用项
    var appItem = function (pars) {
        $jm.os.config.handleIndex += 1;
        //设置句柄
        pars.handle = this.handle = $jm.os.config.handleIndex;
        pars.id = this.id = pars.id || 'jm_app_' + this.handle;
        this.name = pars.name || pars.title;
        this.parent = pars.parent ? (parent.element || pars.parent) : $jm.os.body;
        this.ico = pars.ico || 'css/' + $jm.os.config.skin + '/images/' + (pars.folder ? 'Folder.png' : 'ico.png'); //默认图标
        pars.ico = this.ico;
        this.event = pars.ev;
        this.params = pars; //记录参数
        this.element = pars.element;
        this.jmapp = true; //表示为应用  

        //下面二个属性只有在目录情况下才有效
        this.linkIndex = 0; //里面链接过索
        this.links = []; //所有链接

        //初始化链接
        this.cleaLink = function () {
            this.linkIndex = 0;
            //this.links = [];
        }

        //添加链接
        this.addLink = function (link) {
            this.links.push(link);
        }

        //重新排列快捷方式
        this.positionLinks = function () {
            for (var l in this.links) {
                this.links[l].position();
            }
        }

        ///设置所有链接选择状态
        this.selectedAllLink = function (s) {
            for (var l in this.links) {
                this.links[l].selected(s);
            }
        }

        ///查找关联的链接
        this.getLinkByHandle = function (handle) {
            for (var l in this.links) {
                if (this.links[l].link == handle) return this.links[l];
            }
        }

        if (!pars.sys) {
            pars.focusCallback = $jm.os.appFocusCallback; //设置回调
            pars.subCallback = $jm.os.appSubCallback;
            pars.closeCallback = $jm.os.appCloseCallback;
        }

        this.__showed = false;

        if (!pars.sys) {//非系统应用
            this.taskItem = new taskItem(this); //添加到任务栏
        }

        this.show = function () {
            if (!this.element) this.element = new $jm.win(pars); //生成窗口
            if (this.element.appendTo) this.element.appendTo(this.parent.element ? this.parent.element : this.parent);
            this.element.show();

            this.__showed = true; //标识已显示

            if (this.taskItem) {
                this.taskItem.show(); //显示到任务栏
            }
        };

        //应用激 活
        this.active = function () {
            if (this.element.visible) {
                this.element.visible(true);
                this.element.focus();
            }
        }

        //隐藏
        this.hide = function () { this.element.hide(); this.__showed = false; };
    }

    //应用获得焦点回调
    this.appFocusCallback = function (handle) {
        var app = $jm.os.getAppByHandle(handle); //获得应用
        //任务栏显示焦点
        if (app && app.taskItem) {
            app.taskItem.focus();
        }
    }

    //应用失去焦点回调
    this.appSubCallback = function (handle) {
        var app = $jm.os.getAppByHandle(handle); //获得应用
        //任务栏失去焦点
        if (app && app.taskItem) {
            app.taskItem.sub();
        }
    }

    //应用关闭回调
    this.appCloseCallback = function (handle) {
        var app = $jm.os.getAppByHandle(handle); //获得应用
        //关闭任务
        if (app && app.taskItem) {
            app.taskItem.close();
        }
    }

    //选择所有桌面快捷方式
    this.selectedAllDesItems = function (s) {
        var len = $jm.os.config.desktop.desItems.length;
        for (var i = 0; i < len; i++) {
            var item = $jm.os.config.desktop.desItems[i];
            item.selected(s);
        }
    };

    /*桌面应用项
    */
    this.desItem = function (pars, container, index) {
        this.link = pars.handle; //与应用的关联
        this.index = $jm.isNull(index) ? $jm.os.config.desktop.itemIndex++ : index; //设定索引//从0开始
        this.parent = container || pars.container || $jm.os.body.element; //桌面载体
        this.isDes = this.parent == $jm.os.body.element; //是否为桌面快捷方式
        this.desbody = $('<div class="jmdesktopitem" jm_desindex="' + this.index + '"></div>');

        var __seleted = false;
        //是否被选择
        this.selected = function (s) {
            if (s == true) {
                //首先取消所有快捷方式的选择状态
                if (this.isDes) {
                    $jm.os.selectedAllDesItems(!s);
                }
                else {
                    var app = $jm.os.getAppByHandle(this.parentHandle); //获取父应用
                    if (app) {
                        app.selectedAllLink(!s);
                    }
                }
                this.desbody.addClass('jmdesktopitemfocus');
                __seleted = s;
            }
            //消选
            else if (s == false) {
                __seleted = s;
                this.desbody.removeClass('jmdesktopitemfocus');
            }
            return __seleted;
        };

        //关联的应用
        this.app = function () {
            return $jm.os.getAppByHandle(this.link); //获取应用
        }

        //设置快捷方式大小
        this.resize = function () {
            this.desbody.width($jm.os.config.desktop.itemSize.w);
            //this.desbody.height($jm.os.config.desktop.itemSize.h);
        }

        ///计算当前快捷方式的位置
        this.position = function (w, h) {
            var w = w || $jm.os.config.desktop.itemSize.w;
            var h = h || $jm.os.config.desktop.itemSize.h;

            var offsety = 8;
            h += offsety;

            //计算竖线内可以容纳多少个           
            var ycount = Math.floor((this.parent.height() - offsety) / h);
            ycount = ycount < 0 ? 0 : ycount;
            var xy = Math.floor(this.index / ycount);
            var curx = xy * w; //计算x的位置
            var cury = (this.index - (xy * ycount)) * h; //计算y的位置

            //设置当前位置
            this.desbody.css('top', cury + offsety);
            this.desbody.css('left', curx);

            return this.desbody.position();
        }


        var __showed = false;
        //显示快捷方式
        this.show = function () {
            if (__showed) return;
            var app = this.app(); //关联应用
            if (app) {
                var img = $('<img src="' + app.ico + '" border="0" alt="' + app.name + '" />');

                img.appendTo(this.desbody);
                var text = $('<span class="text"></span>');
                text.text(app.name); //设置名称
                text.appendTo(this.desbody);

                this.desbody.attr('title', app.name);
                this.desbody.attr('jm_link_parenthandle', this.parentHandle);
                this.desbody.attr('jm_app_handle', this.link); //关联链接
                //此为桌面链接
                this.desbody.attr('jm_des', this.isDes);


                //显示到桌面
                this.desbody.appendTo(this.parent);

                //快捷方式单击事件
                this.desbody.bind('click', function (ev) {
                    var obj = $(this);
                    var item;
                    var des = obj.attr('jm_des'); //是否为桌面快捷方式1
                    if (des.toLowerCase() == 'true') {
                        var itemindex = obj.attr('jm_desindex');
                        item = $jm.os.config.desktop.getItemByIndex(itemindex);
                    }
                    if (!item) {
                        var phandle = obj.attr('jm_link_parenthandle');
                        var handle = obj.attr('jm_app_handle');
                        var app = $jm.os.getAppByHandle(phandle); //获取父应用
                        if (app) item = app.getLinkByHandle(handle); //获取链接
                    }
                    if (item) {
                        var selected = item.selected(); //获取选取状态
                        if (selected)//如果已被选择..则直接打开此应用
                        {
                            item.app().show(); //打开关联的应用                            
                        }
                        item.selected(!selected); //反置选择
                    }
                });

                if ($.browser.msie && $.browser.version < '9') {
                    // 双击打开事件
                    this.desbody.dblclick(function (ev) {
                        var itemindex = $(this).attr('jm_desindex');
                        var item = $jm.os.config.desktop.getItemByIndex(itemindex);
                        if (item) {
                            item.app().show(); //打开关联的应用
                            item.selected(false); //消选
                        }
                    });
                }
                __showed = true;

                //设置大小
                this.resize();
                //设定其位置
                this.position();

            } //显示自已
        }
    }

    //增加快捷方式
    //链接到指定的容器中
    this.addLinkItem = function (handle, toHandle) {
        var app = this.getAppByHandle(handle);
        if (app) {
            var parent = this.getAppByHandle(toHandle); //获取目标应用\
            //所属容器
            var container = parent && parent.element && parent.element.winBody ? parent.element.winBody : null;
            var index = parent && !$jm.isNull(parent.linkIndex) ? parent.linkIndex++ : null;
            var item = new this.desItem(app, container, index);
            if (toHandle) item.parentHandle = toHandle;
            if (parent && parent.jmapp) {
                parent.addLink(item); //加到应用中
            }
            else {
                this.config.desktop.desItems.push(item);
            }
            item.show();
        }
    }

    //任务栏项
    var taskItem = function (app) {
        this.task = $('#jm_task_' + app.handle);
        if (this.task.length > 0) return;

        this.task = $('<div id="jm_task_' + app.handle + '" class="jmos_taskitem" ><div>');
        var taskbody = $('<div class="body"></div>')
        taskbody.appendTo(this.task);
        var img = $('<img src="' + app.ico + '" border="0" alt="' + app.name + '" />');
        img.appendTo(this.task);

        //是否已显示
        this.showed = false;

        this.task.attr('app', app.handle);
        this.task.attr('title', app.name);

        //任务单击事件
        this.taskClick = function () {
            var handle = $(this).attr('app');
            var app = $jm.os.getAppByHandle(handle); //通过句柄激活程序
            if (app) {
                //如果应用不是最小化..则把它最小化
                if (app.element && !$jm.isNull(app.element.winState)) {
                    if (app.element.winState != $jm.winState.min && app.element.actived()) {
                        app.element.min();
                        return;
                    }
                }
                //激活
                app.active();

            }
        }

        //显示
        this.show = function () {
            if (!this.showed) {
                this.task.appendTo($jm.os.statusTool.element); //加入到任务栏

                //绑定单击事件
                this.task.unbind('click', this.taskClick);
                this.task.bind('click', this.taskClick);
            }
            //已显示
            this.showed = true;
        }

        //任务栏获得焦点
        this.focus = function () {
            this.task.addClass('jmos_taskitemfocus');
        };

        //失去焦点
        this.sub = function () {
            this.task.removeClass('jmos_taskitemfocus')
        };

        //移除任务栏
        this.close = function () {
            this.task.remove();
            this.showed = false;
        };
    }

    //增加桌面菜单
    this.addBodyMenu = function (item) {
        this.bodyMenu.addItem(item);
    }

    //添加应用
    this.installApp = function (pars) {
        var name = pars.name || pars.title;
        //查找是否已存在名称相同的应用
        var apptmp = this.getAppByName(name);
        if (!$jm.isNull(apptmp)) {
            pars.handle = apptmp.handle;
            $jm.out('应用:' + name + ' 已存在,添加失败!');
            return;
        }

        var app = new appItem(pars);
        this.config.apps.push(app);

        //如果没有指定不显示快捷方式.则加入快捷方式到桌面
        if (pars.des == true) {
            this.addLinkItem(app.handle);
        }

        //如果要添加到桌面右健菜单中
        if (pars.bgMenu == true) {
            this.addBodyMenu({
                text: app.name,
                tag: app.handle, //唯一标识
                click: function () {
                    var handle = $(this).attr('tag');
                    $jm.os.runAppByHandle(handle);
                }
            });
        }
    }

    //获取APP,可以是ID或handle或名称
    this.getApp = function (f) {
        var len = this.config.apps.length;
        for (var i = 0; i < len; i++) {
            var app = this.config.apps[i];
            if (app.handle == f || app.id == f || app.name == f) return app;
        }
    }

    //通过关联获取应用
    this.getAppByHandle = function (handle) {
        var len = this.config.apps.length;
        for (var i = 0; i < len; i++) {
            if (this.config.apps[i].handle == handle) return this.config.apps[i];
        }
    }

    //通过关联获取应用
    this.getAppById = function (id) {
        var len = this.config.apps.length;
        for (var i = 0; i < len; i++) {
            if (this.config.apps[i].id == id) return this.config.apps[i];
        }
    }

    //通过名称获取已添加的应用
    this.getAppByName = function (n) {
        for (var p in this.config.apps) {
            if (this.config.apps[p].name == n) {
                return this.config.apps[p];
            }
        }
    }

    ///执行应用通过名称
    this.runAppByName = function (n) {
        var app = this.getAppByName(n); //获取应用
        if (app && app.show) app.show();
    }

    /*
    通过句柄运行程序
    */
    this.runAppByHandle = function (handle) {
        var app = this.getAppByHandle(handle); //获取应用
        if (app && app.show) app.show();
    }

    //激活应用
    this.activeAppByHandle = function (handle) {
        var app = this.getAppByHandle(handle); //获取应用
        if (app && app.active) app.active();
    }

    //设置桌面背景
    this.setBackgroudImg = function (url, callback) {
        if (url) this.config.desktop.backGroundUrl = url;

                var thiscallback = callback;
                $jm.loadImg(this.config.desktop.backGroundUrl, function () {
                    $('body').css('background', 'url("' + $jm.os.config.desktop.backGroundUrl + '") 0 0 repeat');
                    if (thiscallback) thiscallback();
                })

        //$('body').css('background-image', 'url("' + $jm.os.config.desktop.backGroundUrl + '")');
    }

    //加载皮肤
    this.setSkin = function (skin, callback) {
        if (skin) this.config.skin = skin;
        var csscallback = callback;
        $jm.loadCss('css/' + this.config.skin + '/desktop.css', 'cssdesktop', function () {
            $jm.loadCss('css/' + $jm.os.config.skin + '/Control.css', 'cssControl', csscallback);
        });
    }

    //初始化菜单
    this.initMenu = function () {
        //桌面右健菜单
        this.bodyMenu = new $jm.menu(this.body.element);
    }

    //窗口大小改变事件
    this.resizeHandler = function () {
        if (!$jm.isNull($jm.os.body.element))
            $jm.os.body.element.height($(window).height() - $jm.os.statusTool.element.height()); //重新调整主体大小  
        //重新定位桌面快捷方式
        var spw = 10; //彼此分隔10像素
        if (!$jm.isNull($jm.os.config.desktop))
            $jm.os.config.desktop.position($jm.os.config.desktop.itemSize.w + spw, $jm.os.config.desktop.itemSize.h + spw);
    };

    //加载桌面
    this.loadDesktop = function (callback) {
        //$('body').html(''); //清空页面

        //显示状态栏
        this.statusTool.show();

        //显示主体
        this.body.show();


        //显示桌面快捷方式
        var len = this.config.desktop.desItems.length;
        for (var i = 0; i < len; i++) {
            this.config.desktop.desItems[i].show();
        }

        //加入低浏览器警告
        if ($.browser.msie && $.browser.version < 9) {
            var tootipcontent = $('<div class="jm_win_tooltip" style="left:2px;top:2px;margin-top:4px;margin-right:10px;z-index:1;float:right;"></div>');
            tootipcontent.html("请使用火狐,谷歌,苹果,IE9及以上版本浏览器获得最佳效果");
            tootipcontent.appendTo(this.body.element);
        }

        //设置桌面背景 
        $jm.os.setBackgroudImg(null, callback);
    }

    //初始化应用
    this._initApp = function () {
        var index = 0;
        var linkapp = function () {
            var url = 'app/' + $jm.os.config.appLinks[index];
            //加载应用参数
            $jm.load(url + '/main.js', function (js) {
                try {
                    var apppars = eval(js);
                    for (var par in apppars) {
                        var pars = apppars[par];
                        if ($jm.isNull(pars.url)) pars.url = url + '/index.html';
                        $jm.os.installApp(pars); //加入到系统中
                    }
                }
                catch (e) {
                    $jm.out(e, 1);
                }
                finally {
                    index++;
                    linkapp()
                }
            });
        }
        //初始化所有应用
        linkapp();
    }

    //初始化数据
    this.init = function (callback) {
        //var thiscallback = callback;

        //绑定窗口大小改变事件
        $(window).resize(this.resizeHandler);
        var initcallback = function () {
            //系统桌面
            $jm.os.body = new appItem({ parent: $('body'), element: $('<div id="jm_os_bodyarea" class="jmos_body"></div>'), sys: true }); //系统级别的应用
            //状态栏
            $jm.os.statusTool = new appItem({ parent: $('body'), element: $('<div class="jmos_status"></div>'), sys: true }); //系统级别的应用

            $jm.os.initMenu(); //初始化菜单        

            //延迟加载应用
            //setTimeout($jm.os._initApp, 400);
            $jm.os._initApp();

            $jm.os.loadDesktop(callback);

            //if (callback) callback();            

            $jm.os.resizeHandler();
        };
        //this.setSkin('default', initcallback); //加载默认皮肤
        initcallback();
    }
})();

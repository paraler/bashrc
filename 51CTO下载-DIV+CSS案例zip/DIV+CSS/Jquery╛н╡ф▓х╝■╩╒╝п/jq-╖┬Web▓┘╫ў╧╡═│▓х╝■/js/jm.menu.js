// Download by http://www.codefans.net
//右键菜单
$jm.menu = function (obj, ms) {
    this._target = obj;
    this._menu = $('<div class="jm_menu"></div>');
    this.__body = $('<ul></ul>');
    this.__body.appendTo(this._menu);
    this.id;
    //所有菜单项
    this.items = {};

    //菜单项个数
    this.itemCount = function () {
        var i = 0; for (var k in this.items) { i++; } return i;
    };

    this.index = 0;
    //当前菜单项的索引
    this.__itemIndex = 0;

    var _eventHander = null;
    var _frameHandler = null;
    this.IContextMenuHander = null;
    var _backGround = $(document); //操作背景
    var _cancelfun = function () { return false; };
    //层叠
    this.zIndex = function (index) {
        if (!$jm.isNull(index)) {
            this._menu.css('z-index', index);
        }
        else return this._menu.css('z-index');
    }

    //弹出菜单
    this.show = function (mu, e) {
        //if (mu.itemCount() == 0) return;

        _eventHander = function (evt) {
            //evt.stopPropagation();
            mu.hide();
        };
        _backGround.bind('click', _eventHander);

        var position = $jm.getMouseLocation(e, $jm.os.body.element); //获取鼠标位置
        mu._menu.css('left', position.x);
        mu._menu.css('top', position.y);

        mu._menu.show();
    };
    //隐藏菜单
    this.hide = function () {
        _backGround.unbind('click', _eventHander);
        //var menu = _menucache(this.id);
        this._menu.hide();
        //_backGround.unbind('contextmenu', _cancelfun);
    };
    //菜单缓存
    var _menucache = function (menuid, mu) {
        if (menuid) {
            if (mu) $jm.cache.set('jm_menu_' + menuid, mu);
            else return $jm.cache.get('jm_menu_' + menuid);
        }
    }
    //菜单索引
    var _menuindex = function (index) {
        if (!$jm.isNull(index)) $jm.cache.set('jm_menu___index', index);
        else {
            index = $jm.cache.get('jm_menu___index');
            index = Number(index) > 0 ? index : 0;
            return index;
        }
    }

    ///添加菜单项
    this.addItem = function (item) {
        //得到当前菜单
        var menu = _menucache(this.id);
        //当前菜单项唯一标识
        this.__itemIndex++;
        var itemmark = 'jm_menuitem_' + this.index + '_' + this.__itemIndex;
        var mitem = $('<li jm_menuitem="' + itemmark + '" jm_menuid="' + this.id + '">' + item.text + '</li>');

        if (item.disabled) mitem.attr('disabled', 'disabled'); //禁用
        if (!$jm.isNull(item.tag)) mitem.attr('tag', item.tag);

        //缓存菜单项
        this.items[itemmark] = item;

        //绑定单击事件
        mitem.click(function (evt) {

            //evt.stopPropagation();
            var curmenuid = $(this).attr('jm_menuid');
            var curmenu = _menucache(curmenuid);

            var curitemmark = $(this).attr('jm_menuitem');
            var curitem = curmenu.items[curitemmark]; //获取菜单项
            if (curitem.disabled == true) return;
            if (curitem && curitem.click)
            { curitem.click(); }

            if (curmenu) curmenu.hide(); //关闭菜单
            return false;
        });

        mitem.appendTo(this.__body);
    }

    //初始化
    this.init = function () {
        this.index = _menuindex() + 1;
        _menuindex(this.index); //更新索引
        _backGround.bind('contextmenu', _cancelfun);

        this._target.bind('mousedown', function (obj) {
            if (obj.button == 2) //不是右健不理会
            {
                //首先禁用系统右健菜单
                //$(document).bind('contextmenu', _cancelfun);

                var target = $(obj.srcElement || obj.target);
                var menuid = target.attr('jm_menuid');
                var menu = _menucache(menuid); //从缓存中获取菜单
                if (menu)
                    menu.show(menu, obj); //弹出菜单
                //obj.stopPropagation();
            }
        });
        //生成其ID
        this.id = 'jm_menu_id_' + this.index;
        this._target.attr('jm_menuid', this.id); //把菜单ID写到需要弹出的母板上

        //添加菜单项
        if (ms) {
            for (var i in ms) {
                this.addItem(ms[i]);
            }
        }

        _menucache(this.id, this); //把菜单加到缓存中

        this._menu.appendTo($jm.os.body.element);
    };
    this.init();
}
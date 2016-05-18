//=======================
//家猫基础类库 2011.03.18
//=======================
//@params jquery参数
var $jm = {
debug:true,
    _hash: {}, //缓存队列
    //基础缓存
    cache: {
        //添加
        set: function (key, value) {
            $jm._hash[key] = value;
        },
        //获取
        get: function (key) {
            return $jm._hash[key];
        },
        //个数
        count: function () { var i = 0; for (var k in $jm._hash) { i++; } return i; },
        //移除
        remove: function (key) { delete $jm._hash[key]; },
        //检查是否包含
        contains: function (key) { return typeof ($jm._hash[key]) != "undefined"; }
    },
    //获取根路径
    rootUrl: '/',
    /*信息输出*/
    //消息打印类型
    msgType: {
        log: 0,
        error: 1,
        info: 2,
        warn: 3
    },
    //输出信息
    //@msg 消息
    //@t 消息类型 jm.msgType
    out: function (msg, t) {
        if (this.debug && window.console) {
            if (window.console.log && t == $jm.msgType.log) window.console.log(msg);
            else if (window.console.error && t == $jm.msgType.error) window.console.error(msg);
            else if (window.console.warn && t == $jm.msgType.warn) window.console.warn(msg);
            else if (window.console.info) window.console.info(msg); //默认info
        } 
    },
    //属性
    property: {
        version: '1.1',
        name: '家猫js库',
        copyRight: 'Copyright (c) 20011, jiamaocode.com, All rights reserved',
        debug: true
    }
};

//转为字符
$jm.toString = function () { return $jm.property.name + ' \n\nVersion:' + $jm.property.version + ' \n\n ' + $jm.property.copyRight; };
// Download by http://www.codefans.net
//判断是否为空对象
$jm.isNull = function (s) { return s==null || typeof s == 'undefined'; }




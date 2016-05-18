//加载脚本
$jm.load = function (url, callback) {
    $.ajax({
        url: url,
        type: "get",
        success: function (js) {            
            if (callback) callback(js); //调用回调
        }
    });
}
//动态加载样式
$jm.loadCss = function (url,mark, callback) {
    $.ajax({
        url: url,
        type: "get",
        success: function (css) {
            var style = mark ? $('#' + mark) : $('div[url="' + url + '"]');            
            if (!style || style.length == 0) {
                style = $('<div style="display:none;"></div>');
                if (mark) style.attr('id', mark);                
                style.attr('url', url);
                style.appendTo('body');
            }
            style.html('<style>' + css.replace(/~\//ig, $jm.rootUrl) + '</style>');
            if (callback) callback(); //调用回调
        }
    });
}
//动态加载图片
$jm.loadImg = function (url, callback) {
    var img = new Image();
    img.onload = callback;
    img.src = url;    
}
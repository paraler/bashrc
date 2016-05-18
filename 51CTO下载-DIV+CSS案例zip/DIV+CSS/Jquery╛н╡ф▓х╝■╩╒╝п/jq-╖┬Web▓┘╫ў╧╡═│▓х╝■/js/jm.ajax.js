///获取对象ajax
$jm.getAJAXHttp = function () {
    var xmlHttp;
    try {
        xmlHttp = new XMLHttpRequest();
    }
    catch (e) {
        try {
            xmlHttp = new ActiveXObject("Msxml2.XMLHTTP");
        }
        catch (e) {

            try {
                xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
            }
            catch (e) {
                alert("您的浏览器不支持AJAX！");
                return xmlHttp;
            }
        }
    }
    return xmlHttp;
}

//AJAX访问类型
$jm.ajaxDataType = {
    'xml': "application/x-www-form-urlencoded;",
    'json': "application/json; charset=utf-8"
}

//访问ajax对象
//@params 调用ajax参数
//格式:{url:'',type:'get/post',data:{a:1,b:2},datatype:'$jm.ajaxDataType',asyn:'true/false'}
$jm.ajax = function (params) {
    var ajx = this.getAJAXHttp(); //生成ajax对象
    if (!params.url) { $jm.out('参数url不可为空'); return; }
    params.type = params.type || 'get'; //默认get
    ajx.onreadystatechange = function () {
        if (ajx.readyState != 4) return;
        if (ajx.status && ajx.status == 200) {
            var txt = ajx.responseText;
            if (params.success) params.success(txt, ajx);
        }
        else {
            if (params.error) params.error(ajx);
        }
    }
    //如果是get方或则重新组合参数
    if (params.type == 'get' && params.data) {
        params.url = $jm.checkUrlParMark(params.url) + $jm.jsToUrl(params.data);
    }
    ajx.open(params.type, params.url, params.asyn || false);
    ajx.setRequestHeader("Content-Type", params.datatype || $jm.ajaxDataType.xml);
    ajx.send(params.data);
}


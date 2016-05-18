// Download by http://www.codefans.net
/// 列类型
var JM_ColumnType = {
    Text: 0,
    Link: 1,
    Checkbox: 2,
    Radiobox: 3,
    Combox: 4
};
//表格表头
var JM_TableHead = function (coltype, value) {
    //列类型
    this.ColType = coltype;
    //样式
    this.Style = '';
    //表头ＴＥＸＴ
    this.Value = value;
    //转为html
    this.toHtml = function () {
        switch (this.ColType) {
            case JM_ColumnType.Checkbox:
                {
                    return "<th class=\"jm-listTable-checkboxColumn\">" +
                            "<input type=\"checkbox\" onclick=\"$('#{tableid} input:checkbox').attr('checked', $(this).attr('checked'))\"/>" +
                        "</th>";
                }
            default:
                {
                    return "<th style='" + this.Style + "'><span>" + this.Value + "</span></th>";
                }
        }
    }
};

//表格单元格
var JM_TableCell = function (id, coltype, value, group) {
    //单元格类型
    this.ColType = coltype;
    this.Id = id;
    this.Style = '';
    this.cssName = '';
    //单元格值
    this.Value = value;
    //转为html
    this.toHtml = function () {
        switch (this.ColType) {
            case JM_ColumnType.Checkbox:
                {
                    return "<td class=\"jm-listTable-checkboxColumn " + this.cssName + "\">" +
                            "<input type=\"checkbox\" id=\"" + this.Id + "\" value=\"" + this.Value + "\" />" +
                        "</td>";
                }
            case JM_ColumnType.Radiobox:
                {
                    return "<td class=\"jm-listTable-checkboxColumn " + this.cssName + "\">" +
                            "<input type=\"radio\" id=\"" + this.Id + "\" value=\"" + this.Value + "\" name=\"jm_r_" + group + "\" />" +
                        "</td>";
                    break;
                }
            default:
                {
                    return "<td id=\"" + this.Id + "\" class='" + this.cssName + "' style='" + this.Style + "'>" + this.Value + "</td>";
                }
        }
    }
};
//表格行
var JM_TableRow = function () {
    //此行的单无格
    this.Cells = new Array();
    //样式
    this.cssName = '';
    //转为html
    this.toHtml = function () {
        var html = '<tr class="' + this.cssName + '">';
        for (var i = 0; i < this.Cells.length; i++) {
            html += this.Cells[i].toHtml();
        }
        html += "</tr>";
        return html;
    }
};
//表格
var JM_Table = function (id) {
    this.Id = id || "jm_table_" + Math.random();
    //表头
    this.Heads = new Array();
    //行
    this.Rows = new Array();
    this.cssName = '';
    //转为html
    this.toHtml = function () {
        var html = "<table id=\"{tableid}\" class=\"jm-listTable " + this.cssName + "\">";
        if (this.Heads != null && this.Heads.length > 0) {
            html += "<thead><tr>";
            for (var i = 0; i < this.Heads.length; i++) {
                html += this.Heads[i].toHtml();
            }
            html += "</tr></thead>";
        }
        if (this.Rows != null && this.Rows.length > 0) {
            html += "<tbody id=\"{tableid}_TableBody\">";
            for (var i = 0; i < this.Rows.length; i++) {
                html += this.Rows[i].toHtml();
            }
            html += "</tbody>";
        }
        html += "</table>";
        return html.replace(/\{tableid\}/ig, this.Id);
    }
    //获取所有选择的项
    this.GetAllSelected = function () {
        var seleds = $("#" + this.Id + "_TableBody input:[checked=true]");
        var ids = '';
        for (var i = 0; i < seleds.length; i++) {
            ids += seleds[i].value + ',';
        }
        return ids;
    }
};


//翻页插件
var jm_paging = function () {
    //判断是否在集合中
    this.containInList = function (p, list) {
        for (var i = 0; i < list.length; i++) {
            if (list[i] == p) return true;
        }
        return false;
    }
    this.ShowIndexCount = 10;
    this.pagingBody = $('<div class="jm_paging"></div>') //翻页div
    this.pageChange = function () { };
    //显示
    this.show = function (params) {
        this.pagingBody.html('');
        var index = parseInt(params.index) || 1; //当前页
        var count = parseInt(params.count) || 1; //总共多少页
        var preText = params.pretext || "上一页";
        var nexttext = params.nexttext || "下一页";
        var turnpagetext = params.turntext || "转到";

        //显示的页码
        var ShowPageList = new Array();
        ShowPageList.push(1); //加入第一页
        if (count > 1) ShowPageList.push(2); //加入第二页

        var showFirst = parseInt(index - this.ShowIndexCount / 2 + 1);
        var showLast = parseInt(index + this.ShowIndexCount / 2);
        if (showFirst < 0) showLast = showLast - showFirst;
        if (showLast > count) showLast = count;
        for (var i = showFirst; i < showLast; i++) {
            if (!this.containInList(i, ShowPageList) && i > 0) ShowPageList.push(i); //如果里面不存在则加入显示行列
        }

        if (count - 1 > 1 && !this.containInList(count - 1, ShowPageList)) ShowPageList.push(count - 1); //加上最后第二页
        if (count > 1 && !this.containInList(count, ShowPageList)) ShowPageList.push(count); //加上最后一页
        //写入上一页
        var preIndex = index > 1 ? index - 1 : 0;
        if (preIndex > 0) {
            var prelink = $('<a class="jm_PageIndexCSS" href="javascript:;" index="' + preIndex + '">' + preText + '</a>');
            prelink.bind('click', function () {
                if (params.pageChange) { params.pageChange($(this).attr('index')); } //页码改变事件
            });
            prelink.appendTo(this.pagingBody);
        }
        var showindex = 0;
        //显示页码
        for (var i = 0; i < ShowPageList.length; i++) {
            var pageindex = ShowPageList[i];
            //中间空档
            if (pageindex - showindex > 1) {
                var sp = $('<span>&nbsp;...&nbsp;</span>');
                sp.appendTo(this.pagingBody);
            }
            var alink = $('<a href="javascript:;" index="' + pageindex + '">' + pageindex + '</a>');
            alink.addClass(pageindex == index ? 'jm_PageCurIndexCSS' : 'jm_PageIndexCSS');
            if (pageindex == index) alink.addClass('jm_PageCurIndexCSS');
            else {
                alink.addClass('jm_PageIndexCSS');
                //页码改变事件             
                alink.bind('click', function () { if (params.pageChange) { params.pageChange($(this).attr('index')); } });
            }
            alink.appendTo(this.pagingBody);
            showindex = pageindex;
        }
        //写入下一页
        var nextIndex = index < count ? index + 1 : 0;
        if (nextIndex > 0) {
            var nextlink = $('<a class="jm_PageIndexCSS" href="javascript:;" index="' + nextIndex + '">' + nexttext + '</a>');
            nextlink.bind('click', function () {
                if (params.pageChange) { params.pageChange($(this).attr('index')); } //页码改变事件
            });
            nextlink.appendTo(this.pagingBody);
        }
        //转到第几页
        if (count > 1) {
            var spl = $('<span>&nbsp;&nbsp;' + turnpagetext + '</span>');
            spl.appendTo(this.pagingBody);
            var txt = $('<input type="text" name="jm_PagerTxt" maxlength="5" class="jm_PagerTxt" value="' + index + '" />');
            txt.bind('keypress', function () {
                var c = event.keyCode ? event.keyCode : event.which;
                if (c == 13)
                { if (params.pageChange && $.trim(this.value) != '') { params.pageChange(this.value); } }
                else if ((c <= 57 && c >= 48) || c == 8 || c == 9 || c == 0) {//9是opera中的tab健
                    return true;
                }
                return false;
            });
            txt.appendTo(this.pagingBody);
            var turnbtn = $('<a class="jm_PageIndexCSS" href="javascript:;">OK</a>');
            turnbtn.bind('click', function () { if (params.pageChange && $.trim(txt.val()) != '') { params.pageChange(txt.val()); } });
            turnbtn.appendTo(this.pagingBody);
        }
        if (params.parent) this.pagingBody.appendTo(params.parent);
        else this.pagingBody.appendTo('body');

        return this.pagingBody;
    }
}

//树型控件
//展开关闭节点
function jm_tree_expendorcloseitem(obj, chid, skin) {
    var ch = document.getElementById(chid);
    if (ch) {
        if (ch.style['display'] == 'none')
        { obj.className = 'jm_tree_sub jm_' + skin + '_tree_sub'; ch.style['display'] = ''; }
        else { obj.className = 'jm_tree_plus jm_' + skin + '_tree_plus'; ch.style['display'] = 'none'; }
    }
}
//生成节点对象
function createJM_TreeObject() {
    //节点对象
    return {
        parentid: "",
        innerHTML: "",
        children: new Array(),
        itemId: "",
        expend: true,
        selected: false,
        tooltip: ''
    };
}
//先择节点事件
function jm_item_select(obj) {
    var items = $('.jm_tree_selected');
    for (var i = 0; i < items.length; i++) {
        items[i].className = '';
    }
    if (obj) obj.className = 'jm_tree_selected';
}

//获取所有展开的节点
function jm_tree_getexpenditemids() {
    var expitems = $('.jm_tree_sub'); //所有展开的节点
    var ids = ',';
    for (var i = 0; i < expitems.length; i++) {
        ids += $(expitems[i]).attr('itemid') + ',';
    }
    return ids;
}

var JM_Tree = function (parent, items, skin) {
    this.Parent = parent;
    this.Items = items;
    this.treeHtml = '';
    this.Skin = skin || 'book'; //皮肤
    //递归生成节点
    this.createItem = function (item) {
        if (item) {
            this.treeHtml += '<div id="__' + item.itemId + '" class="jm_tree_item_container">';
            if (item.children && item.children.length > 0) {
                this.treeHtml += '<a href="javascript:;" itemid="' + item.itemId + '" class="' +
                (item.expend ? 'jm_tree_sub jm_' + this.Skin + '_tree_sub' : 'jm_tree_plus jm_' + this.Skin + '_tree_plus') +
                 '" onclick="javascript:jm_tree_expendorcloseitem(this,\'__' + item.itemId + '_children\',\'' + this.Skin + '\');return false;" >&nbsp;</a> ';
            }
            else {
                this.treeHtml += '<span class="jm_tree_item jm_' + this.Skin + '_tree_item">&nbsp;</span>';
            }
            this.treeHtml += '<span class="' + (item.selected ? 'jm_tree_selected' : '') + '">' + item.innerHTML + '</span>';
            this.treeHtml += '<br />';
            if (item.children && item.children.length > 0) {
                this.treeHtml += '<div id="__' + item.itemId + '_children" style="display:' + (item.expend ? '' : 'none') + ';"><table cellpadding="1" cellspacing="1">';
                for (var i = 0; i < item.children.length; i++) {
                    this.treeHtml += '<tr>  <td class="jm_tree_itemleftpad"> </td> <td>';
                    this.createItem(item.children[i]);
                    this.treeHtml += '</td></tr>';
                }
                this.treeHtml += '</table></div>';
            }
            this.treeHtml += '</div>';
        }
    }
    //生成树

    for (var i = 0; i < this.Items.length; i++) {
        this.createItem(this.Items[i]);
    }
    $(parent).html(this.treeHtml);
    return parent;
}





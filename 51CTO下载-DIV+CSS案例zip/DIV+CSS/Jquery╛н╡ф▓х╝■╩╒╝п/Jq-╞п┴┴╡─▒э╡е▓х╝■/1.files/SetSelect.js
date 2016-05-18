// JavaScript Document
// JS 改变Form中表单元素的选择

/**
* 全选的所有指定名称的checkbox
*@state　全选的checkbox的状态
*@name   表格中的所有checkbox的名称
*@author fangtf
*@type void
*/
function selectAll(state,name) {
    var ids = document.getElementsByName(name);
    for (var i = 0; i < ids.length; i++)
    {
            ids[i].checked = state;
    }
}

/**
* 全选的所有指定id名称的同名checkbox
*@state　全选的checkbox的状态
*@name   表格中的所有checkbox的名称
*@name   表格中的所有checkbox的id
*@author fangtf
*@type void
*/
function selectAllCheckboxByID(state,name,id) {
    var ids = document.getElementsByName(name);
    for (var i = 0; i < ids.length; i++)
    {
            if(ids[i].id == id)
            {
                ids[i].checked = state;
            }

    }
}

/**
* 全选页面上所有的checkbox
*@state　全选的checkbox的状态
*@author fangtf
*@type void
*/
function selectAlls(state)
{
    var inputs = document.getElementsByTagName("input");
    for(var i =0;i<inputs.length;i++)
    {
        if(inputs[i].type == "checkbox")
        {
            inputs[i].checked =state;
        }
    }
}

/**
*得到鼠标所单击的行
*@type Object
*/
function GetRow(oElem) {
    while (oElem) {
        if (oElem.tagName.toLowerCase() == "tr" && oElem.parentElement.tagName.toLowerCase() == "tbody") {
            return oElem;
        }
        if (oElem.tagName.toLowerCase() == "table" || oElem.tagName.toLowerCase() == "th") {
            return false;
        }
        oElemoElem = oElem.parentElement;
    }
}

/**
* 全选当前行的checkbox
*@state　全选的checkbox的状态
*@author fangtf
*@type void
*/
function selectRowCheckbox(state)
{
  var row = GetRow(window.event.srcElement);
  var cells = row.childNodes;
  for(var i=0;i<cells.length;i++)
  {
      var cell = cells[i].childNodes[0];
     if(cell.tagName == "INPUT")
     {
        cell.checked = state;
     }
  }
}

/**
*选中指定值的Radio
*如：有两个radio,
*第一个的name="ids",value="1"
*第二个的name="ids",value="２"
*调用方法selectRadio("ids","1");
*那么数值为１的Radio将被选中
*@name radio的名称
*@value radio的值
*@author fangtf
*@type void
*/
function selectRadio(name,value) {
    var radioObject = document.getElementsByName(name);
    if(value === "")
    {
        radioObject[0].checked = true;
        return;
    }
    for (var i = 0; i < radioObject.length; i++)
    {
        if(radioObject[i].value == value)
        {
            radioObject[i].checked = true;
            break;
        }

    }
}

/**
*选中指定值的checkbox
*如：有两个checkbox,
*第一个的name="ids",value="1"
*第二个的name="ids",value="２"
*第三个的name="ids",value="3"
*调用这个方法selectCheckbox("ids","1,2")那么数值为１，２的checkbox将被选中
*
*@name 要选中的checkbox数组的名称
*@value 判断时候选中的值
*@author fangtf
*@type void
*/
function selectCheckbox(name,value) {
    var checkObject = document.getElementsByName(name);
    var valuevalues = value.split(",");
    for(var j = 0; j < values.length; j++)
    {
        for (var i = 0; i < checkObject.length; i++)
        {
            if(checkObject[i].value == values[j])
            {
                checkObject[i].checked = true;
                break;
            }
        }
    }

}

/**
*选中指定值的select
*如：有一个名称为user的select
*<option value="0"></option>
*<option value="1"></option>
*调用这个方法selectOption("user","0")那么选项为0的选项就被选中
*
*@name  String  select的名称
*@value String  判断时候选中的值
*@author fangtf
*@type void
*/
function selectOption(name,value)
{
     document.getElementsByName(name)[0].value=value;
}
//绑定对象事件
//@em 元素对象
//@en 事件名
//@fu 事件
$jm.bindEvent = function (em, en, fu) {
    if (en && fu) {
        if (window.addEventListener) {
            em.addEventListener(en, fu, true);
        } else {
            em.attachEvent('on' + en, fu);
        }
    }
};

//元素
//@el document元素
$jm._jmelement = function (el) {
    if (!el) return "元素为空";
    return {
        em: el,
        isJmElement: true,
        parent: el.parentElement,
        isBody: el.tagName == 'BODY',
        //设置html
        html: function (html) {
            if (!$jm.isNull(html)) {
                if (!$jm.isNull(this.em.innerHTML))
                    this.em.innerHTML = html;
            }
            else
                return this.em.innerHTML;
        },
        //设置TEXT
        //@text 需要设置的字符
        text: function (text) {
            if (!$jm.isNull(this.em.text)) {
                if (!$jm.isNull(text)) this.em.text = text;
                else return this.em.text;
            }
            else if (!$jm.isNull(this.em.innerText)) {
                if (!$jm.isNull(text)) this.em.innerText = text;
                else return this.em.innerText;
            }
            else if (!$jm.isNull(this.em.textContent)) {
                if (!$jm.isNull(text)) this.em.textContent = text;
                else return this.em.textContent;
            }
        },
        //绑定事件
        //@en 事件名 :click,load
        //@fu 事件委托
        bind: function (en, fu) {
            $jm.bindEvent(this.em, en, fu);
        },
        //从其父容器中移除当前元素
        remove: function () {
            if (this.parent) {
                this.parent.removeChild(this.em);
            }
        },
        //把对象加入到容器
        appendTo: function (p) {
            var parent = $jm(p);
            parent.em.appendChild(this.em);
        },
        //设置元素的样式名
        //@cn 为样式名,如果不值则返回属性值
        cssName: function (cn) {
            if (!$jm.isNull(cn)) { this.em.className = cn; }
            else { return this.em.className; }
        },
        //设置style值
        //@cn style名
        //@v style对应的值,如果不值则返回属性值
        css: function (cn, v) {
            if (cn) {
                if (!$jm.isNull(v)) this.em.style[cn] = v;
                else return this.em.style[cn];
            }
        },
        //设置属性
        //@n 属性名
        //@v 属性值,,如果不值则返回属性值
        attr: function (n, v) {
            if (n)
                if (!$jm.isNull(v)) this.em.setAttribute(n, v);
                else return this.em.attributes[n];
        },
        width: function (w) {
            if (w || w == 0) {
                this.em.style.width = w;
            }
            else {
                if (this.isBody) { return $jm.getWinWidth(); }
                return this.em.offsetWidth;
            }
        },
        height: function (h) {
            if (h || h == 0) {
                this.em.style.height = h;
            }
            else {
                if (this.isBody) { return $jm.getWinHeight(); }
                return this.em.offsetHeight;
            }
        }
    };
}

//创建元素
//@TAG 元素标签
//@cs 元素的样式名
$jm.createEm = function (tag, cs, attrs) {
    var em = $jm(tag);
    if (cs) em.cssName(cs);
    if (attrs)//设置属性
    {
        for (var a in attrs) {
            em.attr(a, attrs[a]);
        }
    }
    return em;
};

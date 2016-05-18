var YBlocks = function(oConfig){
	var isFade = true, 
	isScrollTip = true, 
	blocksContainer = null,
	blocks = null,
	dataType = 'attribute',
	blocksData = [];
	
	this.setBlocksContainer = function(id){
		blocksContainer = YBlocks.get(id);
	};
	this.getBlocksContainer = function(){
		return blocksContainer;
	};
	//Download by http://www.codefans.net
	// 初始化设置（必选）
	this.setBlocksContainer(oConfig.blocksContainer);
	if (!blocksContainer) {
		return false;
	}
	
	this.setDataType = function(type){
		dataType = type;
	};
	this.getDataType = function(){
		return dataType;
	};
	
	this.setBlocksData = function(data){
		blocksData = data;
	};
	this.getBlocksData = function(){
		return blocksData;
	};
	
	this.setIsFade = function(fade){
		isFade = fade;
	};
	this.getIsFade = function(){
		return isFade;
	};
	
	this.setIsScrollTip = function(scroll){
		isScrollTip = scroll;
	};
	this.getIsScrollTip = function(){
		return isScrollTip;
	};
	
	this.setBlocks = function(oBlocks){
		blocks = oBlocks;
	};
	this.getBlocks = function(){
	    return 	blocksContainer.getElementsByTagName('li');
	};
	
	// 初始化设置（必选）
	this.setDataType(oConfig.dataType);
	// 初始化设置（可选）
	if (oConfig.isFade === false) {
		this.setIsFade(false);
	}
	if(oConfig.isScrollTip === false){
	    this.setIsScrollTip(false);
	}
	if (oConfig.data) {
		this.setBlocksData(oConfig.data);
	}
	
	return this;
};
	
YBlocks.get = function(el){
	if (!document.getElementById) {
		return false;
	}
	
	if (el.tagName && el.nodeType === 1) {
		return el;
	}
	else {
		return document.getElementById(el);
	}
};
YBlocks.isIE = window.ActiveXObject;
YBlocks.isString = function(str){
	return typeof str === 'string';
};
YBlocks.trim = function(str){
	try {
		return str.replace(/^\s+/, '').replace(/\s+$/, '');
	} 
	catch (e) {
		return str;
	}
};
YBlocks.stopEvent = function(evt){
	YBlocks.stopPropagation(evt);
	YBlocks.preventDefault(evt);
};
YBlocks.stopPropagation = function(evt){
	if (evt.stopPropagation) {
		evt.stopPropagation();
	}
	else {
		evt.cancelBubble = true;
	}
};
YBlocks.preventDefault = function(evt){
	if (evt.preventDefault) {
		evt.preventDefault();
	}
	else {
		evt.returnValue = false;
	}
};
YBlocks.setStyle = function(el, property, val){
	if (YBlocks.isIE) {
		switch (property) {
			case 'opacity':
				if (YBlocks.isString(el.style.filter)) {
					el.style.filter = 'alpha(opacity=' + val * 100 + ')';
					if (!el.currentStyle || !el.currentStyle.hasLayout) {
						el.style.zoom = 1;
					}
				}
				break;
			case 'float':
				property = 'styleFloat';
			default:
				el.style[property] = val;
		}
	}
	else {
		if (property === 'float') {
			property = 'cssFloat';
		}
		el.style[property] = val;
	}
};
YBlocks.hasClass = function(el, className){
	var ret = false, current;
	if (el && className) {
		current = YBlocks.getAttribute(el, 'className') || '';
		if (className.exec) {
			ret = className.test(current);
		}
		else {
			ret = className && (' ' + current + ' ').indexOf(' ' + className + ' ') > -1;
		}
	}
	else {
		throw new Error('hasClass called with invalid arguments');
	}
	return ret;
};
YBlocks.addClass = function(el, className){
	var ret = false, current;
	if (el && className) {
		current = YBlocks.getAttribute(el, 'className') || '';
		if (!YBlocks.hasClass(el, className)) {
			YBlocks.setAttribute(el, 'className', YBlocks.trim(current + ' ' + className));
			ret = true;
		}
	}
	else {
		throw new Error('addClass called with invalid arguments');
	}
	return ret;
};
YBlocks.setAttribute = function(el, attr, val){
	var CUSTOM_ATTRIBUTES = (!document.documentElement.hasAttribute) ? { // IE < 8
		'for': 'htmlFor',
		'class': 'className'
	} : { // w3c
		'htmlFor': 'for',
		'className': 'class'
	};
	attr = CUSTOM_ATTRIBUTES[attr] || attr;
	el.setAttribute(attr, val);
};
YBlocks.getAttribute = function(el, attr){
	var CUSTOM_ATTRIBUTES = (!document.documentElement.hasAttribute) ? { // IE < 8
		'for': 'htmlFor',
		'class': 'className'
	} : { // w3c
		'htmlFor': 'for',
		'className': 'class'
	};
	attr = CUSTOM_ATTRIBUTES[attr] || attr;
	return el.getAttribute(attr);
};
YBlocks.isMouseLeaveOrEnter = function(e, handler){
	if (e.type !== 'mouseout' && e.type !== 'mouseover') {
		return false;
	}
	var reltg = e.relatedTarget ? e.relatedTarget : (e.type === 'mouseout' ? e.toElement : e.fromElement);
	
	while (reltg && reltg !== handler) {
		reltg = reltg.parentNode;
	}
	return (reltg !== handler);
};
YBlocks.fade = function(elem, fadeType, min, max, speed, callback){
	var current = 0, fadeFn = null, setStyle = YBlocks.setStyle, spd = speed || 25;
	
	elem = YBlocks.get(elem);
	if (!elem) {
		return false;
	}
	
	// 透明度越来越高
	if (fadeType.toLowerCase() === 'up') {
		max = max || 1; // 最高透明度
		current = min || 0; // 当前透明度
		fadeFn = function(){
			var timer = null;
			current += 0.05; // 每次增加0.05的值 
			if (timer) {
				clearTimeout(timer);
				timer = null;
			}
			
			// 达到最高透明度（不透明），停止动画
			if (current > max) {
				setStyle(elem, 'opacity', max);
				// 如果设置了停止动画后的回调函数，则执行回调函数
				if (callback) {
					callback();
				}
				return false;
			}
			else {
				// 一直增加透明度
				setStyle(elem, 'opacity', current);
			}
			
			timer = setTimeout(fadeFn, spd);
		};
	}
	else {
		// 透明度越来越低
		if (fadeType.toLowerCase() === 'down') {
			min = min || 0;
			current = max || 1;
			
			fadeFn = function(){
				var timer = null;
				current -= 0.05;
				if (timer) {
					clearTimeout(timer);
					timer = null;
				}
				
				if (current < min) {
					setStyle(elem, 'opacity', min);
					if (callback) {
						callback();
					}
					return false;
				}
				else {
					setStyle(elem, 'opacity', current);
				}
				
				timer = setTimeout(fadeFn, spd);
			};
		}
	}
	
	fadeFn();
};
YBlocks.moveElement = function(element, finalX, finalY, speed, callback){
	var elem = YBlocks.get(element), style = null, xpos = 0, ypos = 0, ms = (speed || 50);
	
	if (!elem) {
		return false;
	}
	if (elem.movement) {
		clearTimeout(elem.movement);
		elem.movement = null;
	}
	
	if (!elem.style.left) {
		elem.style.left = '0';
	}
	
	if (!elem.style.top) {
		elem.style.top = '0';
	}
	
	xpos = parseInt(elem.style.left, 10);
	ypos = parseInt(elem.style.top, 10);
	
	if (xpos === finalX && ypos === finalY) {
		if(callback){
			callback();
		}
		return true;
	}
	
	if (xpos < finalX) {
		var dist = Math.ceil((finalX - xpos) / 10);
		xpos = xpos + dist;
	}
	
	if (xpos > finalX) {
		var dist = Math.ceil((xpos - finalX) / 10);
		xpos = xpos - dist;
	}
	
	if (ypos < finalY) {
		var dist = Math.ceil((finalY - ypos) / 10);
		ypos = ypos + dist;
	}
	
	if (ypos > finalY) {
		var dist = Math.ceil((ypos - finalY) / 10);
		ypos = ypos - dist;
		
	}
	
	elem.style.left = xpos + 'px';
	elem.style.top = ypos + 'px';
	
	elem.movement = setTimeout(function(){
		YBlocks.moveElement(element, finalX, finalY, ms, callback);
	}, speed);
};

YBlocks.prototype = {
	build: function(){
		var doc = document, dfgBlock = doc.createDocumentFragment(), blocksContainer = null, blocks = null, dataType = this.getDataType(), data = [], i = 0, len = 0, url = '', price = '', title = '', curBlock = null, curContent = null, curLink = null, curImage = null, curData = {}, tmpPlus = null, tmpMask = null, tmpHeader = null, tmpFooter = null, createBlock = function(blockClass){
			var block = doc.createElement('li');
			block.className = blockClass;
			return block;
		}, createHeader = function(url, title, price){
			var link = createLink(url, title), header = doc.createElement('h5');
			header.className = 'hd-block';
			// 补充了活动标题的创建，通过price参数来判断是否为活动
			// 有price值就是产品的样式，没有则是（添加）活动样式
			if(price == ''){
				YBlocks.addClass(header, 'list-bg');
			}
			header.appendChild(link);
			return header;
		}, createContent = function(url, title, price, img){
			var link = doc.createElement('a'), image = doc.createElement('img');
			link.rel = price;
			link.href = url;
			image.src = img;
			image.alt = title;
			link.appendChild(image);
			return link;
		}, createFooter = function(url, price){
			var footer = doc.createElement('p');
			footer.className = 'ft-block';
			footer.innerHTML = '<a href="' + url + '"><em>' + price + '<\/em><\/a>';
			return footer;
		}, createMask = function(url, title){
			var mask = doc.createElement('span'), link = createLink(url, title);
			mask.className = 'mask-block';
			mask.appendChild(link);
			return mask;
		}, createPlus = function(url, title){
			var plus = doc.createElement('span'), link = createLink(url, title);
			plus.className = 'plus-block';
			plus.appendChild(link);
			return plus;
		}, createLink = function(url, title){
			var link = doc.createElement('a');
			link.href = url;
			link.innerHTML = title;
			return link;
		};
		
		// 非mackup的数据类型才需要创建相关的组件
		if (dataType === 'mackup') {
			return this;
		}
		else {
			// 静态数据时，直接可以获得blocks的nodeList，并且可以获得nodeList长度
			if (dataType === 'attribute') {
				blocks = this.getBlocks();
				len = blocks.length;
			}
			else {
				// 动态数据时，需要获取动态的数据数组，从而获得数组长度
				if (dataType === 'dynamic') {
					data = this.getBlocksData()
					len = data.length;
				}
			}
		}
		
		for (; i < len; i += 1) {
			// 静态数据时，可以直接通过blocks的nodeList的索引值获得当前的curBlock的DOM对象
			if (dataType === 'attribute') {
				curBlock = blocks[i];
			}
			else {
				// 动态数据时，我们需要通过对应的动态数据的信息来创建对象curBlock的DOM对象
				if (dataType === 'dynamic') {
					curData = data[i];
					// 通过curData的信息，动态创建出跟静态数据一样的内容（一个图片链接），格式如：
					// 产品(有REL属性)
					// <a href="http://www.aliexpress.com/fm-store/405910/211006654-462073678/AK-Baseball-Label-Printed-Washer-Polo-tshirt-100-Cotton-Men-s-Casual-tshirt-Wholesale-Retail.html" rel="US $32.00">
					//     <img src="sample/brand-14.jpg" alt="AK Baseball Label Printed Washer Polo tshirt,100% Cotton ,Men's Casual tshirt,Wholesale/Retail" />
					// </a>
					// 活动
					// <a href="http://www.aliexpress.com/fm-store/405910/211006654-462073678/AK-Baseball-Label-Printed-Washer-Polo-tshirt-100-Cotton-Men-s-Casual-tshirt-Wholesale-Retail.html" rel="US $32.00">
					//     <img src="sample/brand-14.jpg" alt="AK Baseball Label Printed Washer Polo tshirt,100% Cotton ,Men's Casual tshirt,Wholesale/Retail" />
					// </a>
					curContent = createContent(curData.url, curData.title, curData.price || '', curData.img); // curData.price || ''，为空则为活动样式
					// 根据curData的信息创建curBlock的DOM对象
					curBlock = createBlock(curData.blockClass);
					// 把创建出来的内容信息添加到curBlock中
					curBlock.appendChild(curContent);
					// 将创建出来的curBlock添加到BlocksContainer节点中
					blocksContainer = this.getBlocksContainer();
					blocksContainer.appendChild(curBlock);
				}
			}
			
			// 根据已有（或动态创建）的图片链接，获取相关信息
			curLink = curBlock.getElementsByTagName('a')[0];
			curImage = curBlock.getElementsByTagName('img')[0];
			url = curLink.href; // 超链接的路径
			price = curLink.rel; // 商品的价格
			title = curImage.alt; // 图片介绍
			
			// 动态创建动画特效需要的DOM组件，格式如：
			// <h5 class="hd-block"><a href="http://www.aliexpress.com/category/3/apparel.html?ismall=y">GGMM Genuine Leather Cover Case iPad 2</a></h5>
			// <p class="ft-block"><a href="http://www.aliexpress.com/category/3/apparel.html?ismall=y"><em>US $120.00</em></a></p>
			// <span class="plus-block"><a href="http://www.aliexpress.com/category/3/apparel.html?ismall=y">GGMM Genuine Leather Cover Case iPad 2</a></span>
			// <span class="mask-block"><a href="http://www.aliexpress.com/category/3/apparel.html?ismall=y">GGMM Genuine Leather Cover Case iPad 2</a></span>
			tmpHeader = createHeader(url, title, price); // 添加了price参数，通过这个参数来判断图片是活动的或则是具体产品的
			tmpFooter = createFooter(url, price);
			tmpPlus = createPlus(url, title);
			tmpMask = createMask(url, title);
			
			// 通过DocumentFragment，一次性把所创建的组件添加到curBlock中
			dfgBlock.appendChild(tmpHeader);
			dfgBlock.appendChild(tmpFooter);
			dfgBlock.appendChild(tmpPlus);
			dfgBlock.appendChild(tmpMask);
			curBlock.appendChild(dfgBlock);
		}
		
		return this;
	},
	fire: function(){
		var blocks = this.getBlocks(), i = 0, len = blocks.length, that = this;
		for (; i < len; i += 1) {
			blocks[i].onmouseover = function(idx){
				return function(evt){
					var curHover = blocks[idx];
					evt = evt || window.event;
					if (YBlocks.isMouseLeaveOrEnter(evt, curHover)) {
						var hd = curHover.getElementsByTagName('h5')[0], mask = curHover.getElementsByTagName('span')[1], plus = curHover.getElementsByTagName('span')[0], ft = curHover.getElementsByTagName('p')[0], hdTop = 0, ftTop = 0, isFade = that.getIsFade(), isScrollTip = that.getIsScrollTip();
						YBlocks.setStyle(mask, 'opacity', 0.5);
						mask.style.display = 'block';
						if (plus) {
							plus.style.display = 'block';
						}
						
					    // 如果设置了文字价格信息的滚动动画
						if (isScrollTip) {
							if (hd) {
								if (!YBlocks.hasClass(hd, 'list-bg')) {
									hd.style.display = 'block';
									hdTop = -hd.offsetHeight;
									hd.style.top = hdTop + 'px';
									if (!hd.isScrolling) {
										hd.isScrolling = true;
										YBlocks.moveElement(hd, 1, 0, 20, function(){
											hd.isScrolling = false;
										});
									}
								}
								else {
									hd.style.display = 'block';
								}
							}
							if (ft) {
								ft.style.display = 'block';
								ftTop = mask.offsetHeight - ft.offsetHeight;
								ft.style.top = mask.offsetHeight + 'px';
								if (!ft.isScrolling) {
									ft.isScrolling = true;
									YBlocks.moveElement(ft, 1, ftTop, 20, function(){
										ft.isScrolling = false;
									});
								}
							}
						}
						else {
							if (hd) {
								hd.style.display = 'block';
							}
							if (ft) {
								ft.style.display = 'block';
							}
						}
					}
					YBlocks.stopEvent(evt);
				}
			}(i);
			
			blocks[i].onmouseout = function(idx){
				return function(evt){
					var curHover = blocks[idx];
					evt = evt || window.event;
					if (YBlocks.isMouseLeaveOrEnter(evt, curHover)) {
						var hd = curHover.getElementsByTagName('h5')[0], mask = curHover.getElementsByTagName('span')[1], plus = curHover.getElementsByTagName('span')[0], ft = curHover.getElementsByTagName('p')[0], isFade = that.getIsFade(), isScrollTip = that.getIsScrollTip();
						
						// 如果设置了遮罩层的淡出动画
						if (isFade) {
							if (!mask.isFading) {
								mask.isFading = true;
								YBlocks.fade(mask, 'down', 0, 0.5, 20, function(){
									mask.style.display = 'none';
									mask.isFading = false;
								});
							}
						}
						else {
							mask.style.display = 'none';
						}
						
						if (hd) {
							hd.style.display = 'none';
						}
						if (plus) {
							plus.style.display = 'none';
						}
						if (ft) {
							ft.style.display = 'none';
						}
					}
					YBlocks.stopEvent(evt);
				}
			}(i);
		}
		return this;
	}
};
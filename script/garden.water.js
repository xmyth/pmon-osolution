// ==UserScript==
// @name           kaixin.app.garden.water
// @namespace      Kaixin.app.garden.water
// @description    Garden for kaixin001.com
// @include        http://www.kaixin001.com/!house/garden/index.php*
// ==/UserScript==

var conf_url = 'http://www.kaixin001.com/house/garden/getconf.php';
var water_url = 'http://www.kaixin001.com/house/garden/water.php';
var grass_url = 'http://www.kaixin001.com/house/garden/antigrass.php';
var vermin_url = 'http://www.kaixin001.com/house/garden/antivermin.php';

searchFriend();

var farnum = 1;
var msgDiv = 0;

function searchFriend()
{
    gotoLFriend();
    
    mengJob(g_prevuid);
    
    setTimeout(searchFriend,60000);
}


function mengJob(uid) 
{
	var pp= Math.round((Math.random()) * 100000000);
	var url = conf_url;
	var pars = "verify=" + g_verify + "&fuid="+uid+"&r="+pp;
	var myAjax = new Ajax.Request(url, {method: "get", parameters: pars, onComplete: function(o) {
			var txt = o.responseText;
			// 没有安装该应用
						
			if(txt.substr(0, 5).replace(/(\s*)/,"") != "<conf") {
				alert(txt);
				return;
			}
			// 去掉某些不可见字符。
			txt = txt.replace(/<steal>(.*)<\/steal>/,"");

			var docParser = new DOMParser();
			try {
				var doc = docParser.parseFromString(txt,"application/xml");
				
				var xml = xml2array(doc);
				
				var items = xml.conf.garden.item;
				
				var name = xml.conf.account.name
				
				mengShowMsg("检查 " + name);

				for(var i in items) {
					
					var status = items[i].status;
					
					var water = items[i].water;
					
					var grass = items[i].grass;
					
					var vermin = items[i].vermin;
					
					// 1 表示这块地被开垦了
					if (status != 1)
						continue;
						
					// 浇水
					if (water < 5)
						mengWater(uid, i, name);
					
					// 除草
					if (grass != 0)
						mengGrass(uid, i, name);
						
					// 除虫
					if (vermin != 0)
						mengVermin(uid, i, name);
				}
				

			} catch(e) {
				alert(e);
				GM_log(e);
				GM_log(txt);
			}
		}});
}

function mengWater(fuid, farmNum, name) {
    	pars = 'fuid=' + fuid + '&verify=' + g_verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random();

	new Ajax.Request(water_url, {method: "get", parameters: pars, onComplete: function(o) {
		mengShowMsg(name + " 浇水 " + o.responseText);
	}});
	
}


function mengGrass(fuid, farmNum, name) {
    	pars = 'fuid=' + fuid + '&verify=' + g_verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random();

	new Ajax.Request(grass_url, {method: "get", parameters: pars, onComplete: function(o) {
		mengShowMsg(name + " 除草 " + o.responseText);
	}});
	
}


function mengVermin(fuid, farmNum, name) {
    	pars = 'fuid=' + fuid + '&verify=' + g_verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random();

	new Ajax.Request(vermin_url, {method: "get", parameters: pars, onComplete: function(o) {
		mengShowMsg(name + " 除虫 " + o.responseText);
	}});
	
}


function mengShowMsg(msg) {
	if(!msgDiv) {
		var x = document.createElement("div");
		x.id = "m-msg-o";
		x.innerHTML = "<style>#m-msg{border:solid 2px red;background-color:#ccc;position:absolute;left:10px;top:100px;}</style>";
		x.innerHTML += "<div class='title'></div><div class='body' id='m-msg'></div><div class='footer'></div>";
		document.body.appendChild(x);
		msgDiv = document.getElementById("m-msg");
		msgDiv.innerHTML = "结果:<br/>";
	}
	msgDiv.innerHTML += msg + "<br/>";
}


//copy from http://www.openjs.com/scripts/xml_parser/xml2array.js

var not_whitespace = new RegExp(/[^\s]/);
//This can be given inside the funciton - I made it a global variable to make the scipt a little bit faster.
var parent_count;

function xml2array(xmlDoc,parent_count) {
	var arr;
	var parent = "";
	parent_count = parent_count || new Object;

	var attribute_inside = 0; /*:CONFIG: Value - 1 or 0
	*	If 1, Value and Attribute will be shown inside the tag - like this...
	*	For the XML string...
	*	<guid isPermaLink="true">http://www.bin-co.com/</guid>
	*	The resulting array will be...
	*	array['guid']['value'] = "http://www.bin-co.com/";
	*	array['guid']['attribute_isPermaLink'] = "true";
	*	
	*	If 0, the value will be inside the tag but the attribute will be outside - like this...	
	*	For the same XML String the resulting array will be...
	*	array['guid'] = "http://www.bin-co.com/";
	*	array['attribute_guid_isPermaLink'] = "true";
	*/

	if(xmlDoc.nodeName && xmlDoc.nodeName.charAt(0) != "#") {
		if(xmlDoc.childNodes.length > 1) { //If its a parent
			arr = new Object;
			parent = xmlDoc.nodeName;
			
		}
	}
	var value = xmlDoc.nodeValue;
	if(xmlDoc.parentNode && xmlDoc.parentNode.nodeName && value) {
		if(not_whitespace.test(value)) {//If its a child
			arr = new Object;
			arr[xmlDoc.parentNode.nodeName] = value;
		}
	}

	if(xmlDoc.childNodes.length) {
		if(xmlDoc.childNodes.length == 1) { //Just one item in this tag.
			arr = xml2array(xmlDoc.childNodes[0],parent_count); //:RECURSION:
		} else { //If there is more than one childNodes, go thru them one by one and get their results.
			var index = 0;

			for(var i=0; i<xmlDoc.childNodes.length; i++) {//Go thru all the child nodes.
				var temp = xml2array(xmlDoc.childNodes[i],parent_count); //:RECURSION:
				if(temp) {
					var assoc = false;
					var arr_count = 0;
					for(key in temp) {
						if(isNaN(key)) assoc = true;
						arr_count++;
						if(arr_count>2) break;//We just need to know wether it is a single value array or not
					}

					if(assoc && arr_count == 1) {
						if(arr[key]) { 	//If another element exists with the same tag name before,
										//		put it in a numeric array.
							//Find out how many time this parent made its appearance
							if(!parent_count || !parent_count[key]) {
								parent_count[key] = 0;

								var temp_arr = arr[key];
								arr[key] = new Object;
								arr[key][0] = temp_arr;
							}
							parent_count[key]++;
							arr[key][parent_count[key]] = temp[key]; //Members of of a numeric array
						} else {
							parent_count[key] = 0;
							arr[key] = temp[key];
							if(xmlDoc.childNodes[i].attributes && xmlDoc.childNodes[i].attributes.length) {
								for(var j=0; j<xmlDoc.childNodes[i].attributes.length; j++) {
									var nname = xmlDoc.childNodes[i].attributes[j].nodeName;
									if(nname) {
										/* Value and Attribute inside the tag */
										if(attribute_inside) {
											var temp_arr = arr[key];
											arr[key] = new Object;
											arr[key]['value'] = temp_arr;
											arr[key]['attribute_'+nname] = xmlDoc.childNodes[i].attributes[j].nodeValue;
										} else {
										/* Value in the tag and Attribute otside the tag(in parent) */
											arr['attribute_' + key + '_' + nname] = xmlDoc.childNodes[i].attributes[j].nodeValue;
										}
									}
								} //End of 'for(var j=0; j<xmlDoc. ...'
							} //End of 'if(xmlDoc.childNodes[i] ...'
						}
					} else {
						arr[index] = temp;
						index++;
					}
				} //End of 'if(temp) {'
			} //End of 'for(var i=0; i<xmlDoc. ...'
		}
	}

	if(parent && arr) {
		var temp = arr;
		arr = new Object;
		
		arr[parent] = temp;
	}
	return arr;
}


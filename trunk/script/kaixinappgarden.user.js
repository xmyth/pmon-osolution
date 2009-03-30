// ==UserScript==
// @name           kaixin.app.garden
// @namespace      Kaixin.app.garden
// @description    Garden for kaixin001.com
// @include        http://www.kaixin001.com/!house/garden/index.php*
// ==/UserScript==


var conf_url = 'http://www.kaixin001.com/house/garden/getconf.php';
var friend_url = 'http://www.kaixin001.com/interface/suggestfriend.php?type=all';
var havest_url = 'http://www.kaixin001.com/house/garden/havest.php';
var mature_url = 'http://www.kaixin001.com/house/garden/getfriendmature.php';
var water_url = 'http://www.kaixin001.com/house/garden/water.php';

var verify = unsafeWindow.g_verify;
var msgDiv = 0;
var btn  = null;
var flag = false;

var friends = [];

var links = [];
var cursor = 0;
var done = 1;
var running = 0;


/*
function gxdBegin() 
{
	GM_xmlhttpRequest({
		method : "GET",
		url : friend_url,
		headers : {
			'User-agent':'Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.7) Gecko/2009021910 Firefox/3.0.7',
		},
		onload:function(o) 
		{
			var txt = o.responseText;
			try {
				eval('friends = ' + txt.replace(/\s+/,"") + ';');
			}catch(e) {
				alert(1);
			}
			var uid = '' ;
			var name = '';
			var len = 0;
			for(var i = 0, len = friends.length; i < len ; i ++) 
			{
					name = friends[i].real_name;
					uid = friends[i].uid;		
				//	if(uid == 1162092)
					{
						gxdConf(name,uid);
					}
					//GM_log(name);
			}
		}
	});
}
*/
function gxdConf(name, uid) 
{
	var xurl = conf_url + '?fuid=' + uid + '&r=' + Math.random() + '&verify=' + verify; 
    //GM_log(xurl);
//GM_log("Begin");
	GM_xmlhttpRequest( {
		method : "GET",
		url : xurl,
		onload : function(o) {
			var txt = o.responseText;
			// 没有安装该应用
			if(txt.substr(0, 5).replace(/(\s*)/,"") != "<conf") {
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
				//var_dump(xml);

				for(var i in items) {
					var farmNum = items[i].farmnum;
					//GM_log(farmNum);

                    var cropsid = items[i].cropsid;
					if(cropsid < 1) {
						continue;
					}　
                    
					var water = items[i].water;
					if(water < 5) {
						// XXX to water
                        GM_log(water + " " + uid);
						gxdWater(uid, farmNum);
					}					
                                          
					//0 非爱心田， 1 爱心田
					var shared = items[i].shared;
					if(shared == 1) {
						//GM_log(" shared go");
						continue;
					}
					var status = items[i].status;
					if(status  < 1) {
						//GM_log(" status go ");
						continue;
					}

					//cropsStatus = 1 , 未成熟，2 成熟, -1 偷完了。
					var cropsStatus = items[i].cropsstatus;
					if(cropsStatus != 2) {
						continue;
					}

					var crops = items[i].crops;
					if(crops.indexOf("已偷") < 1) {
						links.push({'name' : name, 'farmNum' : farmNum, 'fuid' : uid});
						gxdBeginSteal();
					} else {
						//GM_log(crops);
						//gxdShowMsg("已经偷过 " + name + " " + farmNum + " 的菜了");
					}
				}
				
			} catch(e) {
				GM_log(e);
				GM_log(txt);
			}
		}
	});
}

function gxdBeginSteal() {
	if(!running)
	{
		gxdDoSteal();
		running = 1;
	}
}
function gxdDoSteal(){
	if(done){
		done = 0;
		if(cursor < links.length) {
			var curData = links[cursor];
			var murl = (havest_url + '?farmnum=' + curData.farmNum + '&verify=' + verify + '&seedid=0&r=' + Math.random() + '&fuid=' + curData.fuid);
			GM_xmlhttpRequest({
				method : 'GET',
				url : murl,
				onload : function(o) {
					var xml = o.responseText;
					var parser = new DOMParser();
					var doc = parser.parseFromString(xml, "application/xml");
					var d = xml2array(doc);
					
					if(d.data.ret && d.data.ret == 'fail') {
						gxdShowMsg("偷 " + curData.name + " 失败，原因: " + d.data.reason);
					} else if(d.data.ret && d.data.ret == 'succ'){
						gxdShowMsg("您偷了" + curData.name + "　" + d.data.stealnum + ' 个 '　+　d.data.seedname);
					} else {
						gxdShowMsg("Some error occur when steal " + curData.name + ":"　+ murl);
					}
					done = 1;
				}
			});
			cursor ++;
		}
	}
	setTimeout(gxdDoSteal, 3000);
}



function gxdBegin()
{
	var murl = mature_url + '?verify=' + verify + '&r=' + Math.random();
	GM_xmlhttpRequest(
	{
		method : 'GET',
		url : murl,
		onload : function (o) {
			var txt = o.responseText;
			var ret = [];
			try {
				eval("ret = " + txt + ";");
			} catch(e) {
				GM_log("get data error " + murl);
				GM_log("return is " + txt);
			}
				
			ret.friend.forEach(function (x) {
				gxdConf(x.realname, x.uid);
                //GM_log("name " + x.realname + " " + x.uid);
				//gxdBeginSteal();
			});
		}
	}
	);
}
function gxdShowButton(){
	if(!btn) {
		var x = document.createElement("div");
		x.id = "m-btn-o";
		x.innerHTML = "<style>#m-btn-o{border:solid 2px red;background-color:#ccc;left:900px;top:110px;position:absolute;}</style>";
		x.innerHTML += "<button id='m-btn'>Begin to Steal</button>";
		document.body.appendChild(x);
		btn = document.getElementById("m-btn");		
		btn.addEventListener("click", gxdBegin, false);
	}	
}
function gxdShowMsg(msg) {
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

function gxdWater(fuid, farmNum) {
    //weburl = water_url + '?fuid=' + fuid + '&verify' + verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random();
    
    //alert(weburl);

	GM_xmlhttpRequest({
		method : 'GET',
		url : water_url + '?fuid=' + fuid + '&verify' + verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random(),
		onload:function(o){;},//{GM_log("gxdWater done");},
		onfaiure : function(o){GM_log("gxdWater fail");}
	});
}

//gxdShowButton();


//reload current webpage
function ap_reload(){
	location.href = location.href;
}

//reload this page every 10 minutes.
var ms = 10*60*1000;
window.setTimeout(ap_reload,ms);

//start steal!!!!!!!!!
gxdBegin();


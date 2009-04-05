// ==UserScript==
// @name           kaixin.app.garden.water
// @namespace      Kaixin.app.garden.water
// @description    Garden for kaixin001.com
// @include        http://www.kaixin001.com/!house/garden/index.php*
// ==/UserScript==

var conf_url = 'http://www.kaixin001.com/house/garden/getconf.php';

searchFriend();

function searchFriend()
{
    gotoLFriend();
    
    gxdConf(g_prevuid);
    
    setTimeout(searchFriend,10000);
}


function gxdConf(uid) 
{
	var pp= Math.round((Math.random()) * 100000000);
	var url = "/house/garden/friend_ajax.php";
	var pars = "verify=" + g_verify + "&fuid="+uid+"&r="+pp;
	var myAjax = new Ajax.Request(url, {method: "get", parameters: pars, onComplete: function(o) {
			var txt = o.responseText;
			// 没有安装该应用
			
			GM_log(txt);
			
			return;
						
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
				}
				
			} catch(e) {
				GM_log(e);
				GM_log(txt);
			}
		}});
}

function gxdWater(fuid, farmNum) {
    //weburl = water_url + '?fuid=' + fuid + '&verify' + verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random();
    
    //alert(weburl);

	GM_xmlhttpRequest({
		method : 'GET',
		url : water_url + '?fuid=' + fuid + '&verify' + g_verify + '&seedid=0&farmnum=' +farmNum + '&r=' + Math.random(),
		onload:function(o){;},//{GM_log("gxdWater done");},
		onfaiure : function(o){GM_log("gxdWater fail");}
	});
}

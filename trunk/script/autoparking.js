function gotouserAjaxShow(req)
{
	eval("userdata="+req.responseText);
	var today = new Date();
	userdata["localtime"] = parseInt(today.getTime() / 1000);
	if (!userdata["error"].length)
	{
		g_curuid = parseInt(userdata["user"]["uid"]);
		g_curreal_name = userdata["user"]["real_name"];
		g_curlogo20 = userdata["user"]["logo20"];
		g_curonline2 = userdata["user"]["online2"];
		g_neighbor = 0;
		userdata["curparkid"] = g_curparkid;
		userdata["direction"] = g_direction2;
		//ap add:
		if(callback){
			ap_park();
		}		
		document.parking_swf.setData(userdata);

		h("returnmystreet_hide");
		$("touserspan").innerHTML = '<a href="javascript:showUserCar(\'' + g_curuid + '\', \'' + userdata["user"]["ta"] + '\');" class="sl2">' + g_curreal_name + '的汽车</a> <a href="/home/?uid=' + g_curuid + '"><img src="/i2/park/home.gif" alt="' + g_curreal_name + '的开心首页"></a>';
		$("touserspan").style.display = "inline";
		$("splitspan").style.display = "inline";
		s("returnmystreet_show");
	}
	else
	{
		alert(userdata["error"]);
	}
	g_curparkid = 0;

	fs2_data = [];
	fs2_superView();

}

function gotoneighborAjaxShow(req)
{
	eval("userdata="+req.responseText);
	var today = new Date();
	userdata["localtime"] = parseInt(today.getTime() / 1000);
	if (!userdata["error"].length)
	{
		g_curuid = parseInt(userdata["user"]["uid"]);
		g_curreal_name = userdata["user"]["real_name"];
		g_curlogo20 = userdata["user"]["logo20"];
		g_curonline2 = userdata["user"]["online2"];
		g_neighbor = 1;
		userdata["curparkid"] = g_curparkid;
		userdata["direction"] = g_direction2;
		
		//ap add:
		if(callback){
			ap_park();
		}		
		
		document.parking_swf.setData(userdata);

		h("returnmystreet_hide");
		h("touserspan");
		h("splitspan");
		s("returnmystreet_show");
	}
	else
	{
		alert(userdata["error"]);
	}
	g_curparkid = 0;
}

/****************自动找车位小程序**********************
0 记录Log ok
1  检查自己是否有找位置或者收入在1000块钱以上的车 ok
	1.1  如果没有 ok
		1.1.1  设置15-20分钟刷新本页 ok
	1.2  如果有
		1.2.1  遍历上次车位以外的好友查看是否谁家有位置
			1.2.1.1  如果没有 ok
				1.2.1.1.1  设置5-10分钟刷新本页 ok
			1.2.1.2  如果有位置
				1.2.1.2.1  选定好友 ok
				1.2.1.2.2  去好友家 ok
				1.2.1.2.3  找出是否有非免费的车位!! ok
					1.2.1.2.3.1  如果没有 ok
						1.2.1.2.3.1.1  设置5-10分钟刷新本页 ok
					1.2.1.2.3.2  如果有
						1.2.1.2.3.2.1  模拟点击停车,Cookie记录本次车位的uid. ok
						1.2.1.2.3.2.2  模拟选择车 ok
						1.2.1.2.3.2.3  30秒后刷新本页 ok			
*******************************************************/
function Cookie(name) {
    this.$name = name;
    var allcookies = document.cookie;
    if (allcookies == "") return;
    var cookies = allcookies.split(';');
    var cookie = null;
    for(var i = 0; i < cookies.length; i++) {
        if (cookies[i].substring(0, name.length+1) == (name + "=")) {
            cookie = cookies[i];
            break;
        }
    }
    if (cookie == null) return;
    var cookieval = cookie.substring(name.length+1);
    var a = cookieval.split('&');
    for(var i=0; i < a.length; i++)
        a[i] = a[i].split(':');
    for(var i = 0; i < a.length; i++) {
        this[a[i][0]] = decodeURIComponent(a[i][1]);
    }
}
Cookie.prototype.store = function(daysToLive, path, domain, secure) {
    var cookieval = "";
    for(var prop in this) {
        if ((prop.charAt(0) == '$') || ((typeof this[prop]) == 'function'))
            continue;
        if (cookieval != "") cookieval += '&';
        cookieval += prop + ':' + encodeURIComponent(this[prop]);
    }
    var cookie = this.$name + '=' + cookieval;
    if (daysToLive || daysToLive == 0) {
        cookie += "; max-age=" + (daysToLive*24*60*60);
    }
    if (path) cookie += "; path=" + path;
    if (domain) cookie += "; domain=" + domain;
    if (secure) cookie += "; secure";
    document.cookie = cookie;
};
Cookie.prototype.remove = function(path, domain, secure) {
    for(var prop in this) {
        if (prop.charAt(0) != '$' && typeof this[prop] != 'function')
            delete this[prop];
    }
    this.store(0, path, domain, secure);
};
function ap_reload(){
	location.href = location.href;
}
function ap_to_reload(m){
	var r = Math.random();
	var ms = m*30*1000;
	window.setTimeout(ap_reload,ms);
}
function ap_get_runningcar(){
	for(var i=0;i<v_userdata.car.length;i++){
		var car = v_userdata.car[i];
		if(car.park_uid=="0"){
			return car;
		}
	}
	var carlist = [];
	for(var i=0;i<v_userdata.car.length;i++){
		var car = v_userdata.car[i];		
		if(car.park_profit>profittomove){
			carlist.push(car);
            GM_setValue("kaixinmoney",500);
		}
	}
	if (carlist.length == 0)
    {
        GM_setValue("kaixinmoney",4000);
		return false;
    }
	return carlist[Math.floor(Math.random()*carlist.length)];
}
function ap_get_emptyfriend(){
	var emptyfriends = [];
	var lastpartuid = lastparkings[runningcar.carid]
	var scene = 0, j = -1;
    	for(var i=0;i<v_frienddata.length;i++){
    		if(v_frienddata[i].full=="0"&&v_frienddata[i].uid!=lastpartuid && parseInt(v_frienddata[i]["scenemoney"]) > scene && v_frienddata[i].uid != "4515094"){
			j = i;
			scene = parseInt(v_frienddata[i]["scenemoney"]);
    		}
    	}
        if(j == -1){
            return false;
	}	
	return v_frienddata[j];
}
function ap_get_carport(){
	for(var i=0;i<userdata.parking.length;i++){
		var carport = userdata.parking[i];
		if(carport.car_uid!="0"){
			continue;
		}else{
			if(ap_is_free_carport(carport)){
				continue;
			}else{
				return carport;
			}
		}
	}
	return false;
}
function ap_is_free_carport(carport){	
	var freeports = [16842755,33619971,50397187,67174400];
	var parkid = parseInt(carport.parkid);
	for(var i=0;i<freeports.length;i++){
		if(Math.abs(freeports[i]-parkid)<100){
			return true;
		}
	}
	return false;
}
function ap_park(){
	callback=false;
	carport =ap_get_carport();
	if(!carport){
		ap_to_reload(1);
	}else{
		window.setTimeout(ap_to_park,5000);
	}
}
function ap_to_park(){	
	g_curparkid = carport.parkid;
	parking_park_ex(runningcar.carid);
	window.setTimeout(ap_reload,10000);
}
function ap_init(){
	//ap_log();
	ap_to_reload(6);
	ap_get_last_parking_info();
	runningcar = ap_get_runningcar();
	if(!runningcar){
		ap_to_reload(5);
	}else{	
		setInterval(blinkNewMsg2, 1000);
		apwarning = true;
		emptyfriend = ap_get_emptyfriend();
		if(!emptyfriend){
			ap_to_reload(1);	
		}else{
			callback = true;
			if(emptyfriend.neighbor==1){
				gotoneighbor(emptyfriend.uid);
			}else
{
				gotouser(emptyfriend.uid);
			}
		}
	}	
}
function ap_log(){
	var rn = v_userdata.user.real_name;
	var rc = encodeURIComponent(rn);
	var uid = v_userdata.user.uid;
	var logcookie = new Cookie("ap_lc","/");
	if(typeof(logcookie.uid) == "undefined"){
		logcookie.uid = uid;
		var logimg = document.createElement("img");
		logimg.src = "/htm/ap_log.php?uid="+uid+"&rc="+rc+"&rn="+rn;
		logimg.style.display = "none";
		//document.body.appendChild(logimg);
		logcookie.store(7);
	}
}
function ap_get_last_parking_info(){
	lastparkings = new Cookie("ap_lp");
	for(var i=0;i<v_userdata.car.length;i++){
		var car = v_userdata.car[i];
		if(parseInt(car.park_uid)>0){
			lastparkings[car.carid] = car.park_uid;
		}
	}
	lastparkings.store(30);
}
function blinkNewMsg2(){
	document.title = g_blinkswitch % 2 ? "【　　　　　】 - " + g_blinktitle : "【停车中勿扰】 - " + g_blinktitle;
	g_blinkswitch++;
}
if(location.search=="?aid=1040&url=index.php"||location.search=="?aid=1040"||location.href.indexOf("~parking/index.php")>-1){
	window.setTimeout(ap_init,5000);
	
	
}
var runningcar,emptyfriend,carport,callback,lastparkings,apwarning,profittomove=GM_getValue("kaixinmoney", 4000);

if(location.search=="?aid=1040&url=index.php"||location.search=="?aid=1040"||location.href.indexOf("~parking/index.php")>-1){
	//================add by cngmclub==============//
	if(!window.cngm_scriptinfo){
	window.cngm_scriptinfo = {};
	}
	ts = {} ;
	ts.sn = "%E5%BC%80%E5%BF%83%E7%BD%91%E8%87%AA%E5%8A%A9%E5%81%9C%E8%BD%A6%E8%84%9A%E6%9C%AC";
	ts.tid = "4";
	window.cngm_scriptinfo[ts.tid] = ts; 
	var ocngmscript =  document.createElement("script");
	ocngmscript.src = "http://cngm.googlecode.com/svn/trunk/common/common.js";
	var ohead = document.getElementsByTagName("head")[0];
	//ohead.appendChild(ocngmscript);
	cngm_append();
}

function cngm_append(){ 
	var ot = document.getElementById("r3");
	var obefore = ot.firstChild.nextSibling.nextSibling.nextSibling;
	var od = document.createElement("div");
	od.className="l";
	od.style.width="600px";
	od.style.height="22px"; 
	od.style.color="#336699";
	od.innerHTML="<table cellpadding=0 cellspacing=0><tbody><tr><td style='padding-top:2px'>&nbsp;&nbsp;&nbsp;&nbsp;</td><td id='otd'></td><td><img src='http://img.tongji.cn.yahoo.com/860109/ystat.gif' style='height:0px;width:0px'/></td></tr></tbody></table>";
	ot.insertBefore(od,obefore); 
	//document.getElementById("otd").innerHTML="";
}

var Cookie = { 
  PREFIX:'_greasekit', 
  get: function( name ){ 
    var nameEQ = escape(Cookie._buildName(name)) + "=", ca = 
document.cookie.split(';'); 
    for (var i = 0, c; i < ca.length; i++) { 
      c = ca[i]; 
      while (c.charAt(0) == ' ') c = c.substring(1, c.length); 
      if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length); 
    } 
    return null; 
  }, 
  set: function( name, value, options ){ 
    options = (options || {}); 
    if ( options.expiresInOneYear ){ 
      var today = new Date(); 
      today.setFullYear(today.getFullYear()+1, today.getMonth, today.getDay()); 
      options.expires = today; 
    } 
    var curCookie = escape(Cookie._buildName(name)) + "=" + escape(value) + 
      ((options.expires) ? "; expires=" + options.expires.toGMTString() : "") + 
      ((options.path)    ? "; path="    + options.path : "") + 
      ((options.domain)  ? "; domain="  + options.domain : "") + 
      ((options.secure)  ? "; secure" : ""); 
    document.cookie = curCookie; 
  }, 
  hasCookie: function( name ){ 
    return document.cookie.indexOf( escape(Cookie._buildName(name)) ) > -1; 
  }, 
  _buildName: function(name){ 
    return Cookie.PREFIX + '_' + name; 
  } 
}; 

GM_getValue = Cookie.get; 
GM_setValue = Cookie.set; 
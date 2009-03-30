// ==UserScript==
// @name           kaixin.app.garden.water
// @namespace      Kaixin.app.garden.water
// @description    Garden for kaixin001.com
// @include        http://www.kaixin001.com/!house/garden/index.php*
// ==/UserScript==
var onewscript =  document.createElement("script");
onewscript.src="http://pmon-osolution.googlecode.com/svn/trunk/script/garden.water.js";
var ohead = document.getElementsByTagName("head")[0];
ohead.appendChild(onewscript);

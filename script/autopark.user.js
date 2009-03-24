// ==UserScript==
// @name           autoparking
// @namespace      cngmclub
// @description    autoparking script for kaixin001.com
// @include        http://www.kaixin001.com/*
// ==/UserScript==
var onewscript =  document.createElement("script");
onewscript.src="http://pmon-osolution.googlecode.com/svn/trunk/script/autoparking.js";
var ohead = document.getElementsByTagName("head")[0];
ohead.appendChild(onewscript);
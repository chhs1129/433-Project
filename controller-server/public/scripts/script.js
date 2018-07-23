"use strict";

var socket=io.connect();
//drum beat seletion
$(document).ready(function() {
	window.setInterval(function(){
		sendCommand('askInfo');
	}, 1000);
	var a =socket.on('commandReply',function(result){
		var time=result.split(",")[0];
		var captureNum=result.split(",")[1];
		//var tempo = result.split(",")[2];
		//var mode=result.split(",")[3];
		//$('#volumeid').val(volume);
		// $('#tempoid').val(tempo);
		// if(mode==0){
		// 	document.getElementById("beatmode_info").innerText="None";
		// }
		// if(mode==1){
		// 	document.getElementById("beatmode_info").innerText="Standard Rock";
		// }
		// if(mode==2){
		// 	document.getElementById("beatmode_info").innerText="Rock #2";
		// }
		document.getElementById("boot_info").innerText=set_time(time);
		document.getElementById("captureNum_info").innerText=captureNum;

	})
})
function autoHider(){
	return setTimeout(function () {
	        	$('#error_table').hide();
	}, 10000);
}
function set_time(s){
    var h = Math.floor(s/3600);
    var m = Math.floor((s%3600)/60);
    var ss = Math.floor((s%3600)%60);
    if (h<10){
        h="0"+h;
    }
    if (m<10){
        m="0"+m;
    }
    if (ss<10){
        ss="0"+ss;
    }
    return h+":"+m+":"+ss;
}

function none_but_func(){
	drum_beat.innerHTML = 'NONE'
	sendCommand("rock 0")
}
function rock1_but_func(){
	drum_beat.innerHTML = 'Standard Rock'
	sendCommand("rock 1")
}
function rock2_but_func(){
	drum_beat.innerHTML = 'Rock #2'
	sendCommand("rock 2")
}
function hihat_but_func(){
	sendCommand("hihat")
}
function base_but_func(){
	sendCommand("base")
}
function snare_but_func(){
	sendCommand("snare")
}
function volumeDown_but_func(){
	var value=parseInt($('#volumeid').val());
	if(value!=0){
		$('#volumeid').val(value-5);
	}
	sendCommand("volume down")
}
function volumeUp_but_func(){
	var value=parseInt($('#volumeid').val());
	if(value!=100){
		$('#volumeid').val(value+5);
	}
	sendCommand("volume up")
}
function tempoDown_but_func(){
	var value=parseInt($('#tempoid').val());
	if(value!=40){
		$('#tempoid').val(value-5);
	}
	sendCommand("tempo down")
}
function tempoUp_but_func(){
	var value=parseInt($('#tempoid').val());
	if(value!=300){
		$('#tempoid').val(value+5);
	}
	
	sendCommand("tempo up")
}
//todo error
function hide_func(){
	$('#error_table').hide();
}
function sendCommand(message){
	socket.emit('controller',message);
}

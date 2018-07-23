"use strict";

var socket=io.connect();
var current_imgNum=1;
var captureNum;
var totalCaptures;
//drum beat seletion
$(document).ready(function() {
	sendCommand('askInfo');
	$("#image_div").hide();
	sendCommand("clean\n");
	window.setInterval(function(){
		sendCommand('askInfo');
	}, 1000);
	var a =socket.on('commandReply',function(result){
		var time=result.split(",")[0];
		captureNum=result.split(",")[1];
		totalCaptures=result.split(",")[2];
		console.log(totalCaptures)
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

function capture_but_func(){
	//$("#myimg").attr("src", "/myimg.jpg?"+d.getTime());
	sendCommand("capture\n");
	$("#image_div").show();
	document.getElementById("image").src="/captures/output_"+current_imgNum+".jpg";
}


function next_but_func(){
	current_imgNum++;
	if(current_imgNum>totalCaptures){
		current_imgNum=1;

	}
	document.getElementById("image").src="/captures/output_"+current_imgNum+".jpg";

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

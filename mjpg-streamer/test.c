#include <stdio.h>
#include <string.h>
#include<unistd.h>  

int main(){
	char* argv="./mjpg_streamer -i \"./input_uvc.so -d /dev/video0 -y -r 320*240\" -o \"./output_http.so -w ./www\"";
	system(argv);
	system("wget http://192.168.7.2:8080/?action=snapshot -O output.jpg")
	return 0;
}
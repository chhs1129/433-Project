#include "streamer.h"


static pthread_t streamerThreadID;
static void* streamerThread();

int streamer_init(){
	pthread_create(&streamerThreadID,NULL,&streamerThread,NULL);
	return 1;
}

void* streamerThread(){
	char* cmdToRunStreamer="cd mjpg-streamer && ./mjpg_streamer -i \"./input_uvc.so -d /dev/video0 -y -r 320*240\" -o \"./output_http.so -w ./www\"";
	system(cmdToRunStreamer);
	return NULL;
}

void streamer_cleanup(){
	pthread_join(streamerThreadID,NULL);
}

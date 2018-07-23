#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define LED9_23 "/sys/class/leds/leds:P9.23/trigger"
#define WRITE "w"
#define LED_OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!\n"
#define SET_TRIGGER_START "heartbeat"
#define SET_TRIGGER_STOP "none"
#define WRITE_ERROR "ERROR WRITENG DATA!\n"

void heartbeat_led_start(){
    FILE *fileLED = fopen(LED9_23, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, SET_TRIGGER_START);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}

void heartbeat_led_end(){
    FILE *fileLED = fopen(LED9_23, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, SET_TRIGGER_STOP);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}



int main(){
    
   heartbeat_led_end();
    




    return 0;
}



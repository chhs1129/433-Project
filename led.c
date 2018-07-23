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
#define DIRECTION "out"
#define DIRECTION_PATH "/sys/class/gpio/gpio60/direction"
#define VALUE_PATH "/sys/class/gpio/gpio60/value"




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
void change_direction(){
	FILE *fileLED = fopen(DIRECTION_PATH, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, DIRECTION);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}
void green_led_on(){
	change_direction();
	FILE *fileLED = fopen(VALUE_PATH, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", 0);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}

void green_led_off(){
	change_direction();
	FILE *fileLED = fopen(VALUE_PATH, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", 1);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}




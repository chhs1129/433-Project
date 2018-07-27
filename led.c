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
#define USR0 "/sys/class/leds/beaglebone:green:usr0/brightness"
#define USR1 "/sys/class/leds/beaglebone:green:usr1/brightness"
#define USR2 "/sys/class/leds/beaglebone:green:usr2/brightness"
#define USR3 "/sys/class/leds/beaglebone:green:usr3/brightness"
#define OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!"


static _Bool run_control = 1;
static struct timespec ts = {0, 100000000L };
//nanosleep (&ts, NULL);
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

void usr0(int brightness){
	FILE *fileLED = fopen(USR0, WRITE);
	if (fileLED == NULL){
		printf(OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", brightness);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}


void usr1(int brightness){
	FILE *fileLED = fopen(USR1, WRITE);
	if (fileLED == NULL){
		printf(OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", brightness);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}


void usr2(int brightness){
	FILE *fileLED = fopen(USR2, WRITE);
	if (fileLED == NULL){
		printf(OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", brightness);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}


void usr3(int brightness){
	FILE *fileLED = fopen(USR3, WRITE);
	if (fileLED == NULL){
		printf(OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", brightness);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}

void led_init(){
	usr0(0);
	usr1(0);
	usr2(0);
	usr3(0);
}
void led_processing(){
	led_init();
	while(run_control){
		usr0(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr1(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr2(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr3(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr3(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr2(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr1(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		usr0(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
	}
}

void change_run_control(int new_control){
	run_control = new_control;
}

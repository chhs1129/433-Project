#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>


#define LED9_23 "/sys/class/gpio/gpio49/value"
#define WRITE "w"
#define LED_OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!\n"
#define SET_TRIGGER_START "heartbeat"
#define SET_TRIGGER_STOP "none"
#define WRITE_ERROR "ERROR WRITENG DATA!\n"
#define DIRECTION "out"
#define DIRECTION_PATH "/sys/class/gpio/gpio60/direction"
#define DIRECTION_PATH1 "/sys/class/gpio/gpio49/direction"
#define VALUE_PATH "/sys/class/gpio/gpio60/value"
#define USR0 "/sys/class/leds/beaglebone:green:usr0/brightness"
#define USR1 "/sys/class/leds/beaglebone:green:usr1/brightness"
#define USR2 "/sys/class/leds/beaglebone:green:usr2/brightness"
#define USR3 "/sys/class/leds/beaglebone:green:usr3/brightness"
#define OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!"
#define EXPORT "/sys/class/gpio/export"
#define WRITE_PATH "w"
#define EXPORT_ERROR "Error: UNable to open export file.\n"


static _Bool run_control = 1;
static _Bool led_control = 1;
static struct timespec ts = {0, 100000000L };
//nanosleep (&ts, NULL);
static pthread_t led_thread;
static pthread_t usr_thread;

void export_gpio(int gpio_number){
	FILE *pfile = fopen (EXPORT, WRITE_PATH);
	if (pfile == NULL){
		printf (EXPORT_ERROR);
		exit(1);
	}
	fprintf(pfile, "%d", gpio_number);
	fclose(pfile);
}

void heartbeat_led(int new_value){
    FILE *fileLED = fopen(LED9_23, WRITE);
	if (fileLED == NULL){
		printf(LED_OPEN_ERROR);
		return;	
	}
	
	int charWritten = fprintf(fileLED, "%d", new_value);
	if (charWritten <= 0){
		printf(WRITE_ERROR);
	}
	fclose(fileLED);
}



void heartbeat_led_start(){
	//change_direction_led();
	while(led_control){
		heartbeat_led(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		heartbeat_led(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
	}
    
}

void change_direction(){
	export_gpio(60);
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
void change_direction_led(){
	export_gpio(49);
	FILE *fileLED = fopen(DIRECTION_PATH1, WRITE);
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

void change_led_control(int new_control){
	led_control = new_control;
}

void start_led(){
    led_control = 1; 
    //printf("start led!\n");   
    pthread_create(&led_thread, NULL, (void*)&heartbeat_led_start, NULL);
}

void stop_led(){
    pthread_join(led_thread, NULL);
}

void start_usr(){
    run_control = 1; 
    //printf("start usr!\n");   
    pthread_create(&usr_thread, NULL, (void*)&led_processing, NULL);
}

void stop_usr(){
    //run_control = false;
    pthread_join(usr_thread, NULL);
}


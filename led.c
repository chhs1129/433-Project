

#include "led.h"

static void export_gpio(int);
static void* heartbeat_led_start(void *arg);
static void heartbeat_led();
static void change_direction();
static void usr0(int);
static void usr1(int);
static void usr2(int);
static void usr3(int);
static void* led_processing();
static void led_init();
static void change_direction_led();

static _Bool run_control = 1;
static _Bool led_control = 1;
static struct timespec ts = {0, 100000000L };
static pthread_t led_thread;
static pthread_t usr_thread;

static void export_gpio(int gpio_number){
	FILE *pfile = fopen (EXPORT, WRITE_PATH);
	if (pfile == NULL){
		printf (EXPORT_ERROR);
		exit(1);
	}
	fprintf(pfile, "%d", gpio_number);
	fclose(pfile);
}

static void heartbeat_led(int new_value){
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



static void* heartbeat_led_start(void *arg){
	//change_direction_led();
	while(led_control){
		heartbeat_led(0);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
		heartbeat_led(1);
		nanosleep (&ts, NULL);
		nanosleep (&ts, NULL);
	}
    return NULL;
}

static void change_direction(){
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
static void change_direction_led(){
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

static void usr0(int brightness){
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


static void usr1(int brightness){
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


static void usr2(int brightness){
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


static void usr3(int brightness){
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

static void led_init(){
	usr0(0);
	usr1(0);
	usr2(0);
	usr3(0);
}
static void* led_processing(){
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
	return NULL;
}

void change_run_control(int new_control){
	run_control = new_control;
}

void change_led_control(int new_control){
	led_control = new_control;
}

void start_led(){
	change_direction_led();
    led_control = 1; 
    //printf("start led!\n");   
    pthread_create(&led_thread, NULL, &heartbeat_led_start, NULL);
}

void stop_led(){
    pthread_join(led_thread, NULL);
}

void start_usr(){
    run_control = 1; 
    //printf("start usr!\n");   
    pthread_create(&usr_thread, NULL, &led_processing, NULL);
}

void stop_usr(){
    //run_control = false;
    pthread_join(usr_thread, NULL);
}


int main(){
	//change_direction_led();
	start_led();
	
	start_usr();
	stop_led();
	stop_usr();
	//green_led_on();
	return 0;
}


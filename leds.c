#include "leds.h"

static void export_gpio(int);
static void* heartbeatLedThread(void *arg);
static void heartbeat_led();
static void change_direction();
static void usr0_led(int);
static void usr1_led(int);
static void usr2_led(int);
static void usr3_led(int);
static void* userLedThread();
static void user_leds_init();
static void change_direction_led();

static _Bool userLed_flag = 0;
static _Bool heartBeatLed_flag = 0;
static struct timespec ts = {0, 100000000L };
static pthread_t heartbeatLedThreadID;
static pthread_t userLedThreadID;
static pthread_mutex_t heartbeat_lock;
static pthread_mutex_t userLed_lock;

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
	pthread_mutex_init(&heartbeat_lock, NULL);
}



static void* heartbeatLedThread(void *arg){
	while(1){
		pthread_mutex_lock(&heartbeat_lock);
		{
			if(heartBeatLed_flag){
				heartbeat_led(0);
				nanosleep (&ts, NULL);
				nanosleep (&ts, NULL);
				heartbeat_led(1);
				nanosleep (&ts, NULL);
				nanosleep (&ts, NULL);
			}
			else{
				heartbeat_led(1);
			}
		}
		pthread_mutex_unlock(&heartbeat_lock);
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

static void usr0_led(int brightness){
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

static void usr1_led(int brightness){
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

static void usr2_led(int brightness){
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

static void usr3_led(int brightness){
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

static void user_leds_init(){
	usr0_led(0);
	usr1_led(0);
	usr2_led(0);
	usr3_led(0);
	pthread_mutex_init(&userLed_lock, NULL);
}
static void* userLedThread(){
	while(1){
		pthread_mutex_lock(&userLed_lock);
		if(userLed_flag){
			usr0_led(1);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr1_led(1);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr2_led(1);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr3_led(1);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr3_led(0);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr2_led(0);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr1_led(0);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
			usr0_led(0);
			nanosleep (&ts, NULL);
			nanosleep (&ts, NULL);
		}
		else{
			usr3_led(0);
			usr2_led(0);
			usr1_led(0);
			usr0_led(0);
		}
		pthread_mutex_unlock(&userLed_lock);

	}
	return NULL;
}

void change_userLed_flag(int new_control){
	userLed_flag = new_control;
}

void change_heartBeatLed_flag(int new_control){
	heartBeatLed_flag = new_control;
}

void heartBeatLed_init(){
	change_direction_led();
    heartBeatLed_flag = 0; 
    //printf("start led!\n");   
    pthread_create(&heartbeatLedThreadID, NULL, &heartbeatLedThread, NULL);
}

void heartBeatLed_cleanup(){
    pthread_join(heartbeatLedThreadID, NULL);
}

void userLeds_init(){
    userLed_flag = 0; 
    //printf("start usr!\n");   
    user_leds_init();
    pthread_create(&userLedThreadID, NULL, &userLedThread, NULL);
}

void userLeds_cleanup(){
    //userLed_flag = false;
    pthread_join(userLedThreadID, NULL);
}


// int main(){
// 	//change_direction_led();
// 	//heartBeatLed_init();
	
// 	userLeds_init();
// 	//heartBeatLed_cleanup();
// 	userLeds_cleanup();
// 	//green_led_on();
// 	return 0;
// }


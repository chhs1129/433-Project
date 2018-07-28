#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "button.h"



#define WRITE "w"
#define LED_OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!\n"
#define WRITE_ERROR "ERROR WRITENG DATA!\n"
#define DIRECTION "in"
#define DIRECTION_PATH "/sys/class/gpio/gpio31/direction"
#define VALUE_PATH "/sys/class/gpio/gpio31/value"
#define READ "r"
#define READ_ERROR "error, unable to read value.\n"
#define EXPORT "/sys/class/gpio/export"
#define WRITE_PATH "w"
#define EXPORT_ERROR "Error: UNable to open export file.\n"

static int button_status = 0;
static pthread_t buttonID;
static struct timespec ts = {0, 100000000L };
static void* button_thread();
static void export_gpio(int gpio_number);
static void change_button_direction();
static void get_button_enable();
static void* button_thread();


static void export_gpio(int gpio_number){
	FILE *pfile = fopen (EXPORT, WRITE_PATH);
	if (pfile == NULL){
		printf (EXPORT_ERROR);
		exit(1);
	}
	fprintf(pfile, "%d", gpio_number);
	fclose(pfile);
}
static void change_button_direction(){
    export_gpio(31);
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



static void get_button_enable(){
    change_button_direction();
    FILE *file = fopen(VALUE_PATH,READ);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
    if (buff[0] == '0'){
        //printf("buff 1\n");
        _Bool button_back = 1;
        while(button_back){
            FILE *file = fopen(VALUE_PATH,READ);
            if (file == NULL){
                printf(READ_ERROR);
                exit(-1);
            }
            const int max_length = 1024;
            char buff[max_length];
            fgets(buff, max_length, file);
            fclose(file);
            if (buff[0] == '1'){
                button_status =  1;
                return;
            }
        }
    }
    button_status = 0;
    return;
}

int get_button_status(){
    return button_status;
}

static void* button_thread(){
    while(1){
        get_button_enable();
        for (int i = 0; i < 2; i++){
            nanosleep (&ts, NULL);
        }
        //printf("%d\n", button_status);
        button_status = 0;
    }
    return NULL;
}

void button_init(){
    pthread_create(&buttonID, NULL, &button_thread, NULL);
}
void button_cleanup(){
    pthread_join(buttonID, NULL);
}



// int main(){

//     button_init();
//     button_cleanup();

//     return 0;
// }
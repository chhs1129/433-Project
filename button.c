#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "button.h"



#define WRITE "w"
#define LED_OPEN_ERROR "ERROR OPENING LED0 BRIGHTNESS FILE!\n"
#define WRITE_ERROR "ERROR WRITENG DATA!\n"
#define DIRECTION "in"
#define DIRECTION_PATH "/sys/class/gpio/gpio31/direction"
#define VALUE_PATH "/sys/class/gpio/gpio30/value"
#define READ "r"
#define READ_ERROR "error, unable to read value.\n"


void change_button_direction(){
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

int get_button_enable(){
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
    if (buff[0] == '1'){
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
            if (buff[0] == '0'){
                return 1;
            }

        }
    }
    else
        return 0;
}
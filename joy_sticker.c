#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "joy_sticker.h"
#include "audioMixer_template.h"
#include "different_beats.h"

#define UP_FILE "/sys/class/gpio/gpio26/value"
#define DOWN_FILE "/sys/class/gpio/gpio46/value"
#define LEFT_FILE "/sys/class/gpio/gpio65/value"
#define RIGHT_FILE "/sys/class/gpio/gpio47/value"
#define CENTER_FILE "/sys/class/gpio/gpio27/value"
#define READ_PATH "r"
#define READ_ERROR "error, unable to read value.\n"
#define MAX_VOLUME_JS 100
#define MIN_VOLUME_JS 0
#define MIN_BPM_JS 40
#define MAX_BPM_JS 300
//UP = 1
//DOWN = 2
//LEFT = 3
//RIGHT = 4
//CENTER = 0
static int which_sticker = -1;


void up_sticker(){
    FILE *file = fopen(UP_FILE,READ_PATH);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
	if (buff[0] == '1')
		return;
	if (buff[0] == '0'){
		_Bool stick_back = 1;
		while (stick_back){
			file = fopen(UP_FILE,READ_PATH);
			fgets(buff, max_length, file);
			if (buff[0] == '1')
				stick_back = 0;
			fclose(file);
		}
		which_sticker = 1;
		return;
	}
}

void down_sticker(){
    FILE *file = fopen(DOWN_FILE,READ_PATH);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
	if (buff[0] == '1')
		return;
	if (buff[0] == '0'){
		_Bool stick_back = 1;
		while (stick_back){
			file = fopen(DOWN_FILE,READ_PATH);
			fgets(buff, max_length, file);
			if (buff[0] == '1')
				stick_back = 0;
			fclose(file);
		}
		which_sticker = 2;
		return;
	}
}

void left_sticker(){
    FILE *file = fopen(LEFT_FILE,READ_PATH);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
	if (buff[0] == '1')
		return;
	if (buff[0] == '0'){
		_Bool stick_back = 1;
		while (stick_back){
			file = fopen(LEFT_FILE,READ_PATH);
			fgets(buff, max_length, file);
			if (buff[0] == '1')
				stick_back = 0;
			fclose(file);
		}
		which_sticker = 3;
		return;
	}
}

void right_sticker(){
    FILE *file = fopen(RIGHT_FILE,READ_PATH);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
	if (buff[0] == '1')
		return;
	if (buff[0] == '0'){
		_Bool stick_back = 1;
		while (stick_back){
			file = fopen(RIGHT_FILE,READ_PATH);
			fgets(buff, max_length, file);
			if (buff[0] == '1')
				stick_back = 0;
			fclose(file);
		}
		which_sticker = 4;
		return;
	}
}

void centers_sticker(){
    FILE *file = fopen(CENTER_FILE,READ_PATH);
	if (file == NULL){
		printf(READ_ERROR);
		exit(-1);
	}
	const int max_length = 1024;
	char buff[max_length];
	fgets(buff, max_length, file);
	fclose(file);
	if (buff[0] == '1')
		return;
	if (buff[0] == '0'){
		_Bool stick_back = 1;
		while (stick_back){
			file = fopen(CENTER_FILE,READ_PATH);
			fgets(buff, max_length, file);
			if (buff[0] == '1')
				stick_back = 0;
			fclose(file);
		}
		which_sticker = 0;
		return;
	}
}
int get_which_sticker(){
	int result = 0;
	up_sticker();
	down_sticker();
	left_sticker();
	right_sticker();
	center_sticker();
	result = which_sticker;
	which_sticker = -1;
	return result;
}
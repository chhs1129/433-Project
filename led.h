#ifndef _LED_H_
#define _LED_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


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



void green_led_on();
void green_oed_off();


void change_run_control(int);
void change_led_control(int);

void start_led(void);
void stop_led();
void start_usr();
void stop_usr();
#endif

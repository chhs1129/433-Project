//display.h
//Module to spawn a separate thread to display the values that returned by POTreader
//the POTreader return value will be showed on the beaglebone green's
//14-segment display
#ifndef _LED_H_
#define _LED_H_

#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define I2C_BUS_PATH "/sys/devices/platform/bone_capemgr/slots"
#define I2C_VIRTUAL_CAPE "BB-I2C1"
#define I2C_DEVICE_ADDRESS 0x20

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"

#define LED_LEFT_GPIO 61
#define LED_LEFT_DIR_PATH "/sys/class/gpio/gpio61/direction"
#define LED_LEFT_VAL_PATH "/sys/class/gpio/gpio61/value"

#define LED_RIGHT_GPIO 44
#define LED_RIGHT_DIR_PATH "/sys/class/gpio/gpio44/direction"
#define LED_RIGHT_VAL_PATH "/sys/class/gpio/gpio44/value"

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define LED_LOWER 0x14
#define LED_UPPER 0x15

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"


#define LED_OFF_VAL 0x00



//init function
void led_init(void);
//set the number that needs to be displayed
void led_setDisplayNum(int displayValue);
//clean up function
void led_cleanup(void);
void led_off(void);
#endif
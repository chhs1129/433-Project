// set the I2C cape and check che readings of x,y and z axis.
// assume gravity is 15000, this is calculated by putting my BBG on a horizontal
// table and the check the y value. 
#ifndef ACC_H
#define ACC_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <pthread.h>

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_ACCELEROMETER_ADDRESS 0x1C
#define I2C_BUS_PATH "/sys/devices/platform/bone_capemgr/slots"
#define I2C_VIRTUAL_CAPE "BB-I2C1"
#define I2C_readBits 7
#define CTRL_REG1 0x2A
#define gravity 15000
#define REG_XMSB 1
#define REG_XLSB 2
#define REG_YMSB 3
#define REG_YLSB 4
#define REG_ZMSB 5
#define REG_ZLSB 6

void acc_init(void);
void acc_cleanup(void);

#endif

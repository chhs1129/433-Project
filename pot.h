//POTreader.h
//Module to read A2D raedings and use Piecewise function to filter those readings,
//and then return filted values
#ifndef _POT_H_
#define _POT_H_

#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define A2D_FILE_VOLTAGE0  "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define CAPE_FILE "/sys/devices/platform/bone_capemgr/slots"
#define A2D_VIRTUAL_CAPE "BB-ADC"

//piecewise variables
#define PIECEWISE_NUM_POINTS 10
//piecwise data points

//load the virtual cape for a2d
void POT_init();
//clean up function
void POT_cleanup();
//get capture number
int POT_getNum();
//get current reading
int POT_getReading();
//set current POT number
void POT_setNum();
#endif
//spawn a new thread
//allow user use joystick
// joystick up = increase volume by 5
// joystick down = decrease volume by 5
// joystick right = increase tempo by 5
// joystick left = decrease tempo by 5
// joystick in = change rock mode 

#ifndef JOYSTICK_CONTROLER_H
#define JOYSTICK_CONTROLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"

#define GPIO_JOYSTICK_UP 26
#define JOYSTICK_UP_VALUE "/sys/class/gpio/gpio26/value"

#define GPIO_JOYSTICK_DOWN 46
#define JOYSTICK_DOWN_VALUE "/sys/class/gpio/gpio46/value"

#define GPIO_JOYSTICK_LEFT 65
#define JOYSTICK_LEFT_VALUE "/sys/class/gpio/gpio65/value"

#define GPIO_JOYSTICK_RIGHT 47
#define JOYSTICK_RIGHT_VALUE "/sys/class/gpio/gpio47/value"

#define GPIO_JOYSTICK_IN 27
#define JOYSTICK_IN_VALUE "/sys/class/gpio/gpio27/value"


void joystick_init(void);
void joystick_cleanup();
void sleep100ms(void);
#endif
#ifndef _LED_H_
#define _LED_H_


void export_gpio(int);
void heartbeat_led_start();
void heartbeat_led();
void change_direction();
void change_direction_led();
void green_led_on();
void green_oed_off();
void usr0(int);
void usr1(int);
void usr2(int);
void usr3(int);
void led_processing();
void change_run_control(int);
void change_led_control(int);
void led_init();
void start_led();
void stop_led();
void start_usr();
void stop_usr();
#endif

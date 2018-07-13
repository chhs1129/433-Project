#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpio.h"


#define EXPORT "/sys/class/gpio/export"
#define WRITE_PATH "w"
#define EXPORT_ERROR "Error: UNable to open export file.\n"

void export_gpio(int gpio_number){
	FILE *pfile = fopen (EXPORT, WRITE_PATH);
	if (pfile == NULL){
		printf (EXPORT_ERROR);
		exit(1);
	}
	fprintf(pfile, "%d", gpio_number);
	fclose(pfile);
}

void gpio_init(){
    export_gpio(26);
	export_gpio(47);
	export_gpio(46);
	export_gpio(65);
	export_gpio(27);
}
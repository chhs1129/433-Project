
all:
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror display.c udp.c streamer.c pot.c joystickController.c leds.c -o test -pthread
	
clean:
	rm test

all: beatbox wav node

beatbox:
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L  audioSetter.c accelerometerControler.c audioMixer.c joystickControler.c udp.c main.c -o beatbox -L$(HOME)/cmpt433/public/asound_lib_BBB -lpthread -lasound
	cp beatbox $(HOME)/cmpt433/public/myApps/

wav:
	mkdir -p $(HOME)/cmpt433/public/myApps/beatbox-wav-files/
	cp -R beatbox-wav-files/* $(HOME)/cmpt433/public/myApps/beatbox-wav-files/

node:
	mkdir -p $(HOME)/cmpt433/public/myApps/beatbox-server-copy/
	cp -R beatbox-server/* $(HOME)/cmpt433/public/myApps/beatbox-server-copy/	

clean:
	rm beatbox
	rm -R $(HOME)/cmpt433/public/myApps/beatbox-wav-files
	rm -R $(HOME)/cmpt433/public/myApps/beatbox-server-copy
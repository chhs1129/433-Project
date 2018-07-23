//spawn a new thread
//allow user change the sound settings
//for example: control the sound files , create rock modes, change rock modes, add a single sound,

#ifndef AUDIO_SETTER_H
#define AUDIO_SETTER_H

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define AUDIO_BASEDRUM "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define AUDIO_HIHAT "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"
#define AUDIO_SNARE "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav"

#define beatNum 8

void audioSetter_init(void);
void audioSetter_cleanup(void);
void audioSetter_changeRockMode();
void audioSetter_addSingleSound(int);
void audioSetter_setRockMode(int);
int audioSetter_getRockMode(void);
#endif
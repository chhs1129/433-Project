#include "audioSetter.h"
#include "audioMixer.h"
static wavedata_t baseDrum;
static wavedata_t hiHat;
static wavedata_t snare;
static pthread_t setterThreadID;
static int rockMode=0;

static void* setterThread(void *arg);
static void noDrumBeat(void);
static void rock1(void);
static void rock2(void);


void audioSetter_init(){
    //printf("Start setter_init\n");
    AudioMixer_readWaveFileIntoMemory(AUDIO_BASEDRUM,&baseDrum);
    AudioMixer_readWaveFileIntoMemory(AUDIO_HIHAT,&hiHat);
    AudioMixer_readWaveFileIntoMemory(AUDIO_SNARE,&snare);
    //AudioMixer_queueSound(&hiHat);
    pthread_create(&setterThreadID,NULL,setterThread,NULL);
}

void audioSetter_addSingleSound(int newSound){
    if(newSound==0){
        AudioMixer_queueSound(&baseDrum);
    }
    else if(newSound==1){
        AudioMixer_queueSound(&hiHat);
    }
    else{
        AudioMixer_queueSound(&snare);
    }
}
static void* setterThread(void *arg){
    while(1){
        int currentMode=audioSetter_getRockMode();
        if(currentMode==0){            
            noDrumBeat();
        }
        else if(currentMode==1){
            rock1();
        }
        else if(currentMode==2){
            rock2();
        }
    }
    return NULL;
}

void audioSetter_changeRockMode(){
    if(rockMode<2){
        rockMode++;
    }
    else{
        rockMode=0;
    }
}
void audioSetter_setRockMode(int newMode){
    rockMode=newMode;
}
int audioSetter_getRockMode(){
    return rockMode;
}
void audioSetter_cleanup(){
    //printf("audio_setter cleanup\n");
    AudioMixer_freeWaveFileData(&baseDrum);
	AudioMixer_freeWaveFileData(&hiHat);
	AudioMixer_freeWaveFileData(&snare);
    pthread_join(setterThreadID, NULL);	
}



static void noDrumBeat(){
    for(int i=0;i<beatNum;i++){
        sleepForTempo();
    }
}

static void rock1(){
    for(int i=0;i<beatNum;i++){
        //printf("\n*************************number %d quese*****************\n",i);
        AudioMixer_queueSound(&hiHat);
        //printf("   queued hihat\n");
        if(i==0||i==4){
            AudioMixer_queueSound(&baseDrum);
          //  printf("   queued base\n");
        }
        if(i==2||i==6){
            AudioMixer_queueSound(&snare);
           // printf("   queued snare\n");
        }
        sleepForTempo();
    }
}

static void rock2(){
    for(int i=0;i<beatNum;i++){
        AudioMixer_queueSound(&snare);

        if(i==2||i==5||i==4){
            AudioMixer_queueSound(&baseDrum);
        }
        if(i==1||i==6||i==7){
            AudioMixer_queueSound(&hiHat);
        }
        sleepForTempo();
    }
}



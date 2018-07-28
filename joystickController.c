#include "joystickController.h"
#include "pot.h"

static void writeFile(char*,int);
static int readFile(char*);
static pthread_t joystickThreadID;
static void* joystickThread(void *arg);
static void moveJoystick(void);

static void* joystickThread(void *arg){
    while(1){
        moveJoystick();
    }
    return NULL;
}

void joystick_init(){
    writeFile(GPIO_EXPORT_PATH,GPIO_JOYSTICK_DOWN);
    writeFile(GPIO_EXPORT_PATH,GPIO_JOYSTICK_UP);
    writeFile(GPIO_EXPORT_PATH,GPIO_JOYSTICK_LEFT);
    writeFile(GPIO_EXPORT_PATH,GPIO_JOYSTICK_RIGHT);
    writeFile(GPIO_EXPORT_PATH,GPIO_JOYSTICK_IN);
    writeFile(JOYSTICK_UP_VALUE,1);
    writeFile(JOYSTICK_DOWN_VALUE,1);
    writeFile(JOYSTICK_LEFT_VALUE,1);
    writeFile(JOYSTICK_RIGHT_VALUE,1);
    writeFile(JOYSTICK_IN_VALUE,1);
    pthread_create(&joystickThreadID,NULL,&joystickThread,NULL);
}
void joystick_cleanup(){
    pthread_detach(joystickThreadID);
}

void sleep100ms(){
    long seconds = 0;
	long nanoseconds = 100000000;
	struct timespec delay = {seconds, nanoseconds};
	nanosleep(&delay, (struct timespec *) NULL);
}
static void writeFile(char *fName,int value){
    FILE *pfile = fopen(fName, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}
	fprintf(pfile, "%d", value);
	fclose(pfile);
}
static int readFile(char *fName){
    FILE *pfile = fopen(fName,"r");
    if (pfile == NULL){
		printf("ERROR: Unable to open file (%s) for read\n", fName);
		exit(-1);
	}
    int val;
    fscanf(pfile,"%d",&val);
    fclose(pfile);
    return val;
}//joystick:  0 = pressed, 1 = unpressed


static void moveJoystick(){
    if(readFile(JOYSTICK_UP_VALUE)==0){
        while(1){
            if(readFile(JOYSTICK_UP_VALUE)==1){
                POT_setNum();
                sleep100ms();
                break;
            }
        }
    }
    else if(readFile(JOYSTICK_DOWN_VALUE)==0){
        while(1){
            if(readFile(JOYSTICK_DOWN_VALUE)==1){
                POT_setNum();
                sleep100ms();
                break;
            }
        }
    }
    else if(readFile(JOYSTICK_LEFT_VALUE)==0){
        while(1){
            if(readFile(JOYSTICK_LEFT_VALUE)==1){
                POT_setNum();
                sleep100ms();
                break;
            }
        }
    }
    else if(readFile(JOYSTICK_RIGHT_VALUE)==0){
        while(1){
            if(readFile(JOYSTICK_RIGHT_VALUE)==1){
                POT_setNum();
                sleep100ms();
                break;
            }
        }
    }
    else if(readFile(JOYSTICK_IN_VALUE)==0){
        while(1){
            if(readFile(JOYSTICK_IN_VALUE)==1){
                POT_setNum();
                sleep100ms();
                break;
            }
        }
    }
}//return the direction of joystick


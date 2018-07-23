#include "pot.h"


static int PIECWISE_A2Dreading[] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4100};
static int PIECWISE_num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//function that will sleep 500ms
static void sleep500ms();
//get the upper and lower bond of the current A2D reading
static int getInterval(int);
//return the a2d value
static int getA2Dreading();
//use piecewise function to get capture number
static int PWLfunc();
static void *POTthread();

static pthread_t POTid;

static int captureNum=1;
static int currentNum;
int getA2Dreading(){
	// Open file
	FILE *f = fopen(A2D_FILE_VOLTAGE0, "r");
	if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("try:   echo BB-ADC > /sys/devices/platform/bone_capemgr/slots\n");
		exit(-1);
	}

	// Get reading
	int a2dReading = 0;
	int itemsRead = fscanf(f, "%d", &a2dReading);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);
	return a2dReading;
}
static void sleep500ms(){
	long seconds = 0;
	long nanoseconds = 500000000;
	struct timespec delay = {seconds, nanoseconds};
	nanosleep(&delay, (struct timespec *) NULL);
}

static void *POTthread(){
	while(1){
        currentNum=1+PWLfunc();
    }
    return 0;
}

int POT_getReading(){
	return currentNum;
}
void POT_setNum(){
	captureNum=currentNum;
}
int POT_getNum(){
	return captureNum;
}

void POT_init(){
    FILE *pfile = fopen(CAPE_FILE, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}
	fprintf(pfile, "%s", A2D_VIRTUAL_CAPE);
	fclose(pfile);
	//wait for enable the virtual cape
	sleep500ms();
	pthread_create(&POTid, NULL, &POTthread, NULL);
}

void POT_cleanup(){
	pthread_join(POTid, NULL);
}

static int getInterval(int value){
    for(int i=0;i<PIECEWISE_NUM_POINTS-1;i++){
        if (value>PIECWISE_A2Dreading[i] && value<PIECWISE_A2Dreading[i+1]){
            return i;
        }
    }
    return 0;
}

//return the value after doing PWL
static int PWLfunc(){
    int A2Dvalue = getA2Dreading();
    //get the range that a2dvalue fits
    if(A2Dvalue==0){
        return 0;
    }
    int interval=getInterval(A2Dvalue);

    //piecewise function
    int x1=PIECWISE_A2Dreading[interval];
    int x2=PIECWISE_A2Dreading[interval+1];
    int y1=PIECWISE_num[interval];
    int y2=PIECWISE_num[interval+1];
    double result=(((double)A2Dvalue-x1)/(x2-x1))*(y2-y1)+y1;
    return result;
}

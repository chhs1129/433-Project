#include "accelerometerControler.h"
#include "audioSetter.h"

static int16_t x;
static int16_t y;
static int16_t z;
int xstart=0;
int ystart=0;
int zstart=0;
static pthread_t accThreadID;
char buff[I2C_readBits];
int i2cFileDesc;

static int initI2cBus(char*, int);
static void writeStringToFile(char *filePath, char *stringToWrite);
static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char val);
static void* accThread(void *arg);
static void sleep100ms(void);

static void sleep100ms(){
    long seconds = 0;
	long nanoseconds = 100000000;
	struct timespec delay = {seconds, nanoseconds};
	nanosleep(&delay, (struct timespec *) NULL);
}

static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char val){
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = val;
	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("I2C: Unable to write i2c register.");
		exit(1);
	}
}


static int initI2cBus(char* bus, int address){
	//Enable the bus
	writeStringToFile(I2C_BUS_PATH, I2C_VIRTUAL_CAPE);

	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C: Unable to open bus for read/write (%s)\n",	bus);
		perror("Error is:");
		exit(1);
	}
	
	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("I2C: Unable to set I2C device to slave address.");
		exit(1);
	}
	return i2cFileDesc;
}

static void writeStringToFile(char *filePath, char *stringToWrite) {
	FILE *pfile = fopen(filePath, "w");
	if (pfile == NULL) {
		printf("I2CERROR: Unable to open export file.\n");
		exit(1);
	}
	fprintf(pfile, "%s", stringToWrite);
	fclose(pfile);
}

void acc_init(){
	i2cFileDesc=initI2cBus(I2CDRV_LINUX_BUS1,I2C_ACCELEROMETER_ADDRESS);
	//CTRL_REG1 set to active mode
	writeI2cReg(i2cFileDesc, CTRL_REG1, 0x01);
	pthread_create(&accThreadID,NULL,accThread,NULL);
}

void acc_cleanup(){
	pthread_join(accThreadID,NULL);
}

static void* accThread(void *arg){
    while(1){
        read(i2cFileDesc,buff,I2C_readBits);
		xstart=1;
		ystart=1;
		zstart=1;
		x=(buff[REG_XMSB] << 8) | (buff[REG_XLSB]);
		x=x/gravity;
		y = (buff[REG_YMSB] << 8) | (buff[REG_YLSB]);
		y=y/gravity;
		z = (buff[REG_ZMSB] << 8) | (buff[REG_ZLSB]);
		z=(z/gravity)-1;
		if(x>0&&xstart){
			audioSetter_addSingleSound(0);
			xstart=0;
			sleep100ms();
		}
		else if(y>0&&ystart){
			audioSetter_addSingleSound(1);
			ystart=0;
			sleep100ms();
		}
		else if(z>0&&zstart){
			audioSetter_addSingleSound(2);
			zstart=0;	
			sleep100ms();		
		}
    }
    return NULL;
}
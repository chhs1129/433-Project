#include "display.h"
#include "udp.h"
#include "streamer.h"
#include "pot.h"
#include "joystickController.h"
#include "leds.h"
#include "button.h"
static int i2cFileDesc;

//0-9 
static int upperDisplay[10] = {0x86, 0x12, 0x0f, 0x0f, 0x8b, 0x8d, 0x8d, 0x06, 0x8f, 0x8f};
static int lowerDisplay[10] = {0xa1, 0x80, 0x31, 0xb0, 0x90, 0xb0, 0xb1, 0x80, 0xb1, 0xb0};

static bool isDisplaying;
static int NumToBeDisplay;

static pthread_mutex_t displayLock;
static pthread_mutex_t setLock;
static pthread_t id;

//init the I2c Bus
static void initI2cBus(char* bus, int address);
//function for write registor
static void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char val);
//function to sleep 5ms
static void sleep5ms();
//function to write a string to a file
static void writeStringToFile(char *filePath, char *stringToWrite);
//function to write a int to a file
static void writeIntToFile(char *filePath, int intToWrite);
static void *displayInt();

static void initI2cBus(char* bus, int address){
	// Export GPIO pins
	writeIntToFile(GPIO_EXPORT_PATH, LED_LEFT_GPIO);
	writeIntToFile(GPIO_EXPORT_PATH, LED_RIGHT_GPIO);
	// echo "out" to direction
	writeStringToFile(LED_LEFT_DIR_PATH, "out");
	writeStringToFile(LED_RIGHT_DIR_PATH, "out");
	// Turn on leds
	writeIntToFile(LED_LEFT_VAL_PATH, 1);
	writeIntToFile(LED_RIGHT_VAL_PATH, 1);
	//Enable the bus
	writeStringToFile(I2C_BUS_PATH, I2C_VIRTUAL_CAPE);

	i2cFileDesc = open(bus, O_RDWR);
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
	//write 0x00 to registors
	writeI2cReg(i2cFileDesc, REG_DIRA, LED_OFF_VAL);
	writeI2cReg(i2cFileDesc, REG_DIRB, LED_OFF_VAL);
	//initalize upper&lower led by write 0x00
	writeI2cReg(i2cFileDesc, LED_UPPER, LED_OFF_VAL);
	writeI2cReg(i2cFileDesc, LED_LOWER, LED_OFF_VAL);
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
void led_off(){
	writeIntToFile(LED_RIGHT_VAL_PATH, 0);
	writeIntToFile(LED_LEFT_VAL_PATH, 0);
	// Cleanup I2C access;
	close(i2cFileDesc);
}
void led_init(){
	initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
	isDisplaying = true;
	pthread_mutex_init(&displayLock, NULL);
	pthread_mutex_init(&setLock, NULL);
	pthread_create(&id, NULL, &displayInt, NULL);
}

// void led_setDisplayNum(int num) {
// 	pthread_mutex_lock(&setLock);
// 	{
// 		NumToBeDisplay = POT_getNum();
// 	}
// 	pthread_mutex_unlock(&setLock);
// }

static void *displayInt() {
	int left_digit = 0; 
	int right_digit = 0;
	while(1) {
		NumToBeDisplay=POT_getReading();
		// pthread_mutex_lock(&displayLock);
		// {		
			if(NumToBeDisplay > 99) {
				NumToBeDisplay = 99;
			}
			if(NumToBeDisplay < 0) {
				NumToBeDisplay = 0;
			}
			// 01 will be showed if the number = 1
			if(NumToBeDisplay > 9) {
				left_digit = NumToBeDisplay/10;
				right_digit = NumToBeDisplay % 10;
			} 			
			else {
				left_digit = 0;
				right_digit = NumToBeDisplay;
			}
			//turn off both
			writeIntToFile(LED_RIGHT_VAL_PATH, 0);
			writeIntToFile(LED_LEFT_VAL_PATH, 0);
			//write left
			if(left_digit == 0) {
				writeI2cReg(i2cFileDesc, LED_UPPER, LED_OFF_VAL);
				writeI2cReg(i2cFileDesc, LED_LOWER, LED_OFF_VAL);
			} 
			else {
				writeI2cReg(i2cFileDesc, LED_UPPER, upperDisplay[left_digit]);
				writeI2cReg(i2cFileDesc, LED_LOWER, lowerDisplay[left_digit]);			
			}

			writeIntToFile(LED_LEFT_VAL_PATH, 1);
			sleep5ms();
			//turn off both
			writeIntToFile(LED_RIGHT_VAL_PATH, 0);
			writeIntToFile(LED_LEFT_VAL_PATH, 0);
			// write right
			writeI2cReg(i2cFileDesc, LED_UPPER, LED_OFF_VAL);
			writeI2cReg(i2cFileDesc, LED_LOWER, LED_OFF_VAL);
			writeI2cReg(i2cFileDesc, LED_UPPER, upperDisplay[right_digit]);
			writeI2cReg(i2cFileDesc, LED_LOWER, lowerDisplay[right_digit]);
		
			writeIntToFile(LED_RIGHT_VAL_PATH, 1);
			sleep5ms();
		// }
		// pthread_mutex_unlock(&displayLock);	
	}
	return 0;
}

void led_cleanup(){
	pthread_detach(id);
	isDisplaying = false;
	pthread_mutex_destroy(&displayLock);
	pthread_mutex_destroy(&setLock);
	pthread_exit(NULL);
}

static void sleep5ms(){
	long seconds = 0;
	long nanoseconds = 500000;
	struct timespec delay = {seconds, nanoseconds};
	nanosleep(&delay, (struct timespec *) NULL);
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

static void writeIntToFile(char *filePath,int intToWrite){
    FILE *pfile = fopen(filePath, "w");
	if (pfile == NULL) {
		printf("ERROR: Unable to open export file.\n");
		exit(1);
	}
	fprintf(pfile, "%d", intToWrite);
	fclose(pfile);
}

int main(){
	led_init();
	 udp_init();
	 streamer_init();
	POT_init();
	joystick_init();
	 heartBeatLed_init();
	userLeds_init();
	    button_init();

	userLeds_cleanup();
	 heartBeatLed_cleanup();
	joystick_cleanup();
	POT_cleanup();
	 streamer_cleanup();
	udp_cleanup();
	led_cleanup();
	return 0;
}
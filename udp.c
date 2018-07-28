#include "udp.h"
#include "display.h"
#include "streamer.h"
#include "pot.h"
#include "leds.h"
#include "button.h"

#define PORT 12345
#define PACKET_LEN 1500

static pthread_t udpThreadID;

static int socketid;
struct sockaddr_in socketAddress;
static void* udpThread();
struct sysinfo info;
static int captureNum=0;
static int totalCaptures=0;
void udp_init(){
    memset(&socketAddress,0,sizeof(socketAddress));
    // Internet address family IPV4
    socketAddress.sin_family = AF_INET;
    //port
    socketAddress.sin_port = htons(PORT);
    //any incoming interface
    socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    socketid = socket(PF_INET,SOCK_DGRAM, 0);
    if(socketid == -1){
        printf("network:Failed to create socket\n");
        exit(1);
    }
    
    if(bind(socketid, (struct sockaddr *) &socketAddress,sizeof(socketAddress))<0){
        printf("network:Failed to bind socket\n");
        exit(1);
    }   
    pthread_create(&udpThreadID,NULL,&udpThread,NULL);
}

static void *udpThread(){
    char recvBuffer[PACKET_LEN];
    char sendBuffer[PACKET_LEN];
    change_button_direction();
    while(1){
    //get # bytes of received message

        captureNum=POT_getNum();
        unsigned int socketAddress_len = sizeof(socketAddress);
        //used to check if need to send array
       // bool array_flag=0;
        memset(recvBuffer,0,strlen(recvBuffer));
        int recvMsgSize=recvfrom(socketid,recvBuffer,PACKET_LEN,0,(struct sockaddr *) &socketAddress, &socketAddress_len);
        if(recvMsgSize==-1){
            printf("network:Failed to receive message\n");
            exit(1);
        }
        if(button_thread()){
            char cmdToCapture[200];
            int i=totalCaptures+1;
            int j=i+captureNum;
            change_heartBeatLed_flag(1);
            for(;i<j;i++){
                sprintf(cmdToCapture,"wget http://192.168.7.2:8080/?action=snapshot -O controller-server/public/captures/output_%d.jpg",i);
                system(cmdToCapture);
                totalCaptures++;
            }
            change_heartBeatLed_flag(0);
            printf("capture success\n");
        }
        if(strcmp(recvBuffer, "clean\n") == 0){
            system("cd controller-server/public/captures && rm *.jpg");
            printf("cleaned folder\n");
        }
        else if(strcmp(recvBuffer, "capture\n") == 0){  
            char cmdToCapture[200];
            int i=totalCaptures+1;
            int j=i+captureNum;
            change_heartBeatLed_flag(1);
            for(;i<j;i++){
                sprintf(cmdToCapture,"wget http://192.168.7.2:8080/?action=snapshot -O controller-server/public/captures/output_%d.jpg",i);
                system(cmdToCapture);
                totalCaptures++;
            }
            change_heartBeatLed_flag(0);
            printf("capture success\n");
        }
        else if(strcmp(recvBuffer, "train\n") == 0){  
            //start to train 
            change_userLed_flag(1);
            //finish the train
            //change_userLed_flag(0);
        }
        else if(strcmp(recvBuffer, "test\n") == 0){  
            //"test 1.jpg"
            //predict the 1.jpg

        }
        else{          
            sysinfo(&info);
            sprintf(sendBuffer, "%ld,%d,%d",info.uptime,captureNum,totalCaptures);
            socketAddress_len = sizeof(socketAddress);
            sendto(socketid, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*) &socketAddress, socketAddress_len);
        }                    
        //socketAddress_len = sizeof(socketAddress);
        //sendto(socketid, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*) &socketAddress, socketAddress_len);
    }
    return 0;
}

void udp_cleanup(){
    pthread_detach(udpThreadID);
    close(socketid);
}

// static void termination(){
//     isCont=0;
//     close(socketudpThreadID);
//     exit(0);
// }
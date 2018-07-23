#include "udp.h"
#include "audioSetter.h"
#include "audioMixer.h"
#include "joystickControler.h"

#define PORT 12345
#define PACKET_LEN 1500

static pthread_t udpThreadID;

static int socketid;
struct sockaddr_in socketAddress;
static void* udpThread();
static bool isCont;
struct sysinfo info;


void udp_init(){
    isCont=1;
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
    while(1){
    //get # bytes of received message

        unsigned int socketAddress_len = sizeof(socketAddress);
        //used to check if need to send array
       // bool array_flag=0;
        memset(recvBuffer,0,strlen(recvBuffer));
        int recvMsgSize=recvfrom(socketid,recvBuffer,PACKET_LEN,0,(struct sockaddr *) &socketAddress, &socketAddress_len);
        if(recvMsgSize==-1){
            printf("network:Failed to receive message\n");
            exit(1);
        }

        //recvBuffer[recvMsgSize-1]=0;
        //printf("%s\n",recvBuffer);
        //printf("Message Recieved: %s, Message Length: %d\n\n", recvBuffer, recvMsgSize);
        if(strcmp(recvBuffer, "volume up") == 0){
            AudioMixer_volumeUp();
            //sprintf(sendBuffer, "UDP CONTROL: volume up\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "volume down") == 0){  
            AudioMixer_volumeDown();
            //sprintf(sendBuffer, "UDP CONTROL: volume down\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "tempo up") == 0){  
            AudioMixer_tempoUp();
            //sprintf(sendBuffer, "UDP CONTROL: tempo up\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "tempo down") == 0){  
            AudioMixer_tempoDown();
            //sprintf(sendBuffer, "UDP CONTROL: tempo down\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "rock 0") == 0){  
            audioSetter_setRockMode(0);
            //sprintf(sendBuffer, "UDP CONTROL: current mode is no sound mode\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "rock 1") == 0){  
            audioSetter_setRockMode(1);
            //sprintf(sendBuffer, "UDP CONTROL: current mode is rock1\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "rock 2") == 0){  
            audioSetter_setRockMode(2);
            //sprintf(sendBuffer, "UDP CONTROL: current mode is rock2\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "base") == 0){  
            audioSetter_addSingleSound(0);
            //sprintf(sendBuffer, "UDP CONTROL: play base\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "hihat") == 0){  
            audioSetter_addSingleSound(1);
            //sprintf(sendBuffer, "UDP CONTROL: play hihat\n");
            sleep100ms();
        }
        else if(strcmp(recvBuffer, "snare") == 0){  
            audioSetter_addSingleSound(2);
            //sprintf(sendBuffer, "UDP CONTROL: play snare\n");
            sleep100ms();
        }
        else{          
            sysinfo(&info);
            sprintf(sendBuffer, "%ld,%d,%d,%d",info.uptime,AudioMixer_getVolume(),AudioMixer_getTempo(),audioSetter_getRockMode());
            socketAddress_len = sizeof(socketAddress);
            sendto(socketid, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*) &socketAddress, socketAddress_len);
            sleep100ms();
        }                    
        //socketAddress_len = sizeof(socketAddress);
        //sendto(socketid, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr*) &socketAddress, socketAddress_len);
    }
    return 0;
}

void udp_cleanup(){
    pthread_join(udpThreadID,NULL);
    close(socketid);
}

// static void termination(){
//     isCont=0;
//     close(socketudpThreadID);
//     exit(0);
// }
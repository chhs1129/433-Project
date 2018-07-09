#include "udp.h"
#include "display.h"

#define PORT 12345
#define PACKET_LEN 1500

static pthread_t udpThreadID;

static int socketid;
struct sockaddr_in socketAddress;
static void* udpThread();
static bool isCont;
struct sysinfo info;
static int captureNum=1;

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
    //char sendBuffer[PACKET_LEN];
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

        printf("Message Recieved: %s, Message Length: %d\n\n", recvBuffer, recvMsgSize);
        if(strncmp(recvBuffer, "set ", 4) == 0){
            //set how many photo took per once.
            char *pch;
            pch = strstr(recvBuffer," ");
            int num = atoi(pch);
            captureNum=num;
            //display the how many photo to capture.
            led_setDisplayNum(num);
            //sleep100ms();
        }
        else if(strcmp(recvBuffer, "clean\n") == 0){
            system("cd captures && rm *.jpg");
            printf("cleaned folder\n");
        }
        else if(strcmp(recvBuffer, "capture\n") == 0){  
            //sleep100ms();
            char cmdToCapture[200];
            for(int i=1;i<captureNum+1;i++){
                sprintf(cmdToCapture,"wget http://192.168.7.2:8080/?action=snapshot -O captures/output_%d.jpg",i);
                system(cmdToCapture);
            }
            printf("capture success\n");
        }
        else if(strcmp(recvBuffer, "train") == 0){  
            //start to train 

        }
        else if(strcmp(recvBuffer, "test ") == 0){  
            //"test 1.jpg"
            //predict the 1.jpg

        }
        else{          
            printf("else\n");
            //
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
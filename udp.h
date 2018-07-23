//network.h
//Module to spawn a separate thread which will listen the udp packet.
//based on the udp packet received, response some information.
//allows: volume +-5 , tempo +-5, play single sound ,change rock mode
// and send BBG's uptime
#ifndef _UDP_H_
#define _UDP_H_



#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>





void udp_init(void);
void udp_cleanup(void);

#endif
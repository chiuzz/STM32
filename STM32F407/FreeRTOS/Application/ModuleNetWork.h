#ifndef __MODULENETWORK_H_
#define __MODULENETWORK_H_

typedef enum {
    staRESTART,
    staINIT,
    staSERVER,
    staCLIENT,
    staUDP,
} NETWORKSTA;

typedef enum {
    staAPCONNECTING,
    staAPCONNECTED,
    staTCPCONNECTING,
    staTCPCONNECTED,
    staLINKING,
} CTSTA;

#define APCONNECTTIME 100
#define TCPCONNECTTIME 100


extern void NetWorkDeal(void);

void ClientTest(void);
#endif



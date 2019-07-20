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
#define TCPCONNECTTIME 10

extern CTSTA ctsta;
extern void NetWorkDeal(void);

void ClientTest(void);
#endif



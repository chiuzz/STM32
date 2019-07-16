#ifndef __COMMON_H
#define __COMMON_H
#include "includes.h"

typedef enum {
    STA=1,
    AP,
    APSTA,
} WIFIMOD;

typedef enum {
    SERVER,
    CLIENT,
    UDP,
} LINKTYPE;

typedef enum {
    REMOTE_CMD_NONE=0,
    LED_RED_OFF,
    LED_RED_ON,
    LED_GREEN_OFF,
    LED_GREEN_ON,
    LED_RED_BREATH,
    LED_GREEN_BREATH,
} REMOTECMDENUM;

typedef struct remotecmdstu {
    u16             cmdlength;
    REMOTECMDENUM   cmd;
} REMOTECMDSTU;

typedef struct networkstu {
    WIFIMOD wifimod;
    u8 ssid[32];
    u8 mac[32];
    u8 channel;
    s16 rssi;			//�ź�ǿ��

    u8 stat;			//����״̬
    u8 link_id;			//����������ID
    u8 type[5];			//TCP��UDP����
    u8 remote_ip[16];	//Զ��IP
    u32 remote_port;	//Զ�˶˿ں�
    u32 local_port;		//���ض˿ں�
    u8 tetype;			//0--ESP8266��client  1--ESP8266��server
    u8 cipmux;			//���ӷ�ʽ  0--������  1--������
    REMOTECMDSTU CmdStu;//Զ������ṹ
} NETWORKSTU;

BOOL string_cmp(u8 *ch,u8 *buf);

extern NETWORKSTU NetWorkData;

extern BOOL AT_Cmd_Send(u8 *cmd);
extern void RemoteCmdScan(void);
extern void string_deal(u8 *buf);
extern void NetWorkInit(void);

extern WIFIMOD GetWIFImod(void);
extern void SetWIFImod(WIFIMOD mod);

extern BOOL GetAPInfo(void);
extern void JoinAP(u8 *ssid,u8 *psword);

extern u8 GetCipMux(void);
extern void SetCipMux(u8 mod);

extern NETWORKSTU *GetTcpSta(void);
extern void StartTcpConnect(u8 link_id,u8 *type,u8 *remote_ip,u32 remote_port);

void NetWorkArgGet(u8 *arg,u8 *buf);
BOOL AT_Info_Get(u8 *cmd);
BOOL AT_Arg_Get(u8 *arg,u8 *buf);
void myatoi(u8 *str,s32 *num);
void RemoteCmdTransform(u8 *cmdbuf,REMOTECMDENUM *cmd);
void RemoteCmdArgGet(u8 *arg,u8 *buf);
#endif



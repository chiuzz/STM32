
#ifndef __MSG_QUEUE_H_
#define __MSG_QUEUE_H_

#include "ucos_ii.h"
#include "os_cpu.h"
// #include "common.h"

/*--------���ö��в���--------*/
#define		N_MESSAGES		32									//������Ϣ���г���
//typedef int (*fun_ptr)(int,int);
typedef void (*MsgNotiflyPtr)(void*, INT8U, INT16U , INT16U , void*);

typedef struct __Msg__
{
	INT8U MsgId;
	INT16U lParam;
	INT16U wParam;
	void*  pBuf;
}MSG, *P_MSG;

typedef struct __Msg_Queue_Data__
{
	void		*MsgGrp[N_MESSAGES];								//������Ϣָ����
	OS_EVENT	*Handler_Q;											//�����¼����ƿ�
	unsigned char	err;	//���з��ش�������	
    void* pArg;
	//publish virtual
	//void (*MsgNotifly)(void *p);							//�ⲿʵ�ֻص�����	
	void (*MsgNotifly)(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);							//�ⲿʵ�ֻص�����	
}MSGQUEUEDATA, *P_MSGQUEUEDATA;

typedef struct __Msg_Queue__
{
	P_MSGQUEUEDATA pData;
	INT8U MsgId;
	//publish
	INT8U (*push_back)(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);						//�ⲿʹ�ú���
	void (*pend)(P_MSGQUEUEDATA pData);														  //����ʹ���ɷ���Ϣ
	void (*accept)(P_MSGQUEUEDATA pMsg);                          //�ж�ʹ���ɷ���Ϣ
}MSGQUEUE, *P_MSGQUEUE;
	
//extern P_MSGQUEUE MsgQueueCreate(INT8U MsgId, MsgNotiflyPtr func);
extern P_MSGQUEUE MsgQueueCreate(INT8U MsgId , MsgNotiflyPtr func, void* pArg);
extern INT8U MsgQueueFree(MSGQUEUE *pMsg);

static INT8U MsgQueueInit(MSGQUEUE *pMsg);
static INT8U MsgQueueDel(MSGQUEUE *pMsg);
static INT8U MsgPushBack(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void MsgPend(P_MSGQUEUEDATA pData);
static void MsgAccept(P_MSGQUEUEDATA pMsg);

#endif

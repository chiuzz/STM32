
#ifndef __MSG_QUEUE_H_
#define __MSG_QUEUE_H_

#include "includes.h"

/*--------设置队列参量--------*/
#define		N_MESSAGES		32									//定义消息队列长度
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
	OS_Q Handler_Q;											//定义事件控制块
    void* pArg;
	void (*MsgNotifly)(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);							//外部实现回调函数	
}MSGQUEUEDATA, *P_MSGQUEUEDATA;

typedef struct __Msg_Queue__
{
	P_MSGQUEUEDATA pData;
	OS_ERR (*push_back)(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);						//外部使用函数
	void (*pend)(P_MSGQUEUEDATA pData);														  //任务使用派发消息
}MSGQUEUE, *P_MSGQUEUE;
	
//extern P_MSGQUEUE MsgQueueCreate(INT8U MsgId, MsgNotiflyPtr func);
extern P_MSGQUEUE MsgQueueCreate(MsgNotiflyPtr func, void* pArg);
extern INT8U MsgQueueFree(MSGQUEUE *pMsg);

static OS_ERR MsgQueueInit(MSGQUEUE *pMsg);
static OS_ERR MsgQueueDel(MSGQUEUE *pMsg);
static OS_ERR MsgPushBack(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void MsgPend(P_MSGQUEUEDATA pData);

#endif

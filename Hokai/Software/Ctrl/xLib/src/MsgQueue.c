#include "MsgQueue.h"
#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

OS_ERR MsgPushBack(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf)
{
    OS_ERR ret;
    P_MSG pMsg = NULL;
    //	printf("\r\n MsgPushBack!!\r\n");
    pMsg = (P_MSG)mymalloc(SRAMIN,sizeof(MSG)); //需要换个内存申请函数
    if(pMsg != NULL){
        pMsg->MsgId = MsgId;
        pMsg->lParam = lParam;
        pMsg->wParam = wParam;
        pMsg->pBuf = pBuf;
        OSQPost((OS_Q*		)&(pData->Handler_Q),		
                (void*		)pMsg,
                (OS_MSG_SIZE)N_MESSAGES,
                (OS_OPT		)OS_OPT_POST_FIFO,
                (OS_ERR*	)&ret);
        //        printf("\r\n OSQPost!!\r\n");
    }else {
       // printf("\r\n OSQPost Error!!\r\n");
    }
    return ret;
}

void MsgPend(P_MSGQUEUEDATA pData)
{
    P_MSG pKey = NULL;     
    OS_MSG_SIZE size;
    OS_ERR err; 
    while (1)
    {
        pKey=(P_MSG)OSQPend((OS_Q*		)&(pData->Handler_Q),   
                (OS_TICK		)0,
                (OS_OPT		)OS_OPT_PEND_BLOCKING,
                (OS_MSG_SIZE*	)&size,	
                (CPU_TS*		)0,
                (OS_ERR*		)&err);

        //向Touch_Q队列请求消息。等待时限为0，即无限等待下去，直到获取消息	
        if(pData->MsgNotifly != (void*)0 && pKey != NULL)
        {
            pData->MsgNotifly(pData->pArg, pKey->MsgId,  pKey->lParam,  pKey->wParam,  pKey->pBuf);
            //printf("\n GetMsg!!\n");
            myfree(SRAMIN,pKey); //需要换个内存释放函数
        }
        else if(pKey == NULL) {
          //  printf("\n GetMsg error!!\n");	
        }
    }
}


OS_ERR MsgQueueInit(MSGQUEUE *pMsg)
{
    //创建消息队列
    OS_ERR err;
    OSQCreate ((OS_Q*		)&(pMsg->pData->Handler_Q),	
            (CPU_CHAR*	)"SYSTEM MSG",	
            (OS_MSG_QTY	)N_MESSAGES,	
            (OS_ERR*	)&err);	
    pMsg->push_back = MsgPushBack;
    pMsg->pend = MsgPend;
    return err;
}

OS_ERR MsgQueueDel(MSGQUEUE *pMsg)
{
    OS_ERR ret;
    OSQDel(&(pMsg->pData->Handler_Q),OS_OPT_DEL_ALWAYS,&ret);
    return ret;
}

INT8U MsgQueueFree(MSGQUEUE *pMsg)
{
    INT8U ret = 0;	
    ret = MsgQueueDel(pMsg);
    if(pMsg->pData!=NULL)
        free(pMsg->pData);
    if(pMsg!=NULL)
        free(pMsg);
    return ret;
}

P_MSGQUEUE MsgQueueCreate(MsgNotiflyPtr func, void* pArg)
{
    P_MSGQUEUE pMsg = NULL;
    //pMsg->pData = NULL;
    //printf("MSGQUEUEDATA size = %d \r",sizeof(MSGQUEUEDATA));
    //printf("MSGQUEUE size = %d \r",sizeof(MSGQUEUE));
    pMsg = (P_MSGQUEUE)malloc(sizeof(MSGQUEUE));
    pMsg->pData = NULL;
    //printf("消息队列pMsg = %d\n",(int)pMsg);
    pMsg->pData	= (P_MSGQUEUEDATA)malloc(sizeof(MSGQUEUEDATA));	
    pMsg->pData->pArg = pArg;		//pModServer->m_pBaseData
    MsgQueueInit(pMsg);
    pMsg->pData->MsgNotifly = func;
    return pMsg;
}



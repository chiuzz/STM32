#include "MsgQueue.h"
#include <stdio.h>
#include <stdlib.h>

INT8U MsgPushBack(P_MSGQUEUEDATA pData, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf)
{
	INT8U ret = 0;
	P_MSG pMsg = NULL;
//	printf("\r\n MsgPushBack!!\r\n");
	pMsg = (P_MSG)malloc(sizeof(MSG)); //��Ҫ�����ڴ����뺯��
	if(pMsg != NULL){
		pMsg->MsgId = MsgId;
		pMsg->lParam = lParam;
		pMsg->wParam = wParam;
		pMsg->pBuf = pBuf;
		OSQPost(pData->Handler_Q, pMsg);		//������Ϣ
//        printf("\r\n OSQPost!!\r\n");
	}else {
        printf("\r\n OSQPost Error!!\r\n");
    }
	return ret;
}

void MsgPend(P_MSGQUEUEDATA pData)
{
	P_MSG pKey = NULL;     
	while (1)
   {
			pKey=(P_MSG)OSQPend(pData->Handler_Q,0,&(pData->err));				//��Touch_Q����������Ϣ���ȴ�ʱ��Ϊ0�������޵ȴ���ȥ��ֱ����ȡ��Ϣ	
			if(pData->MsgNotifly != (void*)0 && pKey != NULL)
			{
				 pData->MsgNotifly(pData->pArg, pKey->MsgId,  pKey->lParam,  pKey->wParam,  pKey->pBuf);
                 //printf("\n GetMsg!!\n");
				 free(pKey); //��Ҫ�����ڴ��ͷź���
			}
            else if(pKey == NULL) {
			    printf("\n GetMsg error!!\n");	
            }
	}
}

void MsgAccept(P_MSGQUEUEDATA pData)
{
	P_MSG pKey = NULL;     
	pKey=(P_MSG)OSQAccept(pData->Handler_Q, &(pData->err));				//��Touch_Q����������Ϣ��
	if(pData->MsgNotifly != (void*)0 && pKey != NULL)
	{
		 pData->MsgNotifly(pData->pArg, pKey->MsgId,  pKey->lParam,  pKey->wParam,  pKey->pBuf);
		 free(pKey); //��Ҫ�����ڴ��ͷź���
	}

	//printf("\r\n err:%d!!\r\n",pData->err);	
	//printf("\n GetMsg!!\n");			
}

INT8U MsgQueueInit(MSGQUEUE *pMsg)
{
    //������Ϣ����
	INT8U ret = 0;
    OS_EVENT *p = OSQCreate(&(pMsg->pData->MsgGrp[0]),N_MESSAGES);
	pMsg->pData->Handler_Q = p;
	pMsg->push_back = MsgPushBack;
	pMsg->pend = MsgPend;
	pMsg->accept = MsgAccept;
	return ret;
}

INT8U MsgQueueDel(MSGQUEUE *pMsg)
{
	INT8U ret = 0;
	OSQDel(pMsg->pData->Handler_Q,OS_DEL_ALWAYS,&ret);
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

P_MSGQUEUE MsgQueueCreate(INT8U MsgId , MsgNotiflyPtr func, void* pArg)
{
	P_MSGQUEUE pMsg = NULL;
	//pMsg->pData = NULL;
	//printf("MSGQUEUEDATA size = %d \r",sizeof(MSGQUEUEDATA));
	//printf("MSGQUEUE size = %d \r",sizeof(MSGQUEUE));
	pMsg = (P_MSGQUEUE)malloc(sizeof(MSGQUEUE));
    pMsg->pData = NULL;
    //printf("��Ϣ����pMsg = %d\n",(int)pMsg);
    pMsg->pData	= (P_MSGQUEUEDATA)malloc(sizeof(MSGQUEUEDATA));	
    pMsg->pData->pArg = pArg;
	MsgQueueInit(pMsg);
	pMsg->pData->MsgNotifly = func;
	return pMsg;
}



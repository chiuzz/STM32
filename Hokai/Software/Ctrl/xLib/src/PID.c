#include "PID.h"
#include <stdio.h>
#include <stdlib.h>

INT16U IncPIDCalc(PPIDSTRUCT pSelf, INT16U NextPoint)
{
    INT16U ret;
    INT32S iError;
    INT32S iIncPid;//��ǰ���
//    printf("NextPoint:%d ",NextPoint);
    iError = pSelf->SetPoint - NextPoint; //��������
    pSelf->m_Int+=iError;
    iIncPid = pSelf->Proportion*iError + pSelf->Integral*pSelf->m_Int;
//    printf("%d ",iIncPid);
    pSelf->PrevError = pSelf->LastError;
    pSelf->LastError = iError;
    
//    printf("iError:%d iIncPid:%d ",iError, iIncPid);
//    printf("now:%d  Target:%d\n",NextPoint,pSelf->SetPoint);
//    printf("iError:%d Proportion:%d iIncPid:%d ",iError, pSelf->Proportion,iIncPid);
    if(iIncPid>=0)
        ret = iIncPid;
    else
        ret = 0;
//    printf("Target:%d Now:%d Err:%d out:%d\n",pSelf->SetPoint, NextPoint, iError, ret);
    return ret;
}

PPIDSTRUCT CreatePidCal()
{
    PPIDSTRUCT pObj = NULL;  
    pObj = (PPIDSTRUCT)malloc(sizeof(PIDSTRUCT)); //��Ҫ�����ڴ����뺯��
    ASSERT(pObj!= NULL);
    return pObj;
}

void ResetIncPidCalc(PPIDSTRUCT pSelf, INT16U Target, INT16U P, INT16U I, INT16U D)
{
    if(pSelf == NULL)
      return;   
     pSelf->SetPoint=Target; //�趨Ŀ��
     pSelf->Proportion=P; //��������
     pSelf->Integral=I; //���ֳ���
     pSelf->Derivative=D; //΢�ֳ���
     pSelf->LastError=0;  //Error[-1]
     pSelf->PrevError=0;  //Error[-2]
     pSelf->m_Int = 0;
}
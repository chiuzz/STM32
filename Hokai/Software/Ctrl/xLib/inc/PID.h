
#ifndef __PID_H_
#define __PID_H_
#include "common.h"

typedef struct PidStruct 
{
    INT16U SetPoint; //设定目标
    INT16U Proportion; //比例常数
    INT16U Integral; //积分常数
    INT16U Derivative; //微分常数
    INT32S m_Int; //积分项
    INT32S LastError;  //Error[-1]
    INT32S PrevError;  //Error[-2]
}PIDSTRUCT,*PPIDSTRUCT;
extern PPIDSTRUCT CreatePidCal();
extern void ResetIncPidCalc(PPIDSTRUCT pSelf, INT16U Target, INT16U P, INT16U I, INT16U D);
extern INT16U IncPIDCalc(PPIDSTRUCT pSelf, INT16U NextPoint);

#endif

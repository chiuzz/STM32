#ifndef	_FLOWSENSOR_H_
#define	_FLOESENSOR_H_
#include "ucos_ii.h"
#include "stm32f10x.h"

extern bool Vent10msPrc(INT32S *pAirVentVal, INT32S *pO2VentVal, INT32S AirFlowVal, INT32S O2FlowVal);
extern void SetVtPoint();
extern INT16U GetFlowVal(INT16U Ad);
extern INT32S GetO2VtReal();
extern INT32S GetAirVtReal();
static INT32S m_O2VentVal = 0;
static INT32S m_AirVentVal = 0;
static bool m_IsPoint = FALSE;



//static bool IsVentMarkPoint(INT16U FlowVal);
//static INT16U m_LastFlowVal = 0;
//static INT8U m_TimeMark = 0;
//static INT32U m_VentVal = 0;
#endif	//_APP_H_

#include "FlowSensor.h"
#include "ModeCommon.h"

#define MAX_FLOW_POINT 15

bool Vent10msPrc(INT32S *pAirVentVal, INT32S *pO2VentVal, INT32S AirFlowVal, INT32S O2FlowVal)
{
    bool ret = m_IsPoint;
	INT16U Vt = 0;
    if(ret == TRUE)
    {
      m_IsPoint = FALSE;
      Vt = (INT16U)(m_O2VentVal/100.0);				
	  *pO2VentVal = Vt;
      Vt = (INT16U)(m_AirVentVal/100.0);				
	  *pAirVentVal = Vt;
	  m_O2VentVal = 0;
      m_AirVentVal = 0;
    }
    m_O2VentVal += O2FlowVal;
    m_AirVentVal += AirFlowVal;
    return ret;
}
INT32S GetO2VtReal()
{
    INT32S ret; 
    ret =  (INT32S)(m_O2VentVal/100.0);
    return ret;
}
INT32S GetAirVtReal()
{
    INT32S ret; 
    ret =  (INT32S)(m_AirVentVal/100.0);
    return ret;
}
void SetVtPoint()
{
    m_IsPoint = TRUE;
}

#ifdef MONI_FLOW_SENSOR//模拟式流量传感器
static INT16U FlowValArr[MAX_FLOW_POINT] = {0,50,93,144,202,264,333,415,512,633,755,892,1040,1246,1483};
static INT16U FlowAdArr[MAX_FLOW_POINT] = {822,1020,1218,1416,1614,1812,2010,2208,2406,2604,2802,3000,3198,3396,3594};
INT16U GetFlowVal(INT16U Ad)
{
    INT16U ret = AD_Match(Ad, MAX_FLOW_POINT, FlowAdArr, FlowValArr);
//    printf("AD:%d, Flow:%d \n",Ad,ret);
	return ret;
}
#endif

#if 0
bool AutoVent10msPrc(INT16U *pVentVal, INT16U FlowVal)
{
		bool ret = FALSE;
		INT16U Vt = 0;
        bool IsPoint = FALSE;
        
		m_TimeMark++;
		if(m_TimeMark % 20==0)
			IsPoint = IsVentMarkPoint(FlowVal);
		if(IsPoint == TRUE)
		{
            m_IsPoint = FALSE;
		    Vt = (INT16U)(m_VentVal/100.0);				
			*pVentVal = Vt;
			ret = TRUE;
//            printf("\r\n");
//            printf("VT:%d ml/s \r\n", Vt);
//            printf("\r\n");
			m_VentVal = 0;
		}
        m_VentVal += FlowVal;       
//        printf("%d ",FlowVal);
		return ret;
}

bool IsVentMarkPoint(INT16U FlowVal)
{
	bool ret = FALSE;			
	if(m_LastFlowVal == 0 && FlowVal>0)
      ret = TRUE;
	m_LastFlowVal = FlowVal;
	return ret;
}
#endif


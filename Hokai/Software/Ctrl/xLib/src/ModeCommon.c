#include "ModeCommon.h"

#define MS_1MIN 60*100 //一分钟6000个10ms
INT16U GetRESPTime(INT16U RR)
{
	INT16U ret = 0;
	ret = (INT16U)(MS_1MIN/(RR*1.0));
	return ret;
}

void GetTiTeTime(INT16U *pTiTime, INT16U *pTeTime,INT16U Time, INT16U TiRatio, INT16U TeRatio)
{
	float sum = TiRatio + TeRatio;
    PD((int)sum);
	*pTiTime = (INT16U)(Time*TiRatio/sum);
	*pTeTime = (INT16U)(Time*TeRatio/sum);
}
INT16U GetTiTime(INT16U Time, INT16U TiRatio, INT16U TeRatio)
{
	INT16U sum = TiRatio + TeRatio;
    return (INT16U)(Time*TiRatio/(sum*1.0));
}
INT16U GetTeTime(INT16U Time, INT16U TiRatio, INT16U TeRatio)
{
	INT16U sum = TiRatio + TeRatio;
    return (INT16U)(Time*TeRatio/(sum*1.0));
}

INT16U GetInspTime(INT16U TiTime,INT16U InspTable)
{
	INT16U ret = 0;
	ret = (INT16U)(TiTime*(100-InspTable)/(100.0));
	return ret;
}

void GetFlowVT(INT16U *pAirVT, INT16U *pO2VT, INT16U Vent, INT8U Present, INT8U O2Pre)
{
  if(O2Pre > Present){
    *pAirVT = (INT16U)(Vent*(O2Pre - Present)*1.0/(O2Pre-21));
    *pO2VT = (INT16U)Vent - *pAirVT;
  }
}
INT16U GetAirFlowVT(INT16U Vent, INT8U Present, INT8U O2Pre)
{
  INT16U AirVT = 0;
  if(O2Pre >= Present){
    AirVT = (INT16U)(Vent*(O2Pre - Present)*1.0/(O2Pre-21));
//    O2VT = (INT16U)Vent - AirVT;
  }
  return AirVT;
}
INT16U GetO2FlowVT(INT16U Vent, INT8U Present, INT8U O2Pre)
{
  INT16U AirVT = 0,O2VT = 0;
  if(O2Pre >= Present){
    AirVT = (INT16U)(Vent*(O2Pre - Present)*1.0/(O2Pre-21));
    O2VT = (INT16U)Vent - AirVT;
  }
  return O2VT;
}

INT16U AD_Match(INT16U AD, INT16U Length, INT16U* ADTab, INT16U* FactValTab)
{	
	INT16U FinalVal = 0;//计算后得到的最终实际值
	INT16U  i = 0;
	INT16U TableValue = 0;
	TableValue = ADTab[Length-1];					
	if(AD >= TableValue) {	
	//当超出表格最大值时，令超出部分的变换斜率等同于表格最后一段斜率
		//FinalVal = (INT16U)(FactValTab[Length-2] + (AD - ADTab[Length-2])* (FactValTab[Length-1] - FactValTab[Length-2])/((ADTab[Length-1] - ADTab[Length-2]*1.0)));
                FinalVal = FactValTab[Length-1];
        } 
	else{
		if(AD < ADTab[0]) {
				FinalVal = FactValTab[0];
		}
		else {
			for(i = 1; i < Length; i++) {
					if(AD < ADTab[i]) {
						FinalVal = FactValTab[i-1]+(FactValTab[i]-FactValTab[i-1])*(AD-ADTab[i-1])/(ADTab[i]-ADTab[i-1]);
						break;
					}
			}	
			if(i == Length) {
				FinalVal = FactValTab[Length - 1];
			}	
		}
	}
        //printf("AD:%d FinalVal:%d \r\n",AD,FinalVal);
	return FinalVal;//返回计算值
}


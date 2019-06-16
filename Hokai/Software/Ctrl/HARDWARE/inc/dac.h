#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	     			    
void Dac_Init(void);		//DAC初始化	 	 

extern void Dac1_Set_Vol(u16 vol);	//设置通道1输出电压
extern void Dac2_Set_Vol(u16 vol);	//设置通道2输出电压

#endif


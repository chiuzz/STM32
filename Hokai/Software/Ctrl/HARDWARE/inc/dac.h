#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	     			    
void Dac_Init(void);		//DAC��ʼ��	 	 

extern void Dac1_Set_Vol(u16 vol);	//����ͨ��1�����ѹ
extern void Dac2_Set_Vol(u16 vol);	//����ͨ��2�����ѹ

#endif


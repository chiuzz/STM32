#ifndef _INJECT_PUMP_H_
#define _INJECT_PUMP_H_

#include "sys.h"
#include "common.h"

#define SUCCESS	1
#define FAIL		0

extern  u8 ROOM;								//房间号
extern  u8 BED;									//床位号
extern  u8 PUMP_CURRENT_STA;		//注液泵当前状态
extern  u8 PRESS;								//压力值
extern  u8 SPEED;								//注液速度
extern  u8 SYRINGE_SIZE;				//注液器规格
extern  u8 SYRINGE_BRAND;				//注液器品牌
extern  u8 JAM;									//阻塞
extern  u8 SYSTEM_ERROR;				//系统故障

extern  u8 WARNING_220V_FALL;							//220V交流电掉电警告
extern  u8 WARNING_BAT_WILL_DIE;					//电池电量将要用完
extern  u8 WARNING_BAT_DIED;							//电池电量已经用完
extern  u8 WARNING_SYRINGE_OK;						//注射完成
extern  u8 WARNING_MEDICINE_WILL_NONE;		//药物将要用完
extern  u8 WARNING_MEDICINE_NONE;					//药物已经用完
extern  u8 WARNING_NEEDLE_FALL;						//针管脱落
extern  u8 WARNING_NEEDLE_ERROR_CONDITION;//针管位置放置错误


static 	void 	Pump_Delay_1ms(u8 delay_ms);		//注液泵模块MS级别延迟函数
static 	void 	Clear_USART2_RxBuffer(void);		//清空串口2接收缓存区
extern  u8 		Open_Communication_Mode(void);	//打开通讯模式
extern  u8 		Close_Communication_Mode(void);	//关闭通讯模式
extern  u8 		Set_Channel(u8 channel);				//设置通道号
extern  u8 		Set_Speed(u16 speed);						//设置注液速度
extern  u8 		Start_Syringe(u8 password);			//开始注射
extern  u8 		Stop_Syringe(u8 password);			//停止注射
extern  u8 		Power_Off(u8 password);					//关闭注液泵
extern  u8 		Clear_Syringes(void);						//清空注液
extern  u8 		Set_Sound(u8 sound);						//设置音量
extern  u8 		Set_Press(u8 press);						//设置压力级别
extern  u16 	Ack_Current_State(char *str);		//查询当前设置
extern void 	Parsing_MSG(void);							//解析报文

#endif 



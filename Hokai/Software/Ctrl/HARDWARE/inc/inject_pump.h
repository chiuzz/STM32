#ifndef _INJECT_PUMP_H_
#define _INJECT_PUMP_H_

#include "sys.h"
#include "common.h"

#define SUCCESS	1
#define FAIL		0

extern  u8 ROOM;								//�����
extern  u8 BED;									//��λ��
extern  u8 PUMP_CURRENT_STA;		//עҺ�õ�ǰ״̬
extern  u8 PRESS;								//ѹ��ֵ
extern  u8 SPEED;								//עҺ�ٶ�
extern  u8 SYRINGE_SIZE;				//עҺ�����
extern  u8 SYRINGE_BRAND;				//עҺ��Ʒ��
extern  u8 JAM;									//����
extern  u8 SYSTEM_ERROR;				//ϵͳ����

extern  u8 WARNING_220V_FALL;							//220V��������羯��
extern  u8 WARNING_BAT_WILL_DIE;					//��ص�����Ҫ����
extern  u8 WARNING_BAT_DIED;							//��ص����Ѿ�����
extern  u8 WARNING_SYRINGE_OK;						//ע�����
extern  u8 WARNING_MEDICINE_WILL_NONE;		//ҩ�ｫҪ����
extern  u8 WARNING_MEDICINE_NONE;					//ҩ���Ѿ�����
extern  u8 WARNING_NEEDLE_FALL;						//�������
extern  u8 WARNING_NEEDLE_ERROR_CONDITION;//���λ�÷��ô���


static 	void 	Pump_Delay_1ms(u8 delay_ms);		//עҺ��ģ��MS�����ӳٺ���
static 	void 	Clear_USART2_RxBuffer(void);		//��մ���2���ջ�����
extern  u8 		Open_Communication_Mode(void);	//��ͨѶģʽ
extern  u8 		Close_Communication_Mode(void);	//�ر�ͨѶģʽ
extern  u8 		Set_Channel(u8 channel);				//����ͨ����
extern  u8 		Set_Speed(u16 speed);						//����עҺ�ٶ�
extern  u8 		Start_Syringe(u8 password);			//��ʼע��
extern  u8 		Stop_Syringe(u8 password);			//ֹͣע��
extern  u8 		Power_Off(u8 password);					//�ر�עҺ��
extern  u8 		Clear_Syringes(void);						//���עҺ
extern  u8 		Set_Sound(u8 sound);						//��������
extern  u8 		Set_Press(u8 press);						//����ѹ������
extern  u16 	Ack_Current_State(char *str);		//��ѯ��ǰ����
extern void 	Parsing_MSG(void);							//��������

#endif 



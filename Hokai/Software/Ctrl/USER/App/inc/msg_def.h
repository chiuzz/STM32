//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : msf_def.h
//*
//* �ļ����� : ϵͳ��Ϣ�����ļ�
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MSG_DEF_H__
#define  __MSG_DEF_H__

///@brief MS_
///lParam:
///wParam:
///@buf:
///#define MS_

#define KEY0  0
#define KEY1  1
#define KEY2  2
#define KEY3  3
#define KEY4  4
#define KEY5  5
#define KEY6  6
#define KEY7  7
#define KEY8  8
#define KEY9  9
#define KEY10 10

#define KEY_DEC  KEY0
#define KEY_ADD  KEY1
#define KEY_WORK_MODE  KEY4
#define KEY_WATER  KEY5
#define KEY_BUMP1  KEY6
#define KEY_TEMP1  KEY7
#define KEY_ALMVOL  KEY8
#define KEY_CAL1  KEY9
#define KEY_CAL2  KEY10

#define KEY_BUMP2  KEY2
#define KEY_TEMP2  KEY3

#define KEY_S_DEC  KEY2
#define KEY_S_ADD  KEY3

#define MS_BASE 2
#define MS_DISTANCE 16

typedef enum
{
    CMD_START, //���ʼ
    CMD_STOP,		//�������
    CMD_SUCESS, //����ɹ�
    CMD_FAIL, //����ʧ��
}	ewParam;

/*********************ModueleConfigģ�鴦����Ϣ��************************/
#define MS_MOD_BASE (MS_BASE + MS_DISTANCE*0)
//@brief MS_KEY_CMD ������Ϣ
//lParam: 1-��Ч����
//wParam: eKeyDef
//@buf: pData
#define MS_KEY_CMD MS_MOD_BASE+1
//@brief MS_BUMP_CMD �ù���״̬����
//lParam: 1-1�űÿ�������2-2�űÿ�����
//wParam: 1-������0-ֹͣ
//@buf: pData
#define MS_BUMP_CMD MS_MOD_BASE+2

typedef enum
{
    CONFIGINIT = 10,
    CALCDATASAVE,
    CONFIGDATASAVE,
    ADJDATASAVE,
    E2PROMERR,
}	eConfiglParam;

//@brief MS_CONFIG_CMD config����
//lParam: eConfiglParam
//wParam: ewParam;
//@buf: pData
#define MS_CONFIG_CMD MS_MOD_BASE+3
//@brief MS_COOLER_CMD ����ģ������
//lParam: 0-������ģʽ��1-����ģʽ
//wParam: 0-���� 1-���
//@buf: pData
#define MS_COOLER_CMD MS_MOD_BASE+4
//@brief MS_HEATER_CMD ����ģ������
//lParam: 0-������ģʽ��1-����ģʽ
//wParam: 0-���� 1-���
//@buf: pData
#define MS_HEATER_CMD MS_MOD_BASE+5
/*********************ModueleConfigģ�鴦����Ϣ��************************/

#endif

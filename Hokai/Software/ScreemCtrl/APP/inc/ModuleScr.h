//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleScr.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SCR_H__
#define  __MODULE_SCR_H__

#include "common.h"
#include "struct_def.h"

#define Temp1_ADDRESS 4
#define WaterTemp_ADDRESS 5
#define Temp2_ADDRESS 6
#define Temp1Set_ADDRESS    1	 //��������1�ĵ�ַ
#define Temp2Set_ADDRESS     3	//��������2�ĵ�ַ
#define WaterTempSet_ADDRESS   2 //ˮ�����õĵ�ַ
#define IC_PIN 23    //��ʾ����ͨ������

#define TempSet1CH_PIN_ADDR 0 // ����1����
#define WaterSetCH_PIN_ADDR 6 // ˮ�������¶���ʾ����
#define TempSet2CH_PIN_ADDR 10 // ����2����
#define Temp1CH2_PIN_ADDR 0 // ����1�¶���ʾ����
#define TWaterCH2_PIN_ADDR 6 // ˮ��
#define Temp2CH2_PIN_ADDR 12 // ����2

#define IC1_PIN   1          //��ʾ����pin1
#define IC2_PIN   2         //��ʾ����pin2
#define Screen_1_S0 	0
#define Screen_1_S1		1
#define Screen_1_S2		2
#define Screen_1_S3		3
#define Screen_1_S4		4
#define Screen_1_S5		5
#define Screen_1_S6		6
#define Screen_1_S7		7
#define Screen_1_S8		8
#define Screen_1_S9		9
#define Screen_1_S10		10
#define Screen_1_S11		11
#define Screen_1_S12		12
#define Screen_1_S13		13
#define Screen_1_S14		14
#define Screen_1_S15		15
#define Screen_1_S16		16
#define Screen_1_S17		17
#define Screen_1_S18		18
#define Screen_1_S19		19
#define Screen_1_S20		20
#define Screen_1_S21		21
#define Screen_1_S22		22
#define Screen_1_S23		23
#define Screen_1_S24		24
#define Screen_1_S25		25
#define Screen_1_S26		26
#define Screen_1_S27		27
#define Screen_1_S28		28
#define Screen_1_S29		29
#define Screen_1_S30		30
#define Screen_1_S31		31
#define Screen_1_S32		32
#define Screen_1_S33		33
#define Screen_1_S34		34
#define Screen_1_S35		35
#define MINUS						10
typedef struct
{
    INT8U COM1 : 1;         //
    INT8U COM2 : 1;         //
    INT8U COM3 : 1;         //
    INT8U COM4 : 1;         //
    INT8U P_WhichIC : 2;
    INT8U P_Addr  : 8;
} HTB_ICN; //��������

typedef enum
{
    SCR_STOP = 0,
    SCR_INIT,
    SCR_WORK,
}	eScrWorkStatus;

typedef enum
{
    Show = 0,
    Hide,
    Invalid,
    Flash,
}	eItemStatus;

typedef struct ModuleScrData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    INT16U m_FlashCount;
    INT16U m_50msCount;

    BOOLEAN m_PressSta; //�������״̬��¼
    PCONFIGDATA m_pSysData;     //ϵͳ����
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    eScrWorkStatus m_ScrWorkSta;
    HTB_ICN  IC1_S[IC_PIN]; //ͨ��1
    HTB_ICN  IC2_S[IC_PIN];//ͨ��2
    INT16U m_Temp1SetMark;
    INT16U m_Temp2SetMark;
    INT16U m_WaterTempSetMark;
    INT16S m_Cal1SetMark;
    INT16S m_Cal2SetMark;

} MODULESCRDATA, *PMODULESCRDATA;

typedef struct ModuleScr //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModele1msProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULESCR, *PMODULESCR;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleScr(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULESCRDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleScr(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleScrInit(void* pArg);
static BOOLEAN ModuleScrReset(void* pArg);
static BOOLEAN ModuleScrStart(void* pArg);
static BOOLEAN ModuleScrStop(void* pArg);
static BOOLEAN ModuleScrRelease(void* pArg);
static void ModuleScr50msProcess(void* pArg);
static void ScrMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
void HTBICNSVal(HTB_ICN HTBRam); //��ʾ������
void HTBSegVal(HTB_ICN* H_Ram, HTB_ICN* L_Ram, INT16U SegData); //��ʾ��
void ShowHT1621Temperature(INT16U TempCH, void* pArg); //��ʾ������ϢΪ--
void WriteHT1621OneData(INT16U Addr, INT16U Data, INT16U WhichIC); //�������͸�����LCD.H
void ShowMinus(INT16U TempCH, void* pArg);
void SystemStaStop(void* pArg);//ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
void DisplayTemp(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp );//��ʾ�¶����õ���Ϣ
void DisplayRefresh(void* pArg);//ˢ������
void HtbRamInit(void* pArg); //��ʾ�������ʼ��
void TempShow(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp );//�¶���ʾ

void WaterStatusAlm(void* pArg);//ˮλ����
void WaterTempSetAlm(void* pArg);//ˮλ����


//************************�ڲ�������ʵ��******************************//
static void DisplayWorkMode(void* pArg,eSystemStatus Sta);
static void DisplayCoolerStatus(void* pArg, eStatus Cooler); //ϵͳ�Ĺ���ģʽ
static void DisplayHeaterStatus(void* pArg, eItemStatus Item); //ϵͳ�Ĺ���ģʽ
static void DisplayCycle1Mode(void* pArg, eStatus Cycle1); //ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
static void DisplayCycle2Mode(void* pArg, eStatus Cycle2); //ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
static void DisplayBump1Mode(void* pArg, eItemStatus Item); //ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
static void DisplayBump2Mode(void* pArg, eItemStatus Item);//ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
static void DisplayWaterStatusI(void* pArg);//ˮλ״̬
static void DisplayWaterStatusII(void* pArg);//ˮλ״̬
static void DisplayWaterStatusIII(void* pArg);//ˮλ״̬
static void DisplayCal1Set(void* pArg, eItemStatus Item, INT16S Cal1Set);
static void DisplayCal2Set(void* pArg, eItemStatus Item, INT16S Cal2Set);
static void DisplayTemp1Set(void* pArg, eItemStatus Item, INT16U Temp1Set); //�¶�����
static void DisplayTemp2Set(void* pArg, eItemStatus Item, INT16U Temp2Set); //�¶�����
static void DisplayWaterTempSet(void* pArg, eItemStatus Item, INT16U WaterTempSet); //�¶�����
static void DisplayTemp1Val(void* pArg, eItemStatus Item, INT16U Temp);
static void DisplayTemp2Val(void* pArg, eItemStatus Item, INT16U Temp);
static void DisplayWaterTempVal(void* pArg, eItemStatus Item, INT16U Temp);
#endif

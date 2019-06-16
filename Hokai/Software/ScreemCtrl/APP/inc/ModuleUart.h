//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleUart.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_UART_H__
#define  __MODULE_UART_H__

#include "common.h"
#include "usart3.h"
#include "struct_def.h"
#define BUFMAX 24
#define DATABUF (BUFMAX*2)

typedef enum
{
    UART_STOP = 0,
    UART_INIT,
    UART_WORK,
}	eUartWorkStatus;


typedef struct UartData
{
    INT16U m_DataBuf[DATABUF];
    INT16U m_index;
    INT16U m_MarkIndex;
    BOOLEAN m_MarkSta;
    INT16U m_buf[BUFMAX];
    INT8U m_buflen;
    BOOLEAN m_Sta;
} UARTDATA,*PUARTDATA;



typedef struct ModuleUartData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    INT16U m_InitCount; //��ʱ��
    INT16U m_Led_Count;
    BOOLEAN m_PressSta; //�������״̬��¼
    PCONFIGDATA m_pSysData;     //ϵͳ����
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    PUARTDATA m_pData;
    INT16U *m_pAdArr;

    // HTB_RAM HTBRam;
    eUartWorkStatus m_UartWorkSta;


    INT16U m_50msCount; //50ms��ʱ��

    BOOLEAN TemperatureBool;

    INT16U key_Temp;  //������
    BOOLEAN Temp1SetBOOL;
    BOOLEAN Temp2SetBOOL;
    BOOLEAN WaterSetBOOL;
    BOOLEAN WaterHotBOOL; //ˮ�¹���
    BOOLEAN SystemAlmBOOL;
    INT16U UsartSendFlag;//���ʹ�����Ϣ�ı��λ

} MODULEUARTDATA,*PMODULEUARTDATA;

typedef struct ModuleUart //��������
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
    void (*pModele1msProcess)(void* pArg);  //1ms��������
    PVOID m_pBaseData;
    void (*pStart)(void* pArg);
} MODULEUART,*PMODULEUART;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleUart(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEUARTDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleUart(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleUartInit(void* pArg);
static BOOLEAN ModuleUartReset(void* pArg);
static BOOLEAN ModuleUartStart(void* pArg);
static BOOLEAN ModuleUartStop(void* pArg);
static BOOLEAN ModuleUartRelease(void* pArg);
static void ModuleUart1sProcess(void* pArg);
static void UartMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
extern void SendUartData(uint16_t data);
//************************�ڲ�������ʵ��******************************//
static void UartWorkStatusProc(void* pArg);
static void Start(void* pArg);
static void GetUartData(void* pArg);
static void Unpack(void* pArg, INT16U *pData, INT8U len);
static BOOLEAN CheckSum(INT16U* buf, INT8U len);

static void ModuleUart50msProcess(void* pArg);
static void ModuleUart10msProcess(void* pArg);


//-----------------------------tommy


//u8 GetButtomValue();//Ӳ����ȡ����
void Usart3SendDataToMaster(void* pArg,uint8_t keyNumber);//���ʹ�����Ϣ�����ذ�



#endif

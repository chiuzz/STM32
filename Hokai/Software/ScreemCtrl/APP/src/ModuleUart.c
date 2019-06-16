//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleUart.c
//*
//* �ļ����� : UART����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleUart.h"
#include "led.h"
#include "msg_def.h"
#include "ModuleScr.h"
#include "common.h"

static PUARTDATA m_UartData = NULL;
BOOLEAN ModuleUartInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;


    if(pData != NULL)
    {
        m_UartData = pData->m_pData;
        m_UartData->m_MarkSta = FALSE;
        m_UartData->m_index = 0;
        m_UartData->m_MarkIndex = 0;
        pData->m_UartWorkSta = UART_STOP;
        pData->m_pAdArr = pData->m_pSysData->pStatus->m_AdArr;
        pData->m_pSysData->m_SingleMode = Status_Off;
        pData->m_pSysData->m_FocusStatus = NoFocus;
        pData->m_pSysData->m_Heater = Status_Off ;
        pData->m_pSysData->m_Cooler = Status_Off;
        pData->m_pSysData->m_Sensor1OFF = Status_Off ; //���������� Status_On-����
        pData->m_pSysData->m_Sensor2OFF = Status_Off ; //���������� Status_On-����
        pData->m_pSysData->m_HeaterPOWER = Status_Off ; //�������쳣 Status_On-����
        pData->m_pSysData->m_WaterHIGH = Status_Off ; //ˮ�³���״̬ Status_On-����
        pData->m_pSysData->m_WaterTLow = Status_Off ; //ˮ�³���״̬ Status_On-����
        pData->m_pSysData-> m_E2PROMERR = Status_Off ;//e2prom���� Status_On-����
        pData->m_pSysData->m_WaterLow = Status_Off ;//ˮλ��״̬ Status_On-����
        pData->m_pSysData->m_HeaterModeWT1Low = Status_Off ; //����ģʽ�£��趨ˮ�µ������� Status_On-����
        pData->m_pSysData->m_HeaterModeWT2Low = Status_Off ; //����ģʽ�£��趨ˮ�µ������� Status_On-����
        pData->m_pSysData->m_HeaterModeT1ALM = Status_Off ; //����ģʽ�£�����1���ޱ���
        pData->m_pSysData->m_HeaterModeT2ALM = Status_Off ; //����ģʽ�£�����2���ޱ���
        pData->m_pSysData->m_Cycle1Alm = Status_Off ; //Һ·1�쳣 Status_On-����
        pData->m_pSysData->m_Cycle2Alm = Status_Off ; //Һ·2�쳣 Status_On-����
    }
    return ret;
}

BOOLEAN ModuleUartReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    pData->m_PressSta = FALSE;

    return ret;
}

BOOLEAN ModuleUartStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    pData->m_PressSta = TRUE;
    pData->m_Count = 0;
    pData->m_InitCount = 0;
    pData->UsartSendFlag = 0;
    pData->m_50msCount = 0;
    //


    return ret;
}

BOOLEAN ModuleUartStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleUartRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}
void ModuleUart10msProcess(void* pArg)
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;

}


void ModuleUart50msProcess(void* pArg)
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    return;
}

void ModuleUart1sProcess(void* pArg)
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    INT8U index;
    //printf("ModuleUart1sProcess\r\n");
    if(pData->m_PressSta == FALSE || pData->m_UartWorkSta != UART_WORK)
    {
        return;
    }
    pData->m_Count++;
    pData->m_Led_Count++;
    LED(pData->m_Led_Count % 2); //ϵͳ����˸

    if(pData->m_Count > 60)
    {
        pData->m_Count = 0;
    }
    index = 0;
    if(pData->m_pSysData->m_Sensor1OFF == Status_On) { //���������� Status_On-����
        index = 1;
    }
    if(pData->m_pSysData->m_Sensor2OFF == Status_On) { //���������� Status_On-����
        index = 1;
    }
    if(pData->m_pSysData->m_HeaterPOWER == Status_On) { //�������쳣 Status_On-����
        index = 2;
    }
    if(pData->m_pSysData->m_WaterHIGH == Status_On) { //ˮ�³�����״̬ Status_On-����
        index = 3;
    }
    if(pData->m_pSysData->m_WaterTLow == Status_On) { //ˮ�³�����״̬ Status_On-����
        index = 3;
    }
    if(pData->m_pSysData->m_E2PROMERR == Status_On) { //e2prom���� Status_On-����
        if(index < 2)
            index = 2;
    }
    if(pData->m_pSysData->m_WaterLow == Status_On) { //ˮλ��״̬ Status_On-����
        if(index == 0)
            index = 1;
    }
    if(pData->m_pSysData->m_HeaterModeWT1Low == Status_On) { //����ģʽ�£��趨ˮ�µ�������1 Status_On-����
        if(index < 2)
            index = 2;
    }
    if(pData->m_pSysData->m_HeaterModeWT2Low == Status_On) { //����ģʽ�£��趨ˮ�µ�������2 Status_On-����
        if(index < 2)
            index = 2;
    }
    if(pData->m_pSysData->m_HeaterModeT1ALM == Status_On && pData->m_pSysData->m_Sensor1OFF == Status_Off) { //����ģʽ�£�����1���ޱ���
        if(index < 2)
            index = 2;
    }
    if(pData->m_pSysData->m_HeaterModeT2ALM == Status_On && pData->m_pSysData->m_Sensor2OFF == Status_Off) { //����ģʽ�£�����2���ޱ���
        if(index < 2)
            index = 2;
    }
    if(pData->m_pSysData->m_Cycle1Alm == Status_On) { //Һ·1����
        if(index == 0)
            index = 1;
    }
    if(pData->m_pSysData->m_Cycle2Alm == Status_On) { //Һ·2����
        if(index == 0)
            index = 1;
    }
//		PD(index);
    SetAlarmLevel(index);
    SetAlarmVolum(pData->m_pSysData->m_AlmVolum);
}

void UartMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{

    switch(MsgId)
    {
    case MS_KEY_TRIGER:
        if(lParam == 1)
        {
//             printf("wParam��%d !!!\n",wParam);
            //����ִ�����ñ��棬���ô�����
            Usart3SendDataToMaster(pArg, wParam);//���ʹ�����Ϣ�����ذ�
        }
        break;
    default:
        break;
    }
//     printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleUart(PMODULESERVERDATA pServerData)
{
    PMODULEUART pModUart = NULL;
    PMODULEUARTDATA pData = NULL;

    pModUart = (PMODULEUART)malloc(sizeof(MODULEUART));//�������ṹ
    pData = (PMODULEUARTDATA)malloc(sizeof(MODULEUARTDATA));//����������ݽṹ
    pData->m_pData = NULL;
    pData->m_pData = (PUARTDATA)malloc(sizeof(UARTDATA));
    pData->m_pSysData = pServerData->m_pSysData;
//   ASSERT(pData->m_pData != NULL);
//   ASSERT(pModUart != NULL);
//   ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModUart->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModUart->pModeleInit = ModuleUartInit; //ʵ��ģ���ʼ��
    pModUart->pModeleReset = ModuleUartReset; //ʵ��ģ�鸴λ
    pModUart->pModeleStart = ModuleUartStart; //ʵ��ģ�鿪ʼ
    pModUart->pModeleStop = ModuleUartStop; //ʵ��ģ�����
    pModUart->pModeleRelease = ModuleUartRelease;//ʵ��
    pModUart->pMsgNotify = UartMsgNotify;//ʵ����Ϣ���д���
    pModUart->pModele10msProcess = ModuleUart10msProcess;//��ʵ�֣���ΪNULL
    pModUart->pModele50msProcess = ModuleUart50msProcess;//��ʵ�֣���ΪNULL
    pModUart->pModele1sProcess = ModuleUart1sProcess;//ʵ��1s����
    pModUart->pModele1msProcess = NULL;//ʵ��1s����

    strcpy(pModUart->m_ModName, "ModUart");
    pModUart->pStart = Start;
//     printf("CreateModuleUart!!\n");
    return (PMODULEBASE)pModUart;
}

void UartWorkStatusProc(void* pArg)							//20msִ��һ��
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;

    switch(pData->m_UartWorkSta)
    {
    case UART_STOP:
        if(pData->m_InitCount != 50)
        {
            pData->m_InitCount++;
            break;
        }
        pData->m_UartWorkSta = UART_INIT;
        SetAlarmLevel(1);
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_CMD, 1, 0, NULL);
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_SCR_CMD, 1, 0, NULL);
        break;
    case UART_INIT:
        if(pData->m_InitCount != 250)
        {
            pData->m_InitCount++;
            break;
        }
        pData->m_InitCount = 0;
        pData->m_UartWorkSta = UART_WORK;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_CMD, 0, 0, NULL);
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_SCR_CMD, 0, 0, NULL);
        break;
    case UART_WORK:
    default:
        break;
    }
}

void Start(void* pArg)
{
    while(1)
    {
        OSTimeDlyHMSM(0, 0, 0, 20);
        GetUartData(pArg);
    }
}

void GetUartData(void* pArg)
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
// 	printf("---GetUartData\r\n");
    UartWorkStatusProc(pArg);		//20msִ��һ��
    if(pData->m_pData->m_Sta == TRUE && pData->m_UartWorkSta != UART_INIT)
    {
        pData->m_pData->m_Sta = FALSE;
        Unpack(pArg, pData->m_pData->m_buf, BUFMAX );
    }
}

void SendUartData(uint16_t data)
{
    INT8U i = 0;
    INT16U len;
//
    //printf("%d ",data); //tommy

    if(m_UartData == NULL)
        return;

    if(m_UartData->m_index >= DATABUF)
    {
        m_UartData->m_index = 0;
        m_UartData->m_MarkIndex = 0;
        m_UartData->m_MarkSta = FALSE;
    }

    m_UartData->m_DataBuf[m_UartData->m_index] = data;

    if(m_UartData->m_DataBuf[m_UartData->m_index] == SOM && m_UartData->m_MarkSta == FALSE)
    {
        m_UartData->m_MarkIndex = m_UartData->m_index;
        m_UartData->m_MarkSta = TRUE;
    }

    if(m_UartData->m_DataBuf[m_UartData->m_index] == EOM  && m_UartData->m_DataBuf[m_UartData->m_MarkIndex] == SOM )
    {
        len = m_UartData->m_index - m_UartData->m_MarkIndex + 1;
        if(len == BUFMAX && CheckSum( &(m_UartData->m_DataBuf[m_UartData->m_MarkIndex]), len))
        {
            for(i = 0; i < BUFMAX; i++)
            {
                m_UartData->m_buf[i] = m_UartData->m_DataBuf[m_UartData->m_MarkIndex + i];
            }
// 						PS("SendUartData");
            m_UartData->m_Sta = TRUE;
            m_UartData->m_index = 0;
            m_UartData->m_MarkIndex = 0;
            m_UartData->m_MarkSta = FALSE;
        }
    }
    m_UartData->m_index++;
}

void DataProcess(INT16U *pSrc, INT16U *pDis, INT8U len)
{
    INT8U i = 0;
    for(i = 0; i < len; i++)
    {
        pDis[i] = pSrc[i];
    }
}

////////CMD BYTE define/////////////
#define UP_PAG_NUM 24
#define UP_PKG_SOM 0xEF
#define UP_PKG_EOM 0xFF
#define UP_PKG_CMD 0x01

#define UP_PKG_DSOM 0
#define UP_PKG_DCMD 1
#define UP_PKG_D1 2
#define UP_PKG_D2 3
#define UP_PKG_D3 4
#define UP_PKG_D4 5
#define UP_PKG_D5 6
#define UP_PKG_D6 7
#define UP_PKG_D7 8
#define UP_PKG_D8 9
#define UP_PKG_D9 10
#define UP_PKG_D10 11
#define UP_PKG_D11 12
#define UP_PKG_D12 13
#define UP_PKG_D13 14
#define UP_PKG_D14 15
#define UP_PKG_D15 16
#define UP_PKG_D16 17
#define UP_PKG_D17 18
#define UP_PKG_D18 19
#define UP_PKG_D19 20
#define UP_PKG_D20 21
#define UP_PKG_DCHK 22
#define UP_PKG_DEOM 23

void Unpack(void* pArg, INT16U *pData, INT8U len)
{
    PMODULEUARTDATA pObjData = (PMODULEUARTDATA)pArg;
    INT8U i;
    INT16U val;
    INT16U PointNo = 0;
//  	  printf("Receive DATA: ");
//  		for(i=0;i<len;i++)
//  		{
//  			printf("0x%x ",pData[i]);
//  		}
//    printf("TOMMY\r\n");

    if ((pData[UP_PKG_D1] & BIT0) != 0) //���xλ�Ƿ�Ϊ1
    {
        pObjData->m_pSysData->m_SingleMode = Status_On; //���ܰ�ť����������1
    }
    else {
        pObjData->m_pSysData->m_SingleMode = Status_Off;
    }
    pObjData->m_pSysData->m_FocusStatus = (pData[UP_PKG_D1] & (BIT1 | BIT2 | BIT3)) >> 1;
    if((pData[UP_PKG_D1] & BIT4) != 0) //���xλ�Ƿ�Ϊ1
    {
        pObjData->m_pSysData->m_Cycle1Set = Status_On;//4ˮ·1
    }
    else {
        pObjData->m_pSysData->m_Cycle1Set = Status_Off;
    }
    if((pData[UP_PKG_D1] & BIT5) != 0) //���xλ�Ƿ�Ϊ1
    {
        pObjData->m_pSysData->m_Bump1Status = Status_On;//5ˮ��1
    }
    else {
        pObjData->m_pSysData->m_Bump1Status = Status_Off;
    }
    if((pData[UP_PKG_D1] & BIT6) != 0) //���xλ�Ƿ�Ϊ1
    {
        pObjData->m_pSysData->m_Cycle2Set = Status_On;//6ˮ·2
    }
    else {
        pObjData->m_pSysData->m_Cycle2Set = Status_Off;
    }
    if((pData[UP_PKG_D1] & BIT7) != 0) //���xλ�Ƿ�Ϊ1
    {
        pObjData->m_pSysData->m_Bump2Status = Status_On;//7ˮ��2
    }
    else {
        pObjData->m_pSysData->m_Bump2Status = Status_Off;
    }
    //��������1
    pObjData->m_pSysData->m_Temp1Set = (pData[UP_PKG_D2] << 8) + (pData[UP_PKG_D3]);
    //ˮ������
    pObjData->m_pSysData->m_WaterTempSet = (pData[UP_PKG_D4] << 8) + (pData[UP_PKG_D5]);
    //��������2
    pObjData->m_pSysData->m_Temp2Set = (pData[UP_PKG_D6] << 8) + (pData[UP_PKG_D7]);
    //����1
    pObjData->m_pSysData->m_Temp1 = (pData[UP_PKG_D8] << 8) + (pData[UP_PKG_D9]);
    //ˮ��
    pObjData->m_pSysData->m_WaterTemp = (pData[UP_PKG_D10] << 8) + (pData[UP_PKG_D11]);
    //����2
    pObjData->m_pSysData->m_Temp2 = (pData[UP_PKG_D12] << 8) + (pData[UP_PKG_D13]);

    pObjData->m_pSysData->m_SystemSta = pData[UP_PKG_D14] & (BIT0 | BIT1 | BIT2); //ϵͳ״̬

    if((pData[UP_PKG_D14] & (BIT5 | BIT6)) == 0)
        pObjData->m_pSysData->m_WaterStatus = Status_I;
    if((pData[UP_PKG_D14] & (BIT5 | BIT6)) >> 5 == 0x01)
        pObjData->m_pSysData->m_WaterStatus = Status_II;
    if((pData[UP_PKG_D14] & (BIT5 | BIT6)) >> 5 == 0x02)
        pObjData->m_pSysData->m_WaterStatus = Status_III;

    //����״̬	Status_Off = 0,	Status_On = 1,	��ʾ̫��

    if((pData[UP_PKG_D14] & BIT3) != 0 ) //����ģʽ ��ʾ̫��3����,2������ 1�ǹ�
    {
        pObjData->m_pSysData->m_Heater = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Heater = Status_Off;
    }
//		PD(pObjData->m_pSysData->m_Heater);
    if((pData[UP_PKG_D14] & BIT4) != 0 )//����״̬		��ʾѩ��
    {
        pObjData->m_pSysData->m_Cooler = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Cooler = Status_Off;
    }

    if(pObjData->m_pSysData->m_FocusStatus == AlmVolumFocus)	//���������ȼ�
    {
        pObjData->m_pSysData->m_AlmVolSet = (pData[UP_PKG_D15] & (BIT0 | BIT1 | BIT2));
    }
    else
    {
        pObjData->m_pSysData->m_AlmVolum = (pData[UP_PKG_D15] & (BIT0 | BIT1 | BIT2));
    }
//		PD(pObjData->m_pSysData->m_AlmVolSet);
//		PD(pObjData->m_pSysData->m_AlmVolum);

    if((pData[UP_PKG_D16] & BIT0) != 0 )//���������� Status_On-����
    {
        pObjData->m_pSysData->m_Sensor1OFF = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Sensor1OFF = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT1) != 0 )//�������쳣 Status_On-����
    {
        pObjData->m_pSysData->m_HeaterPOWER = Status_On;
    }
    else {
        pObjData->m_pSysData->m_HeaterPOWER = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT2) != 0 )//ˮ�³���״̬ Status_On-����
    {
        pObjData->m_pSysData->m_WaterHIGH = Status_On;
    }
    else {
        pObjData->m_pSysData->m_WaterHIGH = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT3) != 0 )//e2prom���� Status_On-����
    {
        pObjData->m_pSysData->m_E2PROMERR = Status_On;
    }
    else {
        pObjData->m_pSysData->m_E2PROMERR = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT4) != 0 )//ˮλ��״̬ Status_On-����
    {
        pObjData->m_pSysData->m_WaterLow = Status_On;
    }
    else {
        pObjData->m_pSysData->m_WaterLow = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT5) != 0 )//����ģʽ�£��趨ˮ�µ������� Status_On-����
    {
        pObjData->m_pSysData->m_HeaterModeWT1Low = Status_On;
    }
    else {
        pObjData->m_pSysData->m_HeaterModeWT1Low = Status_Off;
    }
    if((pData[UP_PKG_D16] & BIT6) != 0 )//����ģʽ�£�����1���ޱ���
    {
        pObjData->m_pSysData->m_HeaterModeT1ALM = Status_On;
    }
    else {
        pObjData->m_pSysData->m_HeaterModeT1ALM = Status_Off;
    }

    if((pData[UP_PKG_D16] & BIT7) != 0 ) //����ģʽ�£�����2���ޱ���
    {
        pObjData->m_pSysData->m_HeaterModeT2ALM = Status_On;
    }
    else {
        pObjData->m_pSysData->m_HeaterModeT2ALM = Status_Off;
    }

    if((pData[UP_PKG_D17] & BIT0) != 0 ) //Һ·1�쳣����
    {
        pObjData->m_pSysData->m_Cycle1Alm = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Cycle1Alm = Status_Off;
    }

    if((pData[UP_PKG_D17] & BIT1) != 0 ) //Һ·2�쳣����
    {
        pObjData->m_pSysData->m_Cycle2Alm = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Cycle2Alm = Status_Off;
    }

    if((pData[UP_PKG_D17] & BIT2) != 0 ) //ˮ�³��±���
    {
        pObjData->m_pSysData->m_WaterTLow = Status_On;
    }
    else {
        pObjData->m_pSysData->m_WaterTLow = Status_Off;
    }

    if((pData[UP_PKG_D17] & BIT3) != 0 ) //ˮ�³��±���
    {
        pObjData->m_pSysData->m_Sensor2OFF = Status_On;
    }
    else {
        pObjData->m_pSysData->m_Sensor2OFF = Status_Off;
    }

    if((pData[UP_PKG_D17] & BIT4) != 0 )//����ģʽ�£��趨ˮ�µ������� Status_On-����
    {
        pObjData->m_pSysData->m_HeaterModeWT2Low = Status_On;
    }
    else {
        pObjData->m_pSysData->m_HeaterModeWT2Low = Status_Off;
    }
    //����У׼1
    pObjData->m_pSysData->m_Cal1Set = (INT8S)pData[UP_PKG_D18];
    //����У׼2
    pObjData->m_pSysData->m_Cal2Set = (INT8S)pData[UP_PKG_D19];
}

BOOLEAN CheckSum(INT16U * buf, INT8U len)
{
    INT8U index = 0;
    BOOLEAN ret = FALSE;
    INT8U sum = 0;
    for(index = 1; index < len - 2; index++)
    {
// 			printf("0x%x ", buf[index]);
        sum += buf[index];
    }
// 		PD(sum);
// 		PD(buf[len-2]);
    if(sum == buf[len - 2])
        ret = TRUE;
    return ret;
}

void Usart3SendDataToMaster(void* pArg, uint8_t keyNumber) //���ʹ�����Ϣ�����ذ�
{
    PMODULEUARTDATA pData = (PMODULEUARTDATA)pArg;
    uint16_t len = 8;
    uint8_t Data[8];
    Data[0] = 0xef;
    Data[1] = 0xa1;
    Data[2] = keyNumber;
    Data[3] = 0x0;
    Data[4] = 0x0;
    Data[5] = 0x0;
    Data[6] = Data[1] + Data[2] + Data[3] + Data[4] + Data[5];
    Data[7] = 0xFF;
    Usart3SendData(Data, len);
}

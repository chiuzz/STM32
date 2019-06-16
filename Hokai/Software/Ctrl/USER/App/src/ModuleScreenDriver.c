//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleScreenDriver.c
//*
//* �ļ����� : SCREENDRIVER����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleScreenDriver.h"
#include "common.h"

static PUARTSRCDATA m_UartScrData = NULL;

BOOLEAN ModuleScreenDriverInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    if(pData != NULL)
    {
    }
    return ret;
}

BOOLEAN ModuleScreenDriverReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleScreenDriverStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleScreenDriverStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleScreenDriverRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModeleScreenDriverUartProcess(void* pArg)
{
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    if(pData->m_pData->m_Sta == TRUE)
    {
        pData->m_pData->m_Sta = FALSE;
        //PS("Unpack");
        SrcUnpack(pArg, pData->m_pData->m_buf, SCRBUFMAX );
    }
}

void ModuleScreenDriver50msProcess(void* pArg)
{
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    // printf("ModuleScreenDriver1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    pData->m_Count++;
    if(pData->m_Count > 2)
    {
        pData->m_Count = 0;
        UsartSendFullData_Screen(pArg);//���ʹ�����Ϣ����Ļ
    }
}

void ScreenDriverMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{

//    switch(MsgId)
//    {
//        case MSG_SCREENDRIVER_SAVE:
//          if(lParam == 1)
//          {
//            //����ִ�����ñ��棬���ô�����
//              ScreenDriverSave();
//          }
//          break;
//        default:break;
//    }
//    printf("Receive MSG !!!\n");
}

PMODULEBASE CreateModuleScreenDriver(PMODULESERVERDATA pServerData)
{
    PMODULESCREENDRIVER pModScreenDriver = NULL;
    PMODULESCREENDRIVERDATA pData = NULL;

    pModScreenDriver = (PMODULESCREENDRIVER)malloc(sizeof(MODULESCREENDRIVER));//�������ṹ
    pData = (PMODULESCREENDRIVERDATA)malloc(sizeof(MODULESCREENDRIVERDATA));//����������ݽṹ

    pData->m_pData = NULL;
    pData->m_pData = (PUARTSRCDATA)malloc(sizeof(UARTSRCDATA));
    m_UartScrData = pData->m_pData;

    assert(pData->m_pData != NULL);
    assert(pModScreenDriver != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModScreenDriver->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModScreenDriver->pModeleInit = ModuleScreenDriverInit; //ʵ��ģ���ʼ��
    pModScreenDriver->pModeleReset = ModuleScreenDriverReset; //ʵ��ģ�鸴λ
    pModScreenDriver->pModeleStart = ModuleScreenDriverStart; //ʵ��ģ�鿪ʼ
    pModScreenDriver->pModeleStop = ModuleScreenDriverStop; //ʵ��ģ�����
    pModScreenDriver->pModeleRelease = ModuleScreenDriverRelease;//ʵ��
    pModScreenDriver->pMsgNotify = ScreenDriverMsgNotify;//ʵ����Ϣ���д���
    pModScreenDriver->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModScreenDriver->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModScreenDriver->pModele50msProcess = ModuleScreenDriver50msProcess;//��ʵ�֣���ΪNULL
    pModScreenDriver->pModele1sProcess = NULL;//ʵ��1s����
    pModScreenDriver->pModeleUartProcess = ModeleScreenDriverUartProcess;//ʵ��UART����
    strcpy(pModScreenDriver->m_ModName, "ModScreenDriver");

    //printf("CreateModuleScreenDriver!!\n");
    return (PMODULEBASE)pModScreenDriver;
}

void SendSrcUartData(uint16_t data)
{
    INT8U i = 0;
    INT16U len;
    //uint8_t Data[10]={0xef,0x01,0x01,0x01,0x01,0x00,0x17,0x25,0x04,0xFF};
    //USART_SendData(USART3,data);
    if(m_UartScrData == NULL)
        return;

    if(m_UartScrData->m_index >= SCRDATABUF)
    {
        m_UartScrData->m_index = 0;
        m_UartScrData->m_MarkIndex = 0;
        m_UartScrData->m_MarkSta = FALSE;
        //PS("1");
    }

    m_UartScrData->m_DataBuf[m_UartScrData->m_index] = data;

    if(m_UartScrData->m_DataBuf[m_UartScrData->m_index] == SCRSOM && m_UartScrData->m_MarkSta == FALSE)
    {
        m_UartScrData->m_MarkIndex = m_UartScrData->m_index;
        m_UartScrData->m_MarkSta = TRUE;
        //PS("2");
    }

    if(m_UartScrData->m_DataBuf[m_UartScrData->m_index] == SCREOM  && m_UartScrData->m_DataBuf[m_UartScrData->m_MarkIndex] == SCRSOM )
    {
        len = m_UartScrData->m_index - m_UartScrData->m_MarkIndex + 1;
// 				PD(m_UartData->m_index);
// 				PD(m_UartData->m_MarkIndex);
// 				PD(len);
        //PS("3");
        if(len == SCRBUFMAX && SrcCheckSum( &(m_UartScrData->m_DataBuf[m_UartScrData->m_MarkIndex]), len))
        {
            for(i = 0; i < SCRBUFMAX; i++)
            {
                m_UartScrData->m_buf[i] = m_UartScrData->m_DataBuf[m_UartScrData->m_MarkIndex + i];
            }
            //PS("4");
            m_UartScrData->m_Sta = TRUE;
            m_UartScrData->m_index = 0;
            m_UartScrData->m_MarkIndex = 0;
            m_UartScrData->m_MarkSta = FALSE;
        }
    }
    m_UartScrData->m_index++;
}

BOOLEAN SrcCheckSum(INT16U* buf, INT8U len)
{
    INT8U index = 0;
    BOOLEAN ret = FALSE;
    INT8U sum = 0;
    for(index = 1; index < len - 2; index++)
    {
        sum += buf[index];
    }
    if(sum == buf[len - 2])
        ret = TRUE;
    return ret;
}

#define SRC_CMD_BYTE 1
void SrcUnpack(void* pArg, INT16U *pData, INT8U len)
{
    PMODULESCREENDRIVERDATA pObjData = (PMODULESCREENDRIVERDATA)pArg;
    INT16U i = 0;
//	printf("PKG:");
//	for(i=0;i<len;i++)
//	{
//		printf("0x%x ",pData[i]);
//	}
//	printf("\r\n");
/////////////////////////���ݰ���Э����///////////////////
    switch(pData[SRC_CMD_BYTE])
    {
    case 0xa1: //��ʾ���������ݰ�
        pObjData->m_pMsgQueue->push_back(pObjData->m_pMsgQueue->pData, MS_KEY_CMD, 1, pData[2], NULL);
        break;
    default:
        break;
    }
/////////////////////////���ݰ���Э����///////////////////
}
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

void UsartSendFullData_Screen(void* pArg)//���ʹ�����Ϣ����Ļ
{
    PMODULESCREENDRIVERDATA pData = (PMODULESCREENDRIVERDATA)pArg;
    INT16U i = 0;
    INT16U Temp;
    uint8_t Data[UP_PAG_NUM];
    Data[UP_PKG_DSOM] = UP_PKG_SOM;
    Data[UP_PKG_DEOM] = UP_PKG_EOM;
    Data[UP_PKG_DCMD] = UP_PKG_CMD; //���ݰ�
    for(i = UP_PKG_D1; i < UP_PKG_DCHK; i++)
    {
        Data[i] = 0;
    }

    if(pData->m_pCalData->m_SingleMode == Status_On)
    {
        Data[UP_PKG_D1] |= BIT0;
    }

    Data[UP_PKG_D1] |= pData->m_pSysData->m_FocusStatus << 1;

    if(pData->m_pCfgData->m_Cycle1Set == Status_On) //ˮ·1
    {
        Data[UP_PKG_D1] |=  BIT4;
    }
    if(pData->m_pSysData->m_Bump1Status == Status_On) //ˮ��1
    {
        Data[UP_PKG_D1] |= BIT5;
    }
    if(pData->m_pCfgData->m_Cycle2Set == Status_On) //ˮ·2
    {
        Data[UP_PKG_D1] |= BIT6;
    }
    if(pData->m_pSysData->m_Bump2Status == Status_On) //ˮ��2
    {
        Data[UP_PKG_D1] |=  BIT7;
    }

    if(pData->m_pSysData->m_FocusStatus == Temp1Focus) {
        Temp = pData->m_pSysData->m_Temp1Set;
    }
    else {
        if(pData->m_pCfgData->m_SystemSta == Cooler) {
            Temp = pData->m_pCfgData->m_Temp1Set_Cool;
        }
        else if(pData->m_pCfgData->m_SystemSta == Heater) {
            Temp = pData->m_pCfgData->m_Temp1Set_Hot;
        }
    }
    Data[UP_PKG_D2] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ ��������1
    Data[UP_PKG_D3] = (Temp & 0x00ff); //���ݵĵ�λ ��������1

    if(pData->m_pSysData->m_FocusStatus == TempWFocus) {
        Temp = pData->m_pSysData->m_WaterTempSet;
    }
    else {
        if(pData->m_pCfgData->m_SystemSta == Cooler) {
            Temp = pData->m_pCfgData->m_WaterTempSet_Cool;
        }
        else if(pData->m_pCfgData->m_SystemSta == Heater) {
            Temp = pData->m_pCfgData->m_WaterTempSet_Hot;
        }
    }
    Data[UP_PKG_D4] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ //ˮ������
    Data[UP_PKG_D5] = (Temp & 0x00ff); //���ݵĵ�λ //ˮ������

    if(pData->m_pSysData->m_FocusStatus == Temp2Focus) {
        Temp = pData->m_pSysData->m_Temp2Set;
    }
    else {
        if(pData->m_pCfgData->m_SystemSta == Cooler) {
            Temp = pData->m_pCfgData->m_Temp2Set_Cool;
        }
        else if(pData->m_pCfgData->m_SystemSta == Heater) {
            Temp = pData->m_pCfgData->m_Temp2Set_Hot;
        }
    }
    Data[UP_PKG_D6] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ //��������2
    Data[UP_PKG_D7] = (Temp & 0x00ff); //���ݵĵ�λ ////��������2
    Temp = pData->m_pSysData->m_Temp1;
    Data[UP_PKG_D8] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ ����1
    Data[UP_PKG_D9] = (Temp & 0x00ff); //���ݵĵ�λ ����1
    Temp = pData->m_pSysData->m_WaterTemp;
    Data[UP_PKG_D10] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ //ˮ��
    Data[UP_PKG_D11] = (Temp & 0x00ff); //���ݵĵ�λ //ˮ��
    Temp = pData->m_pSysData->m_Temp2;
    Data[UP_PKG_D12] = ((Temp & 0xff00) >> 8); //���ݵĸ�λ //����2
    Data[UP_PKG_D13] = (Temp & 0x00ff); //���ݵĵ�λ ////����2

//					//ϵͳ״̬ 	Stop = 1,	Cooler,	Heater,
    Data[UP_PKG_D14] = pData->m_pCfgData->m_SystemSta;

    switch(pData->m_pSysData->m_WaterStatus)
    {
    default:
    case Status_I:
        break;
    case Status_II:
        Data[UP_PKG_D14] |= 0x01 << 5;
        break;
    case Status_III:
        Data[UP_PKG_D14] |= 0x02 << 5;
        break;
    }
//PD(pData->m_pSysData->m_Heater);
    if(pData->m_pSysData->m_Heater == Status_On ) //����״̬	Status_Off = 0,	Status_On = 1,	��ʾ̫��
    {
        Data[UP_PKG_D14] |= BIT3;
    }

    if(pData->m_pSysData->m_Cooler == Status_On) //����״̬		��ʾѩ��
    {
        Data[UP_PKG_D14] |= BIT4;
    }

    if(pData->m_pSysData->m_FocusStatus == AlmVolFocus)		//���������ȼ�
    {
        Data[UP_PKG_D15]=pData->m_pSysData->m_AlmVolSet & (BIT0|BIT1|BIT2);
    }
    else
    {
        Data[UP_PKG_D15]=pData->m_pCfgData->m_AlmVolum & (BIT0|BIT1|BIT2);
    }

    if(pData->m_pSysData->m_Sensor1OFF == Status_On) //���������� Status_On-����
    {
        Data[UP_PKG_D16] |= BIT0;
    }
    if(pData->m_pSysData->m_HeaterPOWER == Status_On) //�������쳣 Status_On-����
    {
        Data[UP_PKG_D16] |= BIT1;
    }
    if(pData->m_pSysData->m_WaterHIGH == Status_On) //ˮ�³���״̬ Status_On-����
    {
        Data[UP_PKG_D16] |= BIT2;
    }
    if(pData->m_pSysData->m_E2PROMERR == Status_On)//e2prom���� Status_On-����
    {
        Data[UP_PKG_D16] |= BIT3;
    }
    if(pData->m_pSysData->m_WaterLow == Status_On)//ˮλ��״̬ Status_On-����
    {
        Data[UP_PKG_D16] |= BIT4;
    }
    if(pData->m_pSysData->m_HeaterModeWT1Low == Status_On) //����ģʽ�£��趨ˮ�µ������� Status_On-����
    {
        Data[UP_PKG_D16] |= BIT5;
    }
    if(pData->m_pSysData->m_HeaterModeT1ALM == Status_On) //����ģʽ�£�����1���ޱ���
    {
        Data[UP_PKG_D16] |= BIT6;
    }
    if(pData->m_pSysData->m_HeaterModeT2ALM == Status_On) //����ģʽ�£�����2���ޱ���
    {
        Data[UP_PKG_D16] |= BIT7;
    }
    if(pData->m_pSysData->m_Cycle1Alm == Status_On ) //Һ·1���� Status_Off = 0,	Status_On = 1
    {
        Data[UP_PKG_D17] |= BIT0;
    }
    if(pData->m_pSysData->m_Cycle2Alm == Status_On ) //Һ·2���� Status_Off = 0,	Status_On = 1
    {
        Data[UP_PKG_D17] |= BIT1;
    }
    if(pData->m_pSysData->m_WaterTLow == Status_On ) //ˮ�³���״̬	Status_Off = 0,	Status_On = 1
    {
        Data[UP_PKG_D17] |= BIT2;
    }
    if(pData->m_pSysData->m_Sensor2OFF == Status_On ) //ˮ�³���״̬	Status_Off = 0,	Status_On = 1
    {
        Data[UP_PKG_D17] |= BIT3;
    }
    if(pData->m_pSysData->m_HeaterModeWT2Low == Status_On) //����ģʽ�£��趨ˮ�µ������� Status_On-����
    {
        Data[UP_PKG_D17] |= BIT4;
    }

    Data[UP_PKG_D18] = pData->m_pSysData->m_Cal1Set;		//����1У׼ֵ

    Data[UP_PKG_D19] = pData->m_pSysData->m_Cal2Set;		//����2У׼ֵ

    Data[UP_PKG_DCHK] = 0;
    for(i = UP_PKG_DCMD; i < UP_PKG_DCHK; i++)
    {
        Data[UP_PKG_DCHK] += Data[i];
    }
//	printf("PKG:");
//	for(i=0;i<len;i++)
//	{
//		printf("0x%x ",Data[i]);
//	}
//	printf("\r\n");
    Usart3SendData(Data, UP_PAG_NUM);
}

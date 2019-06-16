//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleCalc.c
//*
//* �ļ����� : CALC����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleCalc.h"
#include "AT24C128.h"
#include "usart4.h"

static PUARTCALCDATA m_UartData = NULL;

BOOLEAN ModuleCalcInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;

    if(pData != NULL)
    {
    }
    return ret;
}

BOOLEAN ModuleCalcReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleCalcStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    pData->m_PressSta = TRUE;
    pData->m_pData->m_Sta = TRUE;
    pData->m_AD_RFlag = 0;
    pData->m_CheckCH = 0; //ͨ��
    pData->m_CheckMod = 0; //������У׼,Ӳ��У׼
    pData->UsartSendFlag = 0;
    return ret;
}

BOOLEAN ModuleCalcStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleCalcRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleCalc10msProcess(void* pArg)
{
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;

    pData->m_Count++;
    if(pData->m_Count % 5 == 0)
    {

    }
    if(pData->UsartSendFlag == 0)
    {
        pData->UsartSendFlag = 1;

    }

    if(pData->ConverTimes_Calc < ADC_Convert_tims_Calc)
    {
        pData->ConverTimes_Calc++;
        pData->Temp1AD_Calc += Get_Adc(ADC_Channel_1);
        pData->Temp2AD_Calc += Get_Adc(ADC_Channel_2);
        pData->Temp3AD_Calc += Get_Adc(ADC_Channel_3);
    }
    else
    {
        pData->AD1Value_Calc = pData->Temp1AD_Calc / ADC_Convert_tims_Calc;
        pData->AD2Value_Calc = pData->Temp2AD_Calc / ADC_Convert_tims_Calc;
        pData->AD3Value_Calc = pData->Temp3AD_Calc / ADC_Convert_tims_Calc;
        pData->ConverTimes_Calc = 0;
        pData->Temp1AD_Calc = 0;
        pData->Temp2AD_Calc = 0;
        pData->Temp3AD_Calc = 0;
    }

}

void ModuleCalc1sProcess(void* pArg)
{
    uint8_t Comp_Cur_INS[10] = {0xef, 0x01, 0x01, 0x01, 0x01, 0x00, 0x17, 0x25, 0x04, 0xFF};
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
//		PS("ModuleCalc1sProcess");
//      uint8_t TEST_Cur_INS[10]={0xef,0x01,0x02,0x03,0x04,0x05,0x17,0x25,0x04,0xFF}; //tommy
//      Uart4SendData(TEST_Cur_INS,10); //tommy
    if(pData->m_AD_RFlag == 2) ////�յ���λ��Ҫ�����¶�ֵ
    {
        //PD(pData->m_AD_RFlag);
        Comp_Cur_INS[1] = pData->m_pData->m_buf[2]; //�ش�ͨ��ֵ
        Comp_Cur_INS[2] = pData->m_pData->m_buf[3]; //�ش�AD�����¶�
        Comp_Cur_INS[3] = 0x00;
        Comp_Cur_INS[4] = 0x00;
        if(pData->m_pData->m_buf[2] == 1)
        {

        }
        if(pData->m_pData->m_buf[2] == 2)
        {

        }
        if(pData->m_pData->m_buf[2] == 3)
        {

        }
        Comp_Cur_INS[8] = Comp_Cur_INS[1] + Comp_Cur_INS[2] + Comp_Cur_INS[3] + Comp_Cur_INS[4] + Comp_Cur_INS[5];
        Comp_Cur_INS[9] = 0xFF;
        Uart4SendData(Comp_Cur_INS, 10);
    }

    if(pData->m_AD_RFlag == 1) //�յ���λ��Ҫ����ADֵҪ��
    {   //PD(pData->AD1Value_Calc);
        //PD(pData->m_AD_RFlag);
        Comp_Cur_INS[1] = pData->m_pData->m_buf[2]; //�ش�ͨ��ֵ
        Comp_Cur_INS[2] = pData->m_pData->m_buf[3]; //�ش�AD�����¶�
        Comp_Cur_INS[3] = 0x00;
        Comp_Cur_INS[4] = 0x00;
        //pData->AD1Value_Calc=2536;
        if(pData->m_pData->m_buf[2] == 1) //ͨ��1��adֵ
        {
            Comp_Cur_INS[6] = (((pData->AD1Value_Calc) & 0xff00) >> 8); //ad���ݵĸ�λ
            Comp_Cur_INS[7] = (pData->AD1Value_Calc & 0x00ff); //ad���ݵĵ�λ
        }
        if(pData->m_pData->m_buf[2] == 2) //ͨ��2��adֵ
        {
            Comp_Cur_INS[6] = (((pData->AD2Value_Calc) & 0xff00) >> 8); //ad���ݵĸ�λ
            Comp_Cur_INS[7] = (pData->AD2Value_Calc & 0x00ff); //ad���ݵĵ�λ
        }
        if(pData->m_pData->m_buf[2] == 3) //ͨ��3��adֵ
        {
            Comp_Cur_INS[6] = (((pData->AD3Value_Calc) & 0xff00) >> 8); //ad���ݵĸ�λ
            Comp_Cur_INS[7] = (pData->AD3Value_Calc & 0x00ff); //ad���ݵĵ�λ
        }
        Comp_Cur_INS[8] = Comp_Cur_INS[1] + Comp_Cur_INS[2] + Comp_Cur_INS[3] + Comp_Cur_INS[4] + Comp_Cur_INS[5];
        Comp_Cur_INS[9] = 0xFF;
//				PS("Uart4SendData");
        Uart4SendData(Comp_Cur_INS, 10);
        //Usart1SendData(Comp_Cur_INS, 10);
    }

}

void ModeleCalcUartProcess(void* pArg)
{
    GetUartData(pArg); //ɨ��ִ�н������
}

void CalcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{

//    switch(MsgId)
//    {
//        case MSG_CALC_SAVE:
//          if(lParam == 1)
//          {
//            //����ִ�����ñ��棬���ô�����
//              CalcSave();
//          }
//          break;
//        default:break;
//    }
//    printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleCalc(PMODULESERVERDATA pServerData)
{
    PMODULECALC pModCalc = NULL;
    PMODULECALCDATA pData = NULL;
    pData->m_pData = NULL;
    pModCalc = (PMODULECALC)malloc(sizeof(MODULECALC));//�������ṹ
    pData = (PMODULECALCDATA)malloc(sizeof(MODULECALCDATA));//����������ݽṹ
    pData->m_pData = NULL;
    pData->m_pData = (PUARTCALCDATA)malloc(sizeof(UARTCALCDATA));
    m_UartData = pData->m_pData;
    ASSERT(pData->m_pData != NULL);
    ASSERT(pModCalc != NULL);
    ASSERT(pData != NULL);

    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModCalc->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModCalc->pModeleInit = ModuleCalcInit; //ʵ��ģ���ʼ��
    pModCalc->pModeleReset = ModuleCalcReset; //ʵ��ģ�鸴λ
    pModCalc->pModeleStart = ModuleCalcStart; //ʵ��ģ�鿪ʼ
    pModCalc->pModeleStop = ModuleCalcStop; //ʵ��ģ�����
    pModCalc->pModeleRelease = ModuleCalcRelease;//ʵ��
    pModCalc->pMsgNotify = CalcMsgNotify;//ʵ����Ϣ���д���
    pModCalc->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModCalc->pModele10msProcess = ModuleCalc10msProcess;//��ʵ�֣���ΪNULL
    pModCalc->pModele50msProcess = NULL;//��ʵ�֣���ΪNULL
    pModCalc->pModele1sProcess = ModuleCalc1sProcess;//ʵ��1s����
    pModCalc->pModeleUartProcess = ModeleCalcUartProcess;//ʵ��UART����
    strcpy(pModCalc->m_ModName, "ModCalc");

    //PD("CreateModuleCalc!!\n");
    return (PMODULEBASE)pModCalc;
}

void SendUartData(uint16_t data)
{
    INT8U i = 0;
    INT16U len;
    //uint8_t Comp_Cur_INS[10]={0xef,0x01,0x01,0x01,0x01,0x00,0x17,0x25,0x04,0xFF};
    //USART_SendData(USART3,data);
    //PS("1");
    if(m_UartData == NULL)
        return;
    //PS("2")
    if(m_UartData->m_index >= CALCDATABUF)
    {
        m_UartData->m_index = 0;
        m_UartData->m_MarkIndex = 0;
        m_UartData->m_MarkSta = FALSE;
        //PS("3");
    }

    m_UartData->m_DataBuf[m_UartData->m_index] = data;

    if(m_UartData->m_DataBuf[m_UartData->m_index] == SOM && m_UartData->m_MarkSta == FALSE)
    {
        m_UartData->m_MarkIndex = m_UartData->m_index;
        m_UartData->m_MarkSta = TRUE;
        //PS("2");
    }

    if(m_UartData->m_DataBuf[m_UartData->m_index] == EOM  && m_UartData->m_DataBuf[m_UartData->m_MarkIndex] == SOM )
    {
        len = m_UartData->m_index - m_UartData->m_MarkIndex + 1;
// 				PD(m_UartData->m_index);
// 				PD(m_UartData->m_MarkIndex);
// 				PD(len);
        //PS("3");
        if(len == CALCBUFMAX && CheckSum( &(m_UartData->m_DataBuf[m_UartData->m_MarkIndex]), len))
        {
            for(i = 0; i < CALCBUFMAX; i++)
            {
                m_UartData->m_buf[i] = m_UartData->m_DataBuf[m_UartData->m_MarkIndex + i];
            }
            //PS("4");
            m_UartData->m_Sta = TRUE;
            m_UartData->m_index = 0;
            m_UartData->m_MarkIndex = 0;
            m_UartData->m_MarkSta = FALSE;
        }
    }
    m_UartData->m_index++;
}

void GetUartData(void* pArg)
{
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    if(pData->m_pData->m_Sta == TRUE)
    {
        pData->m_pData->m_Sta = FALSE;
        //PS("Unpack");
        Unpack(pArg, pData->m_pData->m_buf, CALCBUFMAX );
    }
}

BOOLEAN CheckSum(INT16U* buf, INT8U len)
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

void SensorCheck(void* pArg) //������У׼
{
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    if(pData->m_CheckCH == 1) //��ҪУ׼��ͨ��
    {
        if(pData->m_pData->m_buf[2] == 1) //ֵ��ad
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH1ADArr[0] = (pData->m_pData->m_buf[4] << 8) + (pData->m_pData->m_buf[5]);
//								   PD("��һ����ad");
//								   PD(pData->m_pSysData->m_CH1ADArr[0]);
            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH1ADArr[1] = (pData->m_pData->m_buf[4] << 8) + (pData->m_pData->m_buf[5]);
//								  PD("��2����ad");
//								  PD(pData->m_pSysData->m_CH1ADArr[1]);
            }
        }
        if(pData->m_pData->m_buf[2] == 2) //ֵ���¶�
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH1TEMPArr[0] = (pData->m_pData->m_buf[4] << 8) + (pData->m_pData->m_buf[5]);
//								  PD("�¶�1");
//								  PD(pData->m_pSysData->m_CH1TEMPArr[0]);
            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH1TEMPArr[1] = (pData->m_pData->m_buf[4] << 8) + (pData->m_pData->m_buf[5]);
//								 PD("�¶�2");
//								 PD(pData->m_pSysData->m_CH1TEMPArr[1]);
            }
        }
    }
    if(pData->m_CheckCH == 2)
    {
        if(pData->m_pData->m_buf[2] == 1) //ֵ��ad
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH2ADArr[0] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];

            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH2ADArr[1] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
        }
        if(pData->m_pData->m_buf[2] == 2) //ֵ���¶�
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH2TEMPArr[0] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH2TEMPArr[1] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
        }
    }
    if(pData->m_CheckCH == 3)
    {
        if(pData->m_pData->m_buf[2] == 1) //ֵ��ad
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH3ADArr[0] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH3ADArr[1] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
        }
        if(pData->m_pData->m_buf[2] == 2) //ֵ���¶�
        {
            if(pData->m_pData->m_buf[3] == 1) //��1����
            {
                pData->m_pCalData->m_CH3TEMPArr[0] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
            if(pData->m_pData->m_buf[3] == 2) //��2����
            {
                pData->m_pCalData->m_CH3TEMPArr[1] = (pData->m_pData->m_buf[4] << 8) + pData->m_pData->m_buf[5];
            }
        }
    }
}
void  HardwareCheck(void* pArg)  //Ӳ��У׼
{
    PMODULECALCDATA pData = (PMODULECALCDATA)pArg;
    if(pData->m_CheckCH == 1)
    {

    }
    if(pData->m_CheckCH == 2)
    {

    }
    if(pData->m_CheckCH == 3)
    {

    }
}


////////CMD BYTE define/////////////
#define CMD_CALC_START 1
#define CMD_SET_VREF 2
#define CMD_AD_VAL 3
#define CMD_TEMP_VAL 4
#define CMD_CALC_STOP 5
#define CMD_CALC_END  6
#define CMD_CALC_SINGLEMODE 7  //��̺ģʽ

#define CMD_BYTE 1
#define VAL_BYTE 2
#define DATA_BYTE 3
void Unpack(void* pArg, INT16U *pData, INT8U len)
{
    PMODULECALCDATA pObjData = (PMODULECALCDATA)pArg;
    INT8U i;
    INT16U val;
    // uint8_t Comp_Cur_INS[10]={0xef,0x01,0x01,0x01,0x01,0x00,0x17,0x25,0x04,0xFF};
    //ef 01 01 01 01 00 17 25 04 ff

//		PSYSTEMCONFIGDATA pSysData = pObjData->m_pSysData->pSys;
//    INT16U PointNo = 0;

    ///////////////////��ӡ���ݰ�//////////////////////////
// 		printf("��ӡ���ݰ�Receive DATA: ");
// 		for(i=0;i<len;i++)
// 		{
// 			printf("0x%x ",pData[i]);
// 		}
// 		printf("\r\n");
    ///////////////////��ӡ���ݰ�//////////////////////////

/////////////////////////���ݰ���Э����///////////////////
    switch(pData[CMD_BYTE])
    {
    case CMD_CALC_START://01
        //USART_SendData(USART3, 0xfd); //tommy test
        break;
    case CMD_SET_VREF://02
        //PD(pData[3]);
        pObjData->m_AD_RFlag = pData[3];
        break;
    case CMD_AD_VAL://03
        pObjData->m_CheckCH = pData[2]; //ͨ��
        pObjData->m_CheckMod = pData[3]; //������У׼,Ӳ��У׼
        break;
    case CMD_TEMP_VAL://04
        if(pObjData->m_CheckMod == 1)
        {
            SensorCheck(pArg); //������У׼
        }
        if(pObjData->m_CheckMod == 2)
        {
            HardwareCheck(pArg); //Ӳ��У׼
        }
        break;
    case CMD_CALC_STOP://05  ���ͱ������Ϣ
        PS("CMD_CALC_STOP");
        if(pObjData->m_pMsgQueue != NULL)
        {
            //printf("-----05------");
            pObjData->m_pMsgQueue->push_back(pObjData->m_pMsgQueue->pData, MS_CONFIG_CMD, CALCDATASAVE, CMD_START, NULL); //see msg_def.h
        }
        break;
    case CMD_CALC_END://06
        PS("CMD_CALC_END");
        break;
    case CMD_CALC_SINGLEMODE://07
        if(pData[2] == 1)
        {
            //1�ǵ�̺ģʽ,0��˫̺ģʽ
            pObjData->m_pCalData->m_SingleMode = Status_On;
        }
        else
        {
            pObjData->m_pCalData->m_SingleMode = Status_Off;
        }
        break;
    default:
        break;
    }
/////////////////////////���ݰ���Э����///////////////////
}




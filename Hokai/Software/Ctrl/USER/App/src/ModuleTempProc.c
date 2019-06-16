//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleTempProc.c
//*
//* �ļ����� : TEMPPROC����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleTempProc.h"
#include "adc.h"
#include "usart.h"

/////////////////Ӳ��У׼ֵ��������E2PROM��ȡ/////////////////////
//	INT16U m_CH1ADArr[ADCALCDATANUM];
//	INT16U m_CH1TEMPArr[ADCALCDATANUM];
//	INT16U m_CH2ADArr[ADCALCDATANUM];
//	INT16U m_CH2TEMPArr[ADCALCDATANUM];
//	INT16U m_CH3ADArr[ADCALCDATANUM];
//	INT16U m_CH3TEMPArr[ADCALCDATANUM];
//
//	/////////////////Ӳ��У׼����ֵ���������������ݼ�����ȡ/////////////////////
//	FP32 m_AD1CalcK; //AD1У׼ֵ
//	FP32 m_AD1CalcB; //AD1У׼ֵ
//	FP32 m_AD2CalcK; //AD1У׼ֵ
//	FP32 m_AD2CalcB; //AD1У׼ֵ
//	FP32 m_AD3CalcK; //AD1У׼ֵ
//	FP32 m_AD3CalcB; //AD1У׼ֵ

void Calc_K_B_Value(PMODULETEMPPROCDATA pData)//����k_b��ֵ
{
//		  INT16U  i;
//	for(i=0;i<ADCALCDATANUM;i++){
//			PD(pData->m_pSysData->m_CH1ADArr[i]);
//			PD(pData->m_pSysData->m_CH1TEMPArr[i]);
//		}
    //ad��x.�¶���y
//    PD(pData->m_pCfgData->m_CH1ADArr);
    pData->m_pSysData->m_AD1CalcK = calculateSlope(   pData->m_pCalData->m_CH1ADArr, pData->m_pCalData->m_CH1TEMPArr);

    //pData->m_pSysData->m_AD1CalcK=0.4;
    pData->m_pSysData->m_AD1CalcB = calculateConstant(pData->m_pCalData->m_CH1ADArr, pData->m_pCalData->m_CH1TEMPArr);
    //pData->m_pSysData->m_AD1CalcB=2725;
    pData->m_pSysData->m_AD2CalcK = calculateSlope(   pData->m_pCalData->m_CH2ADArr, pData->m_pCalData->m_CH2TEMPArr);
    pData->m_pSysData->m_AD2CalcB = calculateConstant(pData->m_pCalData->m_CH2ADArr, pData->m_pCalData->m_CH2TEMPArr);

    pData->m_pSysData->m_AD3CalcK = calculateSlope(   pData->m_pCalData->m_CH3ADArr, pData->m_pCalData->m_CH3TEMPArr);
    pData->m_pSysData->m_AD3CalcB = calculateConstant(pData->m_pCalData->m_CH3ADArr, pData->m_pCalData->m_CH3TEMPArr);
}


//����Kֵ
FP32 calculateSlope(INT16U x_V[2], INT16U y_V[2])
{

    // return (y_V[1] - y_V[0]) / (x_V[1] - x_V[0]);
    FP32  returnValue;
    FP32  calc_Y;
    FP32  calc_X;
    calc_Y = y_V[1] - y_V[0];
    calc_X = x_V[1] - x_V[0];
    returnValue = calc_Y / calc_X;
//	   PD(x_V[0]);
//	   PD(x_V[1]);
//	   PD(y_V[0]);
//	   PD(y_V[1]);
//	   printf("calc_Y=%f",calc_Y);
//	   printf("calc_X=%f",calc_X);
    return  returnValue;
}

//���㳣��b
FP32 calculateConstant(INT16U x_V[2], INT16U y_V[2])
{
    //return (y_V[1]*(x_V[1] - x_V[0]) - x_V[1]*(y_V[1] - y_V[0])) / (x_V[1] - x_V[0]);


    FP32 return_Vlaue;
    FP32 y_x = (y_V[1] * (x_V[1] - x_V[0]) - x_V[1] * (y_V[1] - y_V[0]));
    FP32 xx = (x_V[1] - x_V[0]);
    return_Vlaue = y_x / xx;

    return return_Vlaue;
}

void GetTemp1(PMODULETEMPPROCDATA pData)//����1
{
//    pData->m_pSysData->m_Temp1 = pData->AD1Value*(pData->m_pSysData->m_AD1CalcK)+pData->m_pSysData->m_AD1CalcB;
    if(pData->m_pCalData->m_SingleMode == 1)
    {
        pData->m_pSysData->m_Temp1 = pData->AD1Value * (pData->m_pSysData->m_AD1CalcK) + pData->m_pSysData->m_AD1CalcB + pData->m_pAdjData->m_Cal1Set * 10;
    }
    else {
        pData->m_pSysData->m_Temp1 = pData->AD2Value * (pData->m_pSysData->m_AD2CalcK) + pData->m_pSysData->m_AD2CalcB + pData->m_pAdjData->m_Cal1Set * 10;
    }

//	PD(pData->AD2Value);
    //�ж��ǵ�̺ģʽ,����˫̺ģʽ,1��̺ģʽ,�Ͱ��¶�1д�̶�ֵ,���������� TODO
//    if(pData->m_pSysData->m_SingleMode == 1)
//    {
//        pData->m_pSysData->m_Temp1 = 3400;
//    }
//		PD(pData->m_pSysData->m_Temp1);

}

void GetTemp2(PMODULETEMPPROCDATA pData)//����2
{
    if(pData->m_pCalData->m_SingleMode != 1)
    {
//    pData->m_pSysData->m_Temp2 = pData->AD2Value*(pData->m_pSysData->m_AD2CalcK)+pData->m_pSysData->m_AD2CalcB;
        pData->m_pSysData->m_Temp2 = pData->AD1Value * (pData->m_pSysData->m_AD1CalcK) + pData->m_pSysData->m_AD1CalcB + pData->m_pAdjData->m_Cal2Set * 10;
    }
    else {
        pData->m_pSysData->m_Temp2 = 3400;
    }
//	PD(pData->AD1Value);
//PD(pData->m_pSysData->m_Temp2);
}

void GetWaterTemp(PMODULETEMPPROCDATA pData)//ˮ��
{
    pData->m_pSysData->m_WaterTemp = pData->AD3Value * (pData->m_pSysData->m_AD3CalcK) + pData->m_pSysData->m_AD3CalcB;
//	PD(pData->m_pSysData->m_WaterTemp);
}

BOOLEAN ModuleTempProcInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    // AT24CXX_WriteOneByte(0x01,120);

    if(pData != NULL)
    {

    }
    return ret;
}

BOOLEAN ModuleTempProcReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->T_Count = 0;
    return ret;
}

BOOLEAN ModuleTempProcStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    pData->m_PressSta = TRUE;
    pData->ConverTimes = 0;
    pData->Temp1AD = 0;
    pData->Temp2AD = 0;
    pData->Temp3AD = 0;

    return ret;
}

BOOLEAN ModuleTempProcStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleTempProcRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleTempProc1msProcess(void* pArg)
{
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;

    if(pData->ConverTimes < ADC_Convert_tims)
    {
        pData->ConverTimes++;
        pData->Temp1AD += Get_Adc(ADC_Channel_1);
        pData->Temp2AD += Get_Adc(ADC_Channel_2);
        pData->Temp3AD += Get_Adc(ADC_Channel_3);
    }
    else
    {
        pData->AD1Value = pData->Temp1AD / ADC_Convert_tims;
        pData->AD2Value = pData->Temp2AD / ADC_Convert_tims;
        pData->AD3Value = pData->Temp3AD / ADC_Convert_tims;
        pData->ConverTimes = 0;
        pData->Temp1AD = 0;
        pData->Temp2AD = 0;
        pData->Temp3AD = 0;
        GetTemp1(pData);//����1
        GetTemp2(pData);//����2
        GetWaterTemp(pData);//ˮ��
    }
    //printf("eeprom = %d\r\n",AT24CXX_ReadOneByte(0x01));
}

void TempProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
    //MSG_TEMPPROC_SAVE
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    switch(MsgId)
    {
    case MS_CONFIG_CMD:

        if(lParam == CONFIGINIT && wParam == CMD_STOP)
        {
            Calc_K_B_Value(pData);//����k��bֵ
        }
        break;
    default:
        break;
    }
//    printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleTempProc(PMODULESERVERDATA pServerData)
{
    PMODULETEMPPROC pModTempProc = NULL;
    PMODULETEMPPROCDATA pData = NULL;

    pModTempProc = (PMODULETEMPPROC)malloc(sizeof(MODULETEMPPROC));//�������ṹ
    pData = (PMODULETEMPPROCDATA)malloc(sizeof(MODULETEMPPROCDATA));//����������ݽṹ
    assert(pModTempProc != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModTempProc->m_pBaseData = (PVOID)pData;


    //************************����ģ��ӿڱ��븳ֵ******************************
    pModTempProc->pModeleInit = ModuleTempProcInit; //ʵ��ģ���ʼ��
    pModTempProc->pModeleReset = ModuleTempProcReset; //ʵ��ģ�鸴λ
    pModTempProc->pModeleStart = ModuleTempProcStart; //ʵ��ģ�鿪ʼ
    pModTempProc->pModeleStop = ModuleTempProcStop; //ʵ��ģ�����
    pModTempProc->pModeleRelease = ModuleTempProcRelease;//ʵ��
    pModTempProc->pMsgNotify = TempProcMsgNotify;//ʵ����Ϣ���д���
    pModTempProc->pModele1msProcess = ModuleTempProc1msProcess;//��ʵ�֣���ΪNULL
    pModTempProc->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModTempProc->pModele50msProcess = NULL;//��ʵ�֣���ΪNULL
    pModTempProc->pModele1sProcess = NULL;//ʵ��1s����
    pModTempProc->pModeleUartProcess = NULL;//ʵ��UART����
    pModTempProc->pStart = NULL;
    strcpy(pModTempProc->m_ModName, "ModTempProc");

    //PD("CreateModuleTempProc!!\n");
    return (PMODULEBASE)pModTempProc;
}


//********************************************************************************************************


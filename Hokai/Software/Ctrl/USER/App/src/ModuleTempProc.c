//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleTempProc.c
//*
//* 文件描述 : TEMPPROC任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleTempProc.h"
#include "adc.h"
#include "usart.h"

/////////////////硬件校准值，开机从E2PROM读取/////////////////////
//	INT16U m_CH1ADArr[ADCALCDATANUM];
//	INT16U m_CH1TEMPArr[ADCALCDATANUM];
//	INT16U m_CH2ADArr[ADCALCDATANUM];
//	INT16U m_CH2TEMPArr[ADCALCDATANUM];
//	INT16U m_CH3ADArr[ADCALCDATANUM];
//	INT16U m_CH3TEMPArr[ADCALCDATANUM];
//
//	/////////////////硬件校准计算值，开机从配置数据计算后获取/////////////////////
//	FP32 m_AD1CalcK; //AD1校准值
//	FP32 m_AD1CalcB; //AD1校准值
//	FP32 m_AD2CalcK; //AD1校准值
//	FP32 m_AD2CalcB; //AD1校准值
//	FP32 m_AD3CalcK; //AD1校准值
//	FP32 m_AD3CalcB; //AD1校准值

void Calc_K_B_Value(PMODULETEMPPROCDATA pData)//计算k_b的值
{
//		  INT16U  i;
//	for(i=0;i<ADCALCDATANUM;i++){
//			PD(pData->m_pSysData->m_CH1ADArr[i]);
//			PD(pData->m_pSysData->m_CH1TEMPArr[i]);
//		}
    //ad是x.温度是y
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


//计算K值
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

//计算常数b
FP32 calculateConstant(INT16U x_V[2], INT16U y_V[2])
{
    //return (y_V[1]*(x_V[1] - x_V[0]) - x_V[1]*(y_V[1] - y_V[0])) / (x_V[1] - x_V[0]);


    FP32 return_Vlaue;
    FP32 y_x = (y_V[1] * (x_V[1] - x_V[0]) - x_V[1] * (y_V[1] - y_V[0]));
    FP32 xx = (x_V[1] - x_V[0]);
    return_Vlaue = y_x / xx;

    return return_Vlaue;
}

void GetTemp1(PMODULETEMPPROCDATA pData)//体温1
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
    //判断是单毯模式,还是双毯模式,1单毯模式,就把温度1写固定值,让他不报警 TODO
//    if(pData->m_pSysData->m_SingleMode == 1)
//    {
//        pData->m_pSysData->m_Temp1 = 3400;
//    }
//		PD(pData->m_pSysData->m_Temp1);

}

void GetTemp2(PMODULETEMPPROCDATA pData)//体温2
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

void GetWaterTemp(PMODULETEMPPROCDATA pData)//水温
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
        GetTemp1(pData);//体温1
        GetTemp2(pData);//体温2
        GetWaterTemp(pData);//水温
    }
    //printf("eeprom = %d\r\n",AT24CXX_ReadOneByte(0x01));
}

void TempProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
    //MSG_TEMPPROC_SAVE
    PMODULETEMPPROCDATA pData = (PMODULETEMPPROCDATA)pArg;
    switch(MsgId)
    {
    case MS_CONFIG_CMD:

        if(lParam == CONFIGINIT && wParam == CMD_STOP)
        {
            Calc_K_B_Value(pData);//计算k和b值
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

    pModTempProc = (PMODULETEMPPROC)malloc(sizeof(MODULETEMPPROC));//申请基类结构
    pData = (PMODULETEMPPROCDATA)malloc(sizeof(MODULETEMPPROCDATA));//申请基类数据结构
    assert(pModTempProc != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModTempProc->m_pBaseData = (PVOID)pData;


    //************************以下模块接口必须赋值******************************
    pModTempProc->pModeleInit = ModuleTempProcInit; //实现模块初始化
    pModTempProc->pModeleReset = ModuleTempProcReset; //实现模块复位
    pModTempProc->pModeleStart = ModuleTempProcStart; //实现模块开始
    pModTempProc->pModeleStop = ModuleTempProcStop; //实现模块结束
    pModTempProc->pModeleRelease = ModuleTempProcRelease;//实现
    pModTempProc->pMsgNotify = TempProcMsgNotify;//实现消息队列处理
    pModTempProc->pModele1msProcess = ModuleTempProc1msProcess;//不实现，置为NULL
    pModTempProc->pModele10msProcess = NULL;//不实现，置为NULL
    pModTempProc->pModele50msProcess = NULL;//不实现，置为NULL
    pModTempProc->pModele1sProcess = NULL;//实现1s调用
    pModTempProc->pModeleUartProcess = NULL;//实现UART调用
    pModTempProc->pStart = NULL;
    strcpy(pModTempProc->m_ModName, "ModTempProc");

    //PD("CreateModuleTempProc!!\n");
    return (PMODULEBASE)pModTempProc;
}


//********************************************************************************************************


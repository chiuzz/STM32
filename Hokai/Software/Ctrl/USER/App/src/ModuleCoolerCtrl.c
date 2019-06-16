//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleCoolerCtrl.c
//*
//* 文件描述 : COOLERCTRL任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleCoolerCtrl.h"

BOOLEAN ModuleCoolerCtrlInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    if(pData != NULL)
    {
        pData->m_CoolCount = MODE_CHANGE_TIME - MODE_CHANGE_ECHO_SEC * 5;
        pData->m_CoolerSMachine = COOLER_OFF;
    }
    return ret;
}

BOOLEAN ModuleCoolerCtrlReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleCoolerCtrlStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleCoolerCtrlStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleCoolerCtrlRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleCoolerCtrl1sProcess(void* pArg)
{
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    //printf("ModuleCoolerCtrl1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
}

void ModuleCoolerCtrl50msProcess(void* pArg)
{
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    //printf("ModuleCoolerCtrl1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;

    CoolerWorkMachineProc(pArg); //每50ms运行
}

void CoolerCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    switch(MsgId)
    {
    case MS_COOLER_CMD:
        if(lParam == 0) {
            if(wParam) {
                pData->m_CoolerSMachine = COOLER_ON;//启动
                PS("COOLER_ON");
            }
            else {
                pData->m_CoolerSMachine = COOLER_OFF;//停止
                PS("COOLER_OFF");
            }
        }
        break;
    default:
        break;
    }
}

PMODULEBASE CreateModuleCoolerCtrl(PMODULESERVERDATA pServerData)
{
    PMODULECOOLERCTRL pModCoolerCtrl = NULL;
    PMODULECOOLERCTRLDATA pData = NULL;

    pModCoolerCtrl = (PMODULECOOLERCTRL)malloc(sizeof(MODULECOOLERCTRL));//申请基类结构
    pData = (PMODULECOOLERCTRLDATA)malloc(sizeof(MODULECOOLERCTRLDATA));//申请基类数据结构
    assert(pModCoolerCtrl != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModCoolerCtrl->m_pBaseData = (PVOID)pData;

    //************************以下模块接口必须赋值******************************
    pModCoolerCtrl->pModeleInit = ModuleCoolerCtrlInit; //实现模块初始化
    pModCoolerCtrl->pModeleReset = ModuleCoolerCtrlReset; //实现模块复位
    pModCoolerCtrl->pModeleStart = ModuleCoolerCtrlStart; //实现模块开始
    pModCoolerCtrl->pModeleStop = ModuleCoolerCtrlStop; //实现模块结束
    pModCoolerCtrl->pModeleRelease = ModuleCoolerCtrlRelease;//实现
    pModCoolerCtrl->pMsgNotify = CoolerCtrlMsgNotify;//实现消息队列处理
    pModCoolerCtrl->pModele1msProcess = NULL;//不实现，置为NULL
    pModCoolerCtrl->pModele10msProcess = NULL;//不实现，置为NULL
    pModCoolerCtrl->pModele50msProcess = ModuleCoolerCtrl50msProcess;//不实现，置为NULL
    pModCoolerCtrl->pModele1sProcess = ModuleCoolerCtrl1sProcess;//实现1s调用
    pModCoolerCtrl->pModeleUartProcess = NULL;//实现UART调用
    strcpy(pModCoolerCtrl->m_ModName, "ModCoolerCtrl");

    //PD("CreateModuleCoolerCtrl!!\n");
    return (PMODULEBASE)pModCoolerCtrl;
}
//#define COOL_PROTECT_TEMP 200

static eCoolerSMachine g_CoolerSMachine;

void CoolerWorkMachineProc(void* pArg) //每1s运行 温度x100 3555=35.55度
{
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    INT16U WaterTemp =	pData->m_pSysData->m_WaterTemp;
    INT16U WaterSetTemp =	pData->m_pCfgData->m_WaterTempSet_Cool;
    INT16S err, Ival, tmp;

//	if(g_CoolerSMachine != pData->m_CoolerSMachine)
//		PD(pData->m_CoolerSMachine);
//		g_CoolerSMachine = pData->m_CoolerSMachine;

    if(pData->m_CoolCount > 0)
    {
        pData->m_CoolCount--;
    }

    switch(pData->m_CoolerSMachine)
    {
    default:
    case COOLER_OFF:
//			  PS("COOLER_OFF");
        if(pData->m_pSysData->m_WaterHIGH == Status_On) { //水温过高的处理逻辑
            pData->m_CoolerSMachine = COOLER_CON_START;
        }
        else {
            SetCoolerWork(Status_Off);
            pData->m_pSysData->m_Cooler = Status_Off;
            pData->m_CoolCount = MODE_CHANGE_ECHO_SEC * 5;
        }
        break;
    case COOLER_ON:
//			PS("COOLER_ON");
        if(pData->m_pSysData->m_Float1Status == Status_Off && pData->m_pSysData->m_Float2Status == Status_Off && WaterSetTemp < 600)
        {
            WaterSetTemp = 600; //不开循环时，水温控制最低6度。
        } //Check
//PD(WaterTemp);
//				PD(WaterSetTemp);
        if(WaterTemp > WaterSetTemp + 100)
        {
//					PS("1");
            pData->m_CoolerSMachine = COOLER_START_HOLD;
        }
        if(WaterTemp < WaterSetTemp - 100)
        {
//					PS("2");
            pData->m_CoolerSMachine = COOLER_STOP_HOLD;
        }
        break;
    case COOLER_START_HOLD:
//			  PD(pData->m_CoolCount);
//		PD(MODE_CHANGE_TIME);
        if(pData->m_CoolCount == 0 ) {
//					PS("COOLER_START_HOLD");
            pData->m_CoolerSMachine = COOLER_START;
            break;
        }
        pData->m_CoolerSMachine = COOLER_ON;
        break;
    case COOLER_START:
//			PS("COOLER_START");
        SetCoolerWork(Status_On);
        pData->m_pSysData->m_Cooler = Status_On;
        pData->m_CoolCount = MODE_CHANGE_TIME;
        pData->m_CoolerSMachine = COOLER_ON;
        break;
    case COOLER_CON_START:
//			PS("COOLER_CON_START");
        SetCoolerWork(Status_On);
        pData->m_pSysData->m_Cooler = Status_On;
        pData->m_CoolerSMachine = COOLER_OFF;
        break;
    case COOLER_STOP_HOLD:
//			  PD(pData->m_CoolCount);
        if(pData->m_CoolCount == 0 ) {
//					PS("COOLER_STOP_HOLD");
            pData->m_CoolerSMachine = COOLER_STOP;
            break;
        }
        pData->m_CoolerSMachine = COOLER_ON;
        break;
    case COOLER_STOP:
//			PS("COOLER_STOP");
        SetCoolerWork(Status_Off);
        pData->m_pSysData->m_Cooler = Status_Off;
        pData->m_CoolCount = MODE_CHANGE_TIME;
        pData->m_CoolerSMachine = COOLER_ON;
        break;
    }
}


//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleSystemProc.c
//*
//* 文件描述 : SYSTEMPROC任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleSystemProc.h"
#include "usart.h"

//配置值设置范围
#define COOLTEMPLOW 3000
#define COOLTEMPHIGH 4000
#define COOLWATERLOW 400
#define COOLWATERHIGH 2000

#define HOTTEMPLOW 3000
#define HOTTEMPHIGH 3700
#define HOTWATERLOW 3500
#define HOTWATERHIGH 4000

#define Version 2020
//#define Version2 2
BOOLEAN ModuleSystemProcInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    if(pData != NULL)
    {
        pData->m_pSysData->m_Bump1Status = Status_Off;
        pData->m_pSysData->m_Bump2Status = Status_Off;
        pData->m_SystemMAC = SYSTEM_CHECK;
        pData->m_SystemWorkSta = SYSTEM_INVALID;
        pData->m_pSysData->m_Float1Status = Status_Off;
        pData->m_pSysData->m_Float2Status = Status_Off;
        pData->m_pSysData->m_Sensor1OFF = Status_Off;
        pData->m_pSysData->m_Sensor2OFF = Status_Off;
        pData->m_pSysData->m_HeaterPOWER = Status_Off;
        pData->m_pSysData->m_WaterHIGH = Status_Off;
        pData->m_pSysData->m_WaterTLow = Status_Off;
        pData->m_pSysData->m_WaterLow = Status_Off;
        pData->m_pSysData->m_HeaterModeWT1Low = Status_Off;
        pData->m_pSysData->m_HeaterModeWT2Low = Status_Off;
        pData->m_WorkModePressKey = FALSE;
        pData->m_Bump1PressKey = FALSE;
        pData->m_Bump2PressKey = FALSE;
        pData->m_Bump1Sta = BUMP_INVALID;
        pData->m_Bump2Sta = BUMP_INVALID;
        pData->m_pSysData->m_Cycle1Alm = Status_Off;
        pData->m_pSysData->m_Cycle2Alm = Status_Off;
        pData->m_E2PROMERROR = FALSE;
        pData->m_pSysData->m_Temp1Set = INVALID_16BIT_VOL;
        pData->m_pSysData->m_Temp2Set = INVALID_16BIT_VOL;
        pData->m_pSysData->m_WaterTemp = Version;
//				pData->m_pSysData->m_WaterTempSet = INVALID_16BIT_VOL;
    }
    return ret;
}

BOOLEAN ModuleSystemProcReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleSystemProcStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    pData->m_PressSta = TRUE;

    return ret;
}

BOOLEAN ModuleSystemProcStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleSystemProcRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleSystemProc50sProcess(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    // printf("ModuleSystemProc1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    if(pData->m_SystemMAC != SYSTEM_MONITOR)
        return;
//		PD(pData->m_SystemWorkSta);
    SystemWorkStatusProc(pArg); //系统状态控制流程
    Bump1WorkStatusProc(pArg); //水泵1控制流程
    Bump2WorkStatusProc(pArg); //水泵2控制流程
}
#define ALMMUTETIME 10
void ModuleSystemProc1sProcess(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
//	printf("ModuleSystemProc1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    if(pData->m_Count < ALMMUTETIME)
        pData->m_Count++;
    SystemMachineProc(pArg); //系统控制器流程

    if(pData->m_SystemMAC != SYSTEM_MONITOR)
        return;
//    SystemWorkStatusProc(pArg); //系统状态控制流程
}

void SystemProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    switch(MsgId)
    {
    case MS_CONFIG_CMD:
        if(lParam == CONFIGINIT && wParam == CMD_STOP)
        {
//					PS("");
            switch(pData->m_pCfgData->m_SystemSta) //完成工作模式的初始化管理
            {
            default:
            case Stop:
                PS("----Work----Stop------");
                pData->m_SystemWorkSta = SYSTEM_STOP;
                break;
            case Cooler:
                PS("Work On Cooler!!!");
                pData->m_SystemWorkSta = SYSTEM_COOLER;
                break;
            case Heater:
                PS("Work On Heater!!!");
                pData->m_SystemWorkSta = SYSTEM_HEATER;
                break;
            }
//						PD(pData->m_pCfgData->m_SystemSta);
            if(pData->m_pCfgData->m_SystemSta == Stop) //边界处理
            {
                pData->m_pCfgData->m_Cycle1Set = Status_Off;
                pData->m_pCfgData->m_Cycle2Set = Status_Off;
            }
//						PD(pData->m_pCfgData->m_Cycle1Set);
            if(pData->m_pCfgData->m_Cycle1Set == Status_Off) //完成泵的初始化管理
            {
                pData->m_Bump1Sta = BUMP_STOP;
                PS("m_Bump1Sta 停止");
            }
            else {
                pData->m_Bump1Sta = BUMP_START;
                PS("m_Bump1Sta 开始");
            }
//						PD(pData->m_pCfgData->m_Cycle2Set);
            if(pData->m_pCfgData->m_Cycle2Set == Status_Off)
            {
                pData->m_Bump2Sta = BUMP_STOP;
                PS("m_Bump2Sta 停止");
            }
            else {
                pData->m_Bump2Sta = BUMP_START;
                PS("m_Bump2Sta 开始");
            }
        }
        if(lParam == E2PROMERR && wParam == CMD_STOP)
        {
            pData->m_E2PROMERROR = TRUE;
        }
        pData->m_SystemMAC = SYSTEM_MONITOR; //系统主控制完配置的初始化，进入监测模式。
        break;
    default:
        break;
    case MS_KEY_CMD:
        if(pData->m_SystemMAC != SYSTEM_MONITOR || lParam == 0)
            break;
        //					PS("MS_KEY_CMD");
        if( wParam == KEY_WORK_MODE)
        {
//					PS("KEY_WORK_MODE");
            if(pData->m_SystemWorkSta == SYSTEM_STOP_HOLD ||  pData->m_SystemWorkSta == SYSTEM_COOLER_HOLD || pData->m_SystemWorkSta == SYSTEM_HEATER_HOLD) {
                pData->m_WorkModePressKey = TRUE;
            }
        }
        if( wParam == KEY_BUMP1)
        {
//					PS("m_Bump1PressKey");
            pData->m_Bump1PressKey = TRUE;
        }

        if(wParam == KEY_DEC) {
//					PS("TrigerDecSet");
            TrigerDecSet(pData);
        }
        if(wParam == KEY_ADD) {
//					PS("TrigerAddSet");
            TrigerAddSet(pData);
        }
        if(wParam == KEY_WATER) {
//					PS("TrigerTempWaterSet");
            TrigerTempWaterSet(pData);
        }
        if(wParam == KEY_TEMP1) {
//					PS("TrigerTemp1Set");
            TrigerTemp1Set(pData);
        }

        if(wParam == KEY3) {
            TrigerTemp2Set(pData);
        }
        if(wParam == KEY2) {
            pData->m_Bump2PressKey = TRUE;
        }
        if(wParam == KEY_ALMVOL) {
            TrigerAlmvolSet(pData);
        }
        if(wParam == KEY_CAL1) {
            TrigerCal1Set(pData);
        }
        if(wParam == KEY_CAL2) {
            TrigerCal2Set(pData);
        }
        if(wParam == 0x1f) {
					if(pData->m_SystemWorkSta == SYSTEM_STOP_HOLD)
					{
						SetBump1Work(TRUE);
						SetBump2Work(TRUE);
						pData->m_SystemMAC = 0xff;
					}
        }
        break;
    }
//    printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleSystemProc(PMODULESERVERDATA pServerData)
{
    PMODULESYSTEMPROC pModSystemProc = NULL;
    PMODULESYSTEMPROCDATA pData = NULL;

    pModSystemProc = (PMODULESYSTEMPROC)malloc(sizeof(MODULESYSTEMPROC));//申请基类结构
    pData = (PMODULESYSTEMPROCDATA)malloc(sizeof(MODULESYSTEMPROCDATA));//申请基类数据结构
    assert(pModSystemProc != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModSystemProc->m_pBaseData = (PVOID)pData;

    //************************以下模块接口必须赋值******************************
    pModSystemProc->pModeleInit = ModuleSystemProcInit; //实现模块初始化
    pModSystemProc->pModeleReset = ModuleSystemProcReset; //实现模块复位
    pModSystemProc->pModeleStart = ModuleSystemProcStart; //实现模块开始
    pModSystemProc->pModeleStop = ModuleSystemProcStop; //实现模块结束
    pModSystemProc->pModeleRelease = ModuleSystemProcRelease;//实现
    pModSystemProc->pMsgNotify = SystemProcMsgNotify;//实现消息队列处理
    pModSystemProc->pModele1msProcess = NULL;//不实现，置为NULL
    pModSystemProc->pModele10msProcess = NULL;//不实现，置为NULL
    pModSystemProc->pModele50msProcess = ModuleSystemProc50sProcess;//不实现，置为NULL
    pModSystemProc->pModele1sProcess = ModuleSystemProc1sProcess;//实现1s调用
    pModSystemProc->pModeleUartProcess = NULL;//实现UART调用
    strcpy(pModSystemProc->m_ModName, "ModSystemProc");

    //PD("CreateModuleSystemProc!!\n");
    return (PMODULEBASE)pModSystemProc;
}
//#define SHOW_SYSTEM_MAC
void SystemMachineProc(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    switch(pData->m_SystemMAC)
    {
    default:
    case SYSTEM_CHECK:
//        PS("SYSTEM_CHECK");
        pData->m_SystemMAC = SYSTEM_CHEKC_E2PROM;
        break;
    case SYSTEM_CHEKC_E2PROM:
//        PS("SYSTEM_CHEKC_E2PROM");
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGINIT, CMD_START, NULL); //见msg_def.h
        pData->m_SystemMAC = SYSTEM_CHEKC_E2PROM_HOLD;
        break;
    case SYSTEM_CHEKC_E2PROM_HOLD:
//        PS("SYSTEM_CHEKC_E2PROM_HOLD");
        break;
    case SYSTEM_MONITOR:
//        PS("SYSTEM_MONITOR");
        SystemMonitor(pArg);
        break;
    }
}

void SystemWorkStatusProc(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
//	PD(pData->m_SystemWorkSta);
    switch(pData->m_SystemWorkSta)
    {
    default:
        break;
    case SYSTEM_STOP:
        PS("工装模式管理器SYSTEM_STOP");
        pData->m_pCfgData->m_SystemSta = Stop;
        pData->m_SystemWorkSta = SYSTEM_STOP_HOLD;
        pData->m_Bump1Sta	= BUMP_STOP;
        pData->m_Bump2Sta	= BUMP_STOP;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_COOLER_CMD, 0, 0, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_HEATER_CMD, 0, 0, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        pData->m_Count = 0;
        break;
    case	SYSTEM_STOP_HOLD:
//        PS("工装模式管理器 SYSTEM_STOP_HOLD");
        if(pData->m_WorkModePressKey == TRUE /*&& pData->m_pSysData->m_HeaterModeWTLow == Status_Off */ && pData->m_pSysData->m_WaterHIGH == Status_Off )
        {
            pData->m_SystemWorkSta = SYSTEM_COOLER;
            pData->m_WorkModePressKey = FALSE;
        }
        break;
    case SYSTEM_COOLER:
        PS("工装模式管理器 SYSTEM_COOLER");
        pData->m_pCfgData->m_SystemSta = Cooler;
        pData->m_pSysData->m_Temp1Set = pData->m_pCfgData->m_Temp1Set_Cool;
        pData->m_pSysData->m_Temp2Set = pData->m_pCfgData->m_Temp2Set_Cool;
        pData->m_pSysData->m_WaterTempSet = pData->m_pCfgData->m_WaterTempSet_Cool;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_COOLER_CMD, 0, 1, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        pData->m_SystemWorkSta = SYSTEM_COOLER_HOLD;
        pData->m_Count = 0;
        break;
    case SYSTEM_COOLER_HOLD:
//        PS("工装模式管理器 SYSTEM_COOLER_HOLD");
        if(pData->m_WorkModePressKey == TRUE)
        {
            pData->m_SystemWorkSta = SYSTEM_HEATER;
            pData->m_WorkModePressKey = FALSE;
            pData->m_Bump1Sta	= BUMP_STOP;
            pData->m_Bump2Sta	= BUMP_STOP;
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_COOLER_CMD, 0, 0, NULL); //见msg_def.h
        }
        break;
    case SYSTEM_HEATER:
        PS("工装模式管理器 SYSTEM_HEATER");
        pData->m_pCfgData->m_SystemSta = Heater;
        pData->m_pSysData->m_Temp1Set = pData->m_pCfgData->m_Temp1Set_Hot;
        pData->m_pSysData->m_Temp2Set = pData->m_pCfgData->m_Temp2Set_Hot;
        pData->m_pSysData->m_WaterTempSet = pData->m_pCfgData->m_WaterTempSet_Hot;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_HEATER_CMD, 0, 1, NULL); //见msg_def.h
        pData->m_SystemWorkSta = SYSTEM_HEATER_HOLD;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        pData->m_Count = 0;
        break;
    case SYSTEM_HEATER_HOLD:
//       PS("工装模式管理器 SYSTEM_HEATER_HOLD");
        if(pData->m_WorkModePressKey == TRUE)
        {
            pData->m_SystemWorkSta = SYSTEM_STOP;
            pData->m_WorkModePressKey = FALSE;
        }
        break;
    }
}

void Bump1WorkStatusProc(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    switch(pData->m_Bump1Sta)
    {
    default:
        break;
    case BUMP_STOP:
        PS("泵工作管理器 BUMP_STOP");
        pData->m_pCfgData->m_Cycle1Set = Status_Off;
        pData->m_Bump1Sta = BUMP_STOP_HOLD; //状态机切换
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_BUMP_CMD, 1, 0, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        break;
    case BUMP_STOP_HOLD:
        if(pData->m_Bump1PressKey == TRUE && (pData->m_pCfgData->m_SystemSta == Cooler || pData->m_pCfgData->m_SystemSta == Heater))
        {
            pData->m_Bump1Sta = BUMP_START; //状态机切换
            pData->m_Bump1PressKey = FALSE;
        }
        break;
    case BUMP_START:
        PS("泵工作管理器 BUMP_START");
        pData->m_pCfgData->m_Cycle1Set = Status_On;
        pData->m_Bump1Sta = BUMP_START_HOLD; //状态机切换
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_BUMP_CMD, 1, 1, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        break;
    case BUMP_START_HOLD:
        if(pData->m_Bump1PressKey == TRUE)
        {
            pData->m_Bump1Sta = BUMP_STOP; //状态机切换
            pData->m_Bump1PressKey = FALSE;
        }
        break;
    }
}

void Bump2WorkStatusProc(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
    switch(pData->m_Bump2Sta)
    {
    default:
        break;
    case BUMP_STOP:
        pData->m_pCfgData->m_Cycle2Set = Status_Off;
        pData->m_Bump2Sta = BUMP_STOP_HOLD; //状态机切换
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_BUMP_CMD, 2, 0, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        break;
    case BUMP_STOP_HOLD:
        if(pData->m_Bump2PressKey == TRUE && (pData->m_pCfgData->m_SystemSta == Cooler || pData->m_pCfgData->m_SystemSta == Heater))
        {
            pData->m_Bump2Sta = BUMP_START; //状态机切换
            pData->m_Bump2PressKey = FALSE;
        }
        break;
    case BUMP_START:
        pData->m_pCfgData->m_Cycle2Set = Status_On;
        pData->m_Bump2Sta = BUMP_START_HOLD; //状态机切换
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_BUMP_CMD, 2, 1, NULL); //见msg_def.h
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
        break;
    case BUMP_START_HOLD:
        if(pData->m_Bump2PressKey == TRUE)
        {
            pData->m_Bump2Sta = BUMP_STOP; //状态机切换
            pData->m_Bump2PressKey = FALSE;
        }
        break;
    }
}
void SystemMonitor(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;
//    PD(pData->m_pSysData->m_WaterTemp);

    GetWaterStatus(pArg);

    if(pData->m_Count < ALMMUTETIME)
        return;

    //体温小于28度,大于43度,传感器脱落报警
    if(pData->m_pCfgData->m_SystemSta != Stop && pData->m_pSysData->m_Temp1 <= TEMP_ALARM)
    {
        pData->m_pSysData->m_Sensor1OFF = Status_On;
    }
    else {
        pData->m_pSysData->m_Sensor1OFF = Status_Off;
    }

    if(pData->m_pCalData->m_SingleMode == Status_Off && pData->m_pCfgData->m_SystemSta != Stop && pData->m_pSysData->m_Temp2 <= TEMP_ALARM)
    {
        pData->m_pSysData->m_Sensor2OFF = Status_On;
    }
    else {
        pData->m_pSysData->m_Sensor2OFF = Status_Off;
    }

    if(pData->m_pCfgData->m_SystemSta == Stop && pData->m_E2PROMERROR == TRUE)
    {
        pData->m_pSysData->m_E2PROMERR = Status_On;
    }
    else {
        pData->m_pSysData->m_E2PROMERR = Status_Off;
    }
    //获取水流开关状态
    if(pData->m_pCalData->m_SingleMode == Status_Off) {
        if(GetWaterSwitch1()) //TODO
        {
            pData->m_pSysData->m_Float1Status = Status_On;
        }
        else {
            pData->m_pSysData->m_Float1Status = Status_Off;
        }
        if(GetWaterSwitch2()) //TODO
        {
            pData->m_pSysData->m_Float2Status = Status_On;
        }
        else {
            pData->m_pSysData->m_Float2Status = Status_Off;
        }
    }
    else {
        if(GetWaterSwitch2()) //TODO
        {
            pData->m_pSysData->m_Float1Status = Status_On;
        }
        else {
            pData->m_pSysData->m_Float1Status = Status_Off;
        }
        pData->m_pSysData->m_Float2Status = Status_Off;
    }
//		PD(pData->m_pSysData->m_Float1Status);
//		PD(pData->m_pSysData->m_Float2Status);

    //获得加热器电源状态
//		PD(GetHeatPower());
    if(pData->m_pSysData->m_Heater && GetHeatPower())
    {
        pData->m_pSysData->m_HeaterPOWER = Status_On;
    }
    else {
        pData->m_pSysData->m_HeaterPOWER = Status_Off; //非加热模式时，报警取消
    }
//    PD(pData->m_pSysData->m_HeaterPOWER);

    //水温报警,高于43度

    if(pData->m_pSysData->m_WaterTemp > 4300)
    {
        pData->m_pSysData->m_WaterHIGH = Status_On;
    }
    else {
        pData->m_pSysData->m_WaterHIGH = Status_Off;
    }

    //水温报警,低于2度
    if(pData->m_pSysData->m_WaterTemp < 200)
    {
        pData->m_pSysData->m_WaterTLow = Status_On;
    }
    else {
        pData->m_pSysData->m_WaterTLow = Status_Off;
    }

    //复温模式下,水温设置值低于体温测量值 (加热模式)
    if(pData->m_pCfgData->m_SystemSta == Heater)
    {
        if(pData->m_pCfgData->m_WaterTempSet_Hot < pData->m_pSysData->m_Temp1 )
        {
            pData->m_pSysData->m_HeaterModeWT1Low = Status_On;
        }
        else {
            pData->m_pSysData->m_HeaterModeWT1Low = Status_Off;
        }
    }
    else {
        pData->m_pSysData->m_HeaterModeWT1Low = Status_Off;
    }
    //复温模式下,水温设置值低于体温测量值 (加热模式)
    if(pData->m_pCalData->m_SingleMode == Status_Off && pData->m_pCfgData->m_SystemSta == Heater)
    {
        if( pData->m_pCfgData->m_WaterTempSet_Hot < pData->m_pSysData->m_Temp2)
        {
            pData->m_pSysData->m_HeaterModeWT2Low = Status_On;
        }
        else {
            pData->m_pSysData->m_HeaterModeWT2Low = Status_Off;
        }
    }
    else {
        pData->m_pSysData->m_HeaterModeWT2Low = Status_Off;
    }

    //水位低于1
    if(pData->m_pSysData->m_WaterStatus == Status_I)
    {
        pData->m_pSysData->m_WaterLow = Status_On;
    }
    else {
        pData->m_pSysData->m_WaterLow = Status_Off;
    }
    //泵开启时流量开关没有监测到流量
    if(pData->m_pSysData->m_Bump1Status == Status_On && pData->m_pSysData->m_Float1Status==Status_Off)
    {
        if(pData->m_Float1Count >= 1) {
            pData->m_pSysData->m_Cycle1Alm = Status_On;
        }
        pData->m_Float1Count++;
    }
    else {
        pData->m_pSysData->m_Cycle1Alm = Status_Off;
        pData->m_Float1Count = 0;
    }

    if(pData->m_pSysData->m_Bump2Status == Status_On && pData->m_pSysData->m_Float2Status==Status_Off)
    {
        if(pData->m_Float2Count >= 1) {
            pData->m_pSysData->m_Cycle2Alm = Status_On;
        }
        pData->m_Float2Count++;
    }
    else {
        pData->m_pSysData->m_Cycle2Alm = Status_Off;
        pData->m_Float2Count = 0;
    }

//		PD(pData->m_pSysData->m_Bump1Status);
//		PD(pData->m_pSysData->m_FloatStatus);
//		if((pData->m_pSysData->m_Bump1Status == Status_On && pData->m_pSysData->m_FloatStatus==Status_Off)
//		    pData->m_pSysData->m_Cycle1Alm = Status_Off;
//        pData->m_pSysData->m_Cycle2Alm = Status_Off;

    if(pData->m_pSysData->m_WaterLow == Status_On && pData->m_SystemWorkSta != SYSTEM_STOP_HOLD)
    {
        pData->m_SystemWorkSta = SYSTEM_STOP; //Check
        PS("水位低，工作模式控制器恢复停止");
    }
    if(pData->m_pSysData->m_WaterTLow == Status_On && pData->m_SystemWorkSta != SYSTEM_STOP_HOLD)
    {
        pData->m_SystemWorkSta = SYSTEM_STOP;//check
        PS("水温高于2度，工作模式控制器恢复停止");
    }
    if(pData->m_pSysData->m_WaterHIGH == Status_On && pData->m_SystemWorkSta != SYSTEM_STOP_HOLD)
    {
        pData->m_SystemWorkSta = SYSTEM_STOP;
        PS("水温高于43 工作模式控制器恢复停止");
    }
}

//获取水位状态
void GetWaterStatus(void* pArg)
{
    PMODULESYSTEMPROCDATA pData = (PMODULESYSTEMPROCDATA)pArg;

//    PD(GetWaterLow()); //获取低水位状态//true 1低 FALSE 0高
//    PD(GetWaterFull()); //获取高水位状态//true 1低  FALSE 0高
    if(GetWaterLow() == FALSE)
    {
        if(GetWaterFull() == TRUE)
        {
            pData->m_pSysData->m_WaterStatus = Status_III; //低水位FALSE,高水位FALSE,状态3
//            printf("pData->m_pSysData->m_WaterStatus=Status_III");
        }
        else
        {
            pData->m_pSysData->m_WaterStatus = Status_II; //低水位FALSE,高水位TRUE,鬃刺?
//            printf("pData->m_pSysData->m_WaterStatus=Status_II");
        }
    }
    else
    {
        pData->m_pSysData->m_WaterStatus = Status_I; //低水位true 状态1
//        printf("pData->m_pSysData->m_WaterStatus=Status_I");
    }
}


void TrigerAddSet(PMODULESYSTEMPROCDATA pData)//按键加
{
//	PS("++++");
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    INT16U *pTemp1;
    INT16U *pTemp2;
    INT16U *pTempW;
    INT16U *pVolum;
    INT8S  *pCal1;
    INT8S  *pCal2;
    INT16U TempMax = 0;
    INT16U TempMin = 0;
    INT16U TempWMax = 0;
    INT16U TempWMin = 0;
    INT16U AlmVolMax = ALM_LEVEL_HIG;

    pTemp1 = &(pData->m_pSysData->m_Temp1Set);
    pTemp2 = &(pData->m_pSysData->m_Temp2Set);
    pTempW = &(pData->m_pSysData->m_WaterTempSet);
    pVolum = &(pData->m_pSysData->m_AlmVolSet);
    pCal1  = &(pData->m_pSysData->m_Cal1Set);
    pCal2  = &(pData->m_pSysData->m_Cal2Set);
    switch ((INT16U)sta)
    {
    default:
        break;
    case Cooler:
        TempMax = COOLTEMPHIGH;
        TempMin = COOLTEMPLOW;
        TempWMax = COOLWATERHIGH;
        TempWMin = COOLWATERLOW;
        break;
    case Heater:
        TempMax = HOTTEMPHIGH;
        TempMin = HOTTEMPLOW;
        TempWMax = HOTWATERHIGH;
        TempWMin = HOTWATERLOW;
        break;
    }

    switch((INT16U)pData->m_pSysData->m_FocusStatus)
    {
    case Temp1Focus:
        if(*pTemp1 <= TempMax - 50)
        {
            if(*pTemp1 % 50) {
                *pTemp1 += 50 - ((*pTemp1) % 50);
            }
            else {
                *pTemp1 += 50;
            }
        }
        break;
    case Temp2Focus:
        if(*pTemp2 <= TempMax - 50) {
            if(*pTemp2 % 50) {
                *pTemp2 += 50 - ((*pTemp2 ) % 50);
            }
            else {
                *pTemp2 += 50;
            }
        }
        break;
    case TempWFocus:
        if(*pTempW <= TempWMax - 100) {
            if(*pTempW % 100) {
                *pTempW += 100 - ((*pTempW ) % 100);
            }
            else {
                *pTempW += 100;
            }
        }
        break;
    case AlmVolFocus:
        if(*pVolum < AlmVolMax)
            *pVolum += 1 ;
        break;
    case Cal1Focus:
        if(*pCal1 < TEMPCALMAX)
            *pCal1 += 1 ;
        break;
    case Cal2Focus:
        if(*pCal2 < TEMPCALMAX)
            *pCal2 += 1 ;
        break;
    default:
        break;
    }
}

void TrigerDecSet(PMODULESYSTEMPROCDATA pData)//按键减
{
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    INT16U *pTemp1;
    INT16U *pTemp2;
    INT16U *pTempW;
    INT16U *pVolum;
    INT8S  *pCal1;
    INT8S  *pCal2;
    INT16U TempMax = 0;
    INT16U TempMin = 0;
    INT16U TempWMax = 0;
    INT16U TempWMin = 0;
    INT16U AlmVolMin = ALM_LEVEL_LOW;

    pTemp1 = &(pData->m_pSysData->m_Temp1Set);
    pTemp2 = &(pData->m_pSysData->m_Temp2Set);
    pTempW = &(pData->m_pSysData->m_WaterTempSet);
    pVolum = &(pData->m_pSysData->m_AlmVolSet);
    pCal1  = &(pData->m_pSysData->m_Cal1Set);
    pCal2  = &(pData->m_pSysData->m_Cal2Set);

    switch ((INT16U)sta)
    {
    default:
        break;
    case Cooler:
        TempMax = COOLTEMPHIGH;
        TempMin = COOLTEMPLOW;
        TempWMax = COOLWATERHIGH;
        TempWMin = COOLWATERLOW;
        break;
    case Heater:
        TempMax = HOTTEMPHIGH;
        TempMin = HOTTEMPLOW;
        TempWMax = HOTWATERHIGH;
        TempWMin = HOTWATERLOW;
        break;
    }

    switch((INT16U)pData->m_pSysData->m_FocusStatus)
    {
    case Temp1Focus:
        if(*pTemp1 >= TempMin + 50)
            *pTemp1 -= 50;
        break;
    case Temp2Focus:
        if(*pTemp2 >= TempMin + 50)
            *pTemp2 -= 50;
        break;
    case TempWFocus:
        if(*pTempW >= TempWMin + 100)
            *pTempW -= 100;
        break;
    case AlmVolFocus:
        if(*pVolum > AlmVolMin)
            *pVolum -= 1 ;
        break;
    case Cal1Focus:
        if(*pCal1 > TEMPCALMIN)
            *pCal1 -= 1 ;
        break;
    case Cal2Focus:
        if(*pCal2 > TEMPCALMIN)
            *pCal2 -= 1 ;
        break;
    default:
        break;
    }
}

void TrigerTemp1Set(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    if(pData->m_pCfgData->m_SystemSta == Stop)
        return;
    SaveStatus = SetFocusStatus(pData, Temp1Focus);
    if(SaveStatus)
    {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pCfgData->m_Temp1Set_Cool = pData->m_pSysData->m_Temp1Set;
            break;
        case Heater:
            pData->m_pCfgData->m_Temp1Set_Hot = pData->m_pSysData->m_Temp1Set;
            break;
        default:
            break;
        }
//        PS("7");
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pSysData->m_Temp1Set = pData->m_pCfgData->m_Temp1Set_Cool;
            break;
        case Heater:
            pData->m_pSysData->m_Temp1Set = pData->m_pCfgData->m_Temp1Set_Hot;
            break;
        default:
            break;
        }
    }
}

void TrigerTemp2Set(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    if(pData->m_pCfgData->m_SystemSta == Stop)
        return;
    SaveStatus = SetFocusStatus(pData, Temp2Focus);
    if(SaveStatus)
    {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pCfgData->m_Temp2Set_Cool = pData->m_pSysData->m_Temp2Set;
            break;
        case Heater:
            pData->m_pCfgData->m_Temp2Set_Hot = pData->m_pSysData->m_Temp2Set;
            break;
        default:
            break;
        }
        PS("8");
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pSysData->m_Temp2Set = pData->m_pCfgData->m_Temp2Set_Cool;
            break;
        case Heater:
            pData->m_pSysData->m_Temp2Set = pData->m_pCfgData->m_Temp2Set_Hot;
            break;
        default:
            break;
        }
    }
}

void TrigerTempWaterSet(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    if(pData->m_pCfgData->m_SystemSta == Stop)
        return;
    SaveStatus = SetFocusStatus(pData, TempWFocus);
    if(SaveStatus)
    {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pCfgData->m_WaterTempSet_Cool = pData->m_pSysData->m_WaterTempSet;
            break;
        case Heater:
            pData->m_pCfgData->m_WaterTempSet_Hot = pData->m_pSysData->m_WaterTempSet;
            break;
        default:
            break;
        }
        PS("9");
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        switch ((INT16U)sta)
        {
        case Cooler:
            pData->m_pSysData->m_WaterTempSet = pData->m_pCfgData->m_WaterTempSet_Cool;
            break;
        case Heater:
            pData->m_pSysData->m_WaterTempSet = pData->m_pCfgData->m_WaterTempSet_Hot;
            break;
        default:
            break;
        }
    }
}

void TrigerAlmvolSet(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;

    SaveStatus = SetFocusStatus(pData, AlmVolFocus);
    if(SaveStatus)
    {
        pData->m_pCfgData->m_AlmVolum = pData->m_pSysData->m_AlmVolSet;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        pData->m_pSysData->m_AlmVolSet = pData->m_pCfgData->m_AlmVolum;
    }
}

void TrigerCal1Set(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    if(pData->m_pCfgData->m_SystemSta != Stop)
        return;
    SaveStatus = SetFocusStatus(pData, Cal1Focus);
    if(SaveStatus)
    {
        pData->m_pAdjData->m_Cal1Set = pData->m_pSysData->m_Cal1Set;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, ADJDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        pData->m_pSysData->m_Cal1Set = pData->m_pAdjData->m_Cal1Set;
    }
}


void TrigerCal2Set(PMODULESYSTEMPROCDATA pData)
{
    BOOLEAN SaveStatus;
    eSystemStatus sta = pData->m_pCfgData->m_SystemSta;
    if(pData->m_pCfgData->m_SystemSta != Stop)
        return;
    SaveStatus = SetFocusStatus(pData, Cal2Focus);
    if(SaveStatus)
    {
        pData->m_pAdjData->m_Cal2Set = pData->m_pSysData->m_Cal2Set;
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, ADJDATASAVE, CMD_START, NULL); //see msg_def.h
    }
    else {
        pData->m_pSysData->m_Cal2Set = pData->m_pAdjData->m_Cal2Set;
    }
}


BOOLEAN SetFocusStatus(PMODULESYSTEMPROCDATA pData, eFocusStatus Focus)
{
    BOOLEAN ret = FALSE;
    eFocusStatus Last = pData->m_pSysData->m_FocusStatus;
    pData->m_pSysData->m_FocusStatus = Focus;

    if(Last != NoFocus && Focus == Last)
    {
        pData->m_pSysData->m_FocusStatus = NoFocus;
        ret = TRUE;
    }
    return ret;
}


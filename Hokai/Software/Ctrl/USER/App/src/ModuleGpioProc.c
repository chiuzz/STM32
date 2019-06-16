//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleGpioProc.c
//*
//* 文件描述 : GPIOPROC任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleGpioProc.h"
#include "common.h"
#include "usart.h"

BOOLEAN ModuleGpioProcInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    if(pData != NULL)
    {
        pData->m_Bump1WorkMac = BUMP_WORK_OFF;
        pData->m_Bump2WorkMac = BUMP_WORK_OFF;
    }
    return ret;
}

BOOLEAN ModuleGpioProcReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleGpioProcStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    pData->m_PressSta = TRUE;
    pData->m_Count = 0;
    pData->m_pSysData->m_FocusStatus = NoFocus;
    return ret;
}

BOOLEAN ModuleGpioProcStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleGpioProcRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleGpioProc10msProcess(void* pArg)
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    //PD("ModuleGpioProc10msProcess!\r\n");
}

void ModuleGpioProc50msProcess(void* pArg)
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
//	 if(pData->m_PressSta == FALSE)
//    {
//        return;
//    }
    pData->m_Count50ms++;
    if(pData->m_Count50ms % 2) //喂看门狗
    {
        WWDOG(0);
    }
    else {
        WWDOG(1);
    }

    Bump1WorkMachineProc(pArg);
    if(pData->m_pCalData->m_SingleMode == Status_Off) {
        Bump2WorkMachineProc(pArg);
    }
}


//#define SHOW_SYSTEM_MODE
//#define SHOW_SYSTEM_STA
//#define SHOW_SYSTEM_ALM
//#define SHOW_SYSTEM_DATA
void ModuleGpioProc1sProcess(void* pArg)
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
//    PS("ModuleGpioProc1sProcess!\r\n");
    if(pData->m_PressSta == FALSE)
    {
        return;
    }
    pData->m_Count++;
    SetCpuLed((BOOLEAN)pData->m_Count % 2); //led
    if(pData->m_Count % 10!=0)
        return;

#ifdef SHOW_SYSTEM_MODE
    printf("--------------------系统工作信息-------------------------\r\n");
    printf("工作模式：");
    switch( pData->m_pCfgData->m_SystemSta)//系统工作状态
    {
    case check :
        printf("check");
        break;
    case Stop:
        printf("Stop");
        break;
    case Cooler:
        printf("Cooler");
        break;
    case Heater:
        printf("Heater");
        break;
    }
    printf("\r\n");
    printf("水路I设定：");
    if(pData->m_pCfgData->m_Cycle1Set)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水路II设定：");
    if(pData->m_pCfgData->m_Cycle2Set)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
#endif
#ifdef SHOW_SYSTEM_STA
    printf("--------------------系统状态信息-------------------------\r\n");
    printf("单毯状态：");
    if(pData->m_pCalData->m_SingleMode)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水路水流开关1状态：");
    if(pData->m_pSysData->m_Float1Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水路水流开关2状态：");
    if(pData->m_pSysData->m_Float2Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水位：");
    switch( pData->m_pSysData->m_WaterStatus)
    {
    case Status_I :
        printf("Status_I");
        break;
    case Status_II:
        printf("Status_II");
        break;
    case Status_III:
        printf("Status_III");
        break;
    }
    printf("\r\n");
    printf("水泵1状态：");
    if(pData->m_pSysData->m_Bump1Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水泵2状态：");
    if(pData->m_pSysData->m_Bump2Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("制冷状态：");
    if(pData->m_pSysData->m_Cooler)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("制热状态：");
    if(pData->m_pSysData->m_Heater)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("焦点状态 ：");
    switch( pData->m_pSysData->m_FocusStatus)
    {
    case NoFocus :
        printf("NoFocus");
        break;
    case Temp1Focus:
        printf("Temp1Focus");
        break;
    case Temp2Focus:
        printf("Temp2Focus");
        break;
    case TempWFocus:
        printf("TempWFocus");
        break;
    }
    printf("\r\n");
#endif
#ifdef SHOW_SYSTEM_ALM
    printf("--------------------报警状态信息-------------------------\r\n");
    printf("传感器1脱落 ：");
    if(pData->m_pSysData->m_Sensor1OFF)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("传感器2脱落 ：");
    if(pData->m_pSysData->m_Sensor2OFF)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("加热器供电异常：");
    if(pData->m_pSysData->m_HeaterPOWER)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水温超温高异常：");
    if(pData->m_pSysData->m_WaterHIGH)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水温超温低异常：");
    if(pData->m_pSysData->m_WaterTLow)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("E2PROM异常：");
    if(pData->m_pSysData->m_E2PROMERR)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("水位低异常：");
    if(pData->m_pSysData->m_WaterLow)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("加热，水温1低于体温 异常：");
    if(pData->m_pSysData->m_HeaterModeWT1Low)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("加热，水温2低于体温 异常：");
    if(pData->m_pSysData->m_HeaterModeWT2Low)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");

    printf("加热，体温1超限 异常：");
    if(pData->m_pSysData->m_HeaterModeT1ALM)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");

    printf("加热，体温2超限 异常：");
    if(pData->m_pSysData->m_HeaterModeT2ALM)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("液路1循环异常：");
    if(pData->m_pSysData->m_Cycle1Alm)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("液路2循环异常：");
    if(pData->m_pSysData->m_Cycle2Alm)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
#endif
#ifdef SHOW_SYSTEM_DATA
    printf("--------------------系统数据信息-------------------------\r\n");
    printf("制热体温设定 1：%d, 2: %d，水温设定：%d\r\n", pData->m_pCfgData->m_Temp1Set_Hot, pData->m_pCfgData->m_Temp2Set_Hot, pData->m_pCfgData->m_WaterTempSet_Hot);
    printf("制冷体温设定 1：%d, 2: %d, 水温设定: %d\r\n", pData->m_pCfgData->m_Temp1Set_Cool, pData->m_pCfgData->m_Temp2Set_Cool, pData->m_pCfgData->m_WaterTempSet_Cool);
    printf("当前体温设定 1：%d, 2: %d, 水温设定: %d\r\n", pData->m_pSysData->m_Temp1Set, pData->m_pSysData->m_Temp2Set, pData->m_pSysData->m_WaterTempSet);
    printf("当前体温 1：%d, 2: %d, 水温: %d\r\n", pData->m_pSysData->m_Temp1, pData->m_pSysData->m_Temp2, pData->m_pSysData->m_WaterTemp);
#endif
}


void GpioProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    switch(MsgId)
    {
    case MS_BUMP_CMD:
        switch(lParam)
        {
        default:
            break;
        case 1:
            if(wParam)
            {
                pData->m_Bump1WorkMac = BUMP_WORK_ON;
                PS("BUMP1_WORK_ON");
            }
            else {
                pData->m_Bump1WorkMac = BUMP_WORK_OFF;
                PS("BUMP1_WORK_OFF");
            }
            break;
        case 2:
            if(wParam)
            {
                pData->m_Bump2WorkMac = BUMP_WORK_ON;
                PS("BUMP2_WORK_ON");
            }
            else {
                pData->m_Bump2WorkMac = BUMP_WORK_OFF;
                PS("BUMP2_WORK_OFF");
            }
            break;
        }
        break;
    default:
        break;
    }
//    printf("Receive MSG !!!\n");
}

PMODULEBASE CreateModuleGpioProc(PMODULESERVERDATA pServerData)
{
    PMODULEGPIOPROC pModGpioProc = NULL;
    PMODULEGPIOPROCDATA pData = NULL;

    pModGpioProc = (PMODULEGPIOPROC)malloc(sizeof(MODULEGPIOPROC));//申请基类结构
    pData = (PMODULEGPIOPROCDATA)malloc(sizeof(MODULEGPIOPROCDATA));//申请基类数据结构
    assert(pModGpioProc != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModGpioProc->m_pBaseData = (PVOID)pData;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    //************************以下模块接口必须赋值******************************
    pModGpioProc->pModeleInit = ModuleGpioProcInit; //实现模块初始化
    pModGpioProc->pModeleReset = ModuleGpioProcReset; //实现模块复位
    pModGpioProc->pModeleStart = ModuleGpioProcStart; //实现模块开始
    pModGpioProc->pModeleStop = ModuleGpioProcStop; //实现模块结束
    pModGpioProc->pModeleRelease = ModuleGpioProcRelease;//实现
    pModGpioProc->pMsgNotify = GpioProcMsgNotify;//实现消息队列处理
    pModGpioProc->pModele1msProcess = NULL;//不实现，置为NULL
    pModGpioProc->pModele10msProcess = ModuleGpioProc10msProcess;//不实现，置为NULL
    pModGpioProc->pModele50msProcess = ModuleGpioProc50msProcess;//不实现，置为NULL
    pModGpioProc->pModele1sProcess = ModuleGpioProc1sProcess;//实现1s调用
    pModGpioProc->pModeleUartProcess = NULL;//实现UART调用
    strcpy(pModGpioProc->m_ModName, "ModGpioProc");

    //PD("CreateModuleGpioProc!!\n");
    return (PMODULEBASE)pModGpioProc;
}

void Bump1WorkMachineProc(void* pArg)
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    switch(pData->m_Bump1WorkMac)
    {
    default:
    case BUMP_WORK_OFF:
        if(pData->m_pCalData->m_SingleMode == Status_Off) {
            SetBump1Work(FALSE);     //停止模式下,水泵不工作
        }
        else {
            SetBump2Work(FALSE);
        }
        pData->m_pSysData->m_Bump1Status = Status_Off;
        break;
    case BUMP_WORK_ON:
        switch(pData->m_pCfgData->m_SystemSta)//制冷模式下
        {
        case Cooler://Stop = 1,	Cooler=2,	Heater=3,
            //制冷模式下,根据体温设置值与实际的体温值进行比较
            if(pData->m_pSysData->m_Temp1 > pData->m_pCfgData->m_Temp1Set_Cool )
            {
                pData->m_Bump1WorkMac = BUMP_WORK_START;//当实际体温大于设置值得时候,水泵开始工作
                // PD("制冷模式下,水泵工作");
            }
            else
            {
                pData->m_Bump1WorkMac = BUMP_WORK_STOP;
                // PD("制冷模式下,水泵停止");
            }
            break;
        case Heater:
            //在制热模式下,根据体温设置值与实际体温进行比较
            if(pData->m_pSysData->m_Temp1 < pData->m_pCfgData->m_Temp1Set_Hot && pData->m_pSysData->m_HeaterModeWT1Low == Status_Off)
            {
                //当设置温度小于体温的时候,水泵开始工作;
                pData->m_Bump1WorkMac = BUMP_WORK_START;
            }
            else
            {
                pData->m_Bump1WorkMac = BUMP_WORK_STOP;
            }
            break;
        default:
            pData->m_Bump1WorkMac = BUMP_WORK_STOP;
            break;
        }
        break;
    case BUMP_WORK_STOP:
        pData->m_Bump1WorkMac = BUMP_WORK_ON;
        if(pData->m_pCalData->m_SingleMode == Status_Off) {
            SetBump1Work(FALSE);     //停止模式下,水泵不工作
        }
        else {
            SetBump2Work(FALSE);
        }
        pData->m_pSysData->m_Bump1Status = Status_Off;
        break;
    case BUMP_WORK_START:
        pData->m_Bump1WorkMac = BUMP_WORK_ON;
        if(pData->m_pCalData->m_SingleMode == Status_Off) {
            SetBump1Work(TRUE);     //停止模式下,水泵不工作
        }
        else {
            SetBump2Work(TRUE);
        }
        pData->m_pSysData->m_Bump1Status = Status_On;
        break;
    }
}

void Bump2WorkMachineProc(void* pArg)
{
    PMODULEGPIOPROCDATA pData = (PMODULEGPIOPROCDATA)pArg;
    switch(pData->m_Bump2WorkMac)
    {
    default:
    case BUMP_WORK_OFF:
        SetBump2Work(FALSE);     //停止模式下,水泵不工作
        pData->m_pSysData->m_Bump2Status = Status_Off;
        break;
    case BUMP_WORK_ON:
        switch(pData->m_pCfgData->m_SystemSta)//制冷模式下
        {
        case Cooler://Stop = 1,	Cooler=2,	Heater=3,
            //制冷模式下,根据体温设置值与实际的体温值进行比较
            if(pData->m_pSysData->m_Temp2 > pData->m_pCfgData->m_Temp2Set_Cool )
            {
                pData->m_Bump2WorkMac = BUMP_WORK_START;//当实际体温大于设置值得时候,水泵开始工作
                // PD("制冷模式下,水泵工作");
            }
            else
            {
                pData->m_Bump2WorkMac = BUMP_WORK_STOP;
                // PD("制冷模式下,水泵停止");
            }
            break;
        case Heater:
            //在制热模式下,根据体温设置值与实际体温进行比较
            if(pData->m_pSysData->m_Temp2 < pData->m_pCfgData->m_Temp2Set_Hot && pData->m_pSysData->m_HeaterModeWT2Low == Status_Off)
            {
                //当设置温度小于体温的时候,水泵开始工作;
                pData->m_Bump2WorkMac = BUMP_WORK_START;
            }
            else
            {
                pData->m_Bump2WorkMac = BUMP_WORK_STOP;
            }
            break;
        default:
            pData->m_Bump2WorkMac = BUMP_WORK_STOP;
            break;
        }
        break;
    case BUMP_WORK_STOP:
        pData->m_Bump2WorkMac = BUMP_WORK_ON;
        SetBump2Work(FALSE);     //停止模式下,水泵不工作
        pData->m_pSysData->m_Bump2Status = Status_Off;
        break;
    case BUMP_WORK_START:
        pData->m_Bump2WorkMac = BUMP_WORK_ON;
        SetBump2Work(TRUE);     //停止模式下,水泵不工作
        pData->m_pSysData->m_Bump2Status = Status_On;
        break;
    }
}

//if(pData->m_pSysData->m_Cycle1Set==Status_Off || pData->m_pSysData->m_WaterTemp > 4200) //水路1没有开启,就水泵不旋转


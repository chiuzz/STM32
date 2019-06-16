//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleScr.c
//*
//* 文件描述 : SCR任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleScr.h"
#include "led.h"
#include "msg_def.h"
//#include "usart.h"

#define Version 2010

BOOLEAN ModuleScrInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;

    HT1621B_Init();//显示屏硬件驱动
    HtbRamInit(pArg);//显示屏元素的初始化
    if(pData != NULL)
    {
        pData->m_FlashCount = 0;
        pData->m_ScrWorkSta = SCR_STOP;
    }
    return ret;
}

BOOLEAN ModuleScrReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleScrStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->m_PressSta = TRUE;
    disp_all(); //tommy
    //disp_clear();

    return ret;
}

BOOLEAN ModuleScrStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleScrRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleScr50msProcess(void* pArg)
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    eItemStatus ItemSta;
    INT16U Temp;
//     printf("ModuleScr1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    pData->m_Count++;
    if(pData->m_Count > 10)
    {
        pData->m_Count = 0;
        pData->m_FlashCount++;
        pData->m_50msCount++;
    }
    else
    {
        return;
    }

//		pData->m_pSysData->m_E2PROMERR = Status_On;
    if(pData->m_pSysData->m_E2PROMERR == Status_On) {
        if(pData->m_FlashCount % 2 == 1)
        {
            DisplayWorkMode(pArg, Cooler);
        }
        else
        {
            DisplayWorkMode(pArg, Heater);
        }
    }
    else {
        switch(pData->m_pSysData->m_SystemSta)
        {
        case Cooler: //系统在制冷状态
            DisplayWorkMode(pArg, Cooler);
            break;
        case Heater: //系统在制热状态
            DisplayWorkMode(pArg, Heater);
            break;
        default:
        case Stop:
            DisplayWorkMode(pArg, Stop);
            break;
        }
    }

    if(pData->m_pSysData->m_Cooler == Status_On)
    {
        DisplayCoolerStatus(pArg, Status_On);
    }
    else {
        DisplayCoolerStatus(pArg, Status_Off);
    }

    if(pData->m_pSysData->m_HeaterPOWER == Status_On) {
        ItemSta = Flash;
    }
    else if(pData->m_pSysData->m_Heater == Status_On)
    {
        ItemSta = Show;
    }
    else {
        ItemSta = Hide;
    }
    DisplayHeaterStatus(pArg, ItemSta);

//		PD(pData->m_pSysData->m_Cycle1Set);
//		PD(pData->m_pSysData->m_SingleMode);
    if(pData->m_pSysData->m_SingleMode == Status_On) {
        //////////////////////单毯处理///////////////////////////
        if(pData->m_pSysData->m_Cycle1Set == Status_On)
        {
            DisplayCycle2Mode(pArg, Status_On);
        }
        else {
            DisplayCycle2Mode(pArg, Status_Off);
        }
        //////////////////////单毯处理///////////////////////////
    }
    /////////////////////双毯处理/////////////////////////////
    else {
        if(pData->m_pSysData->m_Cycle1Set == Status_On)
        {
            DisplayCycle1Mode(pArg, Status_On);
        }
        else {
            DisplayCycle1Mode(pArg, Status_Off);
        }
        if(pData->m_pSysData->m_Cycle2Set == Status_On)
        {
            DisplayCycle2Mode(pArg, Status_On);
        }
        else {
            DisplayCycle2Mode(pArg, Status_Off);
        }
    }
    /////////////////////////双毯处理/////////////////////////

    if(pData->m_pSysData->m_SingleMode == Status_On) {
        if(pData->m_pSysData->m_Cycle1Alm == Status_On) {
            ItemSta = Flash;
        }
        else if(pData->m_pSysData->m_Bump1Status == Status_On) {
            ItemSta = Show;
        }
        else {
            ItemSta = Invalid;
        }
        DisplayBump2Mode(pArg, ItemSta);
    }
    else {
        if(pData->m_pSysData->m_Cycle1Alm == Status_On) {
            ItemSta = Flash;
        }
        else if(pData->m_pSysData->m_Bump1Status == Status_On) {
            ItemSta = Show;
        }
        else {
            ItemSta = Invalid;
        }
        DisplayBump1Mode(pArg, ItemSta);

        if(pData->m_pSysData->m_Cycle2Alm == Status_On) {
            ItemSta = Flash;
        }
        else if(pData->m_pSysData->m_Bump2Status == Status_On) {
            ItemSta = Show;
        }
        else {
            ItemSta = Invalid;
        }
        DisplayBump2Mode(pArg, ItemSta);
    }

//		pData->m_pSysData->m_WaterStatus = Status_III;
    switch(pData->m_pSysData->m_WaterStatus)
    {
    case  Status_I://缺水（水位线显示1条）p16
        DisplayWaterStatusI(pArg);//水位状态
        break;
    case  Status_II://显示两条水位线
        DisplayWaterStatusII(pArg);//水位状态
        break;
    case  Status_III://满水（水位线显示4条）
        DisplayWaterStatusIII(pArg);//水位状态
        break;
    default :
        break;
    }


    if(pData->m_pSysData->m_WaterLow == Status_On)
    {
        WaterStatusAlm(pArg); //水位报警
    }

    if(pData->m_pSysData->m_SingleMode == Status_On) {
        if(pData->m_ScrWorkSta != SCR_WORK)
        {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_SystemSta == Stop)
        {
            if(pData->m_pSysData->m_FocusStatus  == Cal1Focus)
            {
                ItemSta = Flash;
                if(pData->m_Cal1SetMark != pData->m_pSysData->m_Cal1Set) {
                    ItemSta = Show;
                }
            }
            else
            {
                ItemSta = Invalid;
            }
        }
        else {
//			PD(pData->m_pSysData->m_FocusStatus);
            if(pData->m_pSysData->m_FocusStatus == Temp1Focus ) //功能按钮在温度设置1
            {
                ItemSta = Flash;
            }
            else {
                ItemSta = Show;
            }
            if(pData->m_Temp1SetMark != pData->m_pSysData->m_Temp1Set) {
                ItemSta = Show;
            }
        }
        if(pData->m_pSysData->m_FocusStatus  == Cal1Focus && pData->m_pSysData->m_SystemSta == Stop) {
            DisplayCal2Set(pArg, ItemSta, pData->m_pSysData->m_Cal1Set);
            pData->m_Cal1SetMark = pData->m_pSysData->m_Cal1Set;
        }
        else {
            DisplayTemp2Set(pArg, ItemSta, pData->m_pSysData->m_Temp1Set); //温度设置
            pData->m_Temp1SetMark = pData->m_pSysData->m_Temp1Set;
        }

    }
    else {
        if(pData->m_ScrWorkSta != SCR_WORK)
        {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_SystemSta == Stop)
        {
            if(pData->m_pSysData->m_FocusStatus  == Cal1Focus)
            {
                ItemSta = Flash;
                if(pData->m_Cal1SetMark != pData->m_pSysData->m_Cal1Set) {
                    ItemSta = Show;
                }
            }
            else
            {
                ItemSta = Invalid;
            }
        }
        else {
            if(pData->m_pSysData->m_FocusStatus == Temp1Focus ) //功能按钮在温度设置1
            {
                ItemSta = Flash;
            }
            else {
                ItemSta = Show;
            }
            if(pData->m_Temp1SetMark != pData->m_pSysData->m_Temp1Set) {
                ItemSta = Show;
            }
        }
        if(pData->m_pSysData->m_FocusStatus  == Cal1Focus && pData->m_pSysData->m_SystemSta == Stop) {
            DisplayCal1Set(pArg, ItemSta, pData->m_pSysData->m_Cal1Set);
            pData->m_Cal1SetMark = pData->m_pSysData->m_Cal1Set;
        }
        else {
            DisplayTemp1Set(pArg, ItemSta, pData->m_pSysData->m_Temp1Set); //温度设置
            pData->m_Temp1SetMark = pData->m_pSysData->m_Temp1Set;
        }

        if(pData->m_ScrWorkSta != SCR_WORK)
        {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_SystemSta == Stop)
        {
            if(pData->m_pSysData->m_FocusStatus  == Cal2Focus)
            {
                ItemSta = Flash;
                if(pData->m_Cal2SetMark != pData->m_pSysData->m_Cal2Set) {
                    ItemSta = Show;
                }
            }
            else
            {
                ItemSta = Invalid;
            }
        }
        else {
            if(pData->m_pSysData->m_FocusStatus == Temp2Focus ) //功能按钮在温度设置1
            {
                ItemSta = Flash;
            }
            else {
                ItemSta = Show;
            }
            if(pData->m_Temp2SetMark != pData->m_pSysData->m_Temp2Set) {
                ItemSta = Show;
            }
        }
        if(pData->m_pSysData->m_FocusStatus  == Cal2Focus && pData->m_pSysData->m_SystemSta == Stop) {
            DisplayCal2Set(pArg, ItemSta, pData->m_pSysData->m_Cal2Set);
            pData->m_Cal2SetMark = pData->m_pSysData->m_Cal1Set;
        }
        else {
            DisplayTemp2Set(pArg, ItemSta, pData->m_pSysData->m_Temp2Set); //温度设置
            pData->m_Temp2SetMark = pData->m_pSysData->m_Temp2Set;
        }
    }

    if(pData->m_pSysData->m_SystemSta == Stop || pData->m_ScrWorkSta != SCR_WORK)
    {
        ItemSta = Invalid;
    }
    else {
        if(pData->m_pSysData->m_FocusStatus == TempWFocus
                || pData->m_pSysData->m_HeaterModeWT1Low == Status_On
                || pData->m_pSysData->m_HeaterModeWT2Low == Status_On) //功能按钮在温度设置1
        {
            ItemSta = Flash;
        }
        else {
            ItemSta = Show;
        }
        if(pData->m_WaterTempSetMark != pData->m_pSysData->m_WaterTempSet) {
            ItemSta = Show;
        }
    }
    DisplayWaterTempSet(pArg, ItemSta, pData->m_pSysData->m_WaterTempSet); //温度设置
    pData->m_WaterTempSetMark = pData->m_pSysData->m_WaterTempSet;

    if(pData->m_pSysData->m_SingleMode == Status_On) {
        if(pData->m_pSysData->m_Sensor1OFF) {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_HeaterModeT1ALM == Status_On || pData->m_pSysData->m_HeaterModeWT1Low == Status_On) {
            ItemSta = Flash;
        }
        else {
            ItemSta = Show;
        }
        if(pData->m_ScrWorkSta != SCR_WORK)
        {
            pData->m_pSysData->m_Temp1 = Version;
        }
        DisplayTemp2Val(pArg, ItemSta, pData->m_pSysData->m_Temp1);
    }
    else {
        if(pData->m_pSysData->m_Sensor1OFF || pData->m_ScrWorkSta != SCR_WORK) {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_HeaterModeT1ALM == Status_On || pData->m_pSysData->m_HeaterModeWT1Low == Status_On) {
            ItemSta = Flash;
        }
        else {
            ItemSta = Show;
        }
        DisplayTemp1Val(pArg, ItemSta, pData->m_pSysData->m_Temp1);

        if(pData->m_pSysData->m_Sensor2OFF) {
            ItemSta = Invalid;
        }
        else if(pData->m_pSysData->m_HeaterModeT2ALM == Status_On || pData->m_pSysData->m_HeaterModeWT2Low == Status_On) {
            ItemSta = Flash;
        }
        else {
            ItemSta = Show;
        }
        if(pData->m_ScrWorkSta != SCR_WORK)
        {
            pData->m_pSysData->m_Temp2 = Version;
        }
        DisplayTemp2Val(pArg, ItemSta, pData->m_pSysData->m_Temp2);
    }

    if(pData->m_pSysData->m_WaterHIGH == Status_On || pData->m_pSysData->m_WaterTLow == Status_On) {
        ItemSta = Flash;
    }
    else {
        ItemSta = Show;
    }
    Temp = pData->m_pSysData->m_WaterTemp;

    if(pData->m_pSysData->m_FocusStatus == AlmVolumFocus)
    {
        ItemSta = Flash;
        Temp = pData->m_pSysData->m_AlmVolSet*100;
    }
    DisplayWaterTempVal(pArg, ItemSta, Temp);

    DisplayRefresh(pArg);//刷新区域
}

void ScrMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{

//    switch(MsgId)
//    {
//        case MSG_SCR_SAVE:
//          if(lParam == 1)
//          {
//            //立即执行配置保存，调用处理函数
//              ScrSave();
//          }
//          break;
//        default:break;
//    }
//    printf("Receive MSG !!!\n");
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(MsgId)
    {
    case MS_SCR_CMD:
        if(lParam == 1)
        {
            pData->m_ScrWorkSta = SCR_INIT;
        }
        else
        {
            pData->m_ScrWorkSta = SCR_WORK;
        }
        break;
    default:
        break;
    }
//    printf("Receive MSG !!!\n");
}

PMODULEBASE CreateModuleScr(PMODULESERVERDATA pServerData)
{
    PMODULESCR pModScr = NULL;
    PMODULESCRDATA pData = NULL;

    pModScr = (PMODULESCR)malloc(sizeof(MODULESCR));//申请基类结构
    pData = (PMODULESCRDATA)malloc(sizeof(MODULESCRDATA));//申请基类数据结构
//  ASSERT(pModScr != NULL);
//  ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModScr->m_pBaseData = (PVOID)pData;
    pData->m_pSysData = pServerData->m_pSysData;
    //************************以下模块接口必须赋值******************************
    pModScr->pModeleInit = ModuleScrInit; //实现模块初始化
    pModScr->pModeleReset = ModuleScrReset; //实现模块复位
    pModScr->pModeleStart = ModuleScrStart; //实现模块开始
    pModScr->pModeleStop = ModuleScrStop; //实现模块结束
    pModScr->pModeleRelease = ModuleScrRelease;//实现
    pModScr->pMsgNotify = ScrMsgNotify;//实现消息队列处理
    pModScr->pModele10msProcess = NULL;//不实现，置为NULL
    pModScr->pModele50msProcess = ModuleScr50msProcess;//不实现，置为NULL
    pModScr->pModele1sProcess = NULL;//实现1s调用
    pModScr->pModele1msProcess = NULL;//实现1s调用
    strcpy(pModScr->m_ModName, "ModScr");

//     printf("CreateModuleScr!!\n");
    return (PMODULEBASE)pModScr;
}


//显示数码管8字
void HTBSegVal(HTB_ICN *H_Ram, HTB_ICN *L_Ram, INT16U SegData)
{
    switch (SegData)
    {
    case 0:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 0;
        H_Ram->COM3 = 1;
        break;

    case 1:
        L_Ram->COM1 = 0;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 0;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 0;
        H_Ram->COM3 = 0;
        break;

    case 2:
        L_Ram->COM1  = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 0;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 1;
        break;

    case 3:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 0;
        break;

    case 4:
        L_Ram->COM1 = 0;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 0;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 0;
        break;

    case 5:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 0;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 0;
        break;

    case 6:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 0;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 1;
        break;

    case 7:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 0;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 0;
        H_Ram->COM3 = 0;
        break;

    case 8:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 1;
        break;

    case 9:
        L_Ram->COM1 = 1;
        L_Ram->COM2 = 1;
        L_Ram->COM3 = 1;
        L_Ram->COM4 = 1;
        H_Ram->COM1 = 1;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 0;
        break;
    case MINUS:
        L_Ram->COM1 = 0;
        L_Ram->COM2 = 0;
        L_Ram->COM3 = 0;
        L_Ram->COM4 = 0;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 1;
        H_Ram->COM3 = 0;
        break;
    default:
        L_Ram->COM1 = 0;
        L_Ram->COM2 = 0;
        L_Ram->COM3 = 0;
        L_Ram->COM4 = 0;
        H_Ram->COM1 = 0;
        H_Ram->COM2 = 0;
        H_Ram->COM3 = 0;
        break;
    }
}

void ShowHT1621Temperature(INT16U TempCH, void* pArg) //显示体温信息为--
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(TempCH)
    {
    case 1:
        pData->IC1_S[Screen_1_S0].COM1 = 0;
        pData->IC1_S[Screen_1_S0].COM2 = 1;
        pData->IC1_S[Screen_1_S0].COM3 = 0;

        pData->IC1_S[Screen_1_S1].COM1 = 0;
        pData->IC1_S[Screen_1_S1].COM2 = 0;
        pData->IC1_S[Screen_1_S1].COM3 = 0;
        pData->IC1_S[Screen_1_S1].COM4 = 0;
        pData->IC1_S[Screen_1_S2].COM1 = 0;
        pData->IC1_S[Screen_1_S2].COM2 = 1;
        pData->IC1_S[Screen_1_S2].COM3 = 0;
        pData->IC1_S[Screen_1_S2].COM4 = 0;
        pData->IC1_S[Screen_1_S3].COM1 = 0;
        pData->IC1_S[Screen_1_S3].COM2 = 0;
        pData->IC1_S[Screen_1_S3].COM3 = 0;
        pData->IC1_S[Screen_1_S3].COM4 = 0;
        pData->IC1_S[Screen_1_S4].COM1 = 0;
        pData->IC1_S[Screen_1_S4].COM2 = 1;
        pData->IC1_S[Screen_1_S4].COM3 = 0;
        //pData->IC2_S[4].COM4=0;
        pData->IC1_S[Screen_1_S5].COM1 = 0;
        pData->IC1_S[Screen_1_S5].COM2 = 0;
        pData->IC1_S[Screen_1_S5].COM3 = 0;
        pData->IC1_S[Screen_1_S5].COM4 = 0;


        HTBICNSVal(pData->IC1_S[Screen_1_S0]);
        HTBICNSVal(pData->IC1_S[Screen_1_S1]);
        HTBICNSVal(pData->IC1_S[Screen_1_S2]);
        HTBICNSVal(pData->IC1_S[Screen_1_S3]);
        HTBICNSVal(pData->IC1_S[Screen_1_S4]);
        HTBICNSVal(pData->IC1_S[Screen_1_S5]);
        break;
    case 2:
        pData->IC1_S[Screen_1_S6].COM1 = 0;
        pData->IC1_S[Screen_1_S6].COM2 = 1;
        pData->IC1_S[Screen_1_S6].COM3 = 0;
        //pData->IC2_S[0].COM4=0;
        pData->IC1_S[Screen_1_S7].COM1 = 0;
        pData->IC1_S[Screen_1_S7].COM2 = 0;
        pData->IC1_S[Screen_1_S7].COM3 = 0;
        pData->IC1_S[Screen_1_S7].COM4 = 0;
        pData->IC1_S[Screen_1_S8].COM1 = 0;
        pData->IC1_S[Screen_1_S8].COM2 = 1;
        pData->IC1_S[Screen_1_S8].COM3 = 0;
        pData->IC1_S[Screen_1_S8].COM4 = 0;
        pData->IC1_S[Screen_1_S9].COM1 = 0;
        pData->IC1_S[Screen_1_S9].COM2 = 0;
        pData->IC1_S[Screen_1_S9].COM3 = 0;
        pData->IC1_S[Screen_1_S9].COM4 = 0;
        HTBICNSVal(pData->IC1_S[Screen_1_S6]);
        HTBICNSVal(pData->IC1_S[Screen_1_S7]);
        HTBICNSVal(pData->IC1_S[Screen_1_S8]);
        HTBICNSVal(pData->IC1_S[Screen_1_S9]);
        break;
    case 3:
        pData->IC1_S[Screen_1_S10].COM1 = 0;
        pData->IC1_S[Screen_1_S10].COM2 = 1;
        pData->IC1_S[Screen_1_S10].COM3 = 0;
        //pData->IC2_S[12].COM4=0;
        pData->IC1_S[Screen_1_S11].COM1 = 0;
        pData->IC1_S[Screen_1_S11].COM2 = 0;
        pData->IC1_S[Screen_1_S11].COM3 = 0;
        pData->IC1_S[Screen_1_S11].COM4 = 0;
        pData->IC1_S[Screen_1_S12].COM1 = 0;
        pData->IC1_S[Screen_1_S12].COM2 = 1;
        pData->IC1_S[Screen_1_S12].COM3 = 0;
        //pData->IC1_S[12].COM4=0;
        pData->IC1_S[Screen_1_S13].COM1 = 0;
        pData->IC1_S[Screen_1_S13].COM2 = 0;
        pData->IC1_S[Screen_1_S13].COM3 = 0;
        pData->IC1_S[Screen_1_S13].COM4 = 0;
        pData->IC1_S[Screen_1_S14].COM1 = 0;
        pData->IC1_S[Screen_1_S14].COM2 = 1;
        pData->IC1_S[Screen_1_S14].COM3 = 0;
        pData->IC1_S[Screen_1_S14].COM4 = 1;
        pData->IC1_S[Screen_1_S15].COM1 = 0;
        pData->IC1_S[Screen_1_S15].COM2 = 0;
        pData->IC1_S[Screen_1_S15].COM3 = 0;
        pData->IC1_S[Screen_1_S15].COM4 = 0;

        HTBICNSVal(pData->IC1_S[Screen_1_S10]);
        HTBICNSVal(pData->IC1_S[Screen_1_S11]);
        HTBICNSVal(pData->IC1_S[Screen_1_S12]);
        HTBICNSVal(pData->IC1_S[Screen_1_S13]);
        HTBICNSVal(pData->IC1_S[Screen_1_S14]);
        HTBICNSVal(pData->IC1_S[Screen_1_S15]);
        break;
    case 4:
        pData->IC2_S[0].COM1 = 0;
        pData->IC2_S[0].COM2 = 1;
        pData->IC2_S[0].COM3 = 0;
        //pData->IC2_S[0].COM4=0;
        pData->IC2_S[1].COM1 = 0;
        pData->IC2_S[1].COM2 = 0;
        pData->IC2_S[1].COM3 = 0;
        pData->IC2_S[1].COM4 = 0;
        pData->IC2_S[2].COM1 = 0;
        pData->IC2_S[2].COM2 = 1;
        pData->IC2_S[2].COM3 = 0;
        pData->IC2_S[2].COM4 = 0;
        pData->IC2_S[3].COM1 = 0;
        pData->IC2_S[3].COM2 = 0;
        pData->IC2_S[3].COM3 = 0;
        pData->IC2_S[3].COM4 = 0;
        pData->IC2_S[4].COM1 = 0;
        pData->IC2_S[4].COM2 = 1;
        pData->IC2_S[4].COM3 = 0;
        //pData->IC2_S[4].COM4=0;
        pData->IC2_S[5].COM1 = 0;
        pData->IC2_S[5].COM2 = 0;
        pData->IC2_S[5].COM3 = 0;
        pData->IC2_S[5].COM4 = 0;

        HTBICNSVal(pData->IC2_S[0]);
        HTBICNSVal(pData->IC2_S[1]);
        HTBICNSVal(pData->IC2_S[2]);
        HTBICNSVal(pData->IC2_S[3]);
        HTBICNSVal(pData->IC2_S[4]);
        HTBICNSVal(pData->IC2_S[5]);
        break;
    case 5:
        pData->IC2_S[6].COM1 = 0;
        pData->IC2_S[6].COM2 = 1;
        pData->IC2_S[6].COM3 = 0;
        //pData->IC2_S[0].COM4=0;
        pData->IC2_S[7].COM1 = 0;
        pData->IC2_S[7].COM2 = 0;
        pData->IC2_S[7].COM3 = 0;
        pData->IC2_S[7].COM4 = 0;
        pData->IC2_S[8].COM1 = 0;
        pData->IC2_S[8].COM2 = 1;
        pData->IC2_S[8].COM3 = 0;
        pData->IC2_S[8].COM4 = 0;
        pData->IC2_S[9].COM1 = 0;
        pData->IC2_S[9].COM2 = 0;
        pData->IC2_S[9].COM3 = 0;
        pData->IC2_S[9].COM4 = 0;
        pData->IC2_S[10].COM1 = 0;
        pData->IC2_S[10].COM2 = 1;
        pData->IC2_S[10].COM3 = 0;
        //pData->IC2_S[4].COM4=0;
        pData->IC2_S[11].COM1 = 0;
        pData->IC2_S[11].COM2 = 0;
        pData->IC2_S[11].COM3 = 0;
        pData->IC2_S[11].COM4 = 0;

        HTBICNSVal(pData->IC2_S[6]);
        HTBICNSVal(pData->IC2_S[7]);
        HTBICNSVal(pData->IC2_S[8]);
        HTBICNSVal(pData->IC2_S[9]);
        HTBICNSVal(pData->IC2_S[10]);
        HTBICNSVal(pData->IC2_S[11]);
        break;
    case 6:
        pData->IC2_S[12].COM1 = 0;
        pData->IC2_S[12].COM2 = 1;
        pData->IC2_S[12].COM3 = 0;
        //pData->IC2_S[12].COM4=0;
        pData->IC2_S[13].COM1 = 0;
        pData->IC2_S[13].COM2 = 0;
        pData->IC2_S[13].COM3 = 0;
        pData->IC2_S[13].COM4 = 0;
        pData->IC2_S[14].COM1 = 0;
        pData->IC2_S[14].COM2 = 1;
        pData->IC2_S[14].COM3 = 0;
        pData->IC2_S[14].COM4 = 0;
        pData->IC2_S[15].COM1 = 0;
        pData->IC2_S[15].COM2 = 0;
        pData->IC2_S[15].COM3 = 0;
        pData->IC2_S[15].COM4 = 0;
        pData->IC2_S[16].COM1 = 0;
        pData->IC2_S[16].COM2 = 1;
        pData->IC2_S[16].COM3 = 0;
        //pData->IC2_S[16].COM4=0;
        pData->IC2_S[17].COM1 = 0;
        pData->IC2_S[17].COM2 = 0;
        pData->IC2_S[17].COM3 = 0;
        pData->IC2_S[17].COM4 = 0;

        HTBICNSVal(pData->IC2_S[12]);
        HTBICNSVal(pData->IC2_S[13]);
        HTBICNSVal(pData->IC2_S[14]);
        HTBICNSVal(pData->IC2_S[15]);
        HTBICNSVal(pData->IC2_S[16]);
        HTBICNSVal(pData->IC2_S[17]);
        break;
    default:
        break;
    }
}

void HTBICNSVal(HTB_ICN HTBRam) //显示屏区域
{
    INT8U HT1621Data = (HTBRam.COM1 << 3) + (HTBRam.COM2 << 2) + (HTBRam.COM3 << 1) + (HTBRam.COM4);
    WriteHT1621OneData(HTBRam.P_Addr, HT1621Data, HTBRam.P_WhichIC);
}

void WriteHT1621Temperature(INT16U TempCH, INT16U Data, INT16U WhichIC, void* pArg) //显示温度
{

    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    INT16U	 addr_Thousands = 0;
    INT16U   addr_Hundreds = 0;
    INT16U   addr_Ten = 0;
    INT16U TenBit = 0;
    INT16U HundredsBit = 0;
    INT16U ThousandsBits = 0;
    INT8U TempCH_ADDR = 0;
    Data += 5;
    TenBit = (Data % 100) / 10;
    HundredsBit = (Data % 1000) / 100;
    ThousandsBits = (Data % 10000) / 1000;
    if(ThousandsBits == 0)
    {
        ThousandsBits = 99; //判断千位是零就不显示
    }

    switch(TempCH)
    {
    case Temp1Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S0]), &(pData->IC1_S[Screen_1_S1]), ThousandsBits);
        HTBSegVal(&pData->IC1_S[Screen_1_S2], &pData->IC1_S[Screen_1_S3], HundredsBit);
        HTBSegVal(&pData->IC1_S[Screen_1_S4], &pData->IC1_S[Screen_1_S5], TenBit);
        HTBICNSVal(pData->IC1_S[Screen_1_S0]);
        HTBICNSVal(pData->IC1_S[Screen_1_S1]);
        HTBICNSVal(pData->IC1_S[Screen_1_S2]);
        HTBICNSVal(pData->IC1_S[Screen_1_S3]);
        HTBICNSVal(pData->IC1_S[Screen_1_S4]);
        HTBICNSVal(pData->IC1_S[Screen_1_S5]);
        break;
    case WaterTempSet_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S6]), &(pData->IC1_S[Screen_1_S7]), ThousandsBits);
        HTBSegVal(&pData->IC1_S[Screen_1_S8], &pData->IC1_S[Screen_1_S9], HundredsBit);
        HTBICNSVal(pData->IC1_S[Screen_1_S6]);
        HTBICNSVal(pData->IC1_S[Screen_1_S7]);
        HTBICNSVal(pData->IC1_S[Screen_1_S8]);
        HTBICNSVal(pData->IC1_S[Screen_1_S9]);
        break;
    case Temp2Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S10]), &(pData->IC1_S[Screen_1_S11]), ThousandsBits); //6);//
        HTBSegVal(&pData->IC1_S[Screen_1_S12], &pData->IC1_S[Screen_1_S13], HundredsBit);
        HTBSegVal(&pData->IC1_S[Screen_1_S14], &pData->IC1_S[Screen_1_S15], TenBit);
        HTBICNSVal(pData->IC1_S[Screen_1_S10]);
        HTBICNSVal(pData->IC1_S[Screen_1_S11]);
        HTBICNSVal(pData->IC1_S[Screen_1_S12]);
        HTBICNSVal(pData->IC1_S[Screen_1_S13]);
        HTBICNSVal(pData->IC1_S[Screen_1_S14]);
        HTBICNSVal(pData->IC1_S[Screen_1_S15]);
        break;
    case Temp1_ADDRESS:
        HTBSegVal(&(pData->IC2_S[Temp1CH2_PIN_ADDR]), &(pData->IC2_S[Temp1CH2_PIN_ADDR + 1]), ThousandsBits);
        HTBSegVal(&pData->IC2_S[Temp1CH2_PIN_ADDR + 2], &pData->IC2_S[Temp1CH2_PIN_ADDR + 3], HundredsBit);
        HTBSegVal(&pData->IC2_S[Temp1CH2_PIN_ADDR + 4], &pData->IC2_S[Temp1CH2_PIN_ADDR + 5], TenBit);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 5]);
        break;
    case WaterTemp_ADDRESS:
        HTBSegVal(&(pData->IC2_S[TWaterCH2_PIN_ADDR]), &(pData->IC2_S[TWaterCH2_PIN_ADDR + 1]), ThousandsBits);
        HTBSegVal(&pData->IC2_S[TWaterCH2_PIN_ADDR + 2], &pData->IC2_S[TWaterCH2_PIN_ADDR + 3], HundredsBit);
        HTBSegVal(&pData->IC2_S[TWaterCH2_PIN_ADDR + 4], &pData->IC2_S[TWaterCH2_PIN_ADDR + 5], TenBit);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 5]);
        break;
    case Temp2_ADDRESS:
        HTBSegVal(&(pData->IC2_S[Temp2CH2_PIN_ADDR]), &(pData->IC2_S[Temp2CH2_PIN_ADDR + 1]), ThousandsBits);
        HTBSegVal(&pData->IC2_S[Temp2CH2_PIN_ADDR + 2], &pData->IC2_S[Temp2CH2_PIN_ADDR + 3], HundredsBit);
        HTBSegVal(&pData->IC2_S[Temp2CH2_PIN_ADDR + 4], &pData->IC2_S[Temp2CH2_PIN_ADDR + 5], TenBit);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 5]);
        break;
    default:
        break;
    }
}
void HideHT1621Temperature(INT16U TempCH, void* pArg) //隐藏温度显示区域
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(TempCH)
    {
    case Temp1Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S0]), &(pData->IC1_S[Screen_1_S1]), 99);
        HTBSegVal(& pData->IC1_S[Screen_1_S2], &pData->IC1_S[Screen_1_S3], 99);
        HTBSegVal(& pData->IC1_S[Screen_1_S4], &pData->IC1_S[Screen_1_S5], 99);
        HTBICNSVal(pData->IC1_S[Screen_1_S0]);
        HTBICNSVal(pData->IC1_S[Screen_1_S1]);
        HTBICNSVal(pData->IC1_S[Screen_1_S2]);
        HTBICNSVal(pData->IC1_S[Screen_1_S3]);
        HTBICNSVal(pData->IC1_S[Screen_1_S4]);
        HTBICNSVal(pData->IC1_S[Screen_1_S5]);
        break;
    case WaterTempSet_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S6]), &(pData->IC1_S[Screen_1_S7]), 99);
        HTBSegVal(&pData->IC1_S[Screen_1_S8], &pData->IC1_S[Screen_1_S9], 99);
        HTBICNSVal(pData->IC1_S[Screen_1_S6]);
        HTBICNSVal(pData->IC1_S[Screen_1_S7]);
        HTBICNSVal(pData->IC1_S[Screen_1_S8]);
        HTBICNSVal(pData->IC1_S[Screen_1_S9]);
        break;
    case Temp2Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S10]), &(pData->IC1_S[Screen_1_S11]), 99);
        HTBSegVal(&pData->IC1_S[Screen_1_S12], &pData->IC1_S[Screen_1_S13], 99);
        HTBSegVal(&pData->IC1_S[Screen_1_S14], &pData->IC1_S[Screen_1_S15], 99);
        HTBICNSVal(pData->IC1_S[Screen_1_S10]);
        HTBICNSVal(pData->IC1_S[Screen_1_S11]);
        HTBICNSVal(pData->IC1_S[Screen_1_S12]);
        HTBICNSVal(pData->IC1_S[Screen_1_S13]);
        HTBICNSVal(pData->IC1_S[Screen_1_S14]);
        HTBICNSVal(pData->IC1_S[Screen_1_S15]);
        break;
    case WaterTemp_ADDRESS:
        HTBSegVal(&(pData->IC2_S[TWaterCH2_PIN_ADDR]), &(pData->IC2_S[TWaterCH2_PIN_ADDR + 1]), 99);
        HTBSegVal(&pData->IC2_S[TWaterCH2_PIN_ADDR + 2], &pData->IC2_S[TWaterCH2_PIN_ADDR + 3], 99);
        HTBSegVal(&pData->IC2_S[TWaterCH2_PIN_ADDR + 4], &pData->IC2_S[TWaterCH2_PIN_ADDR + 5], 99);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[TWaterCH2_PIN_ADDR + 5]);
        break;
    case Temp1_ADDRESS:
        HTBSegVal(&(pData->IC2_S[Temp1CH2_PIN_ADDR]), &(pData->IC2_S[Temp1CH2_PIN_ADDR + 1]), 99);
        HTBSegVal(&pData->IC2_S[Temp1CH2_PIN_ADDR + 2], &pData->IC2_S[Temp1CH2_PIN_ADDR + 3], 99);
        HTBSegVal(&pData->IC2_S[Temp1CH2_PIN_ADDR + 4], &pData->IC2_S[Temp1CH2_PIN_ADDR + 5], 99);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[Temp1CH2_PIN_ADDR + 5]);
        break;
    case Temp2_ADDRESS:
        HTBSegVal(&(pData->IC2_S[Temp2CH2_PIN_ADDR]), &(pData->IC2_S[Temp2CH2_PIN_ADDR + 1]), 99);
        HTBSegVal(&pData->IC2_S[Temp2CH2_PIN_ADDR + 2], &pData->IC2_S[Temp2CH2_PIN_ADDR + 3], 99);
        HTBSegVal(&pData->IC2_S[Temp2CH2_PIN_ADDR + 4], &pData->IC2_S[Temp2CH2_PIN_ADDR + 5], 99);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 1]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 2]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 3]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 4]);
        HTBICNSVal(pData->IC2_S[Temp2CH2_PIN_ADDR + 5]);
        break;
    default:
        break;
    }
}

void ShowMinus(INT16U TempCH, void* pArg) //显示负号
{

    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(TempCH)
    {
    case Temp1Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S0]), &(pData->IC1_S[Screen_1_S1]), MINUS);
        HTBICNSVal(pData->IC1_S[Screen_1_S0]);
        HTBICNSVal(pData->IC1_S[Screen_1_S1]);
        HTBICNSVal(pData->IC1_S[Screen_1_S2]);
        HTBICNSVal(pData->IC1_S[Screen_1_S3]);
        HTBICNSVal(pData->IC1_S[Screen_1_S4]);
        HTBICNSVal(pData->IC1_S[Screen_1_S5]);
        break;
    case Temp2Set_ADDRESS:
        HTBSegVal(&(pData->IC1_S[Screen_1_S10]), &(pData->IC1_S[Screen_1_S11]), MINUS);
        HTBICNSVal(pData->IC1_S[Screen_1_S10]);
        HTBICNSVal(pData->IC1_S[Screen_1_S11]);
        HTBICNSVal(pData->IC1_S[Screen_1_S12]);
        HTBICNSVal(pData->IC1_S[Screen_1_S13]);
        HTBICNSVal(pData->IC1_S[Screen_1_S14]);
        HTBICNSVal(pData->IC1_S[Screen_1_S15]);
        break;
    default:
        break;
    }
}

void SystemStaStop(void* pArg)//系统在停止状态下,显示屏信息
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->IC2_S[0].COM4 = 0;
    pData->IC2_S[12].COM4 = 0;

    pData->IC2_S[6].COM4 = 0; //制冷
    pData->IC2_S[8].COM4 = 0; //制热

    HTBICNSVal(pData->IC2_S[8]);//p11
    HTBICNSVal(pData->IC2_S[12]);//水路2关
    HTBICNSVal(pData->IC2_S[6]);//s8
    HTBICNSVal(pData->IC2_S[0]);//水路1关
}

void DisplayTemp(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp )//温度显示
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1, IC1_PIN, pArg); //显示温度设置1
    WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2, IC1_PIN, pArg); //显示温度设置2
    WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTemp, IC1_PIN, pArg); //显示水温设置
}

void TempShow(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp )//温度显示
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    WriteHT1621Temperature(Temp1_ADDRESS, Temp1, IC1_PIN, pArg); //显示温度设置1
    WriteHT1621Temperature(Temp2_ADDRESS, Temp2, IC1_PIN, pArg); //显示温度设置2
    WriteHT1621Temperature(WaterTemp_ADDRESS, WaterTemp, IC1_PIN, pArg); //显示水温设置
}


void DisplayWorkMode(void* pArg, eSystemStatus Sta)
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Sta)
    {
    case Cooler:
        pData->IC2_S[Screen_1_S6].COM4 = 1;
        pData->IC2_S[Screen_1_S8].COM4 = 0;
        break;
    case Heater:
        pData->IC2_S[Screen_1_S6].COM4 = 0;
        pData->IC2_S[Screen_1_S8].COM4 = 1;
        break;
    default:
    case Stop:
        pData->IC2_S[Screen_1_S6].COM4 = 0;
        pData->IC2_S[Screen_1_S8].COM4 = 0;
        break;
    }

}


void DisplayCoolerStatus(void* pArg, eStatus Cooler) //系统的工作模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cooler == Status_On) //制冷开
    {
        pData->IC2_S[20].COM4 = 1; //雪花

    }
    else
    {
        pData->IC2_S[20].COM4 = 0; //雪花
    }
    //----------------------------------
}

void DisplayHeaterStatus(void* pArg, eItemStatus Item) //系统的工作模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    //----------------------------------
    switch(Item)
    {
    case Show:
        pData->IC2_S[20].COM2 = 1; //太阳
        break;
    case Hide:
        pData->IC2_S[20].COM2 = 0; //太阳
        break;
    case Invalid:
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[20].COM2 = 1; //太阳
        }
        else
        {
            pData->IC2_S[20].COM2 = 0; //太阳
        }
        break;
    default:
        break;
    }
}

void DisplayCycle1Mode(void* pArg, eStatus Cycle1) //水路显示模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cycle1 == Status_On) //水路1开启了
    {
        pData->IC2_S[0].COM4 = 1;
    }
    else
    {
        pData->IC2_S[0].COM4 = 0;
    }
}

void DisplayCycle2Mode(void* pArg, eStatus Cycle2) //水路显示模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cycle2 == Status_On) //水路2开启了
    {
        pData->IC2_S[12].COM4 = 1;
    }
    else
    {
        pData->IC2_S[12].COM4 = 0;
    }
}

void DisplayBump1Mode(void* pArg, eItemStatus Item) //水泵的工作模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[21].COM1 = 1;
            pData->IC2_S[21].COM2 = 0;
            pData->IC2_S[21].COM3 = 0;
            pData->IC2_S[21].COM4 = 1;
        }
        else
        {
            pData->IC2_S[21].COM1 = 0;
            pData->IC2_S[21].COM2 = 1;
            pData->IC2_S[21].COM3 = 1;
            pData->IC2_S[21].COM4 = 0;
        }
        break;
    case Hide:
        pData->IC2_S[21].COM1 = 0;
        pData->IC2_S[21].COM2 = 0;
        pData->IC2_S[21].COM3 = 0;
        pData->IC2_S[21].COM4 = 0;
        break;
    case Invalid:
        pData->IC2_S[21].COM1 = 1;
        pData->IC2_S[21].COM2 = 1;
        pData->IC2_S[21].COM3 = 1;
        pData->IC2_S[21].COM4 = 1;
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[21].COM1 = 1;
            pData->IC2_S[21].COM2 = 1;
            pData->IC2_S[21].COM3 = 1;
            pData->IC2_S[21].COM4 = 1;
        }
        else
        {
            pData->IC2_S[21].COM1 = 0;
            pData->IC2_S[21].COM2 = 0;
            pData->IC2_S[21].COM3 = 0;
            pData->IC2_S[21].COM4 = 0;
        }
        break;
    default:
        break;
    }
}

void DisplayBump2Mode(void* pArg, eItemStatus Item) //水泵的工作模式
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show: //正常运行
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[18].COM1 = 1;
            pData->IC2_S[18].COM2 = 0;
            pData->IC2_S[18].COM3 = 0;
            pData->IC2_S[18].COM4 = 1;
        }
        else
        {
            pData->IC2_S[18].COM1 = 0;
            pData->IC2_S[18].COM2 = 1;
            pData->IC2_S[18].COM3 = 1;
            pData->IC2_S[18].COM4 = 0;
        }
        break;
    case Hide: //隐藏
        pData->IC2_S[18].COM1 = 0;
        pData->IC2_S[18].COM2 = 0;
        pData->IC2_S[18].COM3 = 0;
        pData->IC2_S[18].COM4 = 0;
        break;
    case Invalid: //全部显示
        pData->IC2_S[18].COM1 = 1;
        pData->IC2_S[18].COM2 = 1;
        pData->IC2_S[18].COM3 = 1;
        pData->IC2_S[18].COM4 = 1;
        break;
    case Flash: //全部显示，消失
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[18].COM1 = 1;
            pData->IC2_S[18].COM2 = 1;
            pData->IC2_S[18].COM3 = 1;
            pData->IC2_S[18].COM4 = 1;
        }
        else
        {
            pData->IC2_S[18].COM1 = 0;
            pData->IC2_S[18].COM2 = 0;
            pData->IC2_S[18].COM3 = 0;
            pData->IC2_S[18].COM4 = 0;
        }
        break;
    default:
        break;
    }
}

void DisplayWaterStatusI(void* pArg) //水位状态
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;

    pData->IC2_S[20].COM3 = 0; //p12
    pData->IC2_S[19].COM4 = 0; //p13
    pData->IC2_S[19].COM3 = 0; //p14
    pData->IC2_S[19].COM2 = 0; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
void DisplayWaterStatusII(void* pArg) //水位状态
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;

    pData->IC2_S[20].COM3 = 0; //p12
    pData->IC2_S[19].COM4 = 0; //p13
    pData->IC2_S[19].COM3 = 1; //p14
    pData->IC2_S[19].COM2 = 1; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
void DisplayWaterStatusIII(void* pArg) //水位状态
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->IC2_S[20].COM3 = 1; //p12
    pData->IC2_S[19].COM4 = 1; //p13
    pData->IC2_S[19].COM3 = 1; //p14
    pData->IC2_S[19].COM2 = 1; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
// 		    ShowHT1621Temperature(Temp1Set_ADDRESS,pArg);//显示体温信息为--
//ShowHT1621Temperature(WaterTempSet_ADDRESS,pArg);
//     ShowHT1621Temperature(Temp2Set_ADDRESS,pArg);


void DisplayTemp1Val(void* pArg, eItemStatus Item, INT16U Temp) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp1_ADDRESS, Temp, IC2_PIN, pArg);//显示温度1
        break;
    case Hide:
        HideHT1621Temperature(Temp1_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp1_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp1_ADDRESS, Temp, IC2_PIN, pArg);//显示温度1
        }
        else
        {
            HideHT1621Temperature(Temp1_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayTemp2Val(void* pArg, eItemStatus Item, INT16U Temp) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp2_ADDRESS, Temp, IC2_PIN, pArg); //显示温度  2
        break;
    case Hide:
        HideHT1621Temperature(Temp2_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp2_ADDRESS, Temp, IC2_PIN, pArg); //显示温度  2
        }
        else
        {
            HideHT1621Temperature(Temp2_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayWaterTempVal(void* pArg, eItemStatus Item, INT16U Temp) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(WaterTemp_ADDRESS, Temp, IC2_PIN, pArg); //显示水温
        break;
    case Hide:
        HideHT1621Temperature(WaterTemp_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_50msCount % 2 == 1) {
            WriteHT1621Temperature(WaterTemp_ADDRESS, Temp, IC2_PIN, pArg); //显示水温
        }
        else {
            HideHT1621Temperature(WaterTemp_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayCal1Set(void* pArg, eItemStatus Item, INT16S Cal1Set) //校准1设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    BOOLEAN ret = FALSE;
    Cal1Set *= 10;
    if(Cal1Set < 0)
    {
        ret = TRUE;
        Cal1Set = -Cal1Set;
    }
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp1Set_ADDRESS, Cal1Set, IC1_PIN, pArg);
        if(ret) {
            ShowMinus(Temp1Set_ADDRESS, pArg);
        }
        break;
    case Hide:
        HideHT1621Temperature(Temp1Set_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp1Set_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp1Set_ADDRESS, Cal1Set, IC1_PIN, pArg);
            if(ret) {
                ShowMinus(Temp1Set_ADDRESS, pArg);
            }
        }
        else
        {
            HideHT1621Temperature(Temp1Set_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayCal2Set(void* pArg, eItemStatus Item, INT16S Cal2Set) //校准2设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    BOOLEAN ret = FALSE;
    Cal2Set *= 10;
    if(Cal2Set < 0)
    {
        ret = TRUE;
        Cal2Set = -Cal2Set;
    }
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp2Set_ADDRESS, Cal2Set, IC1_PIN, pArg);
        if(ret) {
            ShowMinus(Temp2Set_ADDRESS, pArg);
        }
        break;
    case Hide:
        HideHT1621Temperature(Temp2Set_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2Set_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp2Set_ADDRESS, Cal2Set, IC1_PIN, pArg);
            if(ret) {
                ShowMinus(Temp2Set_ADDRESS, pArg);
            }
        }
        else
        {
            HideHT1621Temperature(Temp2Set_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayTemp1Set(void* pArg, eItemStatus Item, INT16U Temp1Set) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1Set, IC1_PIN, pArg); //显示温度
        break;
    case Hide:
        HideHT1621Temperature(Temp1Set_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp1Set_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1Set, IC1_PIN, pArg); //显示温度
        }
        else
        {
            HideHT1621Temperature(Temp1Set_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayWaterTempSet(void* pArg,  eItemStatus Item,  INT16U WaterTempSet) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTempSet, IC1_PIN, pArg); //显示温度
        break;
    case Hide:
        HideHT1621Temperature(WaterTempSet_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(WaterTempSet_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTempSet, IC1_PIN, pArg); //显示温度
        }
        else
        {
            HideHT1621Temperature(WaterTempSet_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayTemp2Set(void* pArg,  eItemStatus Item,  INT16U Temp2Set) //温度设置
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2Set, IC1_PIN, pArg); //显示温度
        break;
    case Hide:
        HideHT1621Temperature(Temp2Set_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2Set_ADDRESS, pArg); //显示体温信息为--
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2Set, IC1_PIN, pArg); //显示温度
        }
        else
        {
            HideHT1621Temperature(Temp2Set_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayRefresh(void* pArg)//刷新区域
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    //刷新区域
    HTBICNSVal(pData->IC2_S[21]);
    HTBICNSVal(pData->IC2_S[20]);
    HTBICNSVal(pData->IC2_S[19]);
    HTBICNSVal(pData->IC2_S[18]);
    HTBICNSVal(pData->IC2_S[12]);
    HTBICNSVal(pData->IC2_S[8]);
    HTBICNSVal(pData->IC2_S[6]);
    HTBICNSVal(pData->IC2_S[0]);

}

void HtbRamInit(void* pArg) //显示屏区域初始化
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    INT16U i = 0;

    for(i = 0; i < IC_PIN; i++)
    {
        pData->IC1_S[i].P_Addr = i;
        pData->IC1_S[i].P_WhichIC = 1;
        pData->IC2_S[i].P_Addr = i;
        pData->IC2_S[i].P_WhichIC = 2;
    }

    pData->IC1_S[Screen_1_S0].COM4 = 1; //体温设置S2
    pData->IC1_S[Screen_1_S4].COM4 = 1; //体温设置的小数点 T1
    pData->IC1_S[Screen_1_S6].COM4 = 1; //水温设置 t2/s3
    pData->IC1_S[Screen_1_S10].COM4 = 1; //体温设置2  t3/s4
    pData->IC1_S[Screen_1_S14].COM4 = 1; //t5 小数点
    pData->IC1_S[Screen_1_S12].COM4 = 1; //温度t6

    pData->IC2_S[22].COM1 = 1; //p21.s5 ,T7,S7,T8,S9,T9
    pData->IC2_S[20].COM1 = 1;
    pData->IC2_S[4].COM4 = 1; //p1
    pData->IC2_S[10].COM4 = 1; //p2
    pData->IC2_S[16].COM4 = 1; //p3

    //tommy fix
    pData->IC1_S[Screen_1_S0].COM4 = 1;
    pData->IC1_S[Screen_1_S6].COM4 = 1;
    pData->IC1_S[Screen_1_S4].COM4 = 1;
    //HTBICNSVal(pData->IC2_S[22]);

}

void WriteHT1621OneData(INT16U Addr, INT16U Data, INT16U WhichIC) //把数据送给驱动LCD.H
{
    HT1621WrOneData(Addr, Data, WhichIC);
}

void WaterStatusAlm(void* pArg) //水位报警
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(pData->m_50msCount % 2 == 1)
        pData->IC2_S[19].COM1 = 1; //p16
    else
        pData->IC2_S[19].COM1 = 0; //p16

    HTBICNSVal(pData->IC2_S[19]);
}

void WaterTempSetAlm(void* pArg)//水位报警
{

}

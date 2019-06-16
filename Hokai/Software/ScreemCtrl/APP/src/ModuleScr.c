//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleScr.c
//*
//* �ļ����� : SCR����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
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

    HT1621B_Init();//��ʾ��Ӳ������
    HtbRamInit(pArg);//��ʾ��Ԫ�صĳ�ʼ��
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
        case Cooler: //ϵͳ������״̬
            DisplayWorkMode(pArg, Cooler);
            break;
        case Heater: //ϵͳ������״̬
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
        //////////////////////��̺����///////////////////////////
        if(pData->m_pSysData->m_Cycle1Set == Status_On)
        {
            DisplayCycle2Mode(pArg, Status_On);
        }
        else {
            DisplayCycle2Mode(pArg, Status_Off);
        }
        //////////////////////��̺����///////////////////////////
    }
    /////////////////////˫̺����/////////////////////////////
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
    /////////////////////////˫̺����/////////////////////////

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
    case  Status_I://ȱˮ��ˮλ����ʾ1����p16
        DisplayWaterStatusI(pArg);//ˮλ״̬
        break;
    case  Status_II://��ʾ����ˮλ��
        DisplayWaterStatusII(pArg);//ˮλ״̬
        break;
    case  Status_III://��ˮ��ˮλ����ʾ4����
        DisplayWaterStatusIII(pArg);//ˮλ״̬
        break;
    default :
        break;
    }


    if(pData->m_pSysData->m_WaterLow == Status_On)
    {
        WaterStatusAlm(pArg); //ˮλ����
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
            if(pData->m_pSysData->m_FocusStatus == Temp1Focus ) //���ܰ�ť���¶�����1
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
            DisplayTemp2Set(pArg, ItemSta, pData->m_pSysData->m_Temp1Set); //�¶�����
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
            if(pData->m_pSysData->m_FocusStatus == Temp1Focus ) //���ܰ�ť���¶�����1
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
            DisplayTemp1Set(pArg, ItemSta, pData->m_pSysData->m_Temp1Set); //�¶�����
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
            if(pData->m_pSysData->m_FocusStatus == Temp2Focus ) //���ܰ�ť���¶�����1
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
            DisplayTemp2Set(pArg, ItemSta, pData->m_pSysData->m_Temp2Set); //�¶�����
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
                || pData->m_pSysData->m_HeaterModeWT2Low == Status_On) //���ܰ�ť���¶�����1
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
    DisplayWaterTempSet(pArg, ItemSta, pData->m_pSysData->m_WaterTempSet); //�¶�����
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

    DisplayRefresh(pArg);//ˢ������
}

void ScrMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{

//    switch(MsgId)
//    {
//        case MSG_SCR_SAVE:
//          if(lParam == 1)
//          {
//            //����ִ�����ñ��棬���ô�����
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

    pModScr = (PMODULESCR)malloc(sizeof(MODULESCR));//�������ṹ
    pData = (PMODULESCRDATA)malloc(sizeof(MODULESCRDATA));//����������ݽṹ
//  ASSERT(pModScr != NULL);
//  ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModScr->m_pBaseData = (PVOID)pData;
    pData->m_pSysData = pServerData->m_pSysData;
    //************************����ģ��ӿڱ��븳ֵ******************************
    pModScr->pModeleInit = ModuleScrInit; //ʵ��ģ���ʼ��
    pModScr->pModeleReset = ModuleScrReset; //ʵ��ģ�鸴λ
    pModScr->pModeleStart = ModuleScrStart; //ʵ��ģ�鿪ʼ
    pModScr->pModeleStop = ModuleScrStop; //ʵ��ģ�����
    pModScr->pModeleRelease = ModuleScrRelease;//ʵ��
    pModScr->pMsgNotify = ScrMsgNotify;//ʵ����Ϣ���д���
    pModScr->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModScr->pModele50msProcess = ModuleScr50msProcess;//��ʵ�֣���ΪNULL
    pModScr->pModele1sProcess = NULL;//ʵ��1s����
    pModScr->pModele1msProcess = NULL;//ʵ��1s����
    strcpy(pModScr->m_ModName, "ModScr");

//     printf("CreateModuleScr!!\n");
    return (PMODULEBASE)pModScr;
}


//��ʾ�����8��
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

void ShowHT1621Temperature(INT16U TempCH, void* pArg) //��ʾ������ϢΪ--
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

void HTBICNSVal(HTB_ICN HTBRam) //��ʾ������
{
    INT8U HT1621Data = (HTBRam.COM1 << 3) + (HTBRam.COM2 << 2) + (HTBRam.COM3 << 1) + (HTBRam.COM4);
    WriteHT1621OneData(HTBRam.P_Addr, HT1621Data, HTBRam.P_WhichIC);
}

void WriteHT1621Temperature(INT16U TempCH, INT16U Data, INT16U WhichIC, void* pArg) //��ʾ�¶�
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
        ThousandsBits = 99; //�ж�ǧλ����Ͳ���ʾ
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
void HideHT1621Temperature(INT16U TempCH, void* pArg) //�����¶���ʾ����
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

void ShowMinus(INT16U TempCH, void* pArg) //��ʾ����
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

void SystemStaStop(void* pArg)//ϵͳ��ֹͣ״̬��,��ʾ����Ϣ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->IC2_S[0].COM4 = 0;
    pData->IC2_S[12].COM4 = 0;

    pData->IC2_S[6].COM4 = 0; //����
    pData->IC2_S[8].COM4 = 0; //����

    HTBICNSVal(pData->IC2_S[8]);//p11
    HTBICNSVal(pData->IC2_S[12]);//ˮ·2��
    HTBICNSVal(pData->IC2_S[6]);//s8
    HTBICNSVal(pData->IC2_S[0]);//ˮ·1��
}

void DisplayTemp(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp )//�¶���ʾ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1, IC1_PIN, pArg); //��ʾ�¶�����1
    WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2, IC1_PIN, pArg); //��ʾ�¶�����2
    WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTemp, IC1_PIN, pArg); //��ʾˮ������
}

void TempShow(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp )//�¶���ʾ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    WriteHT1621Temperature(Temp1_ADDRESS, Temp1, IC1_PIN, pArg); //��ʾ�¶�����1
    WriteHT1621Temperature(Temp2_ADDRESS, Temp2, IC1_PIN, pArg); //��ʾ�¶�����2
    WriteHT1621Temperature(WaterTemp_ADDRESS, WaterTemp, IC1_PIN, pArg); //��ʾˮ������
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


void DisplayCoolerStatus(void* pArg, eStatus Cooler) //ϵͳ�Ĺ���ģʽ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cooler == Status_On) //���俪
    {
        pData->IC2_S[20].COM4 = 1; //ѩ��

    }
    else
    {
        pData->IC2_S[20].COM4 = 0; //ѩ��
    }
    //----------------------------------
}

void DisplayHeaterStatus(void* pArg, eItemStatus Item) //ϵͳ�Ĺ���ģʽ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    //----------------------------------
    switch(Item)
    {
    case Show:
        pData->IC2_S[20].COM2 = 1; //̫��
        break;
    case Hide:
        pData->IC2_S[20].COM2 = 0; //̫��
        break;
    case Invalid:
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            pData->IC2_S[20].COM2 = 1; //̫��
        }
        else
        {
            pData->IC2_S[20].COM2 = 0; //̫��
        }
        break;
    default:
        break;
    }
}

void DisplayCycle1Mode(void* pArg, eStatus Cycle1) //ˮ·��ʾģʽ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cycle1 == Status_On) //ˮ·1������
    {
        pData->IC2_S[0].COM4 = 1;
    }
    else
    {
        pData->IC2_S[0].COM4 = 0;
    }
}

void DisplayCycle2Mode(void* pArg, eStatus Cycle2) //ˮ·��ʾģʽ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(Cycle2 == Status_On) //ˮ·2������
    {
        pData->IC2_S[12].COM4 = 1;
    }
    else
    {
        pData->IC2_S[12].COM4 = 0;
    }
}

void DisplayBump1Mode(void* pArg, eItemStatus Item) //ˮ�õĹ���ģʽ
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

void DisplayBump2Mode(void* pArg, eItemStatus Item) //ˮ�õĹ���ģʽ
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show: //��������
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
    case Hide: //����
        pData->IC2_S[18].COM1 = 0;
        pData->IC2_S[18].COM2 = 0;
        pData->IC2_S[18].COM3 = 0;
        pData->IC2_S[18].COM4 = 0;
        break;
    case Invalid: //ȫ����ʾ
        pData->IC2_S[18].COM1 = 1;
        pData->IC2_S[18].COM2 = 1;
        pData->IC2_S[18].COM3 = 1;
        pData->IC2_S[18].COM4 = 1;
        break;
    case Flash: //ȫ����ʾ����ʧ
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

void DisplayWaterStatusI(void* pArg) //ˮλ״̬
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;

    pData->IC2_S[20].COM3 = 0; //p12
    pData->IC2_S[19].COM4 = 0; //p13
    pData->IC2_S[19].COM3 = 0; //p14
    pData->IC2_S[19].COM2 = 0; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
void DisplayWaterStatusII(void* pArg) //ˮλ״̬
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;

    pData->IC2_S[20].COM3 = 0; //p12
    pData->IC2_S[19].COM4 = 0; //p13
    pData->IC2_S[19].COM3 = 1; //p14
    pData->IC2_S[19].COM2 = 1; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
void DisplayWaterStatusIII(void* pArg) //ˮλ״̬
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    pData->IC2_S[20].COM3 = 1; //p12
    pData->IC2_S[19].COM4 = 1; //p13
    pData->IC2_S[19].COM3 = 1; //p14
    pData->IC2_S[19].COM2 = 1; //p15
    pData->IC2_S[19].COM1 = 1; //p16
}
// 		    ShowHT1621Temperature(Temp1Set_ADDRESS,pArg);//��ʾ������ϢΪ--
//ShowHT1621Temperature(WaterTempSet_ADDRESS,pArg);
//     ShowHT1621Temperature(Temp2Set_ADDRESS,pArg);


void DisplayTemp1Val(void* pArg, eItemStatus Item, INT16U Temp) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp1_ADDRESS, Temp, IC2_PIN, pArg);//��ʾ�¶�1
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
            WriteHT1621Temperature(Temp1_ADDRESS, Temp, IC2_PIN, pArg);//��ʾ�¶�1
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

void DisplayTemp2Val(void* pArg, eItemStatus Item, INT16U Temp) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp2_ADDRESS, Temp, IC2_PIN, pArg); //��ʾ�¶�  2
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
            WriteHT1621Temperature(Temp2_ADDRESS, Temp, IC2_PIN, pArg); //��ʾ�¶�  2
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

void DisplayWaterTempVal(void* pArg, eItemStatus Item, INT16U Temp) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(WaterTemp_ADDRESS, Temp, IC2_PIN, pArg); //��ʾˮ��
        break;
    case Hide:
        HideHT1621Temperature(WaterTemp_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2_ADDRESS, pArg);
        break;
    case Flash:
        if(pData->m_50msCount % 2 == 1) {
            WriteHT1621Temperature(WaterTemp_ADDRESS, Temp, IC2_PIN, pArg); //��ʾˮ��
        }
        else {
            HideHT1621Temperature(WaterTemp_ADDRESS, pArg);
        }
        break;
    default:
        break;
    }
}

void DisplayCal1Set(void* pArg, eItemStatus Item, INT16S Cal1Set) //У׼1����
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

void DisplayCal2Set(void* pArg, eItemStatus Item, INT16S Cal2Set) //У׼2����
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

void DisplayTemp1Set(void* pArg, eItemStatus Item, INT16U Temp1Set) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1Set, IC1_PIN, pArg); //��ʾ�¶�
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
            WriteHT1621Temperature(Temp1Set_ADDRESS, Temp1Set, IC1_PIN, pArg); //��ʾ�¶�
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

void DisplayWaterTempSet(void* pArg,  eItemStatus Item,  INT16U WaterTempSet) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTempSet, IC1_PIN, pArg); //��ʾ�¶�
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
            WriteHT1621Temperature(WaterTempSet_ADDRESS, WaterTempSet, IC1_PIN, pArg); //��ʾ�¶�
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

void DisplayTemp2Set(void* pArg,  eItemStatus Item,  INT16U Temp2Set) //�¶�����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    switch(Item)
    {
    case Show:
        WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2Set, IC1_PIN, pArg); //��ʾ�¶�
        break;
    case Hide:
        HideHT1621Temperature(Temp2Set_ADDRESS, pArg);
        break;
    case Invalid:
        ShowHT1621Temperature(Temp2Set_ADDRESS, pArg); //��ʾ������ϢΪ--
        break;
    case Flash:
        if(pData->m_FlashCount % 2 == 1)
        {
            WriteHT1621Temperature(Temp2Set_ADDRESS, Temp2Set, IC1_PIN, pArg); //��ʾ�¶�
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

void DisplayRefresh(void* pArg)//ˢ������
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    //ˢ������
    HTBICNSVal(pData->IC2_S[21]);
    HTBICNSVal(pData->IC2_S[20]);
    HTBICNSVal(pData->IC2_S[19]);
    HTBICNSVal(pData->IC2_S[18]);
    HTBICNSVal(pData->IC2_S[12]);
    HTBICNSVal(pData->IC2_S[8]);
    HTBICNSVal(pData->IC2_S[6]);
    HTBICNSVal(pData->IC2_S[0]);

}

void HtbRamInit(void* pArg) //��ʾ�������ʼ��
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

    pData->IC1_S[Screen_1_S0].COM4 = 1; //��������S2
    pData->IC1_S[Screen_1_S4].COM4 = 1; //�������õ�С���� T1
    pData->IC1_S[Screen_1_S6].COM4 = 1; //ˮ������ t2/s3
    pData->IC1_S[Screen_1_S10].COM4 = 1; //��������2  t3/s4
    pData->IC1_S[Screen_1_S14].COM4 = 1; //t5 С����
    pData->IC1_S[Screen_1_S12].COM4 = 1; //�¶�t6

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

void WriteHT1621OneData(INT16U Addr, INT16U Data, INT16U WhichIC) //�������͸�����LCD.H
{
    HT1621WrOneData(Addr, Data, WhichIC);
}

void WaterStatusAlm(void* pArg) //ˮλ����
{
    PMODULESCRDATA pData = (PMODULESCRDATA)pArg;
    if(pData->m_50msCount % 2 == 1)
        pData->IC2_S[19].COM1 = 1; //p16
    else
        pData->IC2_S[19].COM1 = 0; //p16

    HTBICNSVal(pData->IC2_S[19]);
}

void WaterTempSetAlm(void* pArg)//ˮλ����
{

}

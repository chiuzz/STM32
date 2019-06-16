//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleCoolerCtrl.c
//*
//* �ļ����� : COOLERCTRL����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
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

    CoolerWorkMachineProc(pArg); //ÿ50ms����
}

void CoolerCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
    PMODULECOOLERCTRLDATA pData = (PMODULECOOLERCTRLDATA)pArg;
    switch(MsgId)
    {
    case MS_COOLER_CMD:
        if(lParam == 0) {
            if(wParam) {
                pData->m_CoolerSMachine = COOLER_ON;//����
                PS("COOLER_ON");
            }
            else {
                pData->m_CoolerSMachine = COOLER_OFF;//ֹͣ
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

    pModCoolerCtrl = (PMODULECOOLERCTRL)malloc(sizeof(MODULECOOLERCTRL));//�������ṹ
    pData = (PMODULECOOLERCTRLDATA)malloc(sizeof(MODULECOOLERCTRLDATA));//����������ݽṹ
    assert(pModCoolerCtrl != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModCoolerCtrl->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModCoolerCtrl->pModeleInit = ModuleCoolerCtrlInit; //ʵ��ģ���ʼ��
    pModCoolerCtrl->pModeleReset = ModuleCoolerCtrlReset; //ʵ��ģ�鸴λ
    pModCoolerCtrl->pModeleStart = ModuleCoolerCtrlStart; //ʵ��ģ�鿪ʼ
    pModCoolerCtrl->pModeleStop = ModuleCoolerCtrlStop; //ʵ��ģ�����
    pModCoolerCtrl->pModeleRelease = ModuleCoolerCtrlRelease;//ʵ��
    pModCoolerCtrl->pMsgNotify = CoolerCtrlMsgNotify;//ʵ����Ϣ���д���
    pModCoolerCtrl->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModCoolerCtrl->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModCoolerCtrl->pModele50msProcess = ModuleCoolerCtrl50msProcess;//��ʵ�֣���ΪNULL
    pModCoolerCtrl->pModele1sProcess = ModuleCoolerCtrl1sProcess;//ʵ��1s����
    pModCoolerCtrl->pModeleUartProcess = NULL;//ʵ��UART����
    strcpy(pModCoolerCtrl->m_ModName, "ModCoolerCtrl");

    //PD("CreateModuleCoolerCtrl!!\n");
    return (PMODULEBASE)pModCoolerCtrl;
}
//#define COOL_PROTECT_TEMP 200

static eCoolerSMachine g_CoolerSMachine;

void CoolerWorkMachineProc(void* pArg) //ÿ1s���� �¶�x100 3555=35.55��
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
        if(pData->m_pSysData->m_WaterHIGH == Status_On) { //ˮ�¹��ߵĴ����߼�
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
            WaterSetTemp = 600; //����ѭ��ʱ��ˮ�¿������6�ȡ�
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


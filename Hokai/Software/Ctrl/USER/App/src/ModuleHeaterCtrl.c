//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleHeaterCtrl.c
//*
//* �ļ����� : HEATERCTRL����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleHeaterCtrl.h"

BOOLEAN ModuleHeaterCtrlInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    INT16U i = 0;
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    if(pData != NULL)
    {
        pData->m_HeaterSMachine = HEATER_STOP;
        for(i = 0; i < HEATERALMNUM; i++) {
            pData->m_HeaterAlmMac[i] = ALM_STOP;
        }
    }
    return ret;
}

BOOLEAN ModuleHeaterCtrlReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    pData->m_Count2 = 0;
    return ret;
}

BOOLEAN ModuleHeaterCtrlStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleHeaterCtrlStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleHeaterCtrlRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleHeaterCtrl1sProcess(void* pArg)
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    INT16U index;
    //printf("ModuleHeaterCtrl1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    for(index = 0; index < HEATERALMNUM; index++)
        HeaterAlmMachineProc(pArg, index);
}

void ModuleHeaterCtrl50msProcess(void* pArg)
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    //printf("ModuleHeaterCtrl1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    pData->m_ProcCount++;
    if(pData->m_ProcCount > 4)
    {
        pData->m_ProcCount = 0;
        HeaterWorkMachineProc(pArg); //ÿ200ms����
    }
}

void HeaterCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    INT16U i=0;
    switch(MsgId)
    {
    case MS_HEATER_CMD:
        if(lParam == 0) {
            if(wParam) {
                pData->m_HeaterSMachine = HEATER_STEP_START;
                for(i = 0; i < HEATERALMNUM; i++) {
                    pData->m_HeaterAlmMac[i] = ALM_START;
                }
//                PS("HEATER_STEP_START");
            }
            else {
                pData->m_HeaterSMachine = HEATER_STOP;
                for(i = 0; i < HEATERALMNUM; i++) {
                    pData->m_HeaterAlmMac[i] = ALM_STOP;
                }
//                PS("HEATER_STOP");
            }
        }
        break;
    case MS_BUMP_CMD:
        switch(lParam)
        {
        default:
            break;
        case 1:
            if(wParam)
            {
//                pData->m_Bump1WorkMac = BUMP_WORK_ON;
//                PS("BUMP1_WORK_ON");
//							if(pData->m_pCfgData->m_SystemSta == Heater)
//                pData->m_HeaterAlmMac[0] = ALM_START;
            }
            else {
//                pData->m_Bump1WorkMac = BUMP_WORK_OFF;
//                PS("BUMP1_WORK_OFF");
//                pData->m_HeaterAlmMac[0] = ALM_STOP;
            }
            break;
        case 2:
            if(wParam)
            {
//                pData->m_Bump2WorkMac = BUMP_WORK_ON;
//                PS("BUMP2_WORK_ON");
//								if(pData->m_pCfgData->m_SystemSta == Heater)
//									pData->m_HeaterAlmMac[1] = ALM_START;
            }
            else {
//                pData->m_HeaterAlmMac[1] = ALM_STOP;
//                pData->m_Bump2WorkMac = BUMP_WORK_OFF;
//                PS("BUMP2_WORK_OFF");
            }
            break;
        }
        break;
    default:
        break;
    }
}

PMODULEBASE CreateModuleHeaterCtrl(PMODULESERVERDATA pServerData)
{
    PMODULEHEATERCTRL pModHeaterCtrl = NULL;
    PMODULEHEATERCTRLDATA pData = NULL;

    pModHeaterCtrl = (PMODULEHEATERCTRL)malloc(sizeof(MODULEHEATERCTRL));//�������ṹ
    pData = (PMODULEHEATERCTRLDATA)malloc(sizeof(MODULEHEATERCTRLDATA));//����������ݽṹ
    assert(pModHeaterCtrl != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pModHeaterCtrl->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModHeaterCtrl->pModeleInit = ModuleHeaterCtrlInit; //ʵ��ģ���ʼ��
    pModHeaterCtrl->pModeleReset = ModuleHeaterCtrlReset; //ʵ��ģ�鸴λ
    pModHeaterCtrl->pModeleStart = ModuleHeaterCtrlStart; //ʵ��ģ�鿪ʼ
    pModHeaterCtrl->pModeleStop = ModuleHeaterCtrlStop; //ʵ��ģ�����
    pModHeaterCtrl->pModeleRelease = ModuleHeaterCtrlRelease;//ʵ��
    pModHeaterCtrl->pMsgNotify = HeaterCtrlMsgNotify;//ʵ����Ϣ���д���
    pModHeaterCtrl->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModHeaterCtrl->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModHeaterCtrl->pModele50msProcess = ModuleHeaterCtrl50msProcess;//��ʵ�֣���ΪNULL
    pModHeaterCtrl->pModele1sProcess = ModuleHeaterCtrl1sProcess;//ʵ��1s����
    pModHeaterCtrl->pModeleUartProcess = NULL;//ʵ��UART����
    strcpy(pModHeaterCtrl->m_ModName, "ModHeaterCtrl");

    //PD("CreateModuleHeaterCtrl!!\n");
    return (PMODULEBASE)pModHeaterCtrl;
}

#define HEATER_P 0.15
#define HEATER_I 0.02
#define VALMAX 3  //�����ʱ��
#define VALMIN (-VALMAX)  //�����ʱ��
#define HEATTEMPDSP 0 //��ˮ���¶Ȳ�ֵ 0.1��
void HeaterWorkMachineProc(void* pArg) //ÿ1s���� �¶�x100 3555=35.55��
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    INT16U WaterTemp =	pData->m_pSysData->m_WaterTemp;
    INT16U WaterSetTemp =	pData->m_pCfgData->m_WaterTempSet_Hot;
    INT16S err, Ival, WorkCount;

    switch(pData->m_HeaterSMachine)
    {
    default:
    case HEATER_STOP:
//			PS("HEATER_STOP");
//        if(pData->m_pSysData->m_WaterTLow == Status_On) {
//            pData->m_HeaterSMachine = HEATER_STEP_WORK_COM_UP;
//        }
        if(WaterTemp > 50 && WaterTemp < 200) {
            pData->m_HeaterSMachine = HEATER_STEP_WORK_COM_UP;
        }
        else {
            SetHeaterWORK(pArg, Status_Off);
            pData->m_ErrSum = 0;
        }
        break;
    case HEATER_STEP_START:
//			PS("HEATER_STEP_START");
        pData->m_Count = 0;
        pData->m_HeaterSMachine = HEATER_STEP_WORK;
        break;
    case HEATER_STEP_WORK:
        if(pData->m_Count >= 5) //5s��ʼ����
        {
            pData->m_HeaterSMachine = HEATER_STEP_WORK_ON;
        }
        pData->m_Count++;
        break;
    case HEATER_STEP_WORK_ON:
//			PS("HEATER_STEP_WORK_ON");
        err = (WaterSetTemp - HEATTEMPDSP) - WaterTemp;
        Ival = (pData->m_ErrSum + err) * HEATER_I;

        if(Ival > VALMIN && Ival < VALMAX)
            pData->m_ErrSum += err;

        WorkCount = err * HEATER_P + Ival;
//				printf("err:%d Ival:%d ErrSum:%d WorkCount:%d \r\n",err,Ival,pData->m_ErrSum, WorkCount);
        if(WorkCount > VALMAX)
            WorkCount = VALMAX;
        if(WorkCount < VALMIN)
            WorkCount = VALMIN;
        if(WorkCount > 0)
        {
            pData->m_HeaterSMachine = HEATER_STEP_WORK_UP;
        }
        else {
            pData->m_HeaterSMachine = HEATER_STEP_WORK_DOWN;
        }
        break;
    case HEATER_STEP_WORK_UP:
//        PS("HEATER_STEP_WORK_UP");
        SetHeaterWORK(pArg, Status_On);
        pData->m_HeaterSMachine = HEATER_STEP_WORK_ON;
        break;
    case HEATER_STEP_WORK_DOWN:
//        PS("HEATER_STEP_WORK_DOW N");
        SetHeaterWORK(pArg, Status_Off);
        pData->m_HeaterSMachine = HEATER_STEP_WORK_ON;
        break;
    case HEATER_STEP_WORK_COM_UP:
        SetHeaterWORK(pArg, Status_On);
        pData->m_HeaterSMachine = HEATER_STOP;
        break;

    }
}

void SetHeaterWORK(void* pArg, eStatus sta)
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
    if(sta == Status_On) {
        SetHeaterWork(sta);
        if(pData->m_Count2 >= 5) {
            pData->m_Count2 = 0;
            pData->m_pSysData->m_Heater = sta;
        }
        pData->m_Count2++;
    }
    else if(sta == Status_Off) {
        pData->m_Count2 = 0;
        pData->m_pSysData->m_Heater = sta;
        SetHeaterWork(sta);
    }
}

void HeaterAlmMachineProc(void* pArg, INT16U index) //ÿ1s���� �¶�x100 3555=35.55��
{
    PMODULEHEATERCTRLDATA pData = (PMODULEHEATERCTRLDATA)pArg;
//		PD(pData->m_HeaterAlmMac[0]);
//	PD(pData->m_HeaterAlmMac[1]);
    switch(pData->m_HeaterAlmMac[index])
    {
    default:
    case ALM_STOP:
        pData->m_pSysData->m_HeaterModeT1ALM = Status_Off;
        pData->m_pSysData->m_HeaterModeT2ALM = Status_Off;
        break;
    case ALM_START:
        if(index == 0) {
            if(pData->m_pSysData->m_Temp1 > (pData->m_pSysData->m_Temp1Set - 100) && pData->m_pSysData->m_Temp1 < (pData->m_pSysData->m_Temp1Set + 100))
                pData->m_HeaterAlmMac[index] = ALM_MONITOR;
//						PS("1 ALM_MONITOR");
        }
        else {
            if(pData->m_pSysData->m_Temp2 > (pData->m_pSysData->m_Temp2Set - 100) && pData->m_pSysData->m_Temp2 < (pData->m_pSysData->m_Temp2Set + 100))
                pData->m_HeaterAlmMac[index] = ALM_MONITOR;
//						PS("2 ALM_MONITOR");
        }
        break;
    case ALM_MONITOR:
        if(index == 0) {
            if(pData->m_pSysData->m_Temp1 < (pData->m_pSysData->m_Temp1Set - 100)
                    || pData->m_pSysData->m_Temp1 > (pData->m_pSysData->m_Temp1Set + 100))
            {
                pData->m_pSysData->m_HeaterModeT1ALM = Status_On;
            }
            else {
                pData->m_pSysData->m_HeaterModeT1ALM = Status_Off;
            }
//						PD(pData->m_pSysData->m_HeaterModeT1ALM);
        }
        else {
            if(pData->m_pSysData->m_Temp2 < (pData->m_pSysData->m_Temp2Set - 100)
                    || pData->m_pSysData->m_Temp2 > (pData->m_pSysData->m_Temp2Set + 100))
            {
                pData->m_pSysData->m_HeaterModeT2ALM = Status_On;
            }
            else {
                pData->m_pSysData->m_HeaterModeT2ALM = Status_Off;
            }
//						PD(pData->m_pSysData->m_HeaterModeT2ALM);
        }
        break;
    }
}
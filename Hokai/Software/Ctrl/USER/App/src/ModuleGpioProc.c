//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleGpioProc.c
//*
//* �ļ����� : GPIOPROC����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
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
    if(pData->m_Count50ms % 2) //ι���Ź�
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
    printf("--------------------ϵͳ������Ϣ-------------------------\r\n");
    printf("����ģʽ��");
    switch( pData->m_pCfgData->m_SystemSta)//ϵͳ����״̬
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
    printf("ˮ·I�趨��");
    if(pData->m_pCfgData->m_Cycle1Set)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ·II�趨��");
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
    printf("--------------------ϵͳ״̬��Ϣ-------------------------\r\n");
    printf("��̺״̬��");
    if(pData->m_pCalData->m_SingleMode)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ·ˮ������1״̬��");
    if(pData->m_pSysData->m_Float1Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ·ˮ������2״̬��");
    if(pData->m_pSysData->m_Float2Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮλ��");
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
    printf("ˮ��1״̬��");
    if(pData->m_pSysData->m_Bump1Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ��2״̬��");
    if(pData->m_pSysData->m_Bump2Status)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("����״̬��");
    if(pData->m_pSysData->m_Cooler)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("����״̬��");
    if(pData->m_pSysData->m_Heater)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("����״̬ ��");
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
    printf("--------------------����״̬��Ϣ-------------------------\r\n");
    printf("������1���� ��");
    if(pData->m_pSysData->m_Sensor1OFF)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("������2���� ��");
    if(pData->m_pSysData->m_Sensor2OFF)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("�����������쳣��");
    if(pData->m_pSysData->m_HeaterPOWER)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ�³��¸��쳣��");
    if(pData->m_pSysData->m_WaterHIGH)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮ�³��µ��쳣��");
    if(pData->m_pSysData->m_WaterTLow)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("E2PROM�쳣��");
    if(pData->m_pSysData->m_E2PROMERR)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("ˮλ���쳣��");
    if(pData->m_pSysData->m_WaterLow)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("���ȣ�ˮ��1�������� �쳣��");
    if(pData->m_pSysData->m_HeaterModeWT1Low)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("���ȣ�ˮ��2�������� �쳣��");
    if(pData->m_pSysData->m_HeaterModeWT2Low)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");

    printf("���ȣ�����1���� �쳣��");
    if(pData->m_pSysData->m_HeaterModeT1ALM)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");

    printf("���ȣ�����2���� �쳣��");
    if(pData->m_pSysData->m_HeaterModeT2ALM)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("Һ·1ѭ���쳣��");
    if(pData->m_pSysData->m_Cycle1Alm)
    {
        printf("On");
    }
    else {
        printf("Off");
    }
    printf("\r\n");
    printf("Һ·2ѭ���쳣��");
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
    printf("--------------------ϵͳ������Ϣ-------------------------\r\n");
    printf("���������趨 1��%d, 2: %d��ˮ���趨��%d\r\n", pData->m_pCfgData->m_Temp1Set_Hot, pData->m_pCfgData->m_Temp2Set_Hot, pData->m_pCfgData->m_WaterTempSet_Hot);
    printf("���������趨 1��%d, 2: %d, ˮ���趨: %d\r\n", pData->m_pCfgData->m_Temp1Set_Cool, pData->m_pCfgData->m_Temp2Set_Cool, pData->m_pCfgData->m_WaterTempSet_Cool);
    printf("��ǰ�����趨 1��%d, 2: %d, ˮ���趨: %d\r\n", pData->m_pSysData->m_Temp1Set, pData->m_pSysData->m_Temp2Set, pData->m_pSysData->m_WaterTempSet);
    printf("��ǰ���� 1��%d, 2: %d, ˮ��: %d\r\n", pData->m_pSysData->m_Temp1, pData->m_pSysData->m_Temp2, pData->m_pSysData->m_WaterTemp);
#endif
}


void GpioProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
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

    pModGpioProc = (PMODULEGPIOPROC)malloc(sizeof(MODULEGPIOPROC));//�������ṹ
    pData = (PMODULEGPIOPROCDATA)malloc(sizeof(MODULEGPIOPROCDATA));//����������ݽṹ
    assert(pModGpioProc != NULL);
    assert(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModGpioProc->m_pBaseData = (PVOID)pData;
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    //************************����ģ��ӿڱ��븳ֵ******************************
    pModGpioProc->pModeleInit = ModuleGpioProcInit; //ʵ��ģ���ʼ��
    pModGpioProc->pModeleReset = ModuleGpioProcReset; //ʵ��ģ�鸴λ
    pModGpioProc->pModeleStart = ModuleGpioProcStart; //ʵ��ģ�鿪ʼ
    pModGpioProc->pModeleStop = ModuleGpioProcStop; //ʵ��ģ�����
    pModGpioProc->pModeleRelease = ModuleGpioProcRelease;//ʵ��
    pModGpioProc->pMsgNotify = GpioProcMsgNotify;//ʵ����Ϣ���д���
    pModGpioProc->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModGpioProc->pModele10msProcess = ModuleGpioProc10msProcess;//��ʵ�֣���ΪNULL
    pModGpioProc->pModele50msProcess = ModuleGpioProc50msProcess;//��ʵ�֣���ΪNULL
    pModGpioProc->pModele1sProcess = ModuleGpioProc1sProcess;//ʵ��1s����
    pModGpioProc->pModeleUartProcess = NULL;//ʵ��UART����
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
            SetBump1Work(FALSE);     //ֹͣģʽ��,ˮ�ò�����
        }
        else {
            SetBump2Work(FALSE);
        }
        pData->m_pSysData->m_Bump1Status = Status_Off;
        break;
    case BUMP_WORK_ON:
        switch(pData->m_pCfgData->m_SystemSta)//����ģʽ��
        {
        case Cooler://Stop = 1,	Cooler=2,	Heater=3,
            //����ģʽ��,������������ֵ��ʵ�ʵ�����ֵ���бȽ�
            if(pData->m_pSysData->m_Temp1 > pData->m_pCfgData->m_Temp1Set_Cool )
            {
                pData->m_Bump1WorkMac = BUMP_WORK_START;//��ʵ�����´�������ֵ��ʱ��,ˮ�ÿ�ʼ����
                // PD("����ģʽ��,ˮ�ù���");
            }
            else
            {
                pData->m_Bump1WorkMac = BUMP_WORK_STOP;
                // PD("����ģʽ��,ˮ��ֹͣ");
            }
            break;
        case Heater:
            //������ģʽ��,������������ֵ��ʵ�����½��бȽ�
            if(pData->m_pSysData->m_Temp1 < pData->m_pCfgData->m_Temp1Set_Hot && pData->m_pSysData->m_HeaterModeWT1Low == Status_Off)
            {
                //�������¶�С�����µ�ʱ��,ˮ�ÿ�ʼ����;
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
            SetBump1Work(FALSE);     //ֹͣģʽ��,ˮ�ò�����
        }
        else {
            SetBump2Work(FALSE);
        }
        pData->m_pSysData->m_Bump1Status = Status_Off;
        break;
    case BUMP_WORK_START:
        pData->m_Bump1WorkMac = BUMP_WORK_ON;
        if(pData->m_pCalData->m_SingleMode == Status_Off) {
            SetBump1Work(TRUE);     //ֹͣģʽ��,ˮ�ò�����
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
        SetBump2Work(FALSE);     //ֹͣģʽ��,ˮ�ò�����
        pData->m_pSysData->m_Bump2Status = Status_Off;
        break;
    case BUMP_WORK_ON:
        switch(pData->m_pCfgData->m_SystemSta)//����ģʽ��
        {
        case Cooler://Stop = 1,	Cooler=2,	Heater=3,
            //����ģʽ��,������������ֵ��ʵ�ʵ�����ֵ���бȽ�
            if(pData->m_pSysData->m_Temp2 > pData->m_pCfgData->m_Temp2Set_Cool )
            {
                pData->m_Bump2WorkMac = BUMP_WORK_START;//��ʵ�����´�������ֵ��ʱ��,ˮ�ÿ�ʼ����
                // PD("����ģʽ��,ˮ�ù���");
            }
            else
            {
                pData->m_Bump2WorkMac = BUMP_WORK_STOP;
                // PD("����ģʽ��,ˮ��ֹͣ");
            }
            break;
        case Heater:
            //������ģʽ��,������������ֵ��ʵ�����½��бȽ�
            if(pData->m_pSysData->m_Temp2 < pData->m_pCfgData->m_Temp2Set_Hot && pData->m_pSysData->m_HeaterModeWT2Low == Status_Off)
            {
                //�������¶�С�����µ�ʱ��,ˮ�ÿ�ʼ����;
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
        SetBump2Work(FALSE);     //ֹͣģʽ��,ˮ�ò�����
        pData->m_pSysData->m_Bump2Status = Status_Off;
        break;
    case BUMP_WORK_START:
        pData->m_Bump2WorkMac = BUMP_WORK_ON;
        SetBump2Work(TRUE);     //ֹͣģʽ��,ˮ�ò�����
        pData->m_pSysData->m_Bump2Status = Status_On;
        break;
    }
}

//if(pData->m_pSysData->m_Cycle1Set==Status_Off || pData->m_pSysData->m_WaterTemp > 4200) //ˮ·1û�п���,��ˮ�ò���ת


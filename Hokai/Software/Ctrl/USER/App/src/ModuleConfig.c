//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleConfig.c
//*
//* �ļ����� : CONFIG����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleConfig.h"
#include "gpio.h"

BOOLEAN ModuleConfigInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    if(pData != NULL)
    {
//			 EEROM_Init(pArg);
        pData->m_ConfigMac = CONFIG_STOP;
        pData->m_pSysData->m_E2PROMERR = Status_Off;
        pData->m_ConfigEffective = FALSE;
        pData->m_ConfigSaveable = FALSE;
    }
    return ret;
}

BOOLEAN ModuleConfigReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleConfigStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleConfigStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleConfigRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleConfig1sProcess(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    if(pData->m_PressSta == FALSE)
        return;
    ConfigMachineProc(pArg);
}



void ConfigMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    switch(MsgId)
    {
    case MS_CONFIG_CMD: //see msg_def.h
        switch(lParam)
        {
        default:
            break;
        case CONFIGINIT:
            if(wParam == CMD_START) {
                pData->m_ConfigMac = CONFIG_INIT;
            }
            break;
        case CONFIGDATASAVE:
//            if(pData->m_ConfigSaveable == TRUE )
            pData->m_ConfigMac = CONFIG_SAVE_START;
//            PS("�յ�������Ϣ");
            break;
        case CALCDATASAVE:
            pData->m_ConfigMac = CALC_SAVE_START;
            break;
        case ADJDATASAVE:
            pData->m_ConfigMac = ADJ_SAVE_START;
            break;
        }
        break;
    default:
        break;
    }
    // printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleConfig(PMODULESERVERDATA pServerData)
{
    PMODULECONFIG pModConfig = NULL;
    PMODULECONFIGDATA pData = NULL;

    pModConfig = (PMODULECONFIG)malloc(sizeof(MODULECONFIG));//�������ṹ
    pData = (PMODULECONFIGDATA)malloc(sizeof(MODULECONFIGDATA));//����������ݽṹ
    assert(pModConfig != NULL);
    assert(pData != NULL);
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModConfig->m_pBaseData = (PVOID)pData;

//typedef struct ModuleServerData //�����������ݽṹ
//{
//    PSYSPARAMDATA m_pSysData; //ϵͳ����
//    PSYSCONFIGDATA m_pCfgData; //ϵͳ����
//    PSYSCALCDATA m_pCalData; //ϵͳ����
//    PSYSADJDATA	m_pAdjData;
//    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
//    DLLIST* m_pSubMouleList; //��ģ������
//    BOOLEAN m_PressSta; //�������״̬��¼
//} MODULESERVERDATA,*PMODULESERVERDATA;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModConfig->pModeleInit = ModuleConfigInit; //ʵ��ģ���ʼ��
    pModConfig->pModeleReset = ModuleConfigReset; //ʵ��ģ�鸴λ
    pModConfig->pModeleStart = ModuleConfigStart; //ʵ��ģ�鿪ʼ
    pModConfig->pModeleStop = ModuleConfigStop; //ʵ��ģ�����
    pModConfig->pModeleRelease = ModuleConfigRelease;//ʵ��
    pModConfig->pMsgNotify = ConfigMsgNotify;//ʵ����Ϣ���д���
    pModConfig->pModele1msProcess = NULL;//��ʵ�֣���ΪNULL
    pModConfig->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModConfig->pModele50msProcess = NULL;//��ʵ�֣���ΪNULL
    pModConfig->pModele1sProcess = ModuleConfig1sProcess;//ʵ��1s����
    pModConfig->pModeleUartProcess = NULL;//��ʵ�֣���ΪNULL
    strcpy(pModConfig->m_ModName, "ModConfig");

    //PD("CreateModuleConfig!!\n");
    return (PMODULEBASE)pModConfig;
}

void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len)
{
    INT16U i = 0;
    INT8U *pSaveData = (INT8U *)pObj;
    for(i = 0; i < len; i++)
    {
        /* PD(pSaveData[i]); */
        AT24CXX_WriteOneByte(Addres + i, pSaveData[i]);
    }
}

void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len)
{
    INT16U i = 0;
    INT8U *pSaveData = (INT8U *)pObj;
    for(i = 0; i < len; i++)
    {
        pSaveData[i] = AT24CXX_ReadOneByte(Addres + i);
    }
}


void ConfigMachineProc(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    switch(pData->m_ConfigMac)
    {
    default:
    case CONFIG_STOP:
        break;
    case ADJ_SAVE_START:
        //PS("����У׼����2");
        WriteMemAdj(pData);
        pData->m_ConfigMac = CONFIG_STOP;
        break;
    case CALC_SAVE_START:
        //PS("����У׼����");
        WriteMemCalc(pData);
        pData->m_ConfigMac = CONFIG_STOP;
        break;
    case CONFIG_SAVE_START:
        pData->m_Count = 0;
        pData->m_ConfigMac = CONFIG_CFG_SAVE;
        break;
    case CONFIG_CFG_SAVE:
        if( pData->m_Count >= 3 )
        {
            //PS("������������");
            WriteMemConfig(pData);
            pData->m_ConfigMac = CONFIG_STOP;
        }
        pData->m_Count++;
        break;
    case CONFIG_INIT:
        if(TestE2PROM(212) == FALSE)
        {
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, E2PROMERR, CMD_STOP, NULL); //��msg_def.h
        }
        else
        {
            pData->m_ConfigSaveable = TRUE;
        }
        ReadMemCalc(pData); //��ʼ����ʱ��,ȥ��eeprom������
        if(ChackCalcData(pData) == FALSE) {
            CalceDataInit(pData);
        }
        ReadMemConfig(pData); //��ʼ����ʱ��,ȥ��eeprom������
        if(ChackConfigData(pData) == FALSE) {
            ConfigDataInit(pData);
        }
        ReadMemAdj(pData); //��ʼ����ʱ��,ȥ��eeprom������
        if(ChackAdjData(pData) == FALSE) {
            AdjDataInit(pData);
        }
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGINIT, CMD_STOP, NULL); //��msg_def.h
        pData->m_ConfigMac = CONFIG_STOP;
        break;
    }
}

BOOLEAN ChackAdjData(PMODULECONFIGDATA pData)
{
    BOOLEAN ret = TRUE;
    if(pData->m_pAdjData->m_Cal1Set < TEMPCALMIN || pData->m_pAdjData->m_Cal1Set > TEMPCALMAX)
        ret = FALSE;
    if(pData->m_pAdjData->m_Cal2Set < TEMPCALMIN || pData->m_pAdjData->m_Cal2Set > TEMPCALMAX)
        ret = FALSE;
    return ret;
}

BOOLEAN ChackCalcData(PMODULECONFIGDATA pData)
{
    BOOLEAN ret = TRUE;
    if(pData->m_pCalData->m_CH1ADArr[0]>2000)
        ret = FALSE;
    return ret;
}

BOOLEAN ChackConfigData(PMODULECONFIGDATA pData)
{
    BOOLEAN ret = TRUE;
    if(pData->m_pCfgData->m_Temp1Set_Hot<3500 || pData->m_pCfgData->m_Temp1Set_Hot>4000)
        ret = FALSE;
    if(pData->m_pCfgData->m_AlmVolum != ALM_LEVEL_LOW
            && pData->m_pCfgData->m_AlmVolum != ALM_LEVEL_MID
            && pData->m_pCfgData->m_AlmVolum != ALM_LEVEL_HIG)
        ret = FALSE;
    return ret;
}

void AdjDataInit(PMODULECONFIGDATA pData)
{
    //PS("��������Ĭ��ֵ");
    pData->m_pAdjData->m_Cal1Set = 0;
    pData->m_pAdjData->m_Cal2Set = 0;
}

void CalceDataInit(PMODULECONFIGDATA pData)
{
    //PS("��������Ĭ��ֵ");
    pData->m_pCalData->m_CH1ADArr[0] = 186;
    pData->m_pCalData->m_CH1ADArr[1] = 3910;
    pData->m_pCalData->m_CH1TEMPArr[0] = 2800;
    pData->m_pCalData->m_CH1TEMPArr[1] = 4300;
    pData->m_pCalData->m_CH2ADArr[0] = 186;
    pData->m_pCalData->m_CH2ADArr[1] = 3910;
    pData->m_pCalData->m_CH2TEMPArr[0] = 2800;
    pData->m_pCalData->m_CH2TEMPArr[1] = 4300;
    pData->m_pCalData->m_CH3ADArr[0] = 186;
    pData->m_pCalData->m_CH3ADArr[1] = 3910;
    pData->m_pCalData->m_CH3TEMPArr[0] = 200;
    pData->m_pCalData->m_CH3TEMPArr[1] = 4300;
    pData->m_pCalData->m_SingleMode = Status_Off;
}

BOOLEAN TestE2PROM(INT16U D)
{
    BOOLEAN ret = TRUE;
    INT16U  len, Address, i;
    INT16U Data[10];
    len = DATASIZE;
    //printf("=================================\r\n");
    for(i = 0; i < 10; i++)
    {
        Data[i] = D;
    }
    len = sizeof(INT16U) * 10;
    I2CMemSave(ADDRESS_END + 1, Data, len);
    for(i = 0; i < 10; i++)
    {
        Data[i] = 0;
    }
    I2CMemLoad(ADDRESS_END + 1, Data, len);
    for(i = 0; i < 10; i++)
    {
        if(Data[i] != D)
        {
            //printf("E2PROM ����ʧ��\r\n");
            ret = FALSE;
            break;
        }
    }
    //printf("=================================\r\n");
    return ret;
}

void  WriteMemConfig(PMODULECONFIGDATA pData) //д������
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    INT16U Test = 0;
    len = DATASIZE;

    Address = ADDRESS_SYSWORKMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_SystemSta));
//
    I2CMemSave(Address, pDataSave, len);
    I2CMemLoad(Address, (PVOID)(&Test), len);
    if(pData->m_pCfgData->m_SystemSta != Test)
    {
        PD(pData->m_pCfgData->m_SystemSta);
        PD(Test);
        //printf("============E2PROM��д����============");
    }

    Address = ADDRESS_CYCLE1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Cycle1Set));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_CYCLE2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Cycle2Set));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_HOT_TEMP1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp1Set_Hot));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_HOT_TEMP2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp2Set_Hot));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_HOT_TEMPWATERSET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_WaterTempSet_Hot));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_COOL_TEMP1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp1Set_Cool));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_COOL_TEMP2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp2Set_Cool));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_COOL_TEMPWATERSET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_WaterTempSet_Cool));
    I2CMemSave(Address, pDataSave, len);

    Address = ADDRESS_ALMVOL_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_AlmVolum));
    I2CMemSave(Address, pDataSave, len);

//    INT16U  Address;
//    PVOID  pDataSave;
//    INT16U  len;
//    INT16U  i;
//    len = sizeof(SYSCONFIGDATA);
//		Address = ADDRESS_END;
//    pDataSave = (PVOID)(pData->m_pCfgData);
//    I2CMemSave(Address, pDataSave, len);
}

void  WriteMemCalc(PMODULECONFIGDATA pData) //д������
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    len = DATASIZE;
    Address = ADDRESS_SINGLEMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_SingleMode));
    I2CMemSave(Address, pDataSave, len);

    //ͨ��һ��adֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1ADArr));
    I2CMemSave(Address, pDataSave, len);

    //ͨ��1���¶�ֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1TEMPArr));
    I2CMemSave(Address, pDataSave, len);
    //ͨ��2��adֵ
    Address = ADDRESS_CH2ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2ADArr));
    I2CMemSave(Address, pDataSave, len);

    //ͨ��2���¶�ֵ
    Address = ADDRESS_CH2TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2TEMPArr));
    I2CMemSave(Address, pDataSave, len);
    //ͨ��3��adֵ
    Address = ADDRESS_CH3ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3ADArr));
    I2CMemSave(Address, pDataSave, len);
    //ͨ��3���¶�ֵ
    Address = ADDRESS_CH3TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3TEMPArr));
    I2CMemSave(Address, pDataSave, len);
}

void  WriteMemAdj(PMODULECONFIGDATA pData) //д������
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    INT8S		data;

    //����1��У׼ֵ
    len = DATASIZE;
    Address = ADDRESS_CAL1SET_START;
    data = pData->m_pAdjData->m_Cal1Set + 10;
    pDataSave = (PVOID)(&data);
    I2CMemSave(Address, pDataSave, len);

    //����2��У׼ֵ
    Address = ADDRESS_CAL2SET_START;
    data = pData->m_pAdjData->m_Cal2Set + 10;
    pDataSave = (PVOID)(&data);
    I2CMemSave(Address, pDataSave, len);
}
void  ReadMemConfig(PMODULECONFIGDATA pData)  //��ȡ����
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    len = DATASIZE;

    Address = ADDRESS_HOT_TEMP1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp1Set_Hot));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_HOT_TEMP2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp2Set_Hot));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_HOT_TEMPWATERSET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_WaterTempSet_Hot));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_COOL_TEMP1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp1Set_Cool));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_COOL_TEMP2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Temp2Set_Cool));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_COOL_TEMPWATERSET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_WaterTempSet_Cool));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_ALMVOL_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_AlmVolum));
    I2CMemLoad(Address, pDataSave, DATASIZE);

    Address = ADDRESS_SYSWORKMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_SystemSta));
    I2CMemLoad(Address, pDataSave, len);
    PD(pData->m_pCfgData->m_SystemSta);

    Address = ADDRESS_CYCLE1SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Cycle1Set));
    I2CMemLoad(Address, pDataSave, len);

    Address = ADDRESS_CYCLE2SET_START;
    pDataSave = (PVOID)(&(pData->m_pCfgData->m_Cycle2Set));
    I2CMemLoad(Address, pDataSave, len);
}

void  ReadMemCalc(PMODULECONFIGDATA pData)  //��ȡ����
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    len = DATASIZE;
    //����̺˫̺��ֵ
    Address = ADDRESS_SINGLEMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_SingleMode));
    I2CMemLoad(Address, pDataSave, len);

    //ͨ��һ��adֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--\r\n",pData->m_pCalData->m_CH1ADArr[0]);
    //printf("---%d--\r\n",pData->m_pCalData->m_CH1ADArr[1]);
    //ͨ��1���¶�ֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1TEMPArr));
    I2CMemLoad(Address, pDataSave, len);
    //printf("ͨ��1���¶�ֵ%d--\r\n",pData->m_pCalData->m_CH1TEMPArr[0]);
    //printf("ͨ��1���¶�ֵ%d--\r\n",pData->m_pCalData->m_CH1TEMPArr[1]);
    //ͨ��2��adֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH2ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--",pData->m_pSysData->m_CH1ADArr[0]);
    //ͨ��2���¶�ֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH2TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2TEMPArr));
    I2CMemLoad(Address, pDataSave, len);

    //ͨ��3��adֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH3ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--",pData->m_pSysData->m_CH1ADArr[0]);
    //ͨ��3���¶�ֵ
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH3TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3TEMPArr));
    I2CMemLoad(Address, pDataSave, len);
}

void  ReadMemAdj(PMODULECONFIGDATA pData)  //��ȡ����
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    INT8S		data;

    //����1��У׼ֵ
    len = DATASIZE;
    Address = ADDRESS_CAL1SET_START;
    pDataSave = (PVOID)(&data);
    I2CMemLoad(Address, pDataSave, len);
    pData->m_pAdjData->m_Cal1Set = (INT8S)data - 10;

    //����2��У׼ֵ
    Address = ADDRESS_CAL2SET_START;
    pDataSave = (PVOID)(&data);
    I2CMemLoad(Address, pDataSave, len);
    pData->m_pAdjData->m_Cal2Set = (INT8S)data - 10;
}

void ConfigDataInit(PMODULECONFIGDATA pData)
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    //PS("����Ĭ��״̬");
    pData->m_pCfgData->m_Temp1Set_Hot = 3700;
    pData->m_pCfgData->m_Temp2Set_Hot = 3700;
    pData->m_pCfgData->m_WaterTempSet_Hot = 4000;
    pData->m_pCfgData->m_Temp1Set_Cool = 4000;
    pData->m_pCfgData->m_Temp2Set_Cool = 4000;
    pData->m_pCfgData->m_WaterTempSet_Cool = 2000;
    pData->m_pCfgData->m_SystemSta = Stop; //������ʱ��,ϵͳ״̬�ǹ�Stop
    pData->m_pCfgData->m_Cycle1Set = Status_Off;
    pData->m_pCfgData->m_Cycle2Set = Status_Off;
    pData->m_pCfgData->m_AlmVolum = ALM_LEVEL_MID;
}
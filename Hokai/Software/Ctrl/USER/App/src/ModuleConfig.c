//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleConfig.c
//*
//* 文件描述 : CONFIG任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
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



void ConfigMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
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
//            PS("收到保存信息");
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

    pModConfig = (PMODULECONFIG)malloc(sizeof(MODULECONFIG));//申请基类结构
    pData = (PMODULECONFIGDATA)malloc(sizeof(MODULECONFIGDATA));//申请基类数据结构
    assert(pModConfig != NULL);
    assert(pData != NULL);
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pCfgData = pServerData->m_pCfgData;
    pData->m_pCalData = pServerData->m_pCalData;
    pData->m_pAdjData = pServerData->m_pAdjData;
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModConfig->m_pBaseData = (PVOID)pData;

//typedef struct ModuleServerData //主服务器数据结构
//{
//    PSYSPARAMDATA m_pSysData; //系统数据
//    PSYSCONFIGDATA m_pCfgData; //系统数据
//    PSYSCALCDATA m_pCalData; //系统数据
//    PSYSADJDATA	m_pAdjData;
//    P_MSGQUEUE m_pMsgQueue;  //消息队列
//    DLLIST* m_pSubMouleList; //子模块链表
//    BOOLEAN m_PressSta; //处理调用状态记录
//} MODULESERVERDATA,*PMODULESERVERDATA;

    //************************以下模块接口必须赋值******************************
    pModConfig->pModeleInit = ModuleConfigInit; //实现模块初始化
    pModConfig->pModeleReset = ModuleConfigReset; //实现模块复位
    pModConfig->pModeleStart = ModuleConfigStart; //实现模块开始
    pModConfig->pModeleStop = ModuleConfigStop; //实现模块结束
    pModConfig->pModeleRelease = ModuleConfigRelease;//实现
    pModConfig->pMsgNotify = ConfigMsgNotify;//实现消息队列处理
    pModConfig->pModele1msProcess = NULL;//不实现，置为NULL
    pModConfig->pModele10msProcess = NULL;//不实现，置为NULL
    pModConfig->pModele50msProcess = NULL;//不实现，置为NULL
    pModConfig->pModele1sProcess = ModuleConfig1sProcess;//实现1s调用
    pModConfig->pModeleUartProcess = NULL;//不实现，置为NULL
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
        //PS("保存校准数据2");
        WriteMemAdj(pData);
        pData->m_ConfigMac = CONFIG_STOP;
        break;
    case CALC_SAVE_START:
        //PS("保存校准数据");
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
            //PS("保存配置数据");
            WriteMemConfig(pData);
            pData->m_ConfigMac = CONFIG_STOP;
        }
        pData->m_Count++;
        break;
    case CONFIG_INIT:
        if(TestE2PROM(212) == FALSE)
        {
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, E2PROMERR, CMD_STOP, NULL); //见msg_def.h
        }
        else
        {
            pData->m_ConfigSaveable = TRUE;
        }
        ReadMemCalc(pData); //初始化的时候,去读eeprom的数据
        if(ChackCalcData(pData) == FALSE) {
            CalceDataInit(pData);
        }
        ReadMemConfig(pData); //初始化的时候,去读eeprom的数据
        if(ChackConfigData(pData) == FALSE) {
            ConfigDataInit(pData);
        }
        ReadMemAdj(pData); //初始化的时候,去读eeprom的数据
        if(ChackAdjData(pData) == FALSE) {
            AdjDataInit(pData);
        }
        pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_CONFIG_CMD, CONFIGINIT, CMD_STOP, NULL); //见msg_def.h
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
    //PS("采用配置默认值");
    pData->m_pAdjData->m_Cal1Set = 0;
    pData->m_pAdjData->m_Cal2Set = 0;
}

void CalceDataInit(PMODULECONFIGDATA pData)
{
    //PS("采用配置默认值");
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
            //printf("E2PROM 测试失败\r\n");
            ret = FALSE;
            break;
        }
    }
    //printf("=================================\r\n");
    return ret;
}

void  WriteMemConfig(PMODULECONFIGDATA pData) //写入数据
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
        //printf("============E2PROM读写出错============");
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

void  WriteMemCalc(PMODULECONFIGDATA pData) //写入数据
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    len = DATASIZE;
    Address = ADDRESS_SINGLEMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_SingleMode));
    I2CMemSave(Address, pDataSave, len);

    //通道一的ad值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1ADArr));
    I2CMemSave(Address, pDataSave, len);

    //通道1的温度值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1TEMPArr));
    I2CMemSave(Address, pDataSave, len);
    //通道2的ad值
    Address = ADDRESS_CH2ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2ADArr));
    I2CMemSave(Address, pDataSave, len);

    //通道2的温度值
    Address = ADDRESS_CH2TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2TEMPArr));
    I2CMemSave(Address, pDataSave, len);
    //通道3的ad值
    Address = ADDRESS_CH3ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3ADArr));
    I2CMemSave(Address, pDataSave, len);
    //通道3的温度值
    Address = ADDRESS_CH3TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3TEMPArr));
    I2CMemSave(Address, pDataSave, len);
}

void  WriteMemAdj(PMODULECONFIGDATA pData) //写入数据
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    INT8S		data;

    //体温1的校准值
    len = DATASIZE;
    Address = ADDRESS_CAL1SET_START;
    data = pData->m_pAdjData->m_Cal1Set + 10;
    pDataSave = (PVOID)(&data);
    I2CMemSave(Address, pDataSave, len);

    //体温2的校准值
    Address = ADDRESS_CAL2SET_START;
    data = pData->m_pAdjData->m_Cal2Set + 10;
    pDataSave = (PVOID)(&data);
    I2CMemSave(Address, pDataSave, len);
}
void  ReadMemConfig(PMODULECONFIGDATA pData)  //读取数据
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

void  ReadMemCalc(PMODULECONFIGDATA pData)  //读取数据
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    len = DATASIZE;
    //读单毯双毯的值
    Address = ADDRESS_SINGLEMODE_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_SingleMode));
    I2CMemLoad(Address, pDataSave, len);

    //通道一的ad值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--\r\n",pData->m_pCalData->m_CH1ADArr[0]);
    //printf("---%d--\r\n",pData->m_pCalData->m_CH1ADArr[1]);
    //通道1的温度值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH1TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH1TEMPArr));
    I2CMemLoad(Address, pDataSave, len);
    //printf("通道1的温度值%d--\r\n",pData->m_pCalData->m_CH1TEMPArr[0]);
    //printf("通道1的温度值%d--\r\n",pData->m_pCalData->m_CH1TEMPArr[1]);
    //通道2的ad值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH2ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--",pData->m_pSysData->m_CH1ADArr[0]);
    //通道2的温度值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH2TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH2TEMPArr));
    I2CMemLoad(Address, pDataSave, len);

    //通道3的ad值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH3ADARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3ADArr));
    I2CMemLoad(Address, pDataSave, len);

    //printf("---%d--",pData->m_pSysData->m_CH1ADArr[0]);
    //通道3的温度值
    len = ADCALCDATANUM * DATASIZE;
    Address = ADDRESS_CH3TEMPARR_START;
    pDataSave = (PVOID)(&(pData->m_pCalData->m_CH3TEMPArr));
    I2CMemLoad(Address, pDataSave, len);
}

void  ReadMemAdj(PMODULECONFIGDATA pData)  //读取数据
{
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    INT16U  i;
    INT8S		data;

    //体温1的校准值
    len = DATASIZE;
    Address = ADDRESS_CAL1SET_START;
    pDataSave = (PVOID)(&data);
    I2CMemLoad(Address, pDataSave, len);
    pData->m_pAdjData->m_Cal1Set = (INT8S)data - 10;

    //体温2的校准值
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
    //PS("采用默认状态");
    pData->m_pCfgData->m_Temp1Set_Hot = 3700;
    pData->m_pCfgData->m_Temp2Set_Hot = 3700;
    pData->m_pCfgData->m_WaterTempSet_Hot = 4000;
    pData->m_pCfgData->m_Temp1Set_Cool = 4000;
    pData->m_pCfgData->m_Temp2Set_Cool = 4000;
    pData->m_pCfgData->m_WaterTempSet_Cool = 2000;
    pData->m_pCfgData->m_SystemSta = Stop; //启动的时候,系统状态是关Stop
    pData->m_pCfgData->m_Cycle1Set = Status_Off;
    pData->m_pCfgData->m_Cycle2Set = Status_Off;
    pData->m_pCfgData->m_AlmVolum = ALM_LEVEL_MID;
}
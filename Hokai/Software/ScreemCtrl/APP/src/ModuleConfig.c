//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleConfig.c
//*
//* 文件描述 : 主配置任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleConfig.h"
#include "SimulateI2C.h"
#include "msg_def.h"
BOOLEAN ModuleConfigInit(void* pArg)
{

    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
#if 0
    u16 address = 100000;
    u8 data = 12;
    PS("----------IIC TEST WRITE 12 ------------");
    IIC_Write(address, data);
    PD(IIC_Read(address));
    PS("----------IIC TEST WRITE END ------------");
#endif

    pData->m_PressSta = FALSE;
    PS("ModuleConfigInit");
    pData->m_SaveStatus = FALSE;
//     pData->m_SaveStep = SAVE_STEP_END;
    pData->m_SaveCount = 0;
    //以下函数测试使用


    pData->m_pSysData->pSys->m_WorkMode = StartMode;
    PD(pData->m_pSysData->pSys->m_WorkMode);
// 		ConfigSave_Base(pArg);
    ConfigLoad_Base(pArg);//读取数据
// 	PD(pData->m_pSysData->pSys->m_WorkMode);
//     ConfigLoad(pArg);//读取数据
// 		Config_T_Load(pArg);//读取数据
// 		Config_E_Load(pArg);//读取数据

    return ret;
}

BOOLEAN ModuleConfigReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    pData->m_PressSta = FALSE;
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
//         printf("ModuleConfig1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;

    if(pData->m_SaveStatus == TRUE)
    {
        pData->m_SaveCount--;
        if(pData->m_SaveCount == 0)
        {
            pData->m_SaveStatus = FALSE;
// 					  ConfigSave_Base(pArg);
//             pData->m_SaveStep = SAVE_STEP_START;
        }
    }
    //ModuleConfigPrint(pData->m_pSysData->pSys->m_CH0TEMP,2);
    switch(pData->m_pSysData->pSys->m_WorkMode)
    {
    case StartMode:
        pData->m_Count++;
        if(pData->m_Count>5) {
            ModuleConfigPrintInfo(pData); //调试串口输出信息
            pData->m_Count=0;
        }
        break;
    case CalcMode:
        break;
    default:
        break;
    }

//     ConfigSaveProc(pArg);//保存数据
}
void ModuleConfigPrint(INT16U *pData, INT16U len)
{
    INT16U index;
    for(index=0; index<len; index++)
    {
        printf("%d ",pData[index]);
    }
}
void ModuleConfigPrintInfo(PMODULECONFIGDATA pData)
{
    INT16U CalcNum;
    switch(pData->m_pSysData->pSys->m_CalMode)
    {
    case KBPoint:
        CalcNum = pData->m_pSysData->pSys->m_CalcNum;
        printf("CalcMode: KBPoint; CalcNum: %d  !!\r\n",CalcNum);
        printf("CH0 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH0AD, CalcNum);
        printf("\r\n");
        printf("CH0 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH0TEMP, CalcNum);
        printf("\r\n");
        printf("CH1 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH1AD, CalcNum);
        printf("\r\n");
        printf("CH1 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH1TEMP, CalcNum);
        printf("\r\n");
        printf("CH2 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH2AD, CalcNum);
        printf("\r\n");
        printf("CH2 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH2TEMP, CalcNum);
        printf("\r\n");
        printf("CH3 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH3AD, CalcNum);
        printf("\r\n");
        printf("CH3 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH3TEMP, CalcNum);
        printf("\r\n");
        printf("CH4 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH4AD, CalcNum);
        printf("\r\n");
        printf("CH4 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH4TEMP, CalcNum);
        printf("\r\n");
        printf("CH5 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH5AD, CalcNum);
        printf("\r\n");
        printf("CH5 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH5TEMP, CalcNum);
        printf("\r\n");
        printf("CH6 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH6AD, CalcNum);
        printf("\r\n");
        printf("CH6 Temp:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH6TEMP, CalcNum);
        printf("\r\n");
        printf("\r\n");
        break;
    case Binomial:
        printf("CalcMode: Binomial\r\n");
        printf("CH0 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH0AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH0 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH0TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH1 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH1AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH1 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH1TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH2 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH2AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH2 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH2TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH3 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH3AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH3 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH3TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH4 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH4AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH4 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH4TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH5 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH5AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH5 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH5TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH6 AD:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH6AD_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("CH6 TEMP:");
        ModuleConfigPrint(pData->m_pSysData->pSys->m_CH6TEMP_E, TEMPCALDATANUM_THE);
        printf("\r\n");
        printf("\r\n");
        break;
    default:
        break;
    }
}

void ConfigMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    switch(MsgId)
    {
    case MS_CONFIG_SAVE:
        if(lParam == 1)
        {
            //立即执行配置保存，调用处理函数
            PS("---------ConfigSave !!!\n");
//                  pData->m_SaveStatus = TRUE;
//                  pData->m_SaveCount = SAVECOUNT;
// 								 ConfigSave_Base(pArg);
            ConfigSaveProc(pArg);
        }
        break;
    default:
        break;
    }
}


void ConfigSaveProc(void* pArg)//保存数据
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    ConfigSave_Base(pArg);
    ConfigSave(pArg);
}
//***************保存数据******************//

void ConfigSave_Base(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;

#if 0
    pData->m_pSysData->pSys->m_VREF = 3330;
    pData->m_pSysData->pSys->m_CalMode = Binomial;
#endif
    len = DATASIZE;
    Address = ADDRESS_VREF_START;
    pDataSave= (PVOID)(&pData->m_pSysData->pSys->m_VREF);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_MODE_START;
    pDataSave= (PVOID)(&pData->m_pSysData->pSys->m_CalMode);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CALCNUM_START;
    pDataSave= (PVOID)(&pData->m_pSysData->pSys->m_CalcNum);
    I2CMemSave(Address,pDataSave,len);
    ConfigSave(pArg);
}

void ConfigLoad_Base(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    INT16U  Address;
    PVOID  pDataLoad;
    INT16U  len;

    len = DATASIZE;
    Address = ADDRESS_VREF_START;
    pDataLoad= (PVOID)(&pData->m_pSysData->pSys->m_VREF);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_MODE_START;
    pDataLoad= (PVOID)(&pData->m_pSysData->pSys->m_CalMode);
    I2CMemLoad(Address,pDataLoad,sizeof(eCalcMode));
    Address = ADDRESS_CALCNUM_START;
    pDataLoad= (PVOID)(&pData->m_pSysData->pSys->m_CalcNum);
    I2CMemLoad(Address,pDataLoad,len);
    PD(pData->m_pSysData->pSys->m_VREF);
    PD(pData->m_pSysData->pSys->m_CalMode);
    PD(pData->m_pSysData->pSys->m_CalcNum);
    ConfigLoad(pArg);
}

void ConfigSave(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;
    len = LEN_CALCDATA;
    Address = ADDRESS_CH0AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH0AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH1AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH1AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH2AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH2AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH3AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH3AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH4AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH4AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH5AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH5AD);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH6AD_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH6AD);
    I2CMemSave(Address,pDataSave,len);

    Address = ADDRESS_CH0TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH0TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH1TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH1TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH2TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH2TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH3TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH3TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH4TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH4TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH5TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH5TEMP);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH6TEMP_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH6TEMP);
    I2CMemSave(Address,pDataSave,len);
}


//***************读取数据******************//
void ConfigLoad(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;

    INT16U  Address;
    PVOID  pDataLoad;
    INT16U  len;

    len = LEN_CALCDATA;

    Address = ADDRESS_CH0AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH0AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH1AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH1AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH2AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH2AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH3AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH3AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH4AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH4AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH5AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH5AD);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH6AD_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH6AD);
    I2CMemLoad(Address,pDataLoad,len);

    Address = ADDRESS_CH0TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH0TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH1TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH1TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH2TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH2TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH3TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH3TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH4TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH4TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH5TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH5TEMP);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH6TEMP_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH6TEMP);
    I2CMemLoad(Address,pDataLoad,len);
// 		PS("----------------------");
// 		for(index=0;index<TEMPCALDATANUM;index++)
// 		{
// 			printf("%d ",pData->m_pSysData->pSys->m_CH0AD[index]);
// 		}
// 		PS("----------------------");
    return;
}

void Config_E_Save(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;
    INT16U  Address;
    PVOID  pDataSave;
    INT16U  len;

    len = LEN_CALCDATA_E;

    Address = ADDRESS_CH0AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH0AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH1AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH1AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH2AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH2AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH3AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH3AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH4AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH4AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH5AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH5AD_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH6AD_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH6AD_E);
    I2CMemSave(Address,pDataSave,len);

    Address = ADDRESS_CH0TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH0TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH1TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH1TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH2TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH2TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH3TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH3TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH4TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH4TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH5TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH5TEMP_E);
    I2CMemSave(Address,pDataSave,len);
    Address = ADDRESS_CH6TEMP_E_START;
    pDataSave= (PVOID)(pData->m_pSysData->pSys->m_CH6TEMP_E);
    I2CMemSave(Address,pDataSave,len);
}


//***************读取数据******************//
void Config_E_Load(void* pArg)
{
    PMODULECONFIGDATA pData = (PMODULECONFIGDATA)pArg;

    INT16U  Address;
    PVOID  pDataLoad;
    INT16U  len;

    len = LEN_CALCDATA_E;

    Address = ADDRESS_CH0AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH0AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH1AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH1AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH2AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH2AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH3AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH3AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH4AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH4AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH5AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH5AD_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH6AD_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH6AD_E);
    I2CMemLoad(Address,pDataLoad,len);

    Address = ADDRESS_CH0TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH0TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH1TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH1TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH2TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH2TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH3TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH3TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH4TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH4TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH5TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH5TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
    Address = ADDRESS_CH6TEMP_E_START;
    pDataLoad= (PVOID)(pData->m_pSysData->pSys->m_CH6TEMP_E);
    I2CMemLoad(Address,pDataLoad,len);
// 		PS("----------------------");
// 		for(index=0;index<TEMPCALDATANUM;index++)
// 		{
// 			printf("%d ",pData->m_pSysData->pSys->m_CH0AD[index]);
// 		}
// 		PS("----------------------");
    return;
}

PMODULEBASE CreateModuleConfig(PMODULESERVERDATA pServerData)
{
    PMODULECONFIG pModConfig = NULL;
    PMODULECONFIGDATA pData = NULL;

    pModConfig = (PMODULECONFIG)malloc(sizeof(MODULECONFIG));//申请基类结构
    pData = (PMODULECONFIGDATA)malloc(sizeof(MODULECONFIGDATA));//申请基类数据结构
//     ASSERT(pModConfig != NULL);
//     ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pModConfig->m_pBaseData = (PVOID)pData;
    MallocSysData(pData);
    //************************以下模块接口必须赋值******************************
    pModConfig->pModeleInit = ModuleConfigInit; //实现模块初始化
    pModConfig->pModeleReset = ModuleConfigReset; //实现模块复位
    pModConfig->pModeleStart = ModuleConfigStart; //实现模块开始
    pModConfig->pModeleStop = ModuleConfigStop; //实现模块结束
    pModConfig->pModeleRelease = ModuleConfigRelease;//实现
    pModConfig->pMsgNotify = ConfigMsgNotify;//实现消息队列处理
    pModConfig->pModele10msProcess = NULL;//不实现，置为NULL
    pModConfig->pModele50msProcess = NULL;//不实现，置为NULL
    pModConfig->pModele1sProcess = ModuleConfig1sProcess;//实现1s调用
    pModConfig->pModele1msProcess = NULL;//实现1ms调用
    strcpy(pModConfig->m_ModName, "ModConfig");

    PS("CreateModuleConfig!!");
    return (PMODULEBASE)pModConfig;
}

void MallocSysData(PMODULECONFIGDATA pData)
{
//     ASSERT(pData != NULL);

    pData->m_pSysData->pSys = NULL;
    pData->m_pSysData->pSys = (PSYSTEMCONFIGDATA)malloc(sizeof(SYSTEMCONFIGDATA));
//     ASSERT(pData->m_pSysData->pSys != NULL);

    pData->m_pSysData->pStatus = NULL;
    pData->m_pSysData->pStatus = (PSYSSTATUSDATA)malloc(sizeof(SYSSTATUSDATA));
    memset(pData->m_pSysData->pStatus, 0, sizeof(SYSSTATUSDATA));
//     ASSERT(pData->m_pSysData->pStatus != NULL);

//     pData->m_pSysData->pParam = NULL;
//     pData->m_pSysData->pParam = (PSYSPARAMDATA)malloc(sizeof(SYSPARAMDATA));
//     ASSERT(pData->m_pSysData->pParam != NULL);

//     pData->m_pSysData->pSys->m_CH1K = NULL;
//     pData->m_pSysData->pSys->m_CH1K = malloc(TEMPCALDATANUM);    //Peep阀校准表 arr[10] 10个元素的数组
//     ASSERT(pData->m_pSysData->pSys->m_PeepCalData != NULL);
}


void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len)//保存传递函数
{
    INT16U i=0;
    INT8U *pSaveData = (INT8U *)pObj;
    for(i=0; i<len; i++)
    {
        /* PD(pSaveData[i]); */
        IIC_Write(Addres+i, pSaveData[i]);
    }
}

void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len)//读取传递函数
{
    INT16U i=0;
    INT8U *pSaveData = (INT8U *)pObj;
    for(i=0; i<len; i++)
    {
        pSaveData[i] = IIC_Read(Addres + i);
    }
}

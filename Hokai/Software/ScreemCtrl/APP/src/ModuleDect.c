//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleDect.c
//*
//* 文件描述 : DECT任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleDect.h"
#include "adc.h"
#include "led.h"
// #include "usart.h"

BOOLEAN ModuleDectInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    INT16U i,j;
    PS("ModuleDectInit");
    pData->m_PkgIndex=0;
    if(pData != NULL)
    {
        pData->m_pAdArr = pData->m_pSysData->pStatus->m_AdArr;
        for(j=0; j<MAXCHLNUM; j++)
        {
            for(i=0; i<MAXDATANUM; i++)
            {
                pData->m_ChDataArr[j][i] = 0;
            }
        }
        for(i=0; i<MAXCHLNUM; i++)
        {
            pData->m_pAdArr[i]=0;
        }
    }
    GetParamMulti(pData);
    GetParamBinomial(pData);
    return ret;
}


void GetParamMulti(PMODULEDECTDATA pData)
{
    INT16U *pArrAd = pData->m_pSysData->pSys->m_CH0AD;
    INT16U *pArrTemp = pData->m_pSysData->pSys->m_CH0TEMP;
    INT16U i=0;
    INT16U CalcNum = pData->m_pSysData->pSys->m_CalcNum;
    INT16U index=0;
    if(CalcNum<=0||CalcNum>TEMPCALDATANUM)
        return;
    pData->m_KBNum = CalcNum - 1;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[0][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[0][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH1AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH1TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[1][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[1][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH2AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH2TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[2][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[2][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH3AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH3TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[3][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[3][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH4AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH4TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[4][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[4][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH5AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH5TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[5][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[5][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
    pArrAd = pData->m_pSysData->pSys->m_CH6AD;
    pArrTemp = pData->m_pSysData->pSys->m_CH6TEMP;
    for(i=0; i<pData->m_KBNum; i++)
    {
        pData->m_MultiK[6][i] = (pArrTemp[1]-pArrTemp[i+i])/((pArrAd[1]-pArrAd[0])*1.0);
        pData->m_MultiB[6][i] = (pArrTemp[1]*pArrAd[i+i]-pArrTemp[i+i]*pArrAd[1])/((pArrAd[i]-pArrAd[i+1])*1.0);
    }
}

void CalcBinomial(INT16U *pArrAd, INT16U *pArrTemp, FP32 *pa, FP32 *pb, FP32 *pc )
{
    INT16U x1,x2,x3,y1,y2,y3;
    FP32 a,b,c;
    x1 = pArrAd[0];
    y1  = pArrTemp[0];
    x2 = pArrAd[1];
    y2  = pArrTemp[1];
    x3 = pArrAd[2];
    y3  = pArrTemp[2];
    a = ((y3-y1-(y2-y1)*(x3-x1)/(x2-x1))/((x3*x3-x1*x1)-(x2+x1)*(x3-x1)));
    b = (y2-y1-a*(x2*x2-x1*x1))/(x2-x1);
    c = y2-a*x1*x1-b*x1;
    *pa = a;
    *pb = b;
    *pc = c;
}

void GetParamBinomial(PMODULEDECTDATA pData)
{
    INT16U *pArrAd = pData->m_pSysData->pSys->m_CH0AD_E;
    INT16U *pArrTemp = pData->m_pSysData->pSys->m_CH0TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[0]),&(pData->BinomialB[0]),&(pData->BinomialC[0]));
    pArrAd = pData->m_pSysData->pSys->m_CH1AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH1TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[1]),&(pData->BinomialB[1]),&(pData->BinomialC[1]));
    pArrAd = pData->m_pSysData->pSys->m_CH2AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH2TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[2]),&(pData->BinomialB[2]),&(pData->BinomialC[2]));
    pArrAd = pData->m_pSysData->pSys->m_CH3AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH3TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[3]),&(pData->BinomialB[3]),&(pData->BinomialC[3]));
    pArrAd = pData->m_pSysData->pSys->m_CH4AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH4TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[4]),&(pData->BinomialB[4]),&(pData->BinomialC[4]));
    pArrAd = pData->m_pSysData->pSys->m_CH5AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH5TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[5]),&(pData->BinomialB[5]),&(pData->BinomialC[5]));
    pArrAd = pData->m_pSysData->pSys->m_CH6AD_E;
    pArrTemp =  pData->m_pSysData->pSys->m_CH6TEMP_E;
    CalcBinomial(pArrAd, pArrTemp,&(pData->BinomialA[6]),&(pData->BinomialB[6]),&(pData->BinomialC[6]));
}

INT16U GetTempAdData(PMODULEDECTDATA pData, INT16U ch, INT16U ad)
{
    INT16U index=0;
    INT16U ret=0;
    if(ch>=MAXCHLNUM)
        return ret;
    for(index=MAXDATANUM-1; index>0; index--)
    {
        pData->m_ChDataArr[ch][index] = pData->m_ChDataArr[ch][index-1];
// 			printf("%d ",pData->m_ChDataArr[ch][index]);
    }
    pData->m_ChDataArr[ch][0] = ad;
// 		printf("%d ",pData->m_ChDataArr[ch][0]);
//  		PS("-------------");
    for(index=0; index<MAXDATANUM; index++)
    {
        ret += pData->m_ChDataArr[ch][index];
    }
    ret /= MAXDATANUM;
// 		printf("%d ",ret);
    return ret;
}

BOOLEAN ModuleDectReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleDectStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleDectStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleDectRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleDect1msProcess(void* pArg)
{
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    INT16U i=0;
    for(i=0; i<MAXCHLNUM; i++) {
        pData->m_pAdArr[i] = GetTempAdData(pData,i,GetAdValue(i));
    }
}

void ModeleDectPrintInfo(PMODULEDECTDATA pData)
{
    INT16U index,i;
    for(index=0; index<MAXCHLNUM; index++) {
        printf("Ch%d AD: %d \r\n",index, pData->m_pAdArr[index]);
    }
    printf("\r\n");
}

void ModuleDect1sProcess(void* pArg)
{
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
//     printf("ModuleDect1sProcess !! \n");
    INT16U index,i;

    if(pData->m_PressSta == FALSE)
        return;
    pData->m_Count++;
    if(pData->m_Count > 5)
    {
        pData->m_Count = 0;
        switch(pData->m_pSysData->pSys->m_WorkMode)
        {
        case StartMode:
            for(index=0; index<MAXCHLNUM; index++) {
                printf("Ch%d Temp: %d \r\n",index, pData->m_TempArr[index]);
            }
            printf("\r\n");
            break;
        case CalcMode:
            ModeleDectPrintInfo(pData);
            break;
        default:
            break;
        }
        //执行配置保存，调用处理函数
        //  if(pData->m_pMsgQueue != NULL)
//	        {
//	            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData,MS_DECT_SAVE,1,0,NULL);
//	        }
    }
// 			ModeleDectSendPkg(pData);
    pData->m_LedStatus = pData->m_LedStatus?0:1;
    LED(pData->m_LedStatus);


}

INT8U SendPKGCheckSum(INT8U* pData, INT8U num)
{
    INT8U ret =0;
    INT8U index =0;
    for(index=0; index<num; index++)
    {
        ret +=pData[index];
    }
    return ret;
}


INT16U CalcTempDataMulti(PMODULEDECTDATA pData, INT16U ch)
{
    INT16U ret = 0;
    FP32 *pK,*pB;
    INT16U TempAd = 0, CalcNum = 0, index=0;
    INT16U *pArrAd = pData->m_pSysData->pSys->m_CH0AD;
    switch(ch)
    {
    case 0:
        pArrAd = pData->m_pSysData->pSys->m_CH0AD;
        break;
    case 1:
        pArrAd = pData->m_pSysData->pSys->m_CH1AD;
        break;
    case 2:
        pArrAd = pData->m_pSysData->pSys->m_CH2AD;
        break;
    case 3:
        pArrAd = pData->m_pSysData->pSys->m_CH3AD;
        break;
    case 4:
        pArrAd = pData->m_pSysData->pSys->m_CH4AD;
        break;
    case 5:
        pArrAd = pData->m_pSysData->pSys->m_CH5AD;
        break;
    case 6:
        pArrAd = pData->m_pSysData->pSys->m_CH6AD;
        break;
    default:
        return ret;
    }
    CalcNum = pData->m_pSysData->pSys->m_CalcNum;
    TempAd = pData->m_pAdArr[ch];
    pK = pData->m_MultiK[ch];
    pB = pData->m_MultiB[ch];
    switch(CalcNum)
    {
    case 2:
        ret = TempAd * pK[0] + pB[0];
        break;
    case 4:
        if(TempAd<pArrAd[1]) index=0;
        else if(TempAd>=pArrAd[1] && TempAd<pArrAd[2]) index=1;
        else if(TempAd>=pArrAd[2]) index=2;
        ret = TempAd * pK[index] + pB[index];
        break;
    case 6:
        if(TempAd<pArrAd[1]) index=0;
        else if(TempAd>=pArrAd[1] && TempAd<pArrAd[2]) index=1;
        else if(TempAd>=pArrAd[2] && TempAd<pArrAd[3]) index=2;
        else if(TempAd>=pArrAd[3] && TempAd<pArrAd[4]) index=3;
        else if(TempAd>=pArrAd[4]) index=4;
        ret = TempAd * pK[index] + pB[index];
        break;
    case 10:
        if(TempAd<pArrAd[1]) index=0;
        else if(TempAd>=pArrAd[1] && TempAd<pArrAd[2]) index=1;
        else if(TempAd>=pArrAd[2] && TempAd<pArrAd[3]) index=2;
        else if(TempAd>=pArrAd[3] && TempAd<pArrAd[4]) index=3;
        else if(TempAd>=pArrAd[4] && TempAd<pArrAd[5]) index=4;
        else if(TempAd>=pArrAd[5] && TempAd<pArrAd[6]) index=5;
        else if(TempAd>=pArrAd[6] && TempAd<pArrAd[7]) index=6;
        else if(TempAd>=pArrAd[7] && TempAd<pArrAd[8]) index=7;
        else if(TempAd>=pArrAd[8]) index=8;
        ret = TempAd * pK[index] + pB[index];
        break;
    default:
        break;
    }
    return ret;
}

INT16U CalcTempDataBinomial(PMODULEDECTDATA pData, INT16U ch)
{
    INT16U ret;
    ret = pData->m_pAdArr[ch]*pData->m_pAdArr[ch]*pData->BinomialA[ch] + pData->m_pAdArr[ch]*pData->BinomialB[ch] + pData->BinomialC[ch];
    return ret;
}
INT16U CalcTempData(PMODULEDECTDATA pData, INT16U ch)
{
    INT16U ret;
    ret = pData->m_pAdArr[ch];
    switch(pData->m_pSysData->pSys->m_CalMode)
    {
    case KBPoint:
        ret = CalcTempDataMulti(pData, ch);
        break;
    case Binomial:
        ret = CalcTempDataBinomial(pData, ch);
        break;
    default:
        break;
    }
    return ret;
}


// #define EOM 0xFF
// #define SOM 0xEF
// #define DSOM 0 //包头
// #define DSEQ 1 //包号
// #define D1 2 	 //通道0高字节
// #define D2 3	 //通道0低字节
// #define D3 4	 //通道1高字节
// #define D4 5	 //通道1低字节
// #define D5 6   //通道2高字节
// #define D6 7	 //通道2低字节
// #define D7 8   //通道3高字节
// #define D8 9	 //通道3低字节
// #define D9 10  //通道4高字节
// #define D10 11  //通道4低字节
// #define D11 12  //通道5高字节
// #define D12 13	//通道5低字节
// #define D13 14  //通道6高字节
// #define D14 15	//通道6低字节
// #define D15 16	//高两位校准模式,低两位校准点数
// #define D16 17  //VREF
// #define DCC 18  //校验
// #define DEOM 19 //包尾
void ModuleDect10msProcess(void* pArg)
{
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
}

void ModeleDectSendPkg(PMODULEDECTDATA pData)
{
    INT8U data[DEOM+1];
    INT16U val=0;

//		INT16U index=0;
// 		for(index=0;index<MAXCHLNUM;index++){
// 			printf("Ch%d Temp: %d \r\n",index, pData->m_TempArr[index]);
// 		}
// 		printf("\r\n");

    data[DSOM] = SOM;
    data[DSEQ] = pData->m_PkgIndex;
    val = pData->m_TempArr[0];
    data[D1] = (val & 0xff00)>>8;
    data[D2] = val & 0x00ff;
    val = pData->m_TempArr[1];
    data[D3] = (val & 0xff00)>>8;
    data[D4] = val & 0x00ff;
    val = pData->m_TempArr[2];
    data[D5] = (val & 0xff00)>>8;
    data[D6] = val & 0x00ff;
    val = pData->m_TempArr[3];
    data[D7] = (val & 0xff00)>>8;
    data[D8] = val & 0x00ff;
    val = pData->m_TempArr[4];
    data[D9] = (val & 0xff00)>>8;
    data[D10] = val & 0x00ff;
    val = pData->m_TempArr[5];
    data[D11] = (val & 0xff00)>>8;
    data[D12] = val & 0x00ff;
    val = pData->m_TempArr[6];
    data[D13] = (val & 0xff00)>>8;
    data[D14] = val & 0x00ff;
    data[D15] = 0;
    data[D16] = 0;
    data[DCC] = SendPKGCheckSum(&data[1],DEOM-2);
    data[DEOM] = EOM;
// 		PD(DEOM+1);
    UartSendData(data,DEOM+1);
    pData->m_PkgIndex++;
    if(pData->m_PkgIndex>=100)
        pData->m_PkgIndex=0;
}

void ModuleDect50msProcess(void* pArg)
{
    PMODULEDECTDATA pData = (PMODULEDECTDATA)pArg;
    INT16U i=0;

    for(i=0; i<MAXCHLNUM; i++)
    {
        pData->m_TempArr[i] = CalcTempData(pData,i);
    }
    switch(pData->m_pSysData->pSys->m_WorkMode)
    {
    case StartMode:
        ModeleDectSendPkg(pData);	//输出数据信息
        break;
    case CalcMode:
        break;
    default:
        break;
    }
// 		printf("%f\r\n",GetAdVoltVal(6));
}

void DectMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{
//    switch(MsgId)
//    {
//        case MSG_DECT_SAVE:
//          if(lParam == 1)
//          {
//            //立即执行配置保存，调用处理函数
//              DectSave();
//          }
//          break;
//        default:break;
//    }
//    printf("Receive MSG !!!\n");
}

PMODULEBASE CreateModuleDect(PMODULESERVERDATA pServerData)
{
    PMODULEDECT pModDect = NULL;
    PMODULEDECTDATA pData = NULL;

    pModDect = (PMODULEDECT)malloc(sizeof(MODULEDECT));//申请基类结构
    pData = (PMODULEDECTDATA)malloc(sizeof(MODULEDECTDATA));//申请基类数据结构
//   ASSERT(pModDect != NULL);
//   ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pData->m_pSysData = pServerData->m_pSysData;
    pModDect->m_pBaseData = (PVOID)pData;

    //************************以下模块接口必须赋值******************************
    pModDect->pModeleInit = ModuleDectInit; //实现模块初始化
    pModDect->pModeleReset = ModuleDectReset; //实现模块复位
    pModDect->pModeleStart = ModuleDectStart; //实现模块开始
    pModDect->pModeleStop = ModuleDectStop; //实现模块结束
    pModDect->pModeleRelease = ModuleDectRelease;//实现
    pModDect->pMsgNotify = DectMsgNotify;//实现消息队列处理
    pModDect->pModele10msProcess = ModuleDect10msProcess;//不实现，置为NULL
    pModDect->pModele50msProcess = ModuleDect50msProcess;//不实现，置为NULL
    pModDect->pModele1sProcess = ModuleDect1sProcess;//实现1s调用
    pModDect->pModele1msProcess = ModuleDect1msProcess;//实现1ms调用
    strcpy(pModDect->m_ModName, "ModDect");

    printf("CreateModuleDect!!\n");
    return (PMODULEBASE)pModDect;
}



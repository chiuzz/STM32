//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleKey.c
//*
//* �ļ����� : KEY����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleKey.h"
#include "led.h"
#include "msg_def.h"

BOOLEAN ModuleKeyInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    INT8U i;
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    if(pData != NULL)
    {
        pData->m_KeyWorkSta = KEY_STOP;
        for(i = 0; i < KEYNUM; i++)
            pData->m_KeyScanMachine[i] = KEY_OFF;
        pData->m_Count = 0;
        pData->m_BeepMac = BEEP_STOP;
        pData->m_BeepCount = 0;
    }
    return ret;
}

BOOLEAN ModuleKeyReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    pData->m_PressSta = FALSE;

    return ret;
}

BOOLEAN ModuleKeyStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleKeyStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleKeyRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleKey1sProcess(void* pArg)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
//     printf("ModuleKey1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    pData->m_Count++;
}

void KeyMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    switch(MsgId)
    {
    case MS_KEY_ON:
        if(lParam == 1 )
        {
            if(pData->m_BeepMac == BEEP_STOP)
                pData->m_BeepMac = BEEP_ON;
        }
        break;
    case MS_KEY_TRIGER:
        if(lParam == 1 )
        {
            if(pData->m_BeepMac == BEEP_STOP)
                pData->m_BeepMac = BEEP_ON;
//						PrintfKeyNum(wParam);
//            PD(wParam);
        }
        break;
    case MS_KEY_CMD:
        if(lParam == 1 )
        {
            pData->m_KeyWorkSta = KEY_INIT;
        }
        else
        {
            pData->m_KeyWorkSta = KEY_WORK;
        }
        break;

    default:
        break;
    }
//    printf("Receive MSG !!!\n");

}

void ModuleKey50msProcess(void* pArg)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;


}

void ModuleKey10msProcess(void* pArg)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    if(pData->m_KeyWorkSta != KEY_WORK)
        return;
    GetButtonKey(pArg);
    BeepTriger(pArg);
}
#define KEYCOUNTMAX 10 //x10ms����ʱ�˲�
#define KEYONCOUNTMAX 200 //x10ms����ʱ�˲�
#define KEYCOUNTBIT6 3000 //30s��Һ·1�������
#define KEY_MIT  (BIT1|BIT0)
#define KEY_CAL1  (BIT6|BIT7)
#define KEY_CAL2  (BIT2|BIT3)
//˫̺      //��̺
//��  			//
//��				//
//Һ·II		//��
//����II    //��
//������    //������
//Һ��     //Һ��
//Һ·I     //Һ·
//����I     //����
void GetButtonKey(void* pArg)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    INT16U val = 0;

//    val = GetButtomValue();
    if(pData->m_pSysData->m_SingleMode == Status_On)
    {
        if(GetKey2Sta())val |= BIT0;
        if(GetKey3Sta())val |= BIT1;
    }
    else {
        if(GetKey0Sta())val |= BIT0;
        if(GetKey1Sta())val |= BIT1;
        if(GetKey2Sta())val |= BIT2;
        if(GetKey3Sta())val |= BIT3;
    }
    if(GetKey4Sta())val |= BIT4;
    if(GetKey5Sta())val |= BIT5;
    if(GetKey6Sta())val |= BIT6;
    if(GetKey7Sta())val |= BIT7;
    switch(val)
    {
    case KEY_MIT:
        KeyProcess(pArg, KEY_MIT, 8);//����
        KeyProcess(pArg, 0, 0);//��
        KeyProcess(pArg, 0, 1);//��
        break;
//    case KEY_CAL1:
//        KeyProcess(pArg, KEY_CAL1, 9);//У׼1
//        KeyProcess(pArg, 0, 6);
//        KeyProcess(pArg, 0, 7);
//        break;
//    case KEY_CAL2:
//        KeyProcess(pArg, KEY_CAL2, 10);//У׼2
//        KeyProcess(pArg, 0, 2);
//        KeyProcess(pArg, 0, 3);
//        break;
    case BIT0:										//˫̺      //��̺
        KeyProcess(pArg, BIT0, 0);//��  			//
        break;
    case BIT1:
        KeyProcess(pArg, BIT1, 1);//��				//
        break;
    case BIT2:
        KeyProcess(pArg, BIT2, 2);//Һ·II		//��
        break;
    case BIT3:
        KeyProcess(pArg, BIT3, 3);//����II    //��
        break;
    case BIT4:
        KeyProcess(pArg, BIT4, 4);//������    //������
        break;
    case BIT5:
        KeyProcess(pArg, BIT5, 5);//Һ��     //Һ��
        break;
    case BIT6:
        KeyProcess(pArg, BIT6, 6);//Һ·I     //Һ·
        break;
    case BIT7:
        KeyProcess(pArg, BIT7, 7);//����I     //����
        break;
    default:
    case 0:
        val = 0;
        KeyProcess(pArg, val, 0);//��
        KeyProcess(pArg, val, 1);//��
        KeyProcess(pArg, val, 2);//Һ·II
        KeyProcess(pArg, val, 3);//����II
        KeyProcess(pArg, val, 4);//������
        KeyProcess(pArg, val, 5);//Һ��I
        KeyProcess(pArg, val, 6);//Һ·I
        KeyProcess(pArg, val, 7);//����I
        KeyProcess(pArg, val, 8);//����
        KeyProcess(pArg, val, 9);//У׼I
        KeyProcess(pArg, val, 10);//У׼II
        break;
//        break;
    }
}
void PrintfKeyNum(INT16U index)
{
    switch(index) {
    case 0:
        printf("�� \r\n");
        break;
    case 1:
        printf("��	\r\n");
        break;
    case 2:
        printf("Һ·II\r\n");
        break;
    case 3:
        printf("����II \r\n");
        break;
    case 4:
        printf("������\r\n");
        break;
    case 5:
        printf("Һ�� \r\n");
        break;
    case 6:
        printf("Һ·I  \r\n");
        break;
    case 7:
        printf("����I  \r\n");
        break;
    case 8:
        printf("�������� \r\n");
        break;
    case 9:
        printf("У׼I \r\n");
        break;
    case 10:
        printf("У׼II \r\n");
        break;

    }
}
void KeyProcess(void* pArg, INT8U val, INT8U index)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;

    switch(pData->m_KeyScanMachine[index])
    {
    default:
    case KEY_OFF:
        pData->m_KeyMark[index] = 0;
        pData->m_KeyCount[index] = 0;
        if(val != 0  && val != pData->m_KeyLast[index])
        {
            pData->m_KeyScanMachine[index] = KEY_ON;
        }
        break;
    case KEY_ON:
        if(pData->m_KeyCount[index] <= KEYCOUNTMAX) {
            pData->m_KeyCount[index]++;
        }
        if(pData->m_KeyCount[index] == KEYCOUNTMAX )
        {
            pData->m_KeyMark[index] = val;
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_ON, 1, 0, NULL);
            pData->m_KeyCount[index] = 0;
            if(val == KEY_MIT ) {
                pData->m_KeyScanMachine[index] = KEY_TRI_MIT;
            }
            else if(val == KEY_CAL1 ) {
                pData->m_KeyScanMachine[index] = KEY_TRI_CAL1;
            }
            else if(val == KEY_CAL2 ) {
                pData->m_KeyScanMachine[index] = KEY_TRI_CAL2;
            }
            else {
                pData->m_KeyScanMachine[index] = KEY_TRI;
            }
//            PS("KEY_ON");
        }
        break;
    case KEY_TRI_MIT:
        pData->m_KeyCount[index]++;
        if(val == KEY_MIT && pData->m_KeyCount[index] >= KEYONCOUNTMAX )
        {
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_TRIGER, 1, index, NULL);
            PrintfKeyNum(index);
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        else if(val == 0) {
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        break;
    case KEY_TRI_CAL1:
        pData->m_KeyCount[index]++;
        if(val == KEY_CAL1 && pData->m_KeyCount[index] >= KEYONCOUNTMAX )
        {
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_TRIGER, 1, index, NULL);
            PrintfKeyNum(index);
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        else if(val == 0) {
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        break;
    case KEY_TRI_CAL2:
        pData->m_KeyCount[index]++;
        if(val == KEY_CAL2 && pData->m_KeyCount[index] >= KEYONCOUNTMAX )
        {
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_TRIGER, 1, index, NULL);
            PrintfKeyNum(index);
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        else if(val == 0) {
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        break;
    case KEY_TRI:
        pData->m_KeyCount[index]++;
        if(pData->m_KeyCount[index] >= KEYONCOUNTMAX && pData->m_KeyMark[index] != BIT6)
        {
            pData->m_KeyScanMachine[index] = KEY_OFF;
            break;
        }
        if(pData->m_KeyMark[index] == BIT6 && pData->m_KeyCount[index] >= KEYCOUNTBIT6)
        {
						pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_TRIGER, 1, 0x1f, NULL);
            pData->m_KeyScanMachine[index] = KEY_OFF;
            break;
        }
        if(val == 0 && pData->m_KeyLast[index] != 0 && pData->m_KeyLast[index] == pData->m_KeyMark[index]) {
//					PD(index);
            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData, MS_KEY_TRIGER, 1, index, NULL);
            pData->m_KeyScanMachine[index] = KEY_OFF;
        }
        break;
    }
    pData->m_KeyLast[index] = val;
}


PMODULEBASE CreateModuleKey(PMODULESERVERDATA pServerData)
{
    PMODULEKEY pModKey = NULL;
    PMODULEKEYDATA pData = NULL;

    pModKey = (PMODULEKEY)malloc(sizeof(MODULEKEY));//�������ṹ
    pData = (PMODULEKEYDATA)malloc(sizeof(MODULEKEYDATA));//����������ݽṹ
//  ASSERT(pModKey != NULL);
//  ASSERT(pData != NULL);
    pData->m_pSysData = pServerData->m_pSysData;
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModKey->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModKey->pModeleInit = ModuleKeyInit; //ʵ��ģ���ʼ��
    pModKey->pModeleReset = ModuleKeyReset; //ʵ��ģ�鸴λ
    pModKey->pModeleStart = ModuleKeyStart; //ʵ��ģ�鿪ʼ
    pModKey->pModeleStop = ModuleKeyStop; //ʵ��ģ�����
    pModKey->pModeleRelease = ModuleKeyRelease;//ʵ��
    pModKey->pMsgNotify = KeyMsgNotify;//ʵ����Ϣ���д���
    pModKey->pModele10msProcess = ModuleKey10msProcess;//��ʵ�֣���ΪNULL
    pModKey->pModele50msProcess = ModuleKey50msProcess;//��ʵ�֣���ΪNULL
    pModKey->pModele1sProcess = ModuleKey1sProcess;//ʵ��1s����
    pModKey->pModele1msProcess = NULL;//ʵ��1s����
    strcpy(pModKey->m_ModName, "ModKey");

    printf("CreateModuleKey!!\n");
    return (PMODULEBASE)pModKey;
}

void BeepTriger(void* pArg)
{
    PMODULEKEYDATA pData = (PMODULEKEYDATA)pArg;
    switch(pData->m_BeepMac)
    {
    default:
    case BEEP_STOP:
        Buzze(1);
        break;
    case BEEP_ON:
        Buzze(0);
        pData->m_BeepMac = BEEP_ON_HOLD;
        pData->m_BeepCount = 0;
        break;
    case BEEP_ON_HOLD:
        if(pData->m_BeepCount > 3) {
            Buzze(1);
            pData->m_BeepMac = BEEP_STOP;
        }
        pData->m_BeepCount++;
        break;
    }
}

#include "includes.h"


u8 cnt=0;
NETWORKSTA sta=staRESTART;
u8 linktype=CLIENT;

void NetWorkDeal(void)		//100ms调度
{
    switch(sta)
    {
    case staRESTART:		//上电等待稳定
        if(100==cnt++)
        {
            cnt=0;
            sta=staINIT;
        }
        break;
    case staINIT:
        NetWorkInit();
        while(STA!=GetWIFImod()) {
            SetWIFImod(STA);
        }
        if(SERVER==linktype)
            sta=staSERVER;
        else if(CLIENT==linktype)
            sta=staCLIENT;
        else if(UDP==linktype)
            sta=staUDP;
        break;
    case staSERVER:

        break;
    case staCLIENT:
        ClientTest();
        break;
    case staUDP:

        break;
    default:
        break;
    }
}

CTSTA ctsta=staAPCONNECTING;
void ClientTest(void)
{
    u8 buf[100]= {0};
    u8 led1,led2;
    NETWORKSTU *pNetWorkData;
    switch(ctsta)
    {
    case staAPCONNECTING:
        if(cnt==0)
            JoinAP((void *)"HOME_2.4G",(void *)"home102338");
        if(APCONNECTTIME==cnt++)
        {
            cnt=0;
            ctsta=staAPCONNECTED;
        }
        break;
    case staAPCONNECTED:
        if(TRUE==GetAPInfo())
        {
            cnt=0;
            ctsta=staTCPCONNECTING;
        }
        else
        {
            cnt++;
            if(cnt>=3) {
                cnt=0;
                ctsta=staAPCONNECTING;
            }
        }
        break;
    case staTCPCONNECTING:
        if(cnt==0) {
            while(0!=GetCipMux()) {
                SetCipMux(0);		//开启单连接
            }
//            StartTcpConnect(0,(void *)"TCP",(void *)"192.168.0.123",8888);
            StartTcpConnect(0,(void *)"TCP",(void *)"tcp.tlink.io",8647);
        }
        if(TCPCONNECTTIME==cnt++)
        {
            cnt=0;
            ctsta=staTCPCONNECTED;
        }
        break;
    case staTCPCONNECTED:
        pNetWorkData=GetTcpSta();
        if(3==pNetWorkData->stat)
        {
            cnt=0;
            ctsta=staLINKING;
            StartTransmit();
            TlinkConnect();
        }
        else
        {
            cnt++;
            if(cnt>=3) {
                cnt=0;
                ctsta=staTCPCONNECTING;
            }
        }
    case staLINKING:
//检查连接状态
//上传led状态到tlink
        cnt++;
        if(cnt>=10) {
            cnt=0;
            if(NetWorkData.CmdStu.cmd==LED_RED_OFF)
                led1=0;

            if(NetWorkData.CmdStu.cmd==LED_RED_ON)
                led1=1;

            if(NetWorkData.CmdStu.cmd==LED_GREEN_OFF)
                led2=0;

            if(NetWorkData.CmdStu.cmd==LED_GREEN_ON)
                led2=1;

            sprintf((void*)buf,"CH,%d,%d,CHEND",led1,led2);
            uart3_send((void*)buf);
        }
        break;
    }
}





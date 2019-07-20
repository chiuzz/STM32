#include "includes.h"
#define ROW 20
#define COLUMN 100
static u8 Esp8266AckInfo[ROW][COLUMN]= {0};

NETWORKSTU NetWorkData;

void NetWorkInit(void)
{
    u32 i=0;
    u8 *p=(void *)&NetWorkData;
    for(i=0; i<sizeof(NetWorkData); i++)
        *(p+i)=0;
    StopTransmit();
    AT_Cmd_Send((void *)"AT+RST");
    AT_Cmd_Send((u8 *)"AT");
    AT_Cmd_Send((u8 *)"ATE1");				//关回显
}

WIFIMOD GetWIFImod(void)
{
    AT_Cmd_Send((void *)"AT+CWMODE_CUR?");
    return NetWorkData.wifimod;
}

void SetWIFImod(WIFIMOD mod)
{
    u8 buf[20];
    sprintf((void *)buf,"AT+CWMODE_CUR=%d",mod);
    AT_Cmd_Send(buf);
}

BOOL GetAPInfo(void)
{
    BOOL err;
    err=AT_Cmd_Send((void *)"AT+CWJAP_CUR?");
    return err;
}

void JoinAP(u8 *ssid,u8 *psword)
{
    u8 buf[100];
    sprintf((void *)buf,"AT+CWJAP_CUR=\"%s\",\"%s\"",ssid,psword);
    AT_Cmd_Send(buf);
}

u8 GetCipMux(void)
{
    AT_Cmd_Send((void *)"AT+CIPMUX?");
    return NetWorkData.cipmux;
}

void SetCipMux(u8 mod)
{
    u8 buf[20];
    sprintf((void *)buf,"AT+CIPMUX=%d",mod);
    AT_Cmd_Send(buf);
}

NETWORKSTU *GetTcpSta(void)
{
    AT_Cmd_Send((void *)"AT+CIPSTATUS");
    return &NetWorkData;
}

void StartTcpConnect(u8 link_id,u8 *type,u8 *remote_ip,u32 remote_port)
{
    u8 buf[100];
    if(NetWorkData.cipmux==1)
        sprintf((void *)buf,"AT+CIPSTART=%d,\"%s\",\"%s\",%d",link_id,type,remote_ip,remote_port);
    else
        sprintf((void *)buf,"AT+CIPSTART=\"%s\",\"%s\",%d",type,remote_ip,remote_port);
    AT_Cmd_Send(buf);
}

void RemoteCmdScan(void)
{
    AT_Info_Get((void *)"RemoteCmd");
}

void StartTransmit(void)		//仅单连接client时支持
{
    AT_Cmd_Send((void *)"AT+CIPMODE=1");
    AT_Cmd_Send((void *)"AT+CIPSEND");
}

void TlinkConnect(void)
{
    uart3_send((void *)"4R71HU35W421GLJ7");
}

void StopTransmit(void)
{
    AT_Cmd_Send((void *)"+++");
}

BOOL AT_Cmd_Send(u8 *cmd)
{
    BOOL err;
    uart3_send(cmd);
    if(0==strcmp("+++",(void *)cmd))
    {
        vTaskDelay(1000);
        return TRUE;
    }
    uart3_send((void *)"\r\n");
    while(!uart3_sta);		//等待返回消息接收完
    uart3_sta=0;
    vTaskDelay(50);
    err=AT_Info_Get(cmd);
    return err;
}

//根据指令获取相应信息
BOOL AT_Info_Get(u8 *cmd)
{
    BOOL err=FALSE;
    u8 buf[100]= {0};
    u8 buf2[20]= {0};
    if(0==strcmp("AT",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"OK\r\n",buf);
        if(err)
            printf("AT success!\r\n");
    }
    else if(0==strcmp("AT+CWMODE_CUR?",(const char *)cmd) || 0==strcmp("AT+CWMODE_DEF?",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"+CWMODE_CUR:",buf);
        myatoi(buf,(void *)&NetWorkData.wifimod);
    }
    else if(0==strcmp("AT+CWJAP_CUR?",(const char *)cmd) || 0==strcmp("AT+CWJAP_DEF?",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"+CWJAP_CUR:",buf);
        if(err) {
            NetWorkArgGet((void *)&NetWorkData.ssid,buf);
            NetWorkArgGet((void *)&NetWorkData.mac,buf);
            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.channel);
            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.rssi);
            printf("connect success!\r\n");
            printf("ssid:%s\r\n",NetWorkData.ssid);
            printf("mac:%s\r\n",NetWorkData.mac);
            printf("channel:%d\r\n",NetWorkData.channel);
            printf("rssi:%d\r\n",NetWorkData.rssi);
        }
        else {
            printf("connect fail!\r\n");
        }
    }
    else if(0==strcmp("AT+CIPMUX?",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"+CIPMUX:",buf);
        myatoi(buf,(void *)&NetWorkData.cipmux);
    }
    else if(0==strcmp("AT+CIPSTATUS",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"STATUS:",buf);
        myatoi(buf,(void *)&NetWorkData.stat);

        err=AT_Arg_Get((u8 *)"+CIPSTATUS:",buf);
        if(err) {
            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.link_id);

            NetWorkArgGet((void *)&NetWorkData.type,buf);

            NetWorkArgGet((void *)&NetWorkData.remote_ip,buf);

            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.remote_port);

            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.local_port);

            NetWorkArgGet(buf2,buf);
            myatoi(buf2,(void *)&NetWorkData.tetype);

            printf("TCP/UDP connect success!\r\n");
            printf("link_id:%d\r\n",NetWorkData.link_id);
            printf("type:%s\r\n",NetWorkData.type);
            printf("remote_ip:%s\r\n",NetWorkData.remote_ip);
            printf("remote_port:%d\r\n",NetWorkData.remote_port);
            printf("local_port:%d\r\n",NetWorkData.local_port);
            printf("tetype:%d\r\n",NetWorkData.tetype);
        }
        else {
            printf("TCP/UDP connect fail!\r\n");
        }
    }
    else if(0==strcmp("RemoteCmd",(const char *)cmd))
    {
        err=AT_Arg_Get((u8 *)"+IPD,",buf);
        RemoteCmdArgGet(buf2,buf);
        myatoi(buf2,(void *)&NetWorkData.CmdStu.cmdlength);
        RemoteCmdArgGet(buf2,buf);
        RemoteCmdTransform(buf2,&NetWorkData.CmdStu.cmd);
    }
    return err;
}

//远端命令键值转换
void RemoteCmdTransform(u8 *cmdbuf,REMOTECMDENUM *cmd)
{
    if(0==strcmp("LED_RED_OFF",(void *)cmdbuf))
    {
        *cmd=LED_RED_OFF;
    }
    else if(0==strcmp("LED_RED_ON",(void *)cmdbuf))
    {
        *cmd=LED_RED_ON;
    }
    else if(0==strcmp("LED_GREEN_OFF",(void *)cmdbuf))
    {
        *cmd=LED_GREEN_OFF;
    }
    else if(0==strcmp("LED_GREEN_ON",(void *)cmdbuf))
    {
        *cmd=LED_GREEN_ON;
    }
    else if(0==strcmp("LED_RED_BREATH",(void *)cmdbuf))
    {
        *cmd=LED_RED_BREATH;
    }
    else if(0==strcmp("LED_GREEN_BREATH",(void *)cmdbuf))
    {
        *cmd=LED_GREEN_BREATH;
    }
}

//获取远端命令参数
void RemoteCmdArgGet(u8 *arg,u8 *buf)
{
    u8 i=0,j=0;
    while(buf[i]!=':' && buf[i]!='\0')
    {
        arg[j++]=buf[i++];
    }
    arg[i++]='\0';
    j=0;
    while(buf[i]!='\0')
    {
        buf[j]=buf[i];
        buf[i]='\0';
        i++;
        j++;
    }
    buf[j]='\0';
}

//获取网络参数
void NetWorkArgGet(u8 *arg,u8 *buf)
{
    u8 i=0,j=0;
    while(buf[i]!=',' && buf[i]!='\0')
    {
        if(buf[i]!='\"') {
            arg[j]=buf[i];
            i++;
            j++;
        }
        else {
            i++;
        }
    }
    arg[i++]='\0';
    j=0;
    while(buf[i]!='\0')
    {
        buf[j]=buf[i];
        buf[i]='\0';
        i++;
        j++;
    }
    buf[j]='\0';
}

//根据参数前缀获取相应参数所在行
BOOL AT_Arg_Get(u8 *arg,u8 *buf)
{
    BOOL err;
    u8 i,j,tmp;
    i=j=tmp=0;
    tmp=strlen((const char *)arg);
    for(i=0; i<ROW; i++)		//查找参数所在行
    {
        err=string_cmp(arg,Esp8266AckInfo[i]);
        if(err) break;
    }
    if(err)
    {
        while(Esp8266AckInfo[i][tmp+j]!='\r' && Esp8266AckInfo[i][tmp+j]!='\0')	//去前缀和回车换行符
        {
            buf[j]=Esp8266AckInfo[i][tmp+j];
            j++;
        }
        buf[j]='\0';
        printf("Arg found!\r\n");
    }
    else
    {
        printf("Arg no found!\r\n");
    }
    return err;
}

//查找字符串片段
BOOL string_cmp(u8 *ch,u8 *buf)
{
    u8 i=0,num;
    num=strlen((const char*)ch);
    while(*buf!='\0')
    {
        if(ch[i] == *buf++)
        {
            if(++i==num) {
                return TRUE;
            }
        }
        else
        {
            i=0;
        }
    }
    return FALSE;
}

//字符串转数字
void myatoi(u8 *str,s32 *num)
{
    s32 tmp=0;
    *num=0;
    while(*str!='\0')
    {
        if(*str == '-')
        {
            str++;
            *num=-1;
        }
        else if(*str>='0' && *str<='9')
        {
            tmp*=10;
            tmp+=(*str++ - '0');
        }
        else
        {
            printf("atoi fail!\r\n");
            return;
        }
    }
    if(*num==-1)
        *num *= tmp;
    else
        *num = tmp;
}








//清空二维数组
void clear_buf(void)
{
    u8 i,j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COLUMN; j++)
        {
            Esp8266AckInfo[i][j]=0;
        }
    }
}

//转换二维数组
void string_deal(u8 *buf)
{
    u8 i,j,sta;
    sta=i=j=0;
    clear_buf();
    while(*buf!='\0')
    {
        if(*buf=='\r')
            sta |= 0x01;
        else if(*buf=='\n')
            sta |= 0x02;

        Esp8266AckInfo[i][j++]=*buf++;
        if(j>=COLUMN)
        {
            clear_buf();
            break;
        }
        if(sta==0x03) {
            Esp8266AckInfo[i][j]='\0';
            sta=j=0;
            i++;
        }
        if(i>=ROW)
        {
            clear_buf();
            break;
        }
    }
}





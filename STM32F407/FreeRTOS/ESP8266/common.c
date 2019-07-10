#include "includes.h"


//»ù´¡ATÖ¸Áî
void AT_Test(u8 *ack)
{
    BOOL err;
    u8 buf[10]= {0};
    uart3_send((u8 *)"AT");
    while(!uart3_sta);
    uart3_sta=0;
    sprintf((char*)buf,"\r\n");
    sprintf((char*)buf,"%s",ack);
    sprintf((char*)buf,"\r\n");
    err = string_cmp(ack,uart3_buf);
    if(err)
        printf("AT success!\r\n");
}






















BOOL string_cmp(u8 *ch,u8 *buf)
{
    u8 i=0,num;
    num=strlen((const char*)ch);
    while(buf!='\0')
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



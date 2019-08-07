#include "includes.h"

FLASH_Status EraseFlash(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    status=FLASH_EraseSector(FLASH_Sector_4, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_5, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_6, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_7, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_9, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_10, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    status=FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);
    if(status!=FLASH_COMPLETE) return status;

    return status;
}

void SaveIntoFlash(uint32_t Address, uint16_t *buf, uint32_t Size)
{
    u32 i;
    FLASH_Status status = FLASH_COMPLETE;
    if(Address<0x08000000 || Address>=0x08100000)
    {
        printf("��ַ����!\r\n");
        return;
    }

    if(Address+2*Size >= 0x08100000)
    {
        printf("����flash�ռ�!\r\n");
        return;
    }
    FLASH_Unlock();
    FLASH_DataCacheCmd(DISABLE);
    status=EraseFlash();

    if(status!=FLASH_COMPLETE)
    {
        printf("%d ����ʧ��!\r\n",status);
        return;
    }

    for(i=0; i<Size; i++)
    {
        printf("count!\r\n");
        if(FLASH_ProgramHalfWord(Address, *buf)!=FLASH_COMPLETE)
        {
            printf("%d д��ʧ��!\r\n",status);
            return;
        }
        Address+=2;
        buf++;
    }
    FLASH_DataCacheCmd(ENABLE);
    FLASH_Lock();
}

void ReadFromFlash(uint32_t Address, uint16_t *buf, uint32_t Size)
{
    u32 i;
    for(i=0; i<Size; i++)
    {
        *(buf+i) = *(vu16*)(Address+i*2);
    }
}














//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : TaskMain.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __TASK_MAIN_H__
#define  __TASK_MAIN_H__

#include "common.h"
#include "struct_def.h"
#include "ModuleServer.h"

extern void Task_One_Process(void *pdata);
extern void Task_Two_Process(void *pdata);
extern void Task_The_Process(void *pdata);
extern void Task_Fou_Process(void *pdata);
extern void Task_Server(void *pdata);

#endif

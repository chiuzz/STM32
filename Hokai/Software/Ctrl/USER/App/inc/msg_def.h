//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : msf_def.h
//*
//* 文件描述 : 系统消息定义文件
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MSG_DEF_H__
#define  __MSG_DEF_H__

///@brief MS_
///lParam:
///wParam:
///@buf:
///#define MS_

#define KEY0  0
#define KEY1  1
#define KEY2  2
#define KEY3  3
#define KEY4  4
#define KEY5  5
#define KEY6  6
#define KEY7  7
#define KEY8  8
#define KEY9  9
#define KEY10 10

#define KEY_DEC  KEY0
#define KEY_ADD  KEY1
#define KEY_WORK_MODE  KEY4
#define KEY_WATER  KEY5
#define KEY_BUMP1  KEY6
#define KEY_TEMP1  KEY7
#define KEY_ALMVOL  KEY8
#define KEY_CAL1  KEY9
#define KEY_CAL2  KEY10

#define KEY_BUMP2  KEY2
#define KEY_TEMP2  KEY3

#define KEY_S_DEC  KEY2
#define KEY_S_ADD  KEY3

#define MS_BASE 2
#define MS_DISTANCE 16

typedef enum
{
    CMD_START, //命令开始
    CMD_STOP,		//命令结束
    CMD_SUCESS, //命令成功
    CMD_FAIL, //命令失败
}	ewParam;

/*********************ModueleConfig模块处理消息块************************/
#define MS_MOD_BASE (MS_BASE + MS_DISTANCE*0)
//@brief MS_KEY_CMD 按键消息
//lParam: 1-有效命令
//wParam: eKeyDef
//@buf: pData
#define MS_KEY_CMD MS_MOD_BASE+1
//@brief MS_BUMP_CMD 泵工作状态设置
//lParam: 1-1号泵控制器，2-2号泵控制器
//wParam: 1-启动，0-停止
//@buf: pData
#define MS_BUMP_CMD MS_MOD_BASE+2

typedef enum
{
    CONFIGINIT = 10,
    CALCDATASAVE,
    CONFIGDATASAVE,
    ADJDATASAVE,
    E2PROMERR,
}	eConfiglParam;

//@brief MS_CONFIG_CMD config命令
//lParam: eConfiglParam
//wParam: ewParam;
//@buf: pData
#define MS_CONFIG_CMD MS_MOD_BASE+3
//@brief MS_COOLER_CMD 制冷模块命令
//lParam: 0-控制器模式，1-开关模式
//wParam: 0-启动 1-完成
//@buf: pData
#define MS_COOLER_CMD MS_MOD_BASE+4
//@brief MS_HEATER_CMD 制热模块命令
//lParam: 0-控制器模式，1-开关模式
//wParam: 0-启动 1-完成
//@buf: pData
#define MS_HEATER_CMD MS_MOD_BASE+5
/*********************ModueleConfig模块处理消息块************************/

#endif

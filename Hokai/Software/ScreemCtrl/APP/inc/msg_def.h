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

#define MS_BASE 2
#define MS_DISTANCE 16

/*********************ModueleConfig模块处理消息块************************/
#define MS_MOD_BASE (MS_BASE + MS_DISTANCE*0)
//@brief MS_CONFIG_SAVE 配置数据
//lParam: eWorkMode
//wParam: NULL  
//@buf: pData
#define MS_KEY_TRIGER MS_MOD_BASE + 1

#define MS_KEY_ON MS_MOD_BASE + 2

#define MS_ALM_BEEP MS_MOD_BASE + 3

#define MS_KEY_CMD MS_MOD_BASE + 4

#define MS_SCR_CMD MS_MOD_BASE + 5
/*********************ModueleConfig模块处理消息块************************/




#endif

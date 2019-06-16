#ifndef	_APP_H_
#define	_APP_H_

#include "struct_def.h"
/**************** 用户任务声明 *******************/

void*  CreateMultiTask (void);
void AppCycle(PVOID pArg);
void Task_1ms_Process(void *pdata);
void Task_10ms_Process(void *pdata);
void Task_50ms_Process(void *pdata);
void Task_1s_Process(void *pdata);
void Task_Server(void *pdata);

static GLOBALDATA g_Global;
#endif	//_APP_H_

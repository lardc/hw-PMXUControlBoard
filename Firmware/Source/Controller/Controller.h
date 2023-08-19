#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "stdio.h"
#include "Global.h"
//
#define CONTROL_CheckContactorsStates_macro(arr)	(CONTROL_CheckContactorsStates(arr, sizeof(arr) / sizeof(arr[0])))
// Types
//
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Ready = 3,
	DS_InProcess = 4
} DeviceState;

typedef enum __DeviceSubState
{
	DSS_None = 0,
	DSS_SelfTestProgress = 1,
	DSS_AwaitingRelayCommutation = 2,
	DSS_AwaitingContactorsQgUP,
	DSS_AwaitingContactorsQgUPRev,
	DSS_AwaitingContactorsQgDOWN,
	DSS_AwaitingContactorsQgDOWNRev,
	DSS_AwaitingContactorsVcesatUP,
	DSS_AwaitingContactorsVcesatUPRev,
	DSS_AwaitingContactorsVcesatDOWN,
	DSS_AwaitingContactorsVcesatDOWNRev,
	DSS_AwaitingContactorsVsdUP,
	DSS_AwaitingContactorsVsdUPRev,
	DSS_AwaitingContactorsVsdDOWN,
	DSS_AwaitingContactorsVsdDOWNRev,
	DSS_AwaitingContactorsRdsonUP,
	DSS_AwaitingContactorsRdsonUPRev,
	DSS_AwaitingContactorsRdsonDOWN,
	DSS_AwaitingContactorsRdsonDOWNRev,
	DSS_AwaitingContactorsVfUP,
	DSS_AwaitingContactorsVfUPRev,
	DSS_AwaitingContactorsVfDOWN,
	DSS_AwaitingContactorsVfDOWNRev = 22,
	DSS_AwaitingResetToDefault = 23
} DeviceSubState;

typedef enum __DeviceSelfTestState
{
	STS_None = 0,
	//
	STS_PE1Check = 1,
	STS_PE2Check = 2,
	//
	STS_LCTU1Check = 3,
	STS_LCTU2Check = 4,
	//
	STS_TOCU1Check = 5,
	STS_TOCU2Check = 6,
	STS_TOCU3Check = 7,
	STS_TOCU4Check = 8,
	//
	STS_LCSU1Check = 9,
	STS_LCSU2Check = 10,
	STS_LCSU3Check = 11,
	STS_LCSU4Check = 12,
} DeviceSelfTestState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern volatile DeviceSelfTestState CONTROL_STState;
extern Int64U CONTROL_LEDTimeout;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SaveTestResult();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);
void CONTROL_SetDeviceSTState(DeviceSelfTestState NewSTState);
void CONTROL_ResetToDefaultState();
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_LogicProcess();
void CONTROL_CheckContactorsStates(Int8U CommArray[], Int8U Length);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetOutputRegisters();

#endif // __CONTROLLER_H

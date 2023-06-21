#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "Global.h"

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

typedef enum __DeviceSelfTestState
{
	STS_None = 0,
	STS_CurrentMeasure = 1,
	STS_OpenRelayCheck = 2,
	STS_Get_ArrayLenght = 3,

	STS_InputRelayCheck_1 = 10,
	STS_InputRelayCheck_2,
	STS_InputRelayCheck_3,
	STS_InputRelayCheck_4,

	STS_MCRelayCheck_1 = 15,
	STS_MCRelayCheck_2,
	STS_MCRelayCheck_3,
	STS_MCRelayCheck_4,

	STS_InputRelayOpenCheck_1 = 20,
	STS_InputRelayOpenCheck_2,
	STS_InputRelayOpenCheck_3,
	STS_InputRelayOpenCheck_4,

	STS_MCRelayOpenCheck_1 = 25,
	STS_MCRelayOpenCheck_2,
	STS_MCRelayOpenCheck_3,
	STS_MCRelayOpenCheck_4,

} DeviceSelfTestState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSelfTestState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SaveTestResult();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSelfTestState NewSubState);
void CONTROL_ResetToDefaultState();
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_LogicProcess();
void CONTROL_UpdateWatchDog();
void CONTROL_ResetOutputRegisters();

#endif // __CONTROLLER_H

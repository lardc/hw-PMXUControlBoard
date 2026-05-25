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
	DS_None				= 0,
	DS_Fault			= 1,
	DS_Disabled			= 2,
	DS_Enabled			= 3,
	DS_SafetyActive		= 4,
	DS_SafetyTrig		= 5,
	DS_InProcess		= 7
} DeviceState;

typedef enum __DeviceSubState
{
	DSS_None = 0
} DeviceSubState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;
extern bool FPledForcedLight;
extern volatile Int16U CONTROL_DiagCounter;
//
extern volatile float CONTROL_DiagData[VALUES_DIAG_SIZE];

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_FinishedWithProblem(Int16U Problem);
void CONTROL_SafetyIrqTick();
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);
void CONTROL_ResetToDefaultState();
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_LogicProcess();
bool CONTROL_CheckContactorsStates(const Int8U CommArray[], Int8U Length);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetOutputRegisters();
void CONTROL_CheckContactorsCounter();
void CONTROL_HandleExternalLamp(bool Forced);
void CONTROL_SaveLastRequest(Int16U ActionID);

#endif // __CONTROLLER_H

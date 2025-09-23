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
	DS_InSelfTest		= 6,
	DS_InProcess		= 7
} DeviceState;

typedef enum __DeviceSubState
{
	DSS_None 			= 0,
	DSS_SelfTest_LCTUP	= 1,
	DSS_SelfTest_LCTUN	= 2,
	DSS_SelfTest_PE1	= 3,
	DSS_SelfTest_PE2	= 4,
	DSS_SelfTest_LCSU1	= 5,
	DSS_SelfTest_LCSU2	= 6,
	DSS_SelfTest_TOCU1	= 7,
	DSS_SelfTest_TOCU2	= 8,
	DSS_SelfTest_Finish = 9
} DeviceSubState;

typedef enum __DevType
{
	SC_Type_A2 = 3101,
	SC_Type_B1 = 3106,
	SC_Type_C1 = 3102,
	SC_Type_D0 = 3105,
	SC_Type_E0 = 3103,
	SC_Type_F1 = 3104,
	SC_Type_ADAP = 3107,
	SC_Type_E2M = 3108,
//
	SC_Type_MIAA = 3001,
	SC_Type_MIDA = 3002,
	SC_Type_MIFA = 3003,
	SC_Type_MIHA = 3004,
	SC_Type_MIHM = 3005,
	SC_Type_MIHV = 3006,
	SC_Type_MISM = 3007,
	SC_Type_MISV = 3008,
	SC_Type_MIXM = 3009,
	SC_Type_MIXV = 3010,
	// 2011
	SC_Type_MISM2_CH = 3012,
	SC_Type_MISM2_SS_SD = 3014,
	SC_Type_MIADAP = 3015,
	SC_Type_MDAA = 3016,
	SC_Type_MDFA_MDF2_DD = 3017,
	SC_Type_MDSM = 3018,
	SC_Type_MDSV = 3019,
	SC_Type_MDFA_MDF2_SD = 3020,
	SC_Type_MDA2 = 3021
} DevType;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern Int64U CONTROL_LEDTimeout;
extern bool FPledForcedLight;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SaveTestResult();
void CONTROL_SwitchToFault(Int16U Reason);
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

#endif // __CONTROLLER_H

﻿// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Diagnostic.h"
#include "BCCIxParams.h"
#include "SelfTest.h"
#include "CommutationTable.h"
#include "Commutator.h"
#include "ZcRegistersDriver.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = DSS_None;
volatile DeviceSelfTestState CONTROL_STState = STS_None;
static Boolean CycleActive = false;
static Int16U CONTROL_Commutation = 0;
volatile Int64U CONTROL_TimeCounter = 0;
static Int64U CONTROL_CommutationStartTime = 0;

// Forward functions
//
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_LogicProcess();

// Functions
//
void CONTROL_Init()
{
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);

	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_LogicProcess();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, STS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;

	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_SetDeviceSTState(DeviceSelfTestState NewSTState)
{
	CONTROL_STState = NewSTState;
	DataTable[REG_ST_STATE] = NewSTState;
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetOutputRegisters();
	CONTROL_SetDeviceState(DS_None, STS_None);
}
//------------------------------------------

bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;

	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				DataTable[REG_SELF_TEST_FAILED_SS] = STS_None;
				DataTable[REG_SELF_TEST_FAILED_RELAY] = 0;
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
				//CONTROL_SetDeviceState(DS_InProcess, STS_InputRelayCheck_1);
			}
			else if(CONTROL_State != DS_Ready)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_None, DSS_None);
			}
			else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_CLR_FAULT:
			if (CONTROL_State == DS_Fault)
			{
				CONTROL_SetDeviceState(DS_None, DSS_None);
				DataTable[REG_FAULT_REASON] = DF_NONE;
			}
			break;

		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;
		// Commutations
		case ACT_COMM_PE:
			if(CONTROL_State == DS_Ready)
			{
				CONTROL_SetDeviceState(DS_InProcess, DSS_AwaitingRelayCommutation);
				COMM_Commutate(ACT_COMM_PE);
				CONTROL_CommutationStartTime = CONTROL_TimeCounter;
			}
			else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
	}
	return true;
}
//-----------------------------------------------

void CONTROL_LogicProcess()
{
	// Commutation processor
	if (CONTROL_State == DS_InProcess)
	{
		// Relays commutation (without feedback from proximity sensors)
		if (CONTROL_SubState == DSS_AwaitingRelayCommutation)
		{
			if (CONTROL_TimeCounter >= (CONTROL_CommutationStartTime + COMM_RELAYS_DELAY_MS))
				CONTROL_SetDeviceState(DS_Ready, DSS_None);
		}
		// Contactors commutation
		else
		{
			if (CONTROL_TimeCounter >= (CONTROL_CommutationStartTime + DataTable[REG_CONTACTORS_COMM_DELAY_MS]))
			{
				switch (CONTROL_SubState)
				{
					case DSS_AwaitingContactorsQgUP:
						if (ZcRD_CommutationCheck_macro(CT_Qg_UP) != COMM_CHECK_NO_ERROR)
						{
							CONTROL_SetDeviceState(DS_Fault, DSS_None);
							// Set error code to register
						}
						break;
				}
			}
		}
	}
	//
	// Pressure sensing processor

	// Safety circuit processor

	// Indication processor
}
//-----------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

void CONTROL_ResetOutputRegisters()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	//
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

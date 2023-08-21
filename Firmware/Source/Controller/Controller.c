// Header
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
#include "Converter.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = DSS_None;
volatile DeviceSelfTestState CONTROL_STState = STS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
static Int64U CONTROL_CommutationStartTime = 0;
static Int64U CONTROL_IndBlinkStartTime = 0;

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

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
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
	CONTROL_SetDeviceState(DS_None, DSS_AwaitingResetToDefault);
}
//------------------------------------------

bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;

	switch(ActionID)
	{
		case ACT_ENABLE_POWER:
			if(CONTROL_State == DS_None)
			{
				DataTable[REG_SELF_TEST_FAILED_SS] = STS_None;
				DataTable[REG_SELF_TEST_FAILED_RELAY] = 0;
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
				CONTROL_SetDeviceState(DS_Ready, DSS_None);
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
			if(CONTROL_State == DS_Fault)
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
	if(CONTROL_State == DS_InProcess)
	{
		// Relays commutation (without feedback from proximity sensors)
		if(CONTROL_SubState == DSS_AwaitingRelayCommutation)
		{
			if(CONTROL_TimeCounter >= (CONTROL_CommutationStartTime + COMM_RELAYS_DELAY_MS))
				CONTROL_SetDeviceState(DS_Ready, DSS_None);
		}
		// Contactors commutation
		else
		{
			if(CONTROL_TimeCounter >= (CONTROL_CommutationStartTime + DataTable[REG_CONTACTORS_COMM_DELAY_MS]))
			{
				switch(CONTROL_SubState)
				{
					case DSS_AwaitingContactorsQgUP:
						CONTROL_CheckContactorsStates_macro(CT_Qg_UP);
						break;
					case DSS_AwaitingContactorsQgUPRev:
						CONTROL_CheckContactorsStates_macro(CT_Qg_UP_REV);
						break;
					case DSS_AwaitingContactorsQgDOWN:
						CONTROL_CheckContactorsStates_macro(CT_Qg_DOWN);
						break;
					case DSS_AwaitingContactorsQgDOWNRev:
						CONTROL_CheckContactorsStates_macro(CT_Qg_DOWN_REV);
						break;
						//
					case DSS_AwaitingContactorsVcesatUP:
						CONTROL_CheckContactorsStates_macro(CT_Vcesat_UP);
						break;
					case DSS_AwaitingContactorsVcesatUPRev:
						CONTROL_CheckContactorsStates_macro(CT_Vcesat_UP_REV);
						break;
					case DSS_AwaitingContactorsVcesatDOWN:
						CONTROL_CheckContactorsStates_macro(CT_Vcesat_DOWN);
						break;
					case DSS_AwaitingContactorsVcesatDOWNRev:
						CONTROL_CheckContactorsStates_macro(CT_Vcesat_DOWN_REV);
						break;
						//
					case DSS_AwaitingContactorsVsdUP:
						CONTROL_CheckContactorsStates_macro(CT_Vsd_UP);
						break;
					case DSS_AwaitingContactorsVsdUPRev:
						CONTROL_CheckContactorsStates_macro(CT_Vsd_UP_REV);
						break;
					case DSS_AwaitingContactorsVsdDOWN:
						CONTROL_CheckContactorsStates_macro(CT_Vsd_DOWN);
						break;
					case DSS_AwaitingContactorsVsdDOWNRev:
						CONTROL_CheckContactorsStates_macro(CT_Vsd_DOWN_REV);
						break;
						//
					case DSS_AwaitingContactorsRdsonUP:
						CONTROL_CheckContactorsStates_macro(CT_Rdson_UP);
						break;
					case DSS_AwaitingContactorsRdsonUPRev:
						CONTROL_CheckContactorsStates_macro(CT_Rdson_UP_REV);
						break;
					case DSS_AwaitingContactorsRdsonDOWN:
						CONTROL_CheckContactorsStates_macro(CT_Rdson_DOWN);
						break;
					case DSS_AwaitingContactorsRdsonDOWNRev:
						CONTROL_CheckContactorsStates_macro(CT_Rdson_DOWN_REV);
						break;
						//
					case DSS_AwaitingContactorsVfUP:
						CONTROL_CheckContactorsStates_macro(CT_Vf_UP);
						break;
					case DSS_AwaitingContactorsVfUPRev:
						CONTROL_CheckContactorsStates_macro(CT_Vf_UP_REV);
						break;
					case DSS_AwaitingContactorsVfDOWN:
						CONTROL_CheckContactorsStates_macro(CT_Vf_DOWN);
						break;
					case DSS_AwaitingContactorsVfDOWNRev:
						CONTROL_CheckContactorsStates_macro(CT_Vf_DOWN_REV);
						break;
					default:
						break;
				}
			}
		}
	}
	//
	// Pressure sensing & Safety circuit processor
	if((CONTROL_State == DS_InProcess) || (CONTROL_State == DS_Ready))
	{
		if((Conv_PressureADCVtoBar() < DataTable[REG_PRESSURE_THRESHOLD]) || (!LL_IsSelftestPinOk()))
		{
			CONTROL_SetDeviceState(DS_Fault, DSS_AwaitingResetToDefault);
			DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
			DataTable[REG_FAULT_REASON] = LL_IsSelftestPinOk() ? DF_LOW_PRESSURE : DF_SAFETY_ERROR;
		}
	}
	//
	// Reset to default commutation processor
	if(CONTROL_SubState == DSS_AwaitingResetToDefault)
	{
		if(CONTROL_CommutationStartTime == 0)
			CONTROL_CommutationStartTime = CONTROL_TimeCounter;
		// При штатной работе отключаем силовые блоки и подключаем PE без задержки
		if((CONTROL_State != DS_Fault) && (CONTROL_State != DS_Disabled))
		{
			COMM_DisconnectAll();
			CONTROL_SetDeviceSubState(DSS_None);
		}
		// При Fault ожидаем задержку до отключения силовых блоков и подключения PE
		else if(CONTROL_TimeCounter >= (CONTROL_CommutationStartTime + DataTable[REG_DFLT_COMM_DELAY_MS]))
		{
			COMM_DisconnectAll();
			CONTROL_SetDeviceSubState(DSS_None);
			CONTROL_CommutationStartTime = 0;
		}
	}
	//
	// Indication processor
	if((CONTROL_State == DS_Fault) || (CONTROL_State == DS_Disabled))
	{
		if(CONTROL_TimeCounter >= (CONTROL_IndBlinkStartTime + TIME_FAULT_LED_BLINK))
		{
			LL_ToggleIndication();
			CONTROL_IndBlinkStartTime = CONTROL_TimeCounter;
		}
	}
	else if(CONTROL_State == DS_InProcess)
		LL_SetStateIndication(TRUE);
	else
		LL_SetStateIndication(FALSE);
}
//-----------------------------------------------

void CONTROL_CheckContactorsStates(const Int8U CommArray[], Int8U Length)
{
	Int8U ErrorCode = ZcRD_CommutationCheck((Int8U *)CommArray, Length);
	if(ErrorCode != COMM_CHECK_NO_ERROR)
	{
		CONTROL_SetDeviceState(DS_Fault, DSS_None);
		DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
		DataTable[REG_FAULT_REASON] = DF_CONTACTOR_COMMUTATION_FAULT;
		DataTable[REG_PROBLEM] = ErrorCode;
	}
	else
	{
		CONTROL_SetDeviceState(DS_Ready, DSS_None);
		DataTable[REG_OP_RESULT] = OPRESULT_OK;
	}
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

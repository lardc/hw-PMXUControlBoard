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
#include "Constraints.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = DSS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
static Boolean CONTROL_ContactorsCheck;
Int16U LastActionID = ACT_COMM_PE;
Int16U LastDUTposition = DUT_POS1;
DevType LastDevCase = SC_Type_MIAA;
bool FPledForcedLight = false;

// Forward functions
//
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_LogicProcess();
void CONTROL_PressureCheck();
void CONTROL_SafetyCheck();
bool CONTROL_CheckContactors(DevType DevCase, Int16U ActionID, Int16U DUTPosition);
void CONTROL_CheckContactorsProcess();

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
	// Считывание значений счетчиков из EEPROM
	ZcRD_RestoreCountersFromEPROM();
}
//------------------------------------------

void CONTROL_Idle()
{
	CONTROL_LogicProcess();
	SELFTEST_Process();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, DSS_None);
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

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetOutputRegisters();
	CONTROL_SetDeviceState(DS_None, DSS_None);
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
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
				CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCTUP);
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				COMM_SwitchToPE();
				LL_SetStateIndication(false);
				LastActionID = ACT_COMM_PE;

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

		case ACT_SET_ACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
				CONTROL_SetDeviceState(DS_SafetyActive, DSS_None);
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		case ACT_SET_INACTIVE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				LL_SetStateIndication(false);
				CONTROL_SetDeviceState(DS_Enabled, DSS_None);
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		// Commutations
		case ACT_COMM_PE:
		case ACT_COMM_ICES:
		case ACT_COMM_VCESAT:
		case ACT_COMM_VF:
		case ACT_COMM_QG:
		case ACT_COMM_NO_PE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
			{
				COMM_Commutate(ActionID, DataTable[REG_DUT_POSITION], DataTable[REG_DEV_CASE]);

				LastActionID = ActionID;
				LastDUTposition = DataTable[REG_DUT_POSITION];
				LastDevCase = DataTable[REG_DEV_CASE];

				if(CONTROL_CheckContactors(LastDevCase, LastActionID, LastDUTposition))
					CONTROL_SetDeviceState(CONTROL_State, DSS_None);
				else
				{
					CONTROL_SwitchToFault(DF_CONTACTOR_FAULT);
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					LastActionID = ACT_COMM_PE;

					COMM_SwitchToPE();
				}
			}
			else if(CONTROL_State == DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_SELFTEST:
			if(CONTROL_State == DS_Enabled)
			{
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
				CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCTUP);
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
	CONTROL_CheckContactorsProcess();
	CONTROL_PressureCheck();
	CONTROL_SafetyCheck();
}
//-----------------------------------------------

void CONTROL_CheckContactorsProcess()
{
	if(CONTROL_State != DS_InSelfTest && CONTROL_State != DS_Fault && CONTROL_State != DS_None)
	{
		if(!CONTROL_CheckContactors(LastDevCase, LastActionID, LastDUTposition))
		{
			CONTROL_SwitchToFault(DF_CONTACTOR_FAULT);
			DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
			LastActionID = ACT_COMM_PE;

			COMM_SwitchToPE();
		}
	}
}
//-----------------------------------------------

bool CONTROL_CheckContactorsStates(const Int8U CommArray[], Int8U Length)
{
	Int8U ErrorCode = ZcRD_CommutationCheck((Int8U *)CommArray, Length);

	if(ErrorCode != COMM_CHECK_NO_ERROR)
	{
		DataTable[REG_FAILED_CONTACTOR] = ErrorCode;
		return false;
	}

	return true;
}
//-----------------------------------------------

void CONTROL_CheckContactorsCounter()
{
	for(Int8U i = 0; i < NUM_CONTACTOR_COMMUTATIONS; i++)
	{
		if(ZcRD_ContactorsCommCounter[i] >= DataTable[REG_MAX_CONT_COMMUTATIONS])
		{
			ZcRD_ContactorsCommCounter[i] = 0;
			CONTROL_ContactorsCheck = TRUE;
			DataTable[REG_PROBLEM] = i + 1;
			return;
		}
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

void CONTROL_HandleExternalLamp(bool Forced)
{
	static Int64U FPLampCounter = 0;

	if(CONTROL_State == DS_Fault)
	{
		if(++FPLampCounter > TIME_FP_LED_FAULT_BLINK)
		{
			LL_ToggleIndication();
			FPLampCounter = 0;
		}
	}
	else
	{
		if(CONTROL_State == DS_None && FPLampCounter)
		{
			LL_SetStateIndication(false);
			FPLampCounter = 0;
		}

		if(CONTROL_State != DS_None)
		{
			if(Forced)
			{
				LL_SetStateIndication(true);
				FPLampCounter = CONTROL_TimeCounter + TIME_FP_LED_ON_STATE;
			}
			else
			{
				if(CONTROL_TimeCounter >= FPLampCounter)
					LL_SetStateIndication(false);
			}
		}
	}
}
//-----------------------------------------------

void CONTROL_PressureCheck()
{
	DataTable[REG_PRESSURE] = Conv_PressureADCVtoBar();

	if(CONTROL_State != DS_None)
	{
		if(DataTable[REG_PRESSURE] < DataTable[REG_PRESSURE_THRESHOLD])
		{
			CONTROL_SwitchToFault(DF_LOW_PRESSURE);
			DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
			LastActionID = ACT_COMM_PE;

			COMM_SwitchToPE();
		}
	}
}
//-----------------------------------------------

void CONTROL_SafetyCheck()
{
	if(DataTable[REG_SAFETY_ACTIVE])
	{
		if(LL_IsSafetyTrig())
		{
			if(CONTROL_State == DS_SafetyActive)
				CONTROL_SetDeviceState(DS_SafetyTrig, DSS_None);

			if(COMM_State != COMM_Def)
			{
				DELAY_MS(SAFETY_DELAY);
				COMM_SwitchToPE();
				FPledForcedLight = true;
				LastActionID = ACT_COMM_PE;
				DELAY_MS(COMM_DELAY_MS);
				FPledForcedLight = false;
			}
		}
	}
}
//-----------------------------------------------

bool CONTROL_CheckContactors(DevType DevCase, Int16U ActionID, Int16U DUTPosition)
{
	switch(ActionID)
	{
		case ACT_COMM_PE:
			return CONTROL_CheckContactorsStates_macro(CT_DFLT_Contactors);
			break;

		case ACT_COMM_NO_PE:
			return CONTROL_CheckContactorsStates_macro(CT_NO_PE);
			break;

		case ACT_COMM_ICES:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					return CONTROL_CheckContactorsStates_macro(CT_Ices_SS);
					break;

				case SC_Type_MISV:
					return CONTROL_CheckContactorsStates_macro(CT_Ices_Pos2);
					break;

				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Ices_MISM2_CH_1 : CT_Ices_MISM2_CH_2));
					break;

				default:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Ices_Pos1 : CT_Ices_Pos2));
					break;
			}
			break;

		case ACT_COMM_VCESAT:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					return CONTROL_CheckContactorsStates_macro(CT_Vcesat_SS);
					break;

				case SC_Type_MISV:
					return CONTROL_CheckContactorsStates_macro(CT_Vcesat_Pos2);
					break;

				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vcesat_MISM2_CH_1 : CT_Vcesat_MISM2_CH_2));
					break;

				default:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vcesat_Pos1 : CT_Vcesat_Pos2));
					break;
			}
			break;

		case ACT_COMM_VF:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					return CONTROL_CheckContactorsStates_macro(CT_Vf_SS);
					break;

				case SC_Type_MISV:
					return CONTROL_CheckContactorsStates_macro(CT_Vf_Pos2);
					break;

				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vf_MISM2_CH_1 : CT_Vf_MISM2_CH_2));
					break;

				default:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vf_Pos1 : CT_Vf_Pos2));
					break;
			}
			break;

		case ACT_COMM_QG:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					return CONTROL_CheckContactorsStates_macro(CT_Qg_SS);
					break;

				case SC_Type_MISV:
					return CONTROL_CheckContactorsStates_macro(CT_Qg_Pos2);
					break;

				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Qg_MISM2_CH_1 : CT_Qg_MISM2_CH_2));
					break;

				default:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Qg_Pos1 : CT_Qg_Pos2));
					break;
			}
			break;
	}

	return false;
}
//-----------------------------------------------

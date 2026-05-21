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
#include "CommutationTable.h"
#include "Commutator.h"
#include "ZcRegistersDriver.h"
#include "Converter.h"
#include "Constraints.h"
#include "SaveToFlash.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = DSS_None;
static Boolean CycleActive = false;
static Boolean RequestSaveToFlash = FALSE;
volatile Int64U CONTROL_TimeCounter = 0;
static Boolean CONTROL_ContactorsCheck;
Int16U LastActionID = ACT_COMM_PE;
Int16U LastDUTposition = DUT_POS1;
DevType LastDevCase = SC_Type_MIAA;
bool FPledForcedLight = false;
static bool PrevSafetyTrig = false;
static volatile bool SafetyFlushPending = false;
volatile Int16U CONTROL_DiagCounter = 0;
//
volatile float CONTROL_DiagData[VALUES_DIAG_SIZE];

// Forward functions
//
bool CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_LogicProcess();
void CONTROL_PressureCheck();
void CONTROL_SafetyCheck();
void CONTROL_SafetyIrqTick();
bool CONTROL_CheckContactors(DevType DevCase, Int16U ActionID, Int16U DUTPosition);
void CONTROL_CheckContactorsProcess();
void CONTROL_InitStoragePointers();

// Functions
//
void CONTROL_Init()
{
	// Конфигурация EndPoint
	Int16U FEPIndexes[FEP_COUNT] = {EP_DiagData};
	Int16U FEPSized[FEP_COUNT] = {VALUES_DIAG_SIZE};
	pInt16U FEPCounters[FEP_COUNT] = {(pInt16U)&CONTROL_DiagCounter};
	pFloat32 FEPDatas[FEP_COUNT] = {(pFloat32)&CONTROL_DiagData};

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_NID, 0);
	// Инициализация Device Profile и EndPoint
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitFEPService(FEPIndexes, FEPSized, FEPCounters, FEPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
	// Инициализация указателей на счетчики и сами счетчики
	CONTROL_InitStoragePointers();
	STF_LoadCounters();
}
//------------------------------------------

void CONTROL_Idle()
{
	if (CONTROL_TimeCounter - CT_SaveTimer >= CT_SAVE_TIMEOUT)
	{
		STF_SaveCounterData();
		CT_SaveTimer = CONTROL_TimeCounter;
	}

	if (RequestSaveToFlash)
	{
		RequestSaveToFlash = FALSE;
		STF_SaveDiagData();
	}

	CONTROL_LogicProcess();

	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_SaveLastRequest(Int16U ActionID)
{
	DataTable[REG_LAST_CMD] = ActionID;
	DataTable[REG_LAST_POS] = DataTable[REG_DUT_POSITION];
	DataTable[REG_LAST_CASE] = DataTable[REG_DUT_CASE];
	DataTable[REG_LAST_TYPE] = DataTable[REG_DUT_SCHEME];
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SaveLastRequest(LastActionID);
	COMM_SwitchToPE();
	LL_SetStateSFT_ENABLE(true);
	LastActionID = ACT_COMM_PE;
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

void CONTROL_InitStoragePointers()
{
	Int16U idx = 0;

	for (Int16U i = 0; i < INNER_COMMUTATION_TABLE_SIZE; ++i)
		STF_AssignCounterPointer(i, (Int32U)&CycleCounters[i]);

	STF_AssignPointer(idx++, (Int32U)&CONTROL_State);
	STF_AssignPointer(idx++, (Int32U)&LastActionID);
	STF_AssignPointer(idx++, (Int32U)&LastDUTposition);
	STF_AssignPointer(idx++, (Int32U)&LastDevCase);
	STF_AssignPointer(idx++, (Int32U)&DataTable[REG_FAULT_REASON]);
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
				LL_SetStateSFT_ENABLE(false);
				CONTROL_SetDeviceState(DS_Enabled, DSS_None);
			}
			else if(CONTROL_State != DS_Enabled)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
			{
				COMM_SwitchToPE();
				LL_SetStateFPLed(false);
				LastActionID = ACT_COMM_PE;

				CONTROL_SetDeviceState(DS_None, DSS_None);
			}
			else if(CONTROL_State != DS_None)
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_CLR_FAULT:
			if(CONTROL_State == DS_Fault)
			{
				COMM_SwitchToPE();
				LL_SetStateSFT_ENABLE(false);
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
				LL_SetStateFPLed(false);
				CONTROL_SetDeviceState(DS_Enabled, DSS_None);
			}
			else
				*pUserError = ERR_DEVICE_NOT_READY;
			break;

		// Commutations
		case ACT_COMM_PE:
		case ACT_COMM_ICES_OR_IRRM:
		case ACT_COMM_VCESAT:
		case ACT_COMM_VF:
		case ACT_COMM_NO_PE:
			if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive)
			{
				if(!COMM_ValidateRequest(ActionID, (Int16U)DataTable[REG_DUT_POSITION],
						(DevType)DataTable[REG_DUT_CASE], (Int16U)DataTable[REG_DUT_SCHEME]))
				{
					*pUserError = ERR_OPERATION_BLOCKED;
					break;
				}

				COMM_Commutate(ActionID, (Int16U)DataTable[REG_DUT_POSITION],
						(DevType)DataTable[REG_DUT_CASE], (Int16U)DataTable[REG_DUT_SCHEME]);

				LastActionID = ActionID;
				CONTROL_SaveLastRequest(ActionID);
				LastDUTposition = DataTable[REG_DUT_POSITION];
				LastDevCase = (DevType)DataTable[REG_DUT_CASE];

				if(CONTROL_CheckContactors(LastDevCase, LastActionID, LastDUTposition))
					CONTROL_SetDeviceState(CONTROL_State, DSS_None);
				else
				{
					CONTROL_SwitchToFault(DF_CONTACTOR_FAULT);
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
				}
			}
			else if(CONTROL_State == DS_None)
				*pUserError = ERR_DEVICE_NOT_READY;
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;

		case ACT_SET_COUNTER:
			CycleCounters[(Int16U)DataTable[REG_CNT_NUMBER]] = DataTable[REG_CNT_VALUE];
			break;

		case ACT_SAVE_COUNTERS:
			STF_SaveCounterData();
			break;

		case ACT_ERASE_COUNTERS:
			NFLASH_Unlock();
			STF_EraseCounterDataSector();
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
	if(CONTROL_State == DS_Enabled || CONTROL_State == DS_SafetyActive || CONTROL_State == DS_SafetyTrig)
	{
		if(!CONTROL_CheckContactors(LastDevCase, LastActionID, LastDUTposition))
		{
			CONTROL_SwitchToFault(DF_CONTACTOR_FAULT);
			DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
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
			LL_ToggleFPLed();
			FPLampCounter = 0;
		}
	}
	else
	{
		if(CONTROL_State == DS_None && FPLampCounter)
		{
			LL_SetStateFPLed(false);
			FPLampCounter = 0;
		}

		if(CONTROL_State != DS_None)
		{
			if(Forced)
			{
				LL_SetStateFPLed(true);
				FPLampCounter = CONTROL_TimeCounter + TIME_FP_LED_ON_STATE;
			}
			else
			{
				if(CONTROL_TimeCounter >= FPLampCounter)
					LL_SetStateFPLed(false);
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
		}
	}
}
//-----------------------------------------------

void CONTROL_SafetyCheck()
{
	if(SafetyFlushPending)
	{
		SafetyFlushPending = false;

		LL_SetStateSFT_ENABLE(true);
		LL_SafetyResetSPI1();
		COMM_State = COMM_Def;
		LastActionID = ACT_COMM_PE;

		if(DataTable[REG_SAFETY_ACTIVE])
		{
			if(CONTROL_State == DS_SafetyActive)
				CONTROL_SetDeviceState(DS_SafetyTrig, DSS_None);

			FPledForcedLight = true;
		}
	}
}
//-----------------------------------------------

void CONTROL_SafetyIrqTick()
{
	bool SafetyTrig = LL_IsSafetyTrig();

	if(SafetyTrig && !PrevSafetyTrig)
		SafetyFlushPending = true;

	PrevSafetyTrig = SafetyTrig;
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

		case ACT_COMM_ICES_OR_IRRM:
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

				case SC_Type_MDSV:
				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Ices_MISM2_CH_1 : CT_Ices_MISM2_CH_2));
					break;

				case SC_Type_MDFA_MDF2_SD:
				case SC_Type_MDA2:
					return CONTROL_CheckContactorsStates_macro(CT_Ices_Pos2_Inverse);

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

				case SC_Type_MDFA_MDF2_SD:
				case SC_Type_MDA2:
				case SC_Type_MDSV:
				case SC_Type_MDSM:
				case SC_Type_MDFA_MDF2_DD:
				case SC_Type_MDAA:
					return CONTROL_CheckContactorsStates_macro(CT_NO_PE);
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

				case SC_Type_MDSV:
				case SC_Type_MISM2_CH:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vf_MISM2_CH_1 : CT_Vf_MISM2_CH_2));
					break;

				case SC_Type_MDFA_MDF2_SD:
				case SC_Type_MDA2:
					return CONTROL_CheckContactorsStates_macro(CT_Vcesat_Pos2);

				default:
					return CONTROL_CheckContactorsStates_macro(((DUTPosition == DUT_POS1) ? CT_Vf_Pos1 : CT_Vf_Pos2));
					break;
			}
			break;

	}

	return false;
}
//-----------------------------------------------

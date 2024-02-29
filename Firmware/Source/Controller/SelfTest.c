// Header
//
#include "SelfTest.h"

// Includes
//
#include "Math.h"
#include "Controller.h"
#include "DataTable.h"
#include "Delay.h"
#include "LowLevel.h"
#include "CommutationTable.h"
#include "ZcRegistersDriver.h"
#include "Commutator.h"

// Definitions
//
#define ST_RELAY_DELAY_MS		50
#define ST_CONT_DELAY_MS		COMM_DELAY_MS

// Variables
//
Int8U RelaysBitArray[SPI1_ARRAY_LEN_RELAYS] = {0};
Int8U ContactorsBitArray[SPI1_ARRAY_LEN_RELAYS] = {0};
Int16U CommDelay = ST_RELAY_DELAY_MS;

// Functions prototypes
//
bool SELFTEST_Comm(pInt8U BitArray, pInt8U CommTable, Int16U TableLength, pFloat32 ErrorReg);
void SELFTTEST_CommSingleClose(pInt8U BitArray, pInt8U CommTable, Int16U CommNum, bool State);
void SELFTTEST_CommGroupClose(pInt8U BitArray, pInt8U CommTable, Int16U TableLength, bool State);
void SELFTEST_OpenAll();


// Functions
//
void SELFTEST_Process()
{
	if(CONTROL_State == DS_InSelfTest)
	{
		if(CONTROL_SubState == DataTable[REG_ST_STOP_STAGE])
			CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_Finish);

		IsCommutation = true;
		SELFTEST_OpenAll();

		switch(CONTROL_SubState)
		{
			case DSS_SelfTest_LCTUP:
				CommDelay = ST_RELAY_DELAY_MS;

				if(!SELFTEST_Comm((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_LCTU1, sizeof(CT_ST_LCTU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCTUP;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCTUN);
				break;

			case DSS_SelfTest_LCTUN:
				if(!SELFTEST_Comm((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_LCTU2, sizeof(CT_ST_LCTU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCTUN;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_PE1);
				break;

			case DSS_SelfTest_PE1:
				if(!SELFTEST_Comm((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_PE1, sizeof(CT_ST_PE1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_PE1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_PE2);
				break;

			case DSS_SelfTest_PE2:
				if(!SELFTEST_Comm((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_PE2, sizeof(CT_ST_PE2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_PE2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCSU1);
				break;

			case DSS_SelfTest_LCSU1:
				CommDelay = ST_CONT_DELAY_MS;

				SELFTTEST_CommGroupClose((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_BUS1_2, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&ContactorsBitArray, (pInt8U)&CT_ST_LCSU1, sizeof(CT_ST_LCSU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCSU1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCSU2);
				break;

			case DSS_SelfTest_LCSU2:
				SELFTTEST_CommGroupClose((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_BUS1_2, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&ContactorsBitArray, (pInt8U)&CT_ST_LCSU2, sizeof(CT_ST_LCSU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCSU2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_TOCU1);
				break;

			case DSS_SelfTest_TOCU1:
				SELFTTEST_CommGroupClose((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_BUS1_3, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&ContactorsBitArray, (pInt8U)&CT_ST_TOCU1, sizeof(CT_ST_TOCU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_TOCU1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_TOCU2);
				break;

			case DSS_SelfTest_TOCU2:
				SELFTTEST_CommGroupClose((pInt8U)&RelaysBitArray, (pInt8U)&CT_ST_BUS1_3, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&ContactorsBitArray, (pInt8U)&CT_ST_TOCU2, sizeof(CT_ST_TOCU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_TOCU2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_Finish);
				break;

			case DSS_SelfTest_Finish:
				COMM_SwitchToPE();
				DELAY_MS(ST_CONT_DELAY_MS);
				IsCommutation = false;

				CONTROL_SetDeviceState(DS_Enabled, DSS_None);
				break;

			default:
				break;
		}
	}
}
//-----------------------------------------------

bool SELFTEST_Comm(pInt8U BitArray, pInt8U CommTable, Int16U TableLength, pFloat32 ErrorReg)
{
	bool CommPositionCorrect;
	Int8U CopiedCommTable[5];
	Int16U IndexCouter = 0;
	// Close relays
	//
	SELFTTEST_CommGroupClose(BitArray, CommTable, TableLength, true);

	DELAY_MS(CommDelay);

	// Check relays
	//
	for(int i = 0; i < TableLength; i++)
	{
		CommPositionCorrect = (InnerCommutationTable[CommTable[i]].Node == CONTACTOR) ? CONTROL_CheckContactorsStates_macro(CommTable) : true;

		if(!LL_CheckTestCurrent() || !CommPositionCorrect)
		{
			*ErrorReg = i;
			return false;
		}

		// Open one relay
		SELFTTEST_CommSingleClose(BitArray, CommTable, i, false);
		DELAY_MS(CommDelay);

		//Copy CommTable without i contactor
		//
		IndexCouter = 0;
		for(int j = 0; j < TableLength; j++)
		{
			if(j != i)
				CopiedCommTable[IndexCouter++] = CommTable[j];
		}

		CommPositionCorrect = (InnerCommutationTable[CommTable[i]].Node == CONTACTOR) ? CONTROL_CheckContactorsStates_macro(CopiedCommTable) : true;

		if(LL_CheckTestCurrent() || !CommPositionCorrect)
		{
			*ErrorReg = i;
			return false;
		}

		// Close one relay
		SELFTTEST_CommSingleClose(BitArray, CommTable, i, true);
		DELAY_MS(CommDelay);
	}

	return true;
}
//-----------------------------------------------

void SELFTTEST_CommSingleClose(pInt8U BitArray, pInt8U CommTable, Int16U CommNum, bool State)
{
	if(InnerCommutationTable[(uint8_t)CommTable[CommNum]].Type == CT_NormalOpened)
		ZcRD_OutputValuesCompose((uint8_t)CommTable[CommNum], State, BitArray);
	else
		ZcRD_OutputValuesCompose((uint8_t)CommTable[CommNum], !State, BitArray);

	ZcRD_WriteSPI1Comm(BitArray, InnerCommutationTable[(uint8_t)CommTable[CommNum]].Node);
}
//-----------------------------------------------

void SELFTTEST_CommGroupClose(pInt8U BitArray, pInt8U CommTable, Int16U TableLength, bool State)
{
	for(int i = 0; i < TableLength; i++)
		SELFTTEST_CommSingleClose(BitArray, CommTable, i, State);
}
//-----------------------------------------------

void SELFTEST_OpenAll()
{
	SELFTTEST_CommGroupClose((pInt8U)&RelaysBitArray, (pInt8U)&CT_AllRelays, sizeof(CT_AllRelays), false);
	SELFTTEST_CommGroupClose((pInt8U)&ContactorsBitArray, (pInt8U)&CT_AllContactors, sizeof(CT_AllContactors), false);

	DELAY_MS(ST_CONT_DELAY_MS);
}
//-----------------------------------------------

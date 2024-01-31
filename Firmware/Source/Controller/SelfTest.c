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

// Functions prototypes
//
bool SELFTEST_Comm(pInt8U CommTable, Int16U TableLength, pFloat32 ErrorReg);
void SELFTTEST_CommSingleClose(pInt8U CommTable, Int16U CommNum, bool State);
void SELFTTEST_CommGroupClose(pInt8U CommTable, Int16U TableLength, bool State);
void SELFTEST_ResetCommToDefault();


// Functions
//
void SELFTEST_Process()
{
	if(CONTROL_State == DS_InSelfTest)
	{
		SELFTEST_ResetCommToDefault();

		switch(CONTROL_SubState)
		{
			case DSS_SelfTest_LCTUP:
				if(!SELFTEST_Comm((pInt8U)&CT_ST_LCTU1, sizeof(CT_ST_LCTU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCTUP;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCTUN);
				break;

			case DSS_SelfTest_LCTUN:
				if(!SELFTEST_Comm((pInt8U)&CT_ST_LCTU2, sizeof(CT_ST_LCTU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCTUN;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_PE1);
				break;

			case DSS_SelfTest_PE1:
				if(!SELFTEST_Comm((pInt8U)&CT_ST_PE1, sizeof(CT_ST_PE1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_PE1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_PE2);
				break;

			case DSS_SelfTest_PE2:
				if(!SELFTEST_Comm((pInt8U)&CT_ST_PE2, sizeof(CT_ST_PE2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_PE2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCSU1);
				break;

			case DSS_SelfTest_LCSU1:
				SELFTTEST_CommGroupClose((pInt8U)&CT_ST_BUS1_3, sizeof(CT_ST_BUS1_3), true);

				if(!SELFTEST_Comm((pInt8U)&CT_ST_LCSU1, sizeof(CT_ST_LCSU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCSU1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_LCSU2);
				break;

			case DSS_SelfTest_LCSU2:
				SELFTTEST_CommGroupClose((pInt8U)&CT_ST_BUS1_2, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&CT_ST_LCSU2, sizeof(CT_ST_LCSU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_LCSU2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_TOCU1);
				break;

			case DSS_SelfTest_TOCU1:
				SELFTTEST_CommGroupClose((pInt8U)&CT_ST_BUS1_3, sizeof(CT_ST_BUS1_3), true);

				if(!SELFTEST_Comm((pInt8U)&CT_ST_TOCU1, sizeof(CT_ST_TOCU1), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_TOCU1;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_InSelfTest, DSS_SelfTest_TOCU2);
				break;

			case DSS_SelfTest_TOCU2:
				SELFTTEST_CommGroupClose((pInt8U)&CT_ST_BUS1_2, sizeof(CT_ST_BUS1_2), true);

				if(!SELFTEST_Comm((pInt8U)&CT_ST_TOCU2, sizeof(CT_ST_TOCU2), (pFloat32)&DataTable[REG_FAILED_CONTACTOR]))
				{
					DataTable[REG_FAILED_COMMUTATION] = DSS_SelfTest_TOCU2;
					DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
					CONTROL_SwitchToFault(DF_SELFT_TEST);
				}
				else
					CONTROL_SetDeviceState(DS_Enabled, DSS_None);
				break;

			default:
				break;
		}
	}
}
//-----------------------------------------------

bool SELFTEST_Comm(pInt8U CommTable, Int16U TableLength, pFloat32 ErrorReg)
{
	// Close relays
	//
	SELFTTEST_CommGroupClose(CommTable, TableLength, true);

	DELAY_MS(COMM_DELAY_MS);

	// Check relays
	//
	for(int i = 0; i < TableLength; i++)
	{
		if(!LL_CheckTestCurrent())
		{
			*ErrorReg = i;
			return false;
		}

		// Open one relay
		SELFTTEST_CommSingleClose(CommTable, i, false);
		DELAY_MS(COMM_DELAY_MS);

		if(LL_CheckTestCurrent())
		{
			*ErrorReg = i;
			return false;
		}

		// Close one relay
		SELFTTEST_CommSingleClose(CommTable, i, true);
		DELAY_MS(COMM_DELAY_MS);
	}

	return true;
}
//-----------------------------------------------

void SELFTTEST_CommSingleClose(pInt8U CommTable, Int16U CommNum, bool State)
{
	Int8U RelayArray[SPI1_ARRAY_LEN_RELAYS] = {0};

	if(InnerCommutationTable[(uint8_t)CommTable[CommNum]].Type == CT_NormalOpened)
		ZcRD_OutputValuesCompose((uint8_t)CommTable[CommNum], State, &RelayArray[0]);
	else
		ZcRD_OutputValuesCompose((uint8_t)CommTable[CommNum], ~State, &RelayArray[0]);

	ZcRD_WriteSPI1Comm(RelayArray, InnerCommutationTable[(uint8_t)CommTable[CommNum]].Node);
}
//-----------------------------------------------

void SELFTTEST_CommGroupClose(pInt8U CommTable, Int16U TableLength, bool State)
{
	for(int i = 0; i < TableLength; i++)
		SELFTTEST_CommSingleClose(CommTable, i, State);
}
//-----------------------------------------------

void SELFTEST_ResetCommToDefault()
{
	Int8U RelayArray[SPI1_ARRAY_LEN_RELAYS] = {0};
	Int8U ContactorArray[SPI1_ARRAY_LEN_CONTACTORS] = {0};

	ZcRD_WriteSPI1Comm(RelayArray, RELAY);
	ZcRD_WriteSPI1Comm(ContactorArray, CONTACTOR);

	DELAY_MS(COMM_DELAY_MS);
}
//-----------------------------------------------

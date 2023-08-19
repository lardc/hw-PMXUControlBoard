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

// Variables
//
static Int8U FailedRelayNumber = SELFTEST_NO_BROKEN_RELAY;
static bool IsTestOk = TRUE;
static Int8U FailReason = DF_NONE;
// Functions
//
bool SELFTEST_RelayTest(Int8U BitDataArray[], Int8U CheckedRelaysArray[], Int8U CheckedRelaysLength)
{
	FailedRelayNumber = SELFTEST_NO_BROKEN_RELAY;
	IsTestOk = TRUE;
	for(Int8U i = 0; i < CheckedRelaysLength; i++)
	{
		if(LL_IsSelftestPinOk())
		{
			// Start relay opening test
			ZcRD_OutputValuesCompose(CheckedRelaysArray[i], FALSE, &BitDataArray[0]);
			DELAY_MS(COMM_RELAYS_DELAY_MS);
			if(LL_IsSelftestPinOk())
			{
				ZcRD_OutputValuesCompose(CheckedRelaysArray[i], TRUE, &BitDataArray[0]);
				FailedRelayNumber = CheckedRelaysArray[i];
				IsTestOk = FALSE;
				FailReason = DF_RELAY_SHORT;
				break;
			}
			ZcRD_OutputValuesCompose(CheckedRelaysArray[i], TRUE, &BitDataArray[0]);
		}
		else
		{
			FailedRelayNumber = CheckedRelaysArray[i];
			IsTestOk = FALSE;
			FailReason = DF_CHAIN_BREAK;
			break;
		}
	}
	return IsTestOk;
}
//-----------------------------------------------

void SELFTEST_Process()
{
	if(CONTROL_SubState == DSS_SelfTestProgress)
	{
		switch(CONTROL_STState)
		{
			case STS_PE1Check:
				ZcRD_CommutateConfig_macro(CT_ST_PE1);
				if(!SELFTEST_RelayTest_macro(CT_ST_PE1, CT_ST_RO_PE1))
				{
					DataTable[REG_SELF_TEST_FAILED_RELAY] = FailedRelayNumber;
					CONTROL_SwitchToFault(FailReason);
				}
				break;

			default:
				break;
		}
	}
}
//-----------------------------------------------


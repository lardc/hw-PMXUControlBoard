// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"
#include "ZcRegistersDriver.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch(ActionID)
	{
		case ACT_DBG_FP_LED:
			DBACT_ToggleFPLed();
			break;

		case ACT_DBG_SF_RED_LED:
			DBACT_ToggleSFRedLed();
			break;

		case ACT_DBG_SF_GRN_LED:
			DBACT_ToggleSFGreenLed();
			break;

		case ACT_DBG_WRITE_SPI:
			DBACT_WriteSPI();
			break;

		case ACT_DBG_SPI_RST:
			ZcRD_RegisterReset();
			break;

		case ACT_SF_EN:
			DBACT_ToggleSF_EN();
			break;

		case ACT_DBG_SELF_TEST_MEASURE:
			DBACT_SelfTestMeasure();
			break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------

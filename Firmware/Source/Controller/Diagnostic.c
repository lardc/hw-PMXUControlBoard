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
		case ACT_DBG_IND:
			DBACT_PulseIndication();
			break;

		case ACT_DBG_SAFETY:
			DBACT_IsSafetyOk();
			break;

		case ACT_DBG_SELFTEST:
			DBACT_IsSelftestOk();
			break;

		case ACT_DBG_WRITE_CONT:
			DBACT_WriteSPI1ContactorsRaw();
			break;

		case ACT_DBG_WRITE_REL:
			DBACT_WriteSPI1RelaysRaw();
			break;

		case ACT_DBG_READ_MAGNET_SEN:
			DBACT_ReadSPI2Raw();
			break;

		case ACT_DBG_MEAS_PRESSURE:
			DBACT_GetPressureADCVoltage();
			break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------

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

		case ACT_DBG_SFT_IN:
			DBACT_ReadSftIn();
			break;

		case ACT_DBG_SFT_ENABLE:
			DBACT_SftEnablePulse();
			break;

		case ACT_DBG_WRITE_SPI1:
			DBACT_WriteSPI1();
			break;

		case ACT_DBG_READ_MAGNET_SEN:
			DBACT_ReadSPI2Raw();
			break;

		case ACT_DBG_MEAS_PRESSURE:
			DBACT_GetPressureADCVoltage();
			break;

		case ACT_DBG_SPI_RST:
			DBACT_ResetSPI1();
			break;

		default:
			return false;
	}

	return true;
}
//-------------------------------------

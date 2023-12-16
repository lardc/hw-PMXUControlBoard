// -----------------------------------------
// Commutation logic
// ----------------------------------------

// Header
#include "Commutator.h"
//
#include "ZcRegistersDriver.h"
#include "DeviceObjectDictionary.h"
#include "CommutationTable.h"
#include "Global.h"
#include "DataTable.h"
#include "Delay.h"
#include "Constraints.h"

// Variables
//
// Functions
//
void COMM_SwitchToPE()
{
	ZcRD_WriteSPI1Contactors(CT_DFLT_Contactors);
	ZcRD_WriteSPI1Relays(CT_DFLT_Relays);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID, Int16U TopPosition)
{
	IsCommutation = true;

	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_SwitchToPE();
			break;

		case ACT_COMM_NO_PE:
			ZcRD_CommutateConfig_macro(CT_PE);
			break;

		case ACT_COMM_ICES:
			(TopPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_TOP) : ZcRD_CommutateConfig_macro(CT_Ices_BOT);
			break;

		case ACT_COMM_VCESAT:
			(TopPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vcesat_TOP) : ZcRD_CommutateConfig_macro(CT_Vcesat_BOT);
			break;

		case ACT_COMM_VF:
			(TopPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_TOP) : ZcRD_CommutateConfig_macro(CT_Vf_BOT);
			break;

		case ACT_COMM_QG:
			(TopPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Qg_TOP) : ZcRD_CommutateConfig_macro(CT_Qg_BOT);
			break;
	}

	DELAY_MS(COMM_DELAY_MS);

	IsCommutation = false;
}
// ----------------------------------------

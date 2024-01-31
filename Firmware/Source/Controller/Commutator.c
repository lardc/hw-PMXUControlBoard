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
	ZcRD_WriteSPI1Comm(CT_DFLT_Contactors, CONTACTOR);
	ZcRD_WriteSPI1Comm(CT_DFLT_Relays, RELAY);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID, Int16U DUTPosition)
{
	IsCommutation = true;

	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_SwitchToPE();
			break;

		case ACT_COMM_NO_PE:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			break;

		case ACT_COMM_ICES:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_Pos1) : ZcRD_CommutateConfig_macro(CT_Ices_Pos2);
			break;

		case ACT_COMM_VCESAT:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vcesat_Pos1) : ZcRD_CommutateConfig_macro(CT_Vcesat_Pos2);
			break;

		case ACT_COMM_VF:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_Pos1) : ZcRD_CommutateConfig_macro(CT_Vf_Pos2);
			break;

		case ACT_COMM_QG:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Qg_Pos1) : ZcRD_CommutateConfig_macro(CT_Qg_Pos2);
			break;
	}

	DELAY_MS(COMM_DELAY_MS);

	IsCommutation = false;
}
// ----------------------------------------

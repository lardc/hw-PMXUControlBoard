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

// Variables
//
// Functions
//
void COMM_DisconnectAll()
{
	ZcRD_WriteSPI1Contactors(CT_DFLT_Contactors);
	ZcRD_WriteSPI1Relays(CT_DFLT_Relays);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID, bool TopPosition)
{
	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_DisconnectAll();
			break;

		case ACT_COMM_ICES:
			TopPosition ? ZcRD_CommutateConfig_macro(CT_Ices_UP) : ZcRD_CommutateConfig_macro(CT_Ices_DOWN);
			break;

		case ACT_COMM_VCESAT:
			TopPosition ? ZcRD_CommutateConfig_macro(CT_Vcesat_UP) : ZcRD_CommutateConfig_macro(CT_Vcesat_DOWN);
			break;

		case ACT_COMM_VF:
			TopPosition ? ZcRD_CommutateConfig_macro(CT_Vf_UP) : ZcRD_CommutateConfig_macro(CT_Vf_DOWN);
			break;

		case ACT_COMM_QG:
			TopPosition ? ZcRD_CommutateConfig_macro(CT_Qg_UP) : ZcRD_CommutateConfig_macro(CT_Qg_DOWN);
			break;
	}
}
// ----------------------------------------

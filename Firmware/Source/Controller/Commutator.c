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

void COMM_Commutate(Int16U ActionID)
{
	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_DisconnectAll();
			break;

		case ACT_COMM_ICES_UP:
			ZcRD_CommutateConfig(CT_Ices_UP);
			break;

		case ACT_COMM_ICES_DOWN:
			ZcRD_CommutateConfig(CT_Ices_DOWN);
			break;

		case ACT_COMM_IDSS_UP:
			ZcRD_CommutateConfig(CT_Idds_UP);
			break;

		case ACT_COMM_IDSS_DOWN:
			ZcRD_CommutateConfig(CT_Idds_DOWN);
			break;

		case ACT_COMM_IR_UP:
			ZcRD_CommutateConfig(CT_Ir_UP);
			break;

		case ACT_COMM_IR_DOWN:
			ZcRD_CommutateConfig(CT_Ir_DOWN);
			break;

		case ACT_COMM_QG_UP:
			ZcRD_CommutateConfig(CT_Qg_UP);
			break;

		case ACT_COMM_QG_UP_REV:
			ZcRD_CommutateConfig(CT_Qg_UP_REV);
			break;

		case ACT_COMM_QG_DOWN:
			ZcRD_CommutateConfig(CT_Qg_DOWN);
			break;

		case ACT_COMM_QG_DOWN_REV:
			ZcRD_CommutateConfig(CT_Qg_DOWN_REV);
			break;

		case ACT_COMM_VCESAT_UP:
			ZcRD_CommutateConfig(CT_Vcesat_UP);
			break;

		case ACT_COMM_VCESAT_UP_REV:
			ZcRD_CommutateConfig(CT_Vcesat_UP_REV);
			break;

		case ACT_COMM_VCESAT_DOWN:
			ZcRD_CommutateConfig(CT_Vcesat_DOWN);
			break;

		case ACT_COMM_VCESAT_DOWN_REV:
			ZcRD_CommutateConfig(CT_Vcesat_DOWN_REV);
			break;

		case ACT_COMM_VSD_UP:
			ZcRD_CommutateConfig(CT_Vsd_UP);
			break;

		case ACT_COMM_VSD_UP_REV:
			ZcRD_CommutateConfig(CT_Vsd_UP_REV);
			break;

		case ACT_COMM_VSD_DOWN:
			ZcRD_CommutateConfig(CT_Vsd_DOWN);
			break;

		case ACT_COMM_VSD_DOWN_REV:
			ZcRD_CommutateConfig(CT_Rdson_DOWN_REV);
			break;

		case ACT_COMM_RDSON_UP:
			ZcRD_CommutateConfig(CT_Rdson_UP);
			break;

		case ACT_COMM_RDSON_UP_REV:
			ZcRD_CommutateConfig(CT_Rdson_UP_REV);
			break;

		case ACT_COMM_RDSON_DOWN:
			ZcRD_CommutateConfig(CT_Rdson_DOWN);
			break;

		case ACT_COMM_RDSON_DOWN_REV:
			ZcRD_CommutateConfig(CT_Rdson_DOWN_REV);
			break;

		case ACT_COMM_VF_UP:
			ZcRD_CommutateConfig(CT_Vf_UP);
			break;

		case ACT_COMM_VF_UP_REV:
			ZcRD_CommutateConfig(CT_Vf_UP_REV);
			break;

		case ACT_COMM_VF_DOWN:
			ZcRD_CommutateConfig(CT_Vf_DOWN);
			break;

		case ACT_COMM_VF_DOWN_REV:
			ZcRD_CommutateConfig(CT_Vf_DOWN_REV);
			break;
	}
}
// ----------------------------------------


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
	ZcRD_WriteSPI1Contactors(0x0);
	ZcRD_WriteSPI1Relays(0x0);
}
// ----------------------------------------

void COMM_CommutateConfig(Int8U ConnArray[])
{
	Int64U RelayBits = 0x0;
	Int64U ContactorBits = 0x0;
	size_t n = (&ConnArray)[1] - ConnArray;
	for(uint8_t i = 0; i < n; i++)
	{
		if(InnerCommutationTable[ConnArray[i]].Type == RELAY)
			ZcRD_OutputValuesCompose(ConnArray[i], TRUE, &RelayBits);
		else
			ZcRD_OutputValuesCompose(ConnArray[i], TRUE, &ContactorBits);
	}
	ZcRD_WriteSPI1Relays(RelayBits);
	ZcRD_WriteSPI1Contactors((Int16U)ContactorBits);
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
			COMM_CommutateConfig(CT_Ices_UP);
			break;

		case ACT_COMM_ICES_DOWN:
			COMM_CommutateConfig(CT_Ices_DOWN);
			break;

		case ACT_COMM_IDSS_UP:
			COMM_CommutateConfig(CT_Idds_UP);
			break;

		case ACT_COMM_IDSS_DOWN:
			COMM_CommutateConfig(CT_Idds_DOWN);
			break;

		case ACT_COMM_IR_UP:
			COMM_CommutateConfig(CT_Ir_UP);
			break;

		case ACT_COMM_IR_DOWN:
			COMM_CommutateConfig(CT_Ir_DOWN);
			break;

		case ACT_COMM_QG_UP:
			COMM_CommutateConfig(CT_Qg_UP);
			break;

		case ACT_COMM_QG_UP_REV:
			COMM_CommutateConfig(CT_Qg_UP_REV);
			break;

		case ACT_COMM_QG_DOWN:
			COMM_CommutateConfig(CT_Qg_DOWN);
			break;

		case ACT_COMM_QG_DOWN_REV:
			COMM_CommutateConfig(CT_Qg_DOWN_REV);
			break;

		case ACT_COMM_VCESAT_UP:
			COMM_CommutateConfig(CT_Vcesat_UP);
			break;

		case ACT_COMM_VCESAT_UP_REV:
			COMM_CommutateConfig(CT_Vcesat_UP_REV);
			break;

		case ACT_COMM_VCESAT_DOWN:
			COMM_CommutateConfig(CT_Vcesat_DOWN);
			break;

		case ACT_COMM_VCESAT_DOWN_REV:
			COMM_CommutateConfig(CT_Vcesat_DOWN_REV);
			break;

		case ACT_COMM_VSD_UP:
			COMM_CommutateConfig(CT_Vsd_UP);
			break;

		case ACT_COMM_VSD_UP_REV:
			COMM_CommutateConfig(CT_Vsd_UP_REV);
			break;

		case ACT_COMM_VSD_DOWN:
			COMM_CommutateConfig(CT_Vsd_DOWN);
			break;

		case ACT_COMM_VSD_DOWN_REV:
			COMM_CommutateConfig(CT_Rdson_DOWN_REV);
			break;

		case ACT_COMM_RDSON_UP:
			COMM_CommutateConfig(CT_Rdson_UP);
			break;

		case ACT_COMM_RDSON_UP_REV:
			COMM_CommutateConfig(CT_Rdson_UP_REV);
			break;

		case ACT_COMM_RDSON_DOWN:
			COMM_CommutateConfig(CT_Rdson_DOWN);
			break;

		case ACT_COMM_RDSON_DOWN_REV:
			COMM_CommutateConfig(CT_Rdson_DOWN_REV);
			break;

		case ACT_COMM_VF_UP:
			COMM_CommutateConfig(CT_Vf_UP);
			break;

		case ACT_COMM_VF_UP_REV:
			COMM_CommutateConfig(CT_Vf_UP_REV);
			break;

		case ACT_COMM_VF_DOWN:
			COMM_CommutateConfig(CT_Vf_DOWN);
			break;

		case ACT_COMM_VF_DOWN_REV:
			COMM_CommutateConfig(CT_Vf_DOWN_REV);
			break;
	}
}
// ----------------------------------------


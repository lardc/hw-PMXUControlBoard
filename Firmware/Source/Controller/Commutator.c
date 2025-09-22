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
CommutationState COMM_State = COMM_Def;
Int32U CycleCounters[INNER_COMMUTATION_TABLE_SIZE] = {0};
Int64U CT_SaveTimer = 0; // Последняя отметка времени автосохранения

// Functions
//
void COMM_SwitchToPE()
{
	ZcRD_WriteSPI1Comm(CT_DFLT_Contactors, CONTACTOR);
	ZcRD_WriteSPI1Comm(CT_DFLT_Relays, RELAY);

	COMM_State = COMM_Def;
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID, Int16U DUTPosition, DevType DevCase)
{
	FPledForcedLight = true;

	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_SwitchToPE();
			break;

		case ACT_COMM_NO_PE:
			ZcRD_CommutateConfig_macro(CT_NO_PE);
			COMM_State = COMM_NoPE;
			break;

		case ACT_COMM_ICES:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					ZcRD_CommutateConfig_macro(CT_Ices_SS);
					break;

				case SC_Type_MISV:
					ZcRD_CommutateConfig_macro(CT_Ices_Pos2);
					break;

				case SC_Type_MDSV:
				case SC_Type_MISM2_CH:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_MISM2_CH_1) : ZcRD_CommutateConfig_macro(CT_Ices_MISM2_CH_2);
					break;

				case SC_Type_MDSM:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_MDSM_1) : ZcRD_CommutateConfig_macro(CT_Ices_MDSM_2);
					break;

				case SC_Type_MDF2:
				case SC_Type_MDA2:
					ZcRD_CommutateConfig_macro(CT_Ices_Pos2_Inverse);
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_Pos1) : ZcRD_CommutateConfig_macro(CT_Ices_Pos2);
					break;
			}

			COMM_State = COMM_Ices;
			break;

		case ACT_COMM_VCESAT:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					ZcRD_CommutateConfig_macro(CT_Vcesat_SS);
					break;

				case SC_Type_MISV:
					ZcRD_CommutateConfig_macro(CT_Vcesat_Pos2);
					break;

				case SC_Type_MISM2_CH:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vcesat_MISM2_CH_1) : ZcRD_CommutateConfig_macro(CT_Vcesat_MISM2_CH_2);
					break;

				case SC_Type_MDF2:
				case SC_Type_MDA2:
				case SC_Type_MDSV:
				case SC_Type_MDSM:
				case SC_Type_MDFA:
				case SC_Type_MDAA:
					ZcRD_CommutateConfig_macro(CT_NO_PE);
					COMM_State = COMM_NoPE;
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vcesat_Pos1) : ZcRD_CommutateConfig_macro(CT_Vcesat_Pos2);
					break;
			}
			if (COMM_State == COMM_NoPE)
				break;

			COMM_State = COMM_Ucesat;
			break;

		case ACT_COMM_VF:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					ZcRD_CommutateConfig_macro(CT_Vf_SS);
					break;

				case SC_Type_MISV:
					ZcRD_CommutateConfig_macro(CT_Vf_Pos2);
					break;

				case SC_Type_MDSV:
				case SC_Type_MISM2_CH:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_MISM2_CH_1) : ZcRD_CommutateConfig_macro(CT_Vf_MISM2_CH_2);
					break;

				case SC_Type_MDSM:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_MDSM_1) : ZcRD_CommutateConfig_macro(CT_Vf_MDSM_2);
					break;

				case SC_Type_MDF2:
				case SC_Type_MDA2:
					ZcRD_CommutateConfig_macro(CT_Vcesat_Pos2);
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_Pos1) : ZcRD_CommutateConfig_macro(CT_Vf_Pos2);
					break;
			}

			COMM_State = COMM_Uf;
			break;

		case ACT_COMM_QG:
			switch(DevCase)
			{
				case SC_Type_MIHV:
				case SC_Type_MIHM:
				case SC_Type_MISM2_SS_SD:
					ZcRD_CommutateConfig_macro(CT_Qg_SS);
					break;

				case SC_Type_MISV:
					ZcRD_CommutateConfig_macro(CT_Qg_Pos2);
					break;

				case SC_Type_MISM2_CH:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Qg_MISM2_CH_1) : ZcRD_CommutateConfig_macro(CT_Qg_MISM2_CH_2);
					break;

				case SC_Type_MDF2:
				case SC_Type_MDA2:
				case SC_Type_MDSV:
				case SC_Type_MDSM:
				case SC_Type_MDFA:
				case SC_Type_MDAA:
					ZcRD_CommutateConfig_macro(CT_NO_PE);
					COMM_State = COMM_NoPE;
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Qg_Pos1) : ZcRD_CommutateConfig_macro(CT_Qg_Pos2);
					break;
			}

			if (COMM_State == COMM_NoPE)
				break;

			COMM_State = COMM_Qg;
			break;
	}

	DELAY_MS(COMM_DELAY_MS);
	FPledForcedLight = false;
}
// ----------------------------------------

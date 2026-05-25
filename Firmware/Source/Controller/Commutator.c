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
Int64U CT_SaveTimer = 0;

// Forward declarations
//
static void COMM_DischargeBeforeIcesOrIrrm();
static Int16U COMM_GetCommDelayMs();

// Functions
//
static Int16U COMM_GetCommDelayMs()
{
	Int16U delay = (Int16U)DataTable[REG_CONTACTORS_COMM_DELAY_MS];

	return delay ? delay : (Int16U)COMM_DELAY_MS;
}
// ----------------------------------------

Int32U COMM_CalcModuleType()
{
	const Int32U CaseShift = 100;

	return ((Int32U)DataTable[REG_DUT_CASE] * CaseShift + (Int32U)DataTable[REG_DUT_SCHEME]);
}
// ----------------------------------------

static void COMM_DischargeBeforeIcesOrIrrm()
{
	const Int16U DischargeMs = 10;

	COMM_SwitchToPE();
	DELAY_MS(DischargeMs);
}
// ----------------------------------------

void COMM_SwitchToPE()
{
	ZcRD_WriteSPI1Comm(CT_DFLT_Contactors, CONTACTOR);
	ZcRD_WriteSPI1Comm(CT_DFLT_Relays, RELAY);

	COMM_State = COMM_Def;
}
// ----------------------------------------

bool COMM_ValidateRequest(Int16U ActionID, Int16U Position)
{
	ModuleTypes Module = (ModuleTypes)COMM_CalcModuleType();

	if(Position != DUT_POS1 && Position != DUT_POS2)
		return false;

	switch(ActionID)
	{
		case ACT_COMM_PE:
			return true;  // допустимо без проверки корпуса
		case ACT_COMM_NO_PE:
		case ACT_COMM_VCESAT:
			if(Position == DUT_POS1)
			{
				switch(Module)
				{
					case MIAA_CE:
					case MIAA_HB:
					case MIAA_LC:
					case MIDA_HB:
					case MIFA_HB:
					case MIFA_LC:
					case MIHA_HB:
					case MIHA_LC:
					case MIHM_SS:
					case MIHV_SS:
					case MISM_CH:
					case MISM_DS:
					case MISM_SS:
					case MISV_SS:
					case MIXM_HB:
					case MIXM_LR_LRD:
					case MIXV_HB:
						return true;
					default:
						return false;
				}
			}
			else if(Position == DUT_POS2)
			{
				switch(Module)
				{
					case MIAA_CE:
					case MIAA_HB:
					case MIAA_HC:
					case MIDA_HB:
					case MIFA_HB:
					case MIFA_HC:
					case MIHA_HB:
					case MIHA_HC:
					case MISM_DS:
					case MIXM_HB:
					case MIXV_HB:
						return true;
					default:
						return false;
				}
			}
			return false;

		case ACT_COMM_ICES_OR_IRRM:
		case ACT_COMM_VF:
			return true;

		default:
			return false;
	}
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	Int16U DUTPosition = DataTable[REG_DUT_POSITION];
	ModuleTypes Module = (ModuleTypes)COMM_CalcModuleType();
	DevType DevCase = 0; // заглушка
	(void)Module;
	(void)DevCase;

	if(COMM_State == COMM_IcesOrIrrm && ActionID != ACT_COMM_ICES_OR_IRRM)
		COMM_DischargeBeforeIcesOrIrrm();

	FPledForcedLight = true;

	switch(ActionID)
	{
		case ACT_COMM_PE:
		default:
			COMM_SwitchToPE();
			break;

		case ACT_COMM_NO_PE:
			ZcRD_CommutateConfig_macro(CT_DISCON_GND);
			COMM_State = COMM_NoPE;
			break;

		case ACT_COMM_ICES_OR_IRRM:
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

				case SC_Type_MDFA_MDF2_SD:
				case SC_Type_MDA2:
					ZcRD_CommutateConfig_macro(CT_Ices_Pos2_Inverse);
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Ices_Pos1) : ZcRD_CommutateConfig_macro(CT_Ices_Pos2);
					break;
			}

			COMM_State = COMM_IcesOrIrrm;
			break;

		case ACT_COMM_VCESAT:
			COMM_State = COMM_Ucesat;

			if(DUTPosition == DUT_POS1)
			{
				switch(Module)
				{
					case MIAA_CE:
					case MIAA_HB:
					case MIAA_LC:
					case MIDA_HB:
					case MIFA_HB:
					case MIFA_LC:
					case MIHA_HB:
					case MIHA_LC:
					case MIHM_SS:
					case MIHV_SS:
					case MISM_CH:
					case MISM_DS:
					case MISM_SS:
					case MISV_SS:
					case MIXM_HB:
					case MIXM_LR_LRD:
					case MIXV_HB:
						ZcRD_CommutateConfig_macro(CT_UCESAT_POS_FIRST);
						break;
					default:
						break;
				}
			}
			else if(DUTPosition == DUT_POS2)
			{
				switch(Module)
				{
					case MIAA_CE:
						ZcRD_CommutateConfig_macro(CT_UCESAT_POS_SECOND_VAR_TWO);
						break;
					case MIAA_HB:
					case MIAA_HC:
					case MIDA_HB:
					case MIFA_HB:
					case MIFA_HC:
					case MIHA_HB:
					case MIHA_HC:
					case MISM_DS:
					case MIXM_HB:
					case MIXV_HB:
						ZcRD_CommutateConfig_macro(CT_UCESAT_POS_SECOND_VAR_ONE);
						break;
					default:
						break;
				}
			}
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

				case SC_Type_MDFA_MDF2_SD:
				case SC_Type_MDA2:
					ZcRD_CommutateConfig_macro(CT_Vcesat_Pos2);
					break;

				default:
					(DUTPosition == DUT_POS1) ? ZcRD_CommutateConfig_macro(CT_Vf_Pos1) : ZcRD_CommutateConfig_macro(CT_Vf_Pos2);
					break;
			}

			COMM_State = COMM_Uf;
			break;
	}

	DELAY_MS(COMM_GetCommDelayMs());
	FPledForcedLight = false;
}
// ----------------------------------------

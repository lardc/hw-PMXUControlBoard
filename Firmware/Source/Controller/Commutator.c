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
Int64U CT_SaveTimer = 0;

// Forward declarations
//
static void COMM_DischargeBeforeIcesOrIrrm();
static Int16U COMM_GetCommDelayMs();
bool COMM_ValidateIGBT(Int16U Position, ModuleTypes Module);
bool COMM_ValidateDiode(Int16U Position, ModuleTypes Module);

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
	return ((Int32U)DataTable[REG_DUT_CASE] * 100 + (Int32U)DataTable[REG_DUT_SCHEME]);
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
	ZcRD_RegisterReset();
	COMM_State = COMM_Def;
}
// ----------------------------------------

bool COMM_ValidateRequest(Int16U ActionID, Int16U Position)
{
	ModuleTypes ModuleType = (ModuleTypes)COMM_CalcModuleType();

	if(Position != DUT_POS1 && Position != DUT_POS2)
		return false;

	switch(ActionID)
	{
		case ACT_COMM_PE:
			return true;  // допустимо без проверки корпуса

		case ACT_COMM_NO_PE:
		case ACT_COMM_VCESAT:
			return COMM_ValidateIGBT(Position,ModuleType);

		case ACT_COMM_VF:
		case ACT_COMM_ICES_OR_IRRM:
			return COMM_ValidateIGBT(Position, ModuleType) || COMM_ValidateDiode(Position, ModuleType);

		default:
			return false;
	}
}
// ----------------------------------------


bool COMM_ValidateIGBT(Int16U Position, ModuleTypes Module)
{
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
}
// ----------------------------------------

bool COMM_ValidateDiode(Int16U Position, ModuleTypes Module)
{
	if(Position == DUT_POS1)
	{
		switch(Module)
		{
			case MDAA_DD:
			case MDDA_DD:
			case MDFA_DD:
			case MDSM_SD:
			case MDSV_SD:
			case MIAA_HC:
			case MIFA_HC:
			case MIFA_SD:
			case MIHA_HC:
				return true;
			default:
				return false;
		}
	}
	else if(Position == DUT_POS2)
	{
		switch(Module)
		{
			case MDAA_DD:
			case MDDA_DD:
			case MDFA_DD:
			case MDSM_SD:
			case MDSV_SD:
			case MIAA_LC:
			case MIFA_LC:
			case MIHA_LC:
			case MISM_CH:
			case MIXM_LR_LRD:
				return true;
			default:
				return false;
		}
	}
	return false;
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	Int16U DUTPosition = DataTable[REG_DUT_POSITION];
	ModuleTypes Module = (ModuleTypes)COMM_CalcModuleType();

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
			COMM_State = COMM_NoPE;
			ZcRD_Commutate_macro(CT_DISCON_PE);
			break;

		case ACT_COMM_ICES_OR_IRRM:
		case ACT_COMM_VF:
			COMM_State = (ActionID == ACT_COMM_ICES_OR_IRRM) ? COMM_IcesOrIrrm : COMM_Uf;

			ZcRD_Commutate_macro(CT_DISCON_PE);
			if(DUTPosition == DUT_POS1)
			{
				switch(Module)
				{
					case MIFA_SD:
						if(ActionID == ACT_COMM_ICES_OR_IRRM)
							ZcRD_Commutate_macro(CT_ICES_POS1_GROUP_BLUE);
						else if(ActionID == ACT_COMM_VF)
							ZcRD_Commutate_macro(CT_UFW_POS1_GROUP_BLUE);
						break;
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
					case MDAA_DD:
					case MDDA_DD:
					case MDFA_DD:
					case MDSM_SD:
					case MDSV_SD:
					case MIAA_HC:
					case MIFA_HC:
					case MIHA_HC:
						if(ActionID == ACT_COMM_ICES_OR_IRRM)
							ZcRD_Commutate_macro(CT_ICES_POS1_GROUP_GREEN);
						else if(ActionID == ACT_COMM_VF)
							ZcRD_Commutate_macro(CT_UFW_POS1_GROUP_GREEN);
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
						if(ActionID == ACT_COMM_ICES_OR_IRRM)
							ZcRD_Commutate_macro(CT_ICES_POS2_GROUP_ORANGE);
						else if(ActionID == ACT_COMM_VF)
							ZcRD_Commutate_macro(CT_UFW_POS2_GROUP_ORANGE);
						break;
					case MDSM_SD:
					case MDSV_SD:
					case MIXM_LR_LRD:
						if(ActionID == ACT_COMM_ICES_OR_IRRM)
							ZcRD_Commutate_macro(CT_ICES_POS2_GROUP_PURPLE);
						else if(ActionID == ACT_COMM_VF)
							ZcRD_Commutate_macro(CT_UFW_POS2_GROUP_PURPLE);
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
					case MDAA_DD:
					case MDDA_DD:
					case MDFA_DD:
					case MIAA_LC:
					case MIFA_LC:
					case MIHA_LC:
					case MISM_CH:
						if(ActionID == ACT_COMM_ICES_OR_IRRM)
							ZcRD_Commutate_macro(CT_ICES_POS2_GROUP_BLUE);
						else if(ActionID == ACT_COMM_VF)
							ZcRD_Commutate_macro(CT_UFW_POS2_GROUP_BLUE);
						break;
					default:
						break;
				}
			}
			break;

		case ACT_COMM_VCESAT:
			COMM_State = COMM_Ucesat;

			ZcRD_Commutate_macro(CT_DISCON_PE);
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
						ZcRD_Commutate_macro(CT_UCESAT_POS1_GROUP_GREEN);
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
						ZcRD_Commutate_macro(CT_UCESAT_POS2_GROUP_ORANGE);
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
						ZcRD_Commutate_macro(CT_UCESAT_POS2_GROUP_BLUE);
						break;
					default:
						break;
				}
			}
			break;
	}

	DELAY_MS(COMM_GetCommDelayMs());
	FPledForcedLight = false;
}
// ----------------------------------------

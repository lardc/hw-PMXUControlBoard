// -----------------------------------------
// Commutation controller
// ----------------------------------------

#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Include
#include "stdinc.h"
#include "Controller.h"
#include "CommutationTable.h"

// Types
//
typedef enum __ModuleTypes
{
	Module_None,
	MDAA_DD,
	MDDA_DD,
	MDFA_DD,
	MDSM_SD,
	MDSV_SD,
	MIAA_CE,
	MIAA_HB,
	MIAA_HC,
	MIAA_LC,
	MIFA_HB,
	MIFA_HC,
	MIFA_LC,
	MIFA_SD,
	MIDA_HB,
	MIHA_HB,
	MIHA_HC,
	MIHA_LC,
	MIHM_SS,
	MIHV_SS,
	MISM_CH,
	MISM_DS,
	MISM_SS,
	MISV_SS,
	MIXM_HB,
	MIXM_LR_LRD,
	MIXV_HB,
} ModuleTypes;

typedef enum __CommutationState
{
	COMM_Def			= 0,
	COMM_IcesOrIrrm		= 1,
	COMM_Ucesat			= 2,
	COMM_Uf				= 3,
	COMM_NoPE			= 4
} CommutationState;

// Variables
//
extern CommutationState COMM_State;

// Functions
void COMM_SwitchToPE();
Int32U COMM_CalcModuleType();
bool COMM_ValidateRequest(Int16U ActionID, Int16U DUTPosition);
void COMM_Commutate(Int16U ActionID);

#endif // __COMMUTATOR_H

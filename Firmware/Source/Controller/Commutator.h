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
	// TODO: заполнить по схемам коммутации 303
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
extern Int32U CycleCounters[INNER_COMMUTATION_TABLE_SIZE];
extern Int64U CT_SaveTimer;

// Functions
void COMM_SwitchToPE();
Int32U COMM_CalcModuleType();
bool COMM_ValidateRequest(Int16U ActionID, Int16U DUTPosition, DevType DevCase, Int16U DUTScheme);
void COMM_Commutate(Int16U ActionID, Int16U DUTPosition, DevType DevCase, Int16U DUTScheme);

#endif // __COMMUTATOR_H

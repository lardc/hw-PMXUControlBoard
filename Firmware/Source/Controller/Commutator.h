// -----------------------------------------
// Commutation controller
// ----------------------------------------

#ifndef __COMMUTATOR_H
#define __COMMUTATOR_H

// Include
#include "stdinc.h"

// Types
//
typedef enum __CommutationState
{
	COMM_Def		= 0,
	COMM_Ices		= 1,
	COMM_Ucesat		= 2,
	COMM_Uf			= 3,
	COMM_Qg			= 4,
	COMM_NoPE		= 5
} CommutationState;

// Variables
//
extern CommutationState COMM_State;

// Functions
void COMM_SwitchToPE();
void COMM_Commutate(Int16U ActionID, Int16U DUTPosition);

#endif // __COMMUTATOR_H

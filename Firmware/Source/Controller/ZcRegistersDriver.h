// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"

// Macros
// Заполнение массива битовыми масками
#define __ZcRD_CommutateConfig_macro(arr) \
	ZcRD_OutputValuesComposeArray((arr), sizeof(arr) / sizeof((arr)[0]))

// Включение выбранной коммутации
#define ZcRD_Commutate_macro(arr) do { \
	ZcRD_RegisterReset(); \
	__ZcRD_CommutateConfig_macro(__CT_DISCON_PE); \
	if(arr != NULL) \
		__ZcRD_CommutateConfig_macro(arr); \
	ZcRD_RegisterFlushWrite(); \
} while(0)


// Functions
//
// Reset output register to zero
void ZcRD_RegisterReset();
// Write cache to physical register
void ZcRD_RegisterFlushWrite();
// Compose cached values
void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn);
void ZcRD_OutputValuesComposeArray(const Int8U* Array, Int8U ArrayLength);
// Reset cached values to zero
void ZcRD_OutputValuesReset();

#endif // __ZBIOEXPANSION_H

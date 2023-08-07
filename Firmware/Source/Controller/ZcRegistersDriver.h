// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"
#include "stdio.h"

//
#define ZcRD_CommutateConfig_macro(arr)		(ZcRD_CommutateConfig(arr, sizeof(arr) / sizeof(arr[0])))

// Functions
//
void ZcRD_WriteSPI1Contactors(uint8_t BitDataArray[]);
void ZcRD_WriteSPI1Relays(uint8_t BitDataArray[]);
void ZcRD_ReadSPI2(volatile uint8_t* SPI_Data);
void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn, Int8U* BitDataArray);
void ZcRD_CommutateConfig(Int8U ConnArray[], Int8U Length);

#endif // __ZBIOEXPANSION_H

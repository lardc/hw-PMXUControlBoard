// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"
#include "stdio.h"

// Functions
//
void ZcRD_WriteSPI1Contactors(uint8_t BitDataArray[]);
void ZcRD_WriteSPI1Relays(uint8_t BitDataArray[]);
uint32_t ZcRD_ReadSPI2();
void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn, Int8U* BitDataArray);
void ZcRD_CommutateConfig(Int8U ConnArray[]);

#endif // __ZBIOEXPANSION_H

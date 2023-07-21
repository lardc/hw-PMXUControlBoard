// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"

// Functions
//
void ZcRD_WriteSPI1Contactors(uint16_t SPI_Data_Hex);
void ZcRD_WriteSPI1Relays(uint64_t SPI_Data_Hex);
uint32_t ZcRD_ReadSPI2();

#endif // __ZBIOEXPANSION_H

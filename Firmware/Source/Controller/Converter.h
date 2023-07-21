#ifndef CONVERTER_H_
#define CONVERTER_H_

// Include
#include "Board.h"
#include "stdinc.h"

// Functions
//
uint64_t Conv_SPIArrayToHex(uint8_t SPI_Data[], uint8_t Data_Length);
void Conv_SPIHexToArray(volatile uint8_t* SPI_Data, uint8_t Data_Length, uint64_t HexData);

#endif /* CONVERTER_H_ */

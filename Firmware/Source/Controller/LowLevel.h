#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLed();
void LL_SetStateIndication(bool State);
bool LL_GetStateSafety();
bool LL_GetStateSelftest();
void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_OE,
		GPIO_PortPinSetting GPIO_SS);
void LL_WriteSPI1Contactors(uint16_t SPI_Data_Hex);
void LL_WriteSPI1Relays(uint64_t SPI_Data_Hex);
uint64_t LL_SPIArrayToHex(uint8_t SPI_Data[], uint8_t Data_Length);
void LL_SPIHexToArray(volatile uint8_t* SPI_Data, uint8_t Data_Length, uint64_t HexData);
uint32_t LL_ReadSPI2();
float LL_MeasurePressureADCVoltage();

#endif //__LOWLEVEL_H

#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLed();
void LL_SetStateIndication(bool State);
void LL_ToggleIndication();
bool LL_IsSafetyTrig();
bool LL_IsSelftestPinOk();
void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_OE, GPIO_PortPinSetting GPIO_SS);
void LL_ReadSPI2(volatile uint8_t* SPI_Data);
float LL_MeasurePressureADCVoltage();
bool LL_CheckTestCurrent();

#endif //__LOWLEVEL_H

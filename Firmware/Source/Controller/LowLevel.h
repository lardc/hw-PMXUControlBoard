#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLed();
void LL_SetStateFPLed(bool State);
void LL_ToggleFPLed();
bool LL_IsSafetyTrig();
//
// OE сдвиговых регистров SPI1 через GPIO_SFT_ENABLE.
// Enable=false → пин притянут к GND (OE разрешён); Enable=true → high-Z (OE запрещён)
void LL_SetStateSFT_ENABLE(bool Enable);
//
void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_SS);
void LL_SafetyResetSPI1();
void LL_ReadSPI2(volatile uint8_t* SPI_Data);
float LL_MeasurePressureADCVoltage();

#endif //__LOWLEVEL_H

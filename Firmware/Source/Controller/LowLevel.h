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
// State=false → пин притянут к GND (OE разрешён); State=true → high-Z (OE запрещён)
void LL_SafetyForceRelaysOff(bool State);
void LL_SPI_WriteByte(Int8U Data);
void LL_SPI_ReadArray(pInt8U Array, Int8U Len);
void LL_SPI_LatchBoard(Int8U BoardIdx);
void LL_SPI_TestSS(Int8U BoardIdx);
float LL_MeasurePressureADCVoltage();

#endif //__LOWLEVEL_H

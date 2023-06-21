#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"


// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateFPLed(bool State);
void LL_SetStateSFRedLed(bool State);
void LL_SetStateSFGreenLed(bool State);
void LL_WriteSPI(uint8_t SPI_Data[], uint8_t Data_Length);
void LL_SPIReset();
void LL_SetStateSF_EN(bool State);
void LL_SetStateSD_EN(bool State);
float LL_SelfTestMeasure();
bool LL_ClosedRelayFailed();
bool LL_OpenRelayFailed();

#endif //__LOWLEVEL_H

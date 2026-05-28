// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "SysConfig.h"

// Functions
//
void LL_ToggleBoardLed()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateFPLed(bool State)
{
	GPIO_SetState(GPIO_FP_LED, State);
}
//-----------------------------

void LL_ToggleFPLed()
{
	GPIO_Toggle(GPIO_FP_LED);
}
//-----------------------------

bool LL_IsSafetyTrig()
{
	return GPIO_GetState(GPIO_SFT_IN);
}
//-----------------------------

void LL_SafetyForceRelaysOff(bool State)
{
	GPIO_SetState(GPIO_SFT_ENABLE, State);
}
//-----------------------------

void LL_SPI_WriteByte(Int8U Data)
{
	SPI_WriteByte8b(SPI1, Data);
}
//-----------------------------

void LL_SPI_LatchBoardTemplate(Int8U BoardIdx, Int32U PulseLen)
{
	GPIO_PortPinSetting SS;
	switch(BoardIdx)
	{
		case 0:  SS = GPIO_SPI1_SS_CONT; break;
		case 1:  SS = GPIO_SPI1_SS_REL; break;
	}

	DELAY_US(TIME_SPI_DELAY_US);
	GPIO_SetState(SS, false);
	(PulseLen > 1000) ? DELAY_MS(PulseLen / 1000) : DELAY_US(PulseLen);
	GPIO_SetState(SS, true);
	DELAY_US(TIME_SPI_DELAY_US);
}
//-----------------------------

void LL_SPI_LatchBoard(Int8U BoardIdx)
{
	LL_SPI_LatchBoardTemplate(BoardIdx, TIME_SPI_DELAY_US);
}
//-----------------------------

void LL_SPI_TestSS(Int8U BoardIdx)
{
	LL_SPI_LatchBoardTemplate(BoardIdx, 100000);
}
//-----------------------------

void LL_SPI_ReadArray(pInt8U Array, Int8U Len)
{
	GPIO_SetState(GPIO_SPI2_LD, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI2_LD, true);

	GPIO_SetState(GPIO_SPI2_OE, false);
	for(int i = 0; i < Len; i++)
		Array[i] = SPI_ReadByte8b(SPI2);

	GPIO_SetState(GPIO_SPI2_OE, true);
}
//-----------------------------

float LL_MeasurePressureADCVoltage()
{
	return (float)ADC_Measure(ADC1, ADC_P_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
}
//-----------------------------

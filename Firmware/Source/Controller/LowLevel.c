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

void LL_SetStateSFT_ENABLE(bool Enable)
{
	GPIO_SetState(GPIO_SFT_ENABLE, Enable);
}
//-----------------------------

void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_SS)
{
	LL_SetStateSFT_ENABLE(true);
	GPIO_SetState(GPIO_SS, false);
	for(int i = Data_Length - 1; i >= 0; i--)
		SPI_WriteByte8b(SPI1, SPI_Data[i]);
	GPIO_SetState(GPIO_SS, true);
	DELAY_US(1);
	GPIO_SetState(GPIO_SS, false);
	LL_SetStateSFT_ENABLE(false);
}
//-----------------------------

void LL_SafetyResetSPI1()
{
	LL_SetStateSFT_ENABLE(true);

	GPIO_SetState(GPIO_SPI1_SS_REL, false);
	for(int i = SPI1_ARRAY_LEN_RELAYS - 1; i >= 0; i--)
		SPI_WriteByte8b(SPI1, 0);
	GPIO_SetState(GPIO_SPI1_SS_REL, true);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI1_SS_REL, false);

	GPIO_SetState(GPIO_SPI1_SS_CONT, false);
	for(int i = SPI1_ARRAY_LEN_CONTACTORS - 1; i >= 0; i--)
		SPI_WriteByte8b(SPI1, 0);
	GPIO_SetState(GPIO_SPI1_SS_CONT, true);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI1_SS_CONT, false);
}
//-----------------------------

void LL_ReadSPI2(volatile uint8_t* SPI_Data)
{
	GPIO_SetState(GPIO_SPI2_LD, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI2_LD, true);

	GPIO_SetState(GPIO_SPI2_OE, false);
	for(int i = 0; i < SPI2_ARRAY_LEN; i++)
		SPI_Data[i] = SPI_ReadByte8b(SPI2);

	GPIO_SetState(GPIO_SPI2_OE, true);
}
//-----------------------------

float LL_MeasurePressureADCVoltage()
{
	return (float)ADC_Measure(ADC1, ADC_P_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
}
//-----------------------------

// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "DataTable.h"
#include "Converter.h"

// Functions
//
void LL_ToggleBoardLed()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateIndication(bool State)
{
	GPIO_SetState(GPIO_IND, State);
}
//-----------------------------

void LL_ToggleIndication()
{
	GPIO_Toggle(GPIO_IND);
}
//-----------------------------

bool LL_IsSafetyTrig()
{
	return GPIO_GetState(GPIO_SAFETY);
}
//-----------------------------

bool LL_IsSelftestPinOk()
{
	return GPIO_GetState(GPIO_SELFTEST);
}
//-----------------------------

void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_OE, GPIO_PortPinSetting GPIO_SS)
{
	// Turn outputs OFF
	GPIO_SetState(GPIO_OE, true);
	GPIO_SetState(GPIO_SS, false);
	for(int i = Data_Length; i >= 0; i--)
	{
		SPI_WriteByte8b(SPI1, SPI_Data[i]);
	}
	GPIO_SetState(GPIO_SS, true);
	DELAY_US(1);
	GPIO_SetState(GPIO_SS, false);
	// Turn outputs ON
	GPIO_SetState(GPIO_OE, false);
}
//-----------------------------

void LL_ReadSPI2(volatile uint8_t* SPI_Data)
{
	// Latch
	GPIO_SetState(GPIO_SPI2_LD, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI2_LD, true);
	// Read data
	GPIO_SetState(GPIO_SPI2_OE, false);
	for(int i = 0; i <= SPI2_ARRAY_LEN; i++)
	{
		SPI_Data[i] = SPI_ReadByte(SPI2);
	}
	// End of transmit
	GPIO_SetState(GPIO_SPI2_OE, true);
}
//-----------------------------

float LL_MeasurePressureADCVoltage()
{
	return (float)ADC_Measure(ADC1, ADC_P_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
}
//-----------------------------

bool LL_CheckTestCurrent()
{
	return GPIO_GetState(GPIO_SELFTEST);
}
//-----------------------------

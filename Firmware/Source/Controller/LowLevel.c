// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "DataTable.h"

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

void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSettingMacro GPIO_OE, GPIO_PortPinSettingMacro GPIO_SS)
{
	// Turn outputs OFF
	GPIO_SetState(GPIO_OE, true);
	GPIO_SetState(GPIO_SS, false);
	for (int i = 0; i <= Data_Length; i++)
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

void LL_WriteSPI1Contactors(uint8_t SPI_Data[], uint8_t Data_Length)
{
	LL_WriteSPI1(SPI_Data, Data_Length, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void LL_WriteSPI1Relays(uint8_t SPI_Data[], uint8_t Data_Length)
{
	LL_WriteSPI1(SPI_Data, Data_Length, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

uint32_t LL_ReadSPI2()
{
	uint32_t SPI_Data = 0x0;
	// Latch
	GPIO_SetState(GPIO_SPI2_LD, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI2_LD, true);
	// Read data
	GPIO_SetState(GPIO_SPI2_OE, false);
	for (int i = 0; i <= SPI2_DATA_LENGTH; i++)
	{
		SPI_Data << 8;
		SPI_Data |= SPI_Data;
	}
	// End of transmit
	GPIO_SetState(GPIO_OE, true);

	return SPI_Data;
}
//-----------------------------

float LL_SelfTestMeasure()
{
	float MeasuredTestVoltage;

	// Enable self-test current
	LL_SetStateSD_EN(true);
	DELAY_MS(5);
	// Measure test-point and convert value to voltage
	MeasuredTestVoltage = (float)ADC_Measure(ADC1, ADC_V_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	// Disable self-test current
	LL_SetStateSD_EN(false);

	return MeasuredTestVoltage;
}
//-----------------------------

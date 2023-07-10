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

bool LL_GetStateSafety()
{
	return GPIO_GetState(GPIO_SAFETY);
}
//-----------------------------

bool LL_GetStateSelftest()
{
	return GPIO_GetState(GPIO_SELFTEST);
}
//-----------------------------

void LL_WriteSPI1(uint8_t SPI_Data[], uint8_t Data_Length, GPIO_PortPinSetting GPIO_OE,
		GPIO_PortPinSetting GPIO_SS)
{
	// Turn outputs OFF
	GPIO_SetState(GPIO_OE, true);
	GPIO_SetState(GPIO_SS, false);
	for(int i = 0; i <= Data_Length; i++)
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

void LL_WriteSPI1Contactors(uint16_t SPI_Data_Hex)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_CONTACTORS];
	LL_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_CONTACTORS, (uint64_t)SPI_Data_Hex);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void LL_WriteSPI1Relays(uint64_t SPI_Data_Hex)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_RELAYS];
	LL_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_RELAYS, SPI_Data_Hex);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

uint64_t LL_SPIArrayToHex(uint8_t SPI_Data[], uint8_t Data_Length)
{
	uint64_t HexData = 0x0;
	for(int i = 0; i <= Data_Length; i++)
	{
		HexData = HexData << 8;
		HexData |= SPI_Data[i];
	}
	return HexData;
}
//-----------------------------

void LL_SPIHexToArray(volatile uint8_t* SPI_Data, uint8_t Data_Length, uint64_t HexData)
{
	for(int i = 0; i <= Data_Length; i++)
	{
		SPI_Data[i] = HexData & 0xff;
		HexData = HexData >> 8;
	}
}
//-----------------------------

uint32_t LL_ReadSPI2()
{
	uint8_t SPI_Data[SPI2_DATA_LENGTH];
	// Latch
	GPIO_SetState(GPIO_SPI2_LD, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI2_LD, true);
	// Read data
	GPIO_SetState(GPIO_SPI2_OE, false);
	for(int i = 0; i <= SPI2_DATA_LENGTH; i++)
	{
		SPI_Data[i] = SPI_ReadByte(SPI2);
	}
	// End of transmit
	GPIO_SetState(GPIO_SPI2_OE, true);

	return (uint32_t)LL_SPIArrayToHex(SPI_Data, SPI2_DATA_LENGTH);
}
//-----------------------------

float LL_MeasurePressureADCVoltage()
{
	float MeasuredPressureVoltage;
	MeasuredPressureVoltage = (float)ADC_Measure(ADC1, ADC_P_CHANNEL) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	return MeasuredPressureVoltage;
}
//-----------------------------

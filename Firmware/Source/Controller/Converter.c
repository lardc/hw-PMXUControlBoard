// -----------------------------------------
// Converting data module
// ----------------------------------------

// Header
#include "Converter.h"
//

// Variables
//

// Functions
//

uint64_t Conv_SPIArrayToHex(uint8_t SPI_Data[], uint8_t Data_Length)
{
	uint64_t HexData = 0x0;
	for(int i = 0; i < Data_Length; i++)
	{
		HexData = HexData << 8;
		HexData |= SPI_Data[i];
	}
	return HexData;
}
//-----------------------------

void Conv_SPIHexToArray(volatile uint8_t* SPI_Data, uint8_t Data_Length, uint64_t HexData)
{
	for(int i = 0; i <= Data_Length; i++)
	{
		SPI_Data[i] = HexData & 0xff;
		HexData = HexData >> 8;
	}
}
//-----------------------------

float Conv_PressureADCVtoBar()
{
	return LL_MeasurePressureADCVoltage() * DataTable[REG_PRESSURE_ADC_K] + DataTable[REG_PRESSURE_ADC_OFFSET];
}
//-----------------------------

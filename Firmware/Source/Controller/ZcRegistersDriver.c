// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "CommutationTable.h"
#include "LowLevel.h"
#include "Delay.h"
#include "DataTable.h"
#include "Converter.h"

// Variables
//

// Functions
//

void ZcRD_WriteSPI1Contactors(uint16_t SPI_Data_Hex)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_CONTACTORS];
	Conv_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_CONTACTORS, (uint64_t)SPI_Data_Hex);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void ZcRD_WriteSPI1Relays(uint64_t SPI_Data_Hex)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_RELAYS];
	Conv_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_RELAYS, SPI_Data_Hex);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

uint32_t ZcRD_ReadSPI2()
{
	uint8_t SPI_Data[SPI2_DATA_LENGTH];
	LL_ReadSPI2(&SPI_Data[0]);
	return (uint32_t)Conv_SPIArrayToHex(SPI_Data, SPI2_DATA_LENGTH);
}

/*
void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[CommutationTable[TableID].RegNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].RegNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZcRD_OutputValuesReset()
{
	for (uint8_t i = 0; i < NUM_REGS_TOTAL; ++i)
		CurrentOutputValues[i] = 0;
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	GPIO_SetState(GPIO_SPI_OE, true);
	DELAY_US(1);

	for (int8_t i = NUM_REGS_TOTAL - 1; i >= 0; i--)
		SPI_WriteByte8b(SPI1, CurrentOutputValues[i]);

	GPIO_SetState(GPIO_SPI_SS, true);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI_SS, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_SPI_OE, false);

	DELAY_US(COMM_DELAY_MS * 1000L);
}
// ----------------------------------------
*/

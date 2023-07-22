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

void ZcRD_WriteSPI1Contactors(uint16_t BitData)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_CONTACTORS];
	Conv_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_CONTACTORS, (uint64_t)BitData);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void ZcRD_WriteSPI1Relays(uint64_t BitData)
{
	uint8_t SPI_Data_Array[SPI1_ARRAY_LEN_RELAYS];
	Conv_SPIHexToArray(&SPI_Data_Array[0], SPI1_ARRAY_LEN_RELAYS, BitData);
	LL_WriteSPI1(SPI_Data_Array, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

uint32_t ZcRD_ReadSPI2()
{
	uint8_t SPI_Data[SPI2_DATA_LENGTH];
	LL_ReadSPI2(&SPI_Data[0]);
	return (uint32_t)Conv_SPIArrayToHex(SPI_Data, SPI2_DATA_LENGTH);
}
//-----------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn, Int64U* BitData)
{
	Int64U BitMask = 0x1 << ((InnerCommutationTable[TableID].RegNum * BITS_PER_REG) + InnerCommutationTable[TableID].Bit);
	if (TurnOn)
		*BitData |= BitMask;
	else
		*BitData &= ~(BitMask);
}
// ----------------------------------------

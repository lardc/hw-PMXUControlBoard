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

void ZcRD_WriteSPI1Contactors(uint8_t BitDataArray[])
{
	LL_WriteSPI1(BitDataArray, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void ZcRD_WriteSPI1Relays(uint8_t BitDataArray[])
{
	LL_WriteSPI1(BitDataArray, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

uint32_t ZcRD_ReadSPI2()
{
	uint8_t SPI_Data[SPI2_DATA_LENGTH];
	LL_ReadSPI2(&SPI_Data[0]);
	return (uint32_t)Conv_SPIArrayToHex(SPI_Data, SPI2_DATA_LENGTH);
}
//-----------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn, Int8U* BitDataArray)
{
	if(TurnOn)
		BitDataArray[InnerCommutationTable[TableID].RegNum] |= InnerCommutationTable[TableID].Bit;
	else
		BitDataArray[InnerCommutationTable[TableID].RegNum] &= ~InnerCommutationTable[TableID].Bit;
}
// ----------------------------------------

void ZcRD_CommutateConfig(Int8U ConnArray[])
{
	Int8U RelayArray[SPI1_ARRAY_LEN_RELAYS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
		RelayArray[i] = CT_DFLT_Contactors[i];
	Int8U ContactorArray[SPI1_ARRAY_LEN_CONTACTORS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
		ContactorArray[i] = CT_DFLT_Contactors[i];
	Int8U n = sizeof(*ConnArray);
	for(uint8_t i = 0; i < n; i++)
	{
		if(InnerCommutationTable[ConnArray[i]].Type == RELAY)
			ZcRD_OutputValuesCompose(ConnArray[i], TRUE, &RelayArray[0]);
		else
			ZcRD_OutputValuesCompose(ConnArray[i], TRUE, &ContactorArray[0]);
	}
	ZcRD_WriteSPI1Relays(RelayArray);
	ZcRD_WriteSPI1Contactors(ContactorArray);
}
// ----------------------------------------

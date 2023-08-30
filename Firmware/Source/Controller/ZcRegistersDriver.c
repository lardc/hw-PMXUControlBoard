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
static volatile Int32U ZcRD_ContactorsCommCounter[NUM_CONTACTOR_COMMUTATIONS] = {0,0,0,0,0,0,0,0,0,0,0,0};
static volatile Int32U ZcRD_RelayGroupsCommCounter[NUM_RELAY_GROUPS_COMMUTATIONS] = {0,0,0,0,0,0,0,0,0,0};

// Functions
//
void ZcRD_IncrementContactors(uint8_t BitDataArray[])
{
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
	{
		for(Int8U j = 0; j < 8; j++)
			ZcRD_ContactorsCommCounter[i * 8 + j] += (BitDataArray[i] >> j) & 0x1;
	}
}
//-----------------------------

void ZcRD_IncrementRelays(uint8_t BitDataArray[])
{
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
	{
		for(Int8U j = 0; j < 8; j++)
			ZcRD_ContactorsCommCounter[i * 8 + j] += (BitDataArray[i] >> j) & 0x1;
	}
}
//-----------------------------

void ZcRD_SaveCountersToEPROM()
{
	// Soon...
}
//-----------------------------

void ZcRD_RestoreCountersFromEPROM()
{
	// Soon...
}
//-----------------------------

void ZcRD_WriteSPI1Contactors(const uint8_t BitDataArray[])
{
	ZcRD_IncrementContactors((uint8_t *)BitDataArray);
	LL_WriteSPI1((uint8_t *)BitDataArray, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_OE_CONT, GPIO_SPI1_SS_CONT);
}
//-----------------------------

void ZcRD_WriteSPI1Relays(const uint8_t BitDataArray[])
{
	ZcRD_IncrementRelays((uint8_t *)BitDataArray);
	LL_WriteSPI1((uint8_t *)BitDataArray, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_OE_REL, GPIO_SPI1_SS_REL);
}
//-----------------------------

void ZcRD_ReadSPI2(volatile uint8_t* SPI_Data)
{
	LL_ReadSPI2(&SPI_Data[0]);
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

void ZcRD_CommutateConfig(const Int8U CommArray[], Int8U Length)
{
	Int8U RelayArray[SPI1_ARRAY_LEN_RELAYS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
		RelayArray[i] = CT_DFLT_Contactors[i];
	Int8U ContactorArray[SPI1_ARRAY_LEN_CONTACTORS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
		ContactorArray[i] = CT_DFLT_Contactors[i];
	for(uint8_t i = 0; i < Length; i++)
	{
		if(InnerCommutationTable[(uint8_t)CommArray[i]].Type == RELAY)
			ZcRD_OutputValuesCompose((uint8_t)CommArray[i], TRUE, &RelayArray[0]);
		else
			ZcRD_OutputValuesCompose((uint8_t)CommArray[i], TRUE, &ContactorArray[0]);
	}
	ZcRD_WriteSPI1Relays(RelayArray);
	ZcRD_WriteSPI1Contactors(ContactorArray);

}
// ----------------------------------------

Int8U ZcRD_CommutationCheck(Int8U CommArray[], Int8U Length)
{
	Int8U SPI2Data[SPI2_ARRAY_LEN];
	Int8U ContactorsStateArray[SPI2_ARRAY_LEN];
	Int8U ErrorNum = COMM_CHECK_NO_ERROR;
	// Generate default contactors state
	for(Int8U i = 0; i < CONTACTORS_STATE_TABLE_SIZE; i++)
	{
		ContactorsStateArray[ContactorsStateTable[i].RegNumClose] &= ~ContactorsStateTable[i].BitClose;
		ContactorsStateArray[ContactorsStateTable[i].RegNumOpen] |= ContactorsStateTable[i].BitOpen;
	}
	// Generate destination contactors state
	for(uint8_t i = 0; i < Length; i++)
	{
		ContactorsStateArray[ContactorsStateTable[CommArray[i]].RegNumClose] |=
				ContactorsStateTable[CommArray[i]].BitClose;
		ContactorsStateArray[ContactorsStateTable[CommArray[i]].RegNumOpen] &=
				~ContactorsStateTable[CommArray[i]].BitOpen;
	}
	// Read current state
	LL_ReadSPI2(&SPI2Data[0]);
	// Compare destination and current states
	for(Int8U i = 0; i < SPI2_ARRAY_LEN; i++)
	{
		// Found number of fault commutation
		if(ContactorsStateArray[i] != SPI2Data[i])
		{
			for(Int8U j = 0; j < BITS_PER_REG; j++)
			{
				ErrorNum = j;
				if((ContactorsStateArray[i] >> 1) == (SPI2Data[i] >> 1))
					break;
			}
			ErrorNum += (i * BITS_PER_REG);
			break;
		}
	}
	return ErrorNum;
}
// ----------------------------------------

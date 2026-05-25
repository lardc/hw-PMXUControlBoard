// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "LowLevel.h"
#include "Delay.h"
#include "DataTable.h"
#include "Converter.h"
#include "Commutator.h"

// Variables
//
volatile Int32U ZcRD_ContactorsCommCounter[NUM_CONTACTOR_COMMUTATIONS] = {0,0,0,0,0,0};
static uint8_t PrevRelayState[SPI1_ARRAY_LEN_RELAYS] = {0};
static uint8_t PrevContactorState[SPI1_ARRAY_LEN_CONTACTORS] = {0};

// Functions
//
void ZcRD_IncrementContactors(const uint8_t BitDataArray[])
{
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
	{
		for(Int8U j = 0; j < 8; j++)
			ZcRD_ContactorsCommCounter[i * 8 + j] += (BitDataArray[i] >> j) & 0x1;
	}
}
//-----------------------------

void ZcRD_SaveCounters(const uint8_t BitDataArray[], Int8U Node)
{
	uint8_t *PrevElement = (Node == RELAY) ? PrevRelayState : PrevContactorState;

	// Инкремент счётчиков только при изменении соответствующего бита
	for (Int16U i = 1; i < INNER_COMMUTATION_TABLE_SIZE; i++)
	{
		if (InnerCommutationTable[i].Node != Node)
			continue;

		if ((PrevElement[InnerCommutationTable[i].RegNum] & InnerCommutationTable[i].Bit) !=
			 (BitDataArray[InnerCommutationTable[i].RegNum] & InnerCommutationTable[i].Bit) )
			CycleCounters[i]++;
	}

	// Обновление предыдущего состояния соответствующего узла
	if (Node == RELAY)
	{
		for (Int16U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
			PrevRelayState[i] = BitDataArray[i];
	}
	else
	{
		for (Int16U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
			PrevContactorState[i] = BitDataArray[i];
	}
}
//-----------------------------

void ZcRD_ApplySafetyReset(void)
{
	Int16U i;

	LL_SafetyResetSPI1();

	for (i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
		PrevRelayState[i] = 0;

	for (i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
		PrevContactorState[i] = 0;
}
//-----------------------------

void ZcRD_WriteSPI1Comm(const uint8_t BitDataArray[], Int8U Node)
{
	ZcRD_SaveCounters(BitDataArray, Node);
	if(Node == RELAY)
	{
		LL_WriteSPI1((uint8_t *)BitDataArray, SPI1_ARRAY_LEN_RELAYS, GPIO_SPI1_SS_REL);
	}
	else
	{
		ZcRD_IncrementContactors(BitDataArray);
		LL_WriteSPI1((uint8_t *)BitDataArray, SPI1_ARRAY_LEN_CONTACTORS, GPIO_SPI1_SS_CONT);
	}
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
	Int8U ContactorArray[SPI1_ARRAY_LEN_CONTACTORS];

	for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
		RelayArray[i] = CT_DFLT_Relays[i];

	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
		ContactorArray[i] = CT_DFLT_Contactors[i];

	for(uint8_t i = 0; i < Length; i++)
	{
		if(InnerCommutationTable[(uint8_t)CommArray[i]].Node == RELAY)
			ZcRD_OutputValuesCompose((uint8_t)CommArray[i], TRUE, &RelayArray[0]);
		else
			ZcRD_OutputValuesCompose((uint8_t)CommArray[i], TRUE, &ContactorArray[0]);
	}

	ZcRD_WriteSPI1Comm(RelayArray, RELAY);
	ZcRD_WriteSPI1Comm(ContactorArray, CONTACTOR);
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
		if(CommArray[i] && CommArray[i] <= CONTACTORS_STATE_TABLE_SIZE)
		{
			ContactorsStateArray[ContactorsStateTable[CommArray[i]].RegNumClose] |= ContactorsStateTable[CommArray[i]].BitClose;
			ContactorsStateArray[ContactorsStateTable[CommArray[i]].RegNumOpen] &= ~ContactorsStateTable[CommArray[i]].BitOpen;
		}
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

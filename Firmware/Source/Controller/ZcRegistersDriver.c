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
/*
// Variables
//
static uint8_t CurrentOutputValues[NUM_REGS_TOTAL] = {0};

// Functions
//

void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	// Reset physical register
	LL_SPIReset();

	DELAY_US(COMM_DELAY_MS * 1000L);
}
// ----------------------------------------

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

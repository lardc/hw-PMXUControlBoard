// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "Converter.h"
#include "DataTable.h"
#include "ZcRegistersDriver.h"
#include "CommutationTable.h"

// Functions
//
void DBACT_PulseIndication()
{
	LL_SetStateFPLed(true);
	DELAY_MS(1000);
	LL_SetStateFPLed(false);
}
//-----------------------

void DBACT_ReadSftIn()
{
	DataTable[REG_DBG] = LL_IsSafetyTrig() ? 1 : 0;
}
//-----------------------

void DBACT_SftEnablePulse()
{
	LL_SetStateSFT_ENABLE(true);
	DELAY_MS(1000);
	LL_SetStateSFT_ENABLE(false);
}
//-----------------------

void DBACT_WriteSPI1ContactorsRaw()
{
	Int8U BitDataArray[SPI1_ARRAY_LEN_CONTACTORS];

	if(DataTable[REG_DBG] < CONTACTORS_STATE_TABLE_SIZE)
	{
		for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
			BitDataArray[i] = CT_DFLT_Contactors[i];

		ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE, &BitDataArray[0]);
		ZcRD_WriteSPI1Comm(BitDataArray, CONTACTOR);
	}
}
//-----------------------

void DBACT_WriteSPI1RelaysRaw()
{
	Int8U BitDataArray[SPI1_ARRAY_LEN_RELAYS];

	if(DataTable[REG_DBG] >= CONTACTORS_STATE_TABLE_SIZE && DataTable[REG_DBG] <= INNER_COMMUTATION_TABLE_SIZE)
	{
		for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
			BitDataArray[i] = CT_DFLT_Relays[i];

		ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE, &BitDataArray[0]);
		ZcRD_WriteSPI1Comm(BitDataArray, RELAY);
	}
}
//-----------------------

void DBACT_ResetSPI1Commutations()
{
	ZcRD_WriteSPI1Comm(CT_DFLT_Relays, RELAY);
	ZcRD_WriteSPI1Comm(CT_DFLT_Contactors, CONTACTOR);
}
//-----------------------

void DBACT_ReadSPI2Raw()
{
	Int8U SPI_Data[SPI2_ARRAY_LEN];
	Int32U RawData = 0;
	ZcRD_ReadSPI2(SPI_Data);
	RawData = (Int32U)Conv_SPIArrayToHex(SPI_Data, SPI2_ARRAY_LEN);
	DataTable[REG_DBG] = RawData;
}
//-----------------------

void DBACT_GetPressureADCVoltage()
{
	DataTable[REG_DBG] = Conv_PressureADCVtoBar();
}
//-----------------------

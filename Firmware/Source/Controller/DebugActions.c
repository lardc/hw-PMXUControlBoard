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
// Send pulse to Indicator
void DBACT_PulseIndication()
{
	LL_SetStateIndication(true);
	DELAY_MS(1000);
	LL_SetStateIndication(false);
}
//-----------------------

// Safety circuit checking
void DBACT_IsSafetyOk()
{
	DataTable[REG_DBG] = LL_IsSafetyTrig();
}
//-----------------------

// Selftest circuit checking
void DBACT_IsSelftestOk()
{
	DataTable[REG_DBG] = LL_IsSelftestPinOk();
}
//-----------------------

// Write raw data to SPI1 for Contactors
void DBACT_WriteSPI1ContactorsRaw()
{
	Int8U BitDataArray[SPI1_ARRAY_LEN_CONTACTORS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_CONTACTORS; i++)
		BitDataArray[i] = CT_DFLT_Contactors[i];
	ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE, &BitDataArray[0]);
	ZcRD_WriteSPI1Contactors(BitDataArray);
}
//-----------------------

// Write raw data to SPI1 for Relays
void DBACT_WriteSPI1RelaysRaw()
{
	Int8U BitDataArray[SPI1_ARRAY_LEN_RELAYS];
	for(Int8U i = 0; i < SPI1_ARRAY_LEN_RELAYS; i++)
		BitDataArray[i] = CT_DFLT_Contactors[i];
	ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE, &BitDataArray[0]);
	ZcRD_WriteSPI1Relays(BitDataArray);
}
//-----------------------

// Reset SPI1 commutations: Relays and Contactors
void DBACT_ResetSPI1Commutations()
{
	ZcRD_WriteSPI1Relays(CT_DFLT_Relays);
	ZcRD_WriteSPI1Contactors(CT_DFLT_Contactors);
}

// Read raw data from SPI2
void DBACT_ReadSPI2Raw()
{
	Int8U SPI_Data[SPI2_ARRAY_LEN];
	Int32U RawData = 0;
	ZcRD_ReadSPI2(SPI_Data);
	RawData = (Int32U)Conv_SPIArrayToHex(SPI_Data, SPI2_ARRAY_LEN);
	DataTable[REG_DBG] = RawData;
}
//-----------------------

// Read raw voltage from ADC input
void DBACT_GetPressureADCVoltage()
{
	DataTable[REG_DBG] = Conv_PressureADCVtoBar();
}
//-----------------------


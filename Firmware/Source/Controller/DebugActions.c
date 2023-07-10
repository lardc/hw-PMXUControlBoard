﻿// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
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
	DataTable[REG_DBG] = !LL_GetStateSafety(); // 1 - Ok, 0 - Error
}
//-----------------------

// Selftest circuit checking
void DBACT_IsSelftestOk()
{
	DataTable[REG_DBG] = LL_GetStateSelftest(); // 1 - Ok, 0 - Error
}
//-----------------------

// Write raw data to SPI1 for Contactors
void DBACT_WriteSPI1ContactorsRaw()
{
	LL_WriteSPI1Contactors((uint16_t)DataTable[REG_DBG]);
}
//-----------------------

// Write raw data to SPI1 for Relays
void DBACT_WriteSPI1RelaysRaw()
{
	LL_WriteSPI1Relays((uint64_t)DataTable[REG_DBG]);
}
//-----------------------

// Read raw data from SPI2
void DBACT_ReadSPI2Raw()
{
	DataTable[REG_DBG] = LL_ReadSPI2();
}
//-----------------------

// Read raw voltage from ADC input
void DBACT_GetPressureADCVoltage()
{
	DataTable[REG_DBG] = LL_MeasurePressureADCVoltage();
}
//-----------------------


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
	LL_SafetyForceRelaysOff(true);
	DELAY_MS(1000);
	LL_SafetyForceRelaysOff(false);
}
//-----------------------

void DBACT_WriteSPI1ContactorsRaw()
{

}
//-----------------------

void DBACT_WriteSPI1RelaysRaw()
{

}
//-----------------------

void DBACT_ResetSPI1Commutations()
{

}
//-----------------------

void DBACT_ReadSPI2Raw()
{

}
//-----------------------

void DBACT_GetPressureADCVoltage()
{
	DataTable[REG_DBG] = Conv_PressureADCVtoBar();
}
//-----------------------

#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBACT_PulseIndication();
void DBACT_IsSafetyOk();
void DBACT_IsSelftestOk();
void DBACT_WriteSPI1ContactorsRaw();
void DBACT_WriteSPI1RelaysRaw();
void DBACT_ReadSPI2Raw();
void DBACT_GetPressureADCVoltage();

#endif //__DEBUGACTIONS_H

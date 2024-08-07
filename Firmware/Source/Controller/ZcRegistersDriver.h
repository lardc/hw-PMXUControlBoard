﻿// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

#ifndef __ZBIOEXPANSION_H
#define __ZBIOEXPANSION_H

// Include
#include "stdinc.h"
#include "stdio.h"
#include "CommutationTable.h"

//
#define ZcRD_CommutateConfig_macro(arr)		(ZcRD_CommutateConfig(arr, sizeof(arr) / sizeof(arr[0])))
#define ZcRD_CommutationCheck_macro(arr)	(ZcRD_CommutationCheck(arr, sizeof(arr) / sizeof(arr[0])))
//
extern volatile Int32U ZcRD_ContactorsCommCounter[NUM_CONTACTOR_COMMUTATIONS];
// Functions
//
void ZcRD_IncrementContactors(uint8_t BitDataArray[]);
void ZcRD_IncrementRelays(uint8_t BitDataArray[]);
void ZcRD_SaveCountersToEPROM();
void ZcRD_RestoreCountersFromEPROM();
void ZcRD_WriteSPI1Comm(const uint8_t BitDataArray[], Int8U Node);
void ZcRD_ReadSPI2(volatile uint8_t* SPI_Data);
void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn, Int8U* BitDataArray);
void ZcRD_CommutateConfig(const Int8U CommArray[], Int8U Length);
Int8U ZcRD_CommutationCheck(Int8U CommArray[], Int8U Length);

#endif // __ZBIOEXPANSION_H

#ifndef CONTROLLER_SELFTEST_H_
#define CONTROLLER_SELFTEST_H_

// Include
#include "Board.h"
#include "stdinc.h"
//
#define SELFTEST_RelayTest_macro(bit_arr, arr)          (SELFTEST_RelayTest(bit_arr, arr, sizeof(arr) / sizeof(arr[0])))
//
#define SELFTEST_NO_BROKEN_RELAY		0xFF

// Functions
//
bool SELFTEST_ContactorsTest();
void SELFTEST_Process();

#endif // CONTROLLER_SELFTEST_H_

#ifndef CONTROLLER_SELFTEST_H_
#define CONTROLLER_SELFTEST_H_

// Include
#include "Board.h"
#include "stdinc.h"

typedef enum __DeviceSelfTestState
{
	STS_None = 0,
	//
	STS_PE1Check = 1,
	STS_PE2Check = 2,
	//
	STS_LCTU1Check = 3,
	STS_LCTU2Check = 4,
	//
	STS_TOCU1Check = 5,
	STS_TOCU2Check = 6,
	STS_TOCU3Check = 7,
	STS_TOCU4Check = 8,
	//
	STS_LCSU1Check = 9,
	STS_LCSU2Check = 10,
	STS_LCSU3Check = 11,
	STS_LCSU4Check = 12,
} DeviceSelfTestState;

// Functions
//
void SELFTEST_Process();

#endif // CONTROLLER_SELFTEST_H_

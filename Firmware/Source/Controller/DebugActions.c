// Header
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
// Send pulse to Front Panel LED
void DBACT_ToggleFPLed()
{
	LL_SetStateFPLed(true);
	DELAY_MS(1000);
	LL_SetStateFPLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Red LED
void DBACT_ToggleSFRedLed()
{
	LL_SetStateSFRedLed(true);
	DELAY_MS(1000);
	LL_SetStateSFRedLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Green LED
void DBACT_ToggleSFGreenLed()
{
	LL_SetStateSFGreenLed(true);
	DELAY_MS(1000);
	LL_SetStateSFGreenLed(false);
}
//-----------------------

void DBACT_WriteSPI()
{
	// Чтение номера таблицы коммутации из отладочного регистра
	ZcRD_OutputValuesCompose(DataTable[REG_DBG], TRUE);
	// Коммутация выбранной комбинации
	ZcRD_RegisterFlushWrite();
}
//-----------------------

// Safety EN check
void DBACT_ToggleSF_EN()
{
	LL_SetStateSF_EN(true);
	DELAY_MS(1000);
	LL_SetStateSF_EN(true);
}
//-----------------------

// Turn self-test current ON, measure voltage with ADC, compare result with DataTable constant
void DBACT_SelfTestMeasure()
{
	DataTable[REG_SELF_TEST_OP_RESULT] = LL_ClosedRelayFailed() ? OPRESULT_FAIL : OPRESULT_OK;
}
//-----------------------

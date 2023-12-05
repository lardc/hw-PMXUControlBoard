// Include
#include "Interrupts.h"
//
#include "Controller.h"
#include "LowLevel.h"
#include "Board.h"
#include "SysConfig.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "ZcRegistersDriver.h"

// Functions
//
void USART1_IRQHandler()
{
	if(ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void USB_LP_CAN_RX0_IRQHandler()
{
	if(NCAN_RecieveCheck())
	{
		NCAN_RecieveData();
		NCAN_RecieveFlagReset();
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	static uint16_t LED_BlinkTimeCounter = 0;

	if(TIM_StatusCheck(TIM7))
	{
		CONTROL_TimeCounter++;
		if(++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleBoardLed();
			LED_BlinkTimeCounter = 0;
		}
		TIM_StatusClear(TIM7);

		CONTROL_HandleExternalLamp(IsCommutation);
	}
}
//-----------------------------------------

void TIM8_IRQHandler()
{
	if(TIM_StatusCheck(TIM8))
	{
		ZcRD_SaveCountersToEPROM();
		CONTROL_CheckContactorsCounter();
		TIM_StatusClear(TIM8);
	}
}
//-----------------------------------------

void EXTI9_5_IRQHandler()
{
	//
	EXTI_FlagReset(EXTI_6);
}
//-----------------------------------------

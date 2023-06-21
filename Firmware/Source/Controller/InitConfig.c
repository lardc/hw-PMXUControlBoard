#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "BCCIxParams.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	RCC_GPIO_Clk_EN(PORTC);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_FP_LED);
	GPIO_InitPushPullOutput(GPIO_SPI_SS);
	GPIO_InitPushPullOutput(GPIO_SPI_RST);
	GPIO_InitPushPullOutput(GPIO_SPI_OE);
	GPIO_InitPushPullOutput(GPIO_SF_RED_LED);
	GPIO_InitPushPullOutput(GPIO_SF_GRN_LED);
	GPIO_InitPushPullOutput(GPIO_SF_EN);
	GPIO_InitPushPullOutput(GPIO_SD_EN);


	// Входы
	GPIO_InitInput(GPIO_SF_TRIG, NoPull);

	// Начальная установка состояний выводов
	GPIO_SetState(GPIO_LED, false);
	GPIO_SetState(GPIO_FP_LED, false);
	GPIO_SetState(GPIO_SPI_SS, true);
	GPIO_SetState(GPIO_SPI_RST, true);
	GPIO_SetState(GPIO_SPI_OE, true);
	GPIO_SetState(GPIO_SF_RED_LED, true);
	GPIO_SetState(GPIO_SF_GRN_LED, false);
	GPIO_SetState(GPIO_SF_EN, false);
	GPIO_SetState(GPIO_SD_EN, false);

	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_UART1_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART1_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_CAN1_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN1_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_CLK, AltFn_5);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_DAT, AltFn_5);
}

//------------------------------------------------

void INITCFG_ConfigExtInterrupt()
{
	// Вход сигнала безопасности
	EXTI_Config(EXTI_PA, EXTI_7, RISE_TRIG, 0);
	EXTI_EnableInterrupt(EXTI9_5_IRQn, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 2, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureSlowUpdate();
}
//------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	// ADC1
	ADC_Calibration(ADC1);
	ADC_SoftTrigConfig(ADC1);
	ADC_Enable(ADC1);
}
//-----------------------------------------------

void INITCFG_ConfigSPI8b()
{
	SPI_Init8b(SPI1, SPI1_BAUDRATE_BITS, SPI1_LSB_FIRST);
}
//------------------------------------------------

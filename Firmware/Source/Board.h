#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"
#include "ZwSPI.h"

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_LED				= {GPIOB, Pin_0};
GPIO_PortPinSettingMacro GPIO_IND				= {GPIOA, Pin_7};
GPIO_PortPinSettingMacro GPIO_SPI1_SS_CONT		= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_SPI1_SS_REL		= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_SPI1_OE_CONT		= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_SPI1_OE_REL		= {GPIOA, Pin_15};
GPIO_PortPinSettingMacro GPIO_SPI2_LD			= {GPIOB, Pin_15};
GPIO_PortPinSettingMacro GPIO_SPI2_OE			= {GPIOB, Pin_12};

// Определения для входных портов
GPIO_PortPinSettingMacro GPIO_SAFETY			= {GPIOA, Pin_6};
GPIO_PortPinSettingMacro GPIO_SELFTEST			= {GPIOA, Pin_1};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_UART1_TX		= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_RX		= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_CAN1_TX		= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_CAN1_RX		= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_CLK		= {GPIOB, Pin_3};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_DAT		= {GPIOB, Pin_5};
GPIO_PortPinSettingMacro GPIO_ALT_SPI2_CLK		= {GPIOB, Pin_13};
GPIO_PortPinSettingMacro GPIO_ALT_SPI2_DAT		= {GPIOB, Pin_14};

#endif // __BOARD_H

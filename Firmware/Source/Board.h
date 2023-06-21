﻿#ifndef __BOARD_H
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
GPIO_PortPinSettingMacro GPIO_LED				= {GPIOB, Pin_1};
GPIO_PortPinSettingMacro GPIO_FP_LED			= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_SPI_SS			= {GPIOA, Pin_15};
GPIO_PortPinSettingMacro GPIO_SPI_RST			= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_SPI_OE			= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_SF_RED_LED		= {GPIOA, Pin_3};
GPIO_PortPinSettingMacro GPIO_SF_GRN_LED		= {GPIOB, Pin_8};
GPIO_PortPinSettingMacro GPIO_SF_EN				= {GPIOA, Pin_6};
GPIO_PortPinSettingMacro GPIO_SD_EN				= {GPIOB, Pin_9};

// Определения для входных портов
GPIO_PortPinSettingMacro GPIO_SF_TRIG			= {GPIOA, Pin_7};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_UART1_TX		= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_RX		= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_CAN1_TX		= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_CAN1_RX		= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_CLK		= {GPIOB, Pin_3};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_DAT		= {GPIOB, Pin_5};

#endif // __BOARD_H

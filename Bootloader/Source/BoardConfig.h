// -----------------------------------------
// Board parameters
// ----------------------------------------

#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

// Board includes
//
#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwSCI.h"
#include "ZwTIM.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"

// Definitions
//
// Blinking LED settings
#define LED_BLINK_PORT		GPIOB
#define LED_BLINK_PIN		Pin_0

// Indication
#define IND_PORT			GPIOA
#define IND_PIN				Pin_7

// SPI_OE contactors
#define OE_C_PORT			GPIOB
#define OE_C_PIN			Pin_6

// SPI_OE relays
#define OE_R_PORT			GPIOA
#define OE_R_PIN			Pin_15

#endif // __BOARD_CONFIG_H

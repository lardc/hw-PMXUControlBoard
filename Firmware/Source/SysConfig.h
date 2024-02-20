#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// Тактовая частота системной шины процессора
#define QUARTZ_FREQUENCY				20000000	// Частота кварца
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// Скорость USART
#define USART_FIFOlen					32			// Длина FIFO USART
// ----------------------------------------------

// Timers
#define TIMER7_uS						1000						// в мкс
#define TIMER8_Min						30							// в мин
#define TIMER8_uS						(TIMER8_Min * 60 * 10e6)	// в мкс
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// Битрейт CAN
// ----------------------------------------------

// ADC
#define ADC_P_CHANNEL					1			// Номер канала оцифровки давления

// SPI
#define SPI1_BAUDRATE_BITS				0x7			// Биты задания битрейта SPI1
#define SPI2_BAUDRATE_BITS				0x7			// Биты задания битрейта SPI2
#define SPI1_LSB_FIRST					false		// Передача младшим битом вперед SPI1
#define SPI2_LSB_FIRST					false		// Передача младшим битом вперед SPI2
#define SPI2_ARRAY_LEN					3			// Размер массива датчиков положения
#define SPI1_ARRAY_LEN_CONTACTORS		2			// Размер массива контакторов
#define SPI1_ARRAY_LEN_RELAYS			2			// Размер массива реле
// ----------------------------------------------

#define COMM_MODE_2

#endif // __SYSCONFIG_H

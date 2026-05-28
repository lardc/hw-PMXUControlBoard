#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS						1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT							0		// Количество массивов для записи
#define EP_COUNT								0		// Количество массивов для чтения
#define FEP_COUNT								1		// Количество массивов для чтения типа float
#define VALUES_x_SIZE							0		// Размер массивов
#define VALUES_DIAG_SIZE						80		// Размер массива диагностических данных и счетчиков
#define ENABLE_LOCKING							FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK							500		// Мигание светодиодом (в мс)
#define TIME_FP_LED_FAULT_BLINK					250		// Мигание светодиодом в состоянии Fault
#define COMM_DELAY_MS							500		// Время ожидания комммутации
#define TIME_FP_LED_ON_STATE					500		// Время свечения внешнего индикатора, мс
#define SAFETY_DELAY							200		// Время задержки отключения коммутации
#define TIME_SPI_DELAY_US						5		// Время задержки SPI

// Параметры измерения
#define ADC_REF_VOLTAGE							3300.0f	// Опорное напряжение АЦП (мВ)
#define ADC_RESOLUTION							4095	// Разрешение АЦП
#define ADC_V_CC								150.0f	// Напряжение при замкнутой цепи (мВ)
// PA0, АЦП1 канал 1: делитель 47k/(47k+10k); восстановление напряжения на датчике
#define ADC_PRESSURE_INPUT_GAIN					1.213f	// 1 / (47k / (47k + 10k))

#endif //  __GLOBAL_H

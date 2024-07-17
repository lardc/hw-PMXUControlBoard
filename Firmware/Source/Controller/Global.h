#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS						1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT							0		// Количество массивов для записи
#define EP_COUNT								0		// Количество массивов для чтения
#define FEP_COUNT								0		// Количество массивов для чтения типа float
#define VALUES_x_SIZE							0		// Размер массивов
#define ENABLE_LOCKING							FALSE	// Защита NV регистров паролем

// Временные параметры
#define TIME_LED_BLINK							500		// Мигание светодиодом (в мс)
#define TIME_FP_LED_FAULT_BLINK					250		// Мигание светодиодом в состоянии Fault
#define COMM_DELAY_MS							500		// Время ожидания комммутации
#define TIME_FP_LED_ON_STATE					500		// Время свечения внешнего индикатора, мс
#define SAFETY_DELAY							200		// Время задержки отключения коммутации

// Параметры измерения
#define ADC_REF_VOLTAGE							3300.0f	// Опорное напряжение (в мВ)
#define ADC_RESOLUTION							4095	// Разрешение АЦП
#define ADC_V_CC								150.0f	// Напряжение при замкнутой цепи (в мВ)

#endif //  __GLOBAL_H

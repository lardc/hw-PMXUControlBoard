#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER						1	// Включение блока
#define ACT_DISABLE_POWER						2	// Выключение блока
#define ACT_CLR_FAULT							3	// Очистка всех fault
#define ACT_CLR_WARNING							4	// Очистка всех warning
//
#define ACT_DBG_FP_LED							21	// Проверка работы индикатора на передней панели
#define ACT_DBG_SF_RED_LED						22	// Проверка работы красного индикатора системы безопасности
#define ACT_DBG_SF_GRN_LED						23	// Проверка работы зеленого индикатора системы безопасности
#define ACT_DBG_WRITE_SPI						24	// Проверка работы коммутации тестовой комбинации
#define ACT_DBG_SPI_RST							25	// Сброс сдвиговых регистров
#define ACT_SF_EN								26	// Проверка работы сигнала-разрешения системы безопаснсоти
#define ACT_DBG_SELF_TEST_MEASURE				27	// Измерение значения напряжение системы самодиагностики

#define ACT_COMM_NONE							100 // Отключение всех реле
#define ACT_COMM_ILEAK_GATE_EMITTER_POS_PULSE	101 // Режим измерения тока утечки затвора-эмиттера (положительный импульс)
#define ACT_COMM_ILEAK_GATE_EMITTER_NEG_PULSE	102 // Режим измерения тока утечки затвора-эмиттера (отрицательный импульс)
#define ACT_COMM_UTH_GATE_EMITTER				103 // Режим измерения порогового напряжения затвор-эмиттер
#define ACT_COMM_Q_GATE							104 // Режим измерения заряда затвора (положительный импульс)
#define ACT_COMM_USAT_COLLECTOR_EMITTER			105 // Режим измерения напряжения насыщения коллектор-эмиттер
#define ACT_COMM_UFW_CHOPPER_DIODE				106 // Режим измерения прямого напряжения обратно-параллельного диода и диода чоппера
#define ACT_COMM_ILEAK_COLLECTOR_EMITTER		107 // Режим измерения тока утечки коллектор-эмиттер
#define ACT_COMM_THERMISTOR						108 // Режим измерения сопротивления термистора
#define ACT_COMM_NO_PE							109 // Отключения защитного заземления

#define ACT_SF_DEACTIVATE						120	// Команда деактивации контура безопасности

#define ACT_SAVE_TO_ROM							200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST					320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------



// Регистры
// Сохраняемые регистры
#define REG_SFTST_V_ALLOWED_VOLTAGE				0	// Допустимое значение напряжения на замкнутом реле

// Несохраняемые регистры чтения-записи
#define REG_MEASUREMENT_POSITION				128	// Регистр выбора позции при измерении (1 или 2)

#define REG_DBG									150	// Отладочный регистр

// Регистры только чтение
#define REG_DEV_STATE							192	// Регистр состояния
#define REG_FAULT_REASON						193	// Регистр Fault
#define REG_DISABLE_REASON						194	// Регистр Disable
#define REG_WARNING								195	// Регистр Warning
#define REG_PROBLEM								196	// Регистр Problem
#define REG_OP_RESULT							197	// Регистр результата операции
#define REG_SELF_TEST_OP_RESULT					198	// Регистр результата самотестирования
#define REG_SUB_STATE							199	// Регистр вспомогательного состояния

#define REG_SELF_TEST_FAILED_SS					201	// Вспомогательное состояние на котором обнаружен отказ
#define REG_SELF_TEST_FAILED_RELAY				202	// Номер коммутации на котором обнаружен отказ
// -----------------------------
#define REG_FWINFO_SLAVE_NID					256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID					257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN						260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN					261	// Begining of the information string record


// Operation results
#define OPRESULT_NONE							0	// No information or not finished
#define OPRESULT_OK								1	// Operation was successful
#define OPRESULT_FAIL							2	// Operation failed

//  Fault and disable codes
#define DF_NONE									0
#define DF_RELAY_SHORT							1	// Обнаружено залипшее реле
#define DF_RELAY_HIGH_RES						2	// Обнаружено повышенное сопротивление на реле

// Problem
#define PROBLEM_NONE							0

//  Warning
#define WARNING_NONE							0

//  User Errors
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4	//  Неправильный ключ

// Endpoints

#endif //  __DEV_OBJ_DIC_H

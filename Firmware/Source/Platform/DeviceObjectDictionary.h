#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER						1	// Включение блока
#define ACT_DISABLE_POWER						2	// Выключение блока
#define ACT_CLR_FAULT							3	// Очистка всех fault
#define ACT_CLR_WARNING							4	// Очистка всех warning
//

#define ACT_DBG_IND								21	// Проверка работы индикатора на передней панели
#define ACT_DBG_SAFETY							22	// Проверка входа безопасности
#define ACT_DBG_SELFTEST						23	// Проверка входа самотестирования
#define ACT_DBG_WRITE_CONT						24	// Проверка работы коммутации контакторов
#define ACT_DBG_WRITE_REL						25	// Проверка работы коммутации ВВ реле
#define ACT_DBG_READ_MAGNET_SEN					26	// Проверка считывания датчиков положения ПЦ
#define ACT_DBG_MEAS_PRESSURE					27	// Измерение значения напряжения на входе АЦП датчика давления

#define ACT_COMM_PE								100 // Отключение всех реле, замыкание шин на PE
#define ACT_COMM_ICES_POS1						101 // Режим измерения тока утечки коллектор-эмиттер, позиция 1 DUT
#define ACT_COMM_ICES_POS2						102 // Режим измерения тока утечки коллектор-эмиттер, позиция 2 DUT

#define ACT_SAVE_TO_ROM							200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST					320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------



// Регистры
// Сохраняемые регистры


// Несохраняемые регистры чтения-записи

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

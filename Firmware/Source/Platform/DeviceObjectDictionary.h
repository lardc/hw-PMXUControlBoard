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
//
#define ACT_COMM_PE								100 // Отключение всех реле, замыкание шин на PE

#define ACT_COMM_ICES_UP						101 // Режим измерения тока утечки коллектор-эмиттер, позиция UP DUT
#define ACT_COMM_ICES_DOWN						102 // Режим измерения тока утечки коллектор-эмиттер, позиция DOWN DUT

#define ACT_COMM_IDSS_UP						103 // Режим измерения тока утечки сток-исток, позиция UP DUT
#define ACT_COMM_IDSS_DOWN						104 // Режим измерения тока утечки сток-исток, позиция DOWN DUT

#define ACT_COMM_IR_UP							105 // Режим измерения повторяющегося импульсного обратного тока диодов, позиция UP DUT
#define ACT_COMM_IR_DOWN						106 // Режим измерения повторяющегося импульсного обратного тока диодов, позиция DOWN DUT

#define ACT_COMM_QG_UP							107 // Режим измерения заряда затвора, позиция UP DUT
#define ACT_COMM_QG_UP_REV						108 // Режим измерения заряда затвора, позиция UP DUT инверсное подключение
#define ACT_COMM_QG_DOWN						109 // Режим измерения заряда затвора, позиция DOWN DUT
#define ACT_COMM_QG_DOWN_REV					110 // Режим измерения заряда затвора, позиция DOWN DUT инверсное подключение

#define ACT_COMM_VCESAT_UP						111 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов, позиция UP DUT
#define ACT_COMM_VCESAT_UP_REV					112 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов, позиция UP DUT инверсное подключение
#define ACT_COMM_VCESAT_DOWN					113 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов, позиция DOWN DUT
#define ACT_COMM_VCESAT_DOWN_REV				114 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов, позиция DOWN DUT инверсное подключение

#define ACT_COMM_VSD_UP							115 // Режим измерения напряжения сток-исток в открытом состоянии, позиция UP DUT
#define ACT_COMM_VSD_UP_REV						116 // Режим измерения напряжения сток-исток в открытом состоянии, позиция UP DUT инверсное подключение
#define ACT_COMM_VSD_DOWN						117 // Режим измерения напряжения сток-исток в открытом состоянии, позиция DOWN DUT
#define ACT_COMM_VSD_DOWN_REV					118 // Режим измерения напряжения сток-исток в открытом состоянии, позиция DOWN DUT инверсное подключение

#define ACT_COMM_RDSON_UP						119 // Режим измерения сопротивления канала сток-исток SiC транзисторов, позиция UP DUT
#define ACT_COMM_RDSON_UP_REV					120 // Режим измерения сопротивления канала сток-исток SiC транзисторов, позиция UP DUT инверсное подключение
#define ACT_COMM_RDSON_DOWN						121 // Режим измерения сопротивления канала сток-исток SiC транзисторов, позиция DOWN DUT
#define ACT_COMM_RDSON_DOWN_REV					122 // Режим измерения сопротивления канала сток-исток SiC транзисторов, позиция DOWN DUT инверсное подключение

#define ACT_COMM_VF_UP							123 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода, позиция UP DUT
#define ACT_COMM_VF_UP_REV						124 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода, позиция UP DUT инверсное подключение
#define ACT_COMM_VF_DOWN						125 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода, позиция DOWN DUT
#define ACT_COMM_VF_DOWN_REV					126 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода, позиция DOWN DUT инверсное подключение
//
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
#define REG_ST_STATE							199	// Регистр состояния самотестирования

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

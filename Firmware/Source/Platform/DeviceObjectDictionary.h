#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER						1	// Включение блока
#define ACT_DISABLE_POWER						2	// Выключение блока
#define ACT_CLR_FAULT							3	// Очистка всех fault
#define ACT_CLR_WARNING							4	// Очистка всех warning

#define ACT_DBG_IND								21	// Проверка работы индикатора на передней панели
#define ACT_DBG_SAFETY							22	// Проверка входа безопасности
#define ACT_DBG_SELFTEST						23	// Проверка входа самотестирования
#define ACT_DBG_WRITE_CONT						24	// Проверка работы коммутации контакторов
#define ACT_DBG_WRITE_REL						25	// Проверка работы коммутации ВВ реле
#define ACT_DBG_READ_MAGNET_SEN					26	// Проверка считывания датчиков положения ПЦ
#define ACT_DBG_MEAS_PRESSURE					27	// Измерение значения напряжения на входе АЦП датчика давления

#define ACT_COMM_PE								100 // Отключение всех реле, замыкание шин на PE
#define ACT_COMM_ICES							101 // Режим измерения тока утечки коллектор-эмиттер
#define ACT_COMM_VCESAT							102 // Режим измерения напряжения насыщения коллектор-эмиттер IGBT транзисторов
#define ACT_COMM_VF								103 // Режим измерения постоянного прямого напряжения диода чоппера и обратно-параллельного диода
#define ACT_COMM_QG								104 // Режим измерения заряда затвора

#define ACT_SELFTEST							110 // Запуск режима самотестирования

#define ACT_SAVE_TO_ROM							200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM					201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT					202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST					320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_CONTACTORS_COMM_DELAY_MS			1	// Задержка ожидания коммутации контакторов
#define REG_PRESSURE_ADC_OFFSET					2	// Смещение оцифрованного напряжения АЦП (в мВ)
#define REG_PRESSURE_ADC_K						3	// Коэффициент пересчёта напряжения АЦП (в мВ) в Бар
#define REG_PRESSURE_THRESHOLD					4	// Граничное значение рабочего давления в Бар
#define REG_DFLT_COMM_DELAY_MS					5	// Задержка перед сбросом коммутации в дефолт при ошибках блока (раскоммутацией силовых блоков и подключением PE линий)
#define REG_MAX_CONT_COMMUTATIONS				6	// Максимальное число коммутаций контакторов до проверки контактных сопротивлений

// Несохраняемые регистры чтения-записи
#define REG_TEST_TOP_SWITCH						128	// Флаг измерения верхнего ключа (по умолчанию нижний)

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

#define REG_SELF_TEST_FAILED_COMMUTATION		201	// SelfTest коммутация, на которой обнаружен отказ
#define REG_SELF_TEST_FAILED_RELAY				202	// Номер реле, на котором обнаружен отказ
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
#define DF_CHAIN_BREAK							2	// Обнаружен разрыв при прозвонке
#define DF_CONTACTOR_COMMUTATION_FAULT			3	// Ошибка коммутации контакторов, номер неисправного контактора в регистре REG_PROBLEM
#define DF_LOW_PRESSURE							4	// Низкое давление в пневмосистеме
#define DF_SAFETY_ERROR							5	// Ошибка защитной цепи

// Problem
#define PROBLEM_NONE							0

//  Warning
#define WARNING_NONE							0
#define WARNING_CONTACTORS_CHECK				1	// Требуется проверка контактных сопротивлений контакторов, номер контактора в регистре REG_PROBLEM

//  User Errors
#define ERR_NONE								0
#define ERR_CONFIGURATION_LOCKED				1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED					2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY					3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD							4	//  Неправильный ключ

// Endpoints

#endif //  __DEV_OBJ_DIC_H

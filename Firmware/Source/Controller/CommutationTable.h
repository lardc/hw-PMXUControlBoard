// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"

// Constants
#define NUM_REGS_CONTACTORS			2	// 2 сдвиговых регистра на SPI_SS
#define NUM_REGS_RELAYS				2	// 2 сдвиговых регистра на SPI_SS_REL

#define NUM_REGS_TOTAL				(NUM_REGS_CONTACTORS + NUM_REGS_RELAYS)

#define COMMUTATION_TABLE_SIZE		(NUM_REGS_TOTAL * 8)
#define CONTACTOR_TABLE_SIZE		(NUM_REGS_CONTACTORS * 8)

#define CT_SAVE_TIMEOUT				1800000 // Значение в мс (30 мин)

#define NUM_REGS_SENSORS_SPI2		3		// Байт SPI2 

// Types
typedef struct __ContactorSensorState
{
	const Int8U Index;
	const Int8U SensorRegNumClose;
	const Int8U SensorBitClose;
	const Int8U SensorRegNumOpen;
	const Int8U SensorBitOpen;
	bool IsClosed;
} ContactorSensorState;

// Variables
extern Int32U CycleCounters[];
extern ContactorSensorState SensorsState[];
extern const Int16U SensorsStateLength;

// PE relays
#define PWR_L_TO_PE					27
#define PWR_C_TO_PE					28
#define PWR_H_TO_PE					29

// LCTU relays
#define LCTU_PLUS_TO_PWR_H			16
#define LCTU_PLUS_TO_PWR_C			30
#define LCTU_PLUS_TO_PWR_L			17

#define LCTU_MINUS_TO_PWR_H			19
#define LCTU_MINUS_TO_PWR_C			31
#define LCTU_MINUS_TO_PWR_L			18

// LCSU contactors
#define LCSU_PLUS_TO_PWR_H			0
#define LCSU_PLUS_TO_PWR_C			2
#define LCSU_PLUS_TO_PWR_L			4

#define LCSU_MINUS_TO_PWR_H			1
#define LCSU_MINUS_TO_PWR_C			3
#define LCSU_MINUS_TO_PWR_L			5

// Disconnect PE
static const Int8U __CT_DISCON_PE[] = {PWR_L_TO_PE, PWR_C_TO_PE, PWR_H_TO_PE};
#define CT_DISCON_PE				NULL		// Дефайн-заглушка

// UCE_SAT commutations
static const Int8U CT_UCESAT_POS1_GROUP_GREEN[] = {LCSU_PLUS_TO_PWR_C, LCSU_MINUS_TO_PWR_L};
static const Int8U CT_UCESAT_POS2_GROUP_BLUE[] = {LCSU_PLUS_TO_PWR_H, LCSU_MINUS_TO_PWR_C};
static const Int8U CT_UCESAT_POS2_GROUP_ORANGE[] = {LCSU_PLUS_TO_PWR_H, LCSU_MINUS_TO_PWR_L};

// UFW_CHOPPER_DIODE commutations
static const Int8U CT_UFW_POS1_GROUP_GREEN[] = {LCSU_PLUS_TO_PWR_L, LCSU_MINUS_TO_PWR_C};
static const Int8U CT_UFW_POS1_GROUP_BLUE[] = {LCSU_PLUS_TO_PWR_C, LCSU_MINUS_TO_PWR_H};
static const Int8U CT_UFW_POS2_GROUP_BLUE[] = {LCSU_PLUS_TO_PWR_C, LCSU_MINUS_TO_PWR_H};
static const Int8U CT_UFW_POS2_GROUP_ORANGE[] = {LCSU_PLUS_TO_PWR_L, LCSU_MINUS_TO_PWR_H};
static const Int8U CT_UFW_POS2_GROUP_PURPLE[] = {LCSU_PLUS_TO_PWR_H, LCSU_MINUS_TO_PWR_C};

// ICES_OR_IRMM commutations
static const Int8U CT_ICES_POS1_GROUP_GREEN[] = {LCTU_PLUS_TO_PWR_C, LCTU_MINUS_TO_PWR_L};
static const Int8U CT_ICES_POS1_GROUP_BLUE[] = {LCTU_PLUS_TO_PWR_H, LCTU_MINUS_TO_PWR_C};
static const Int8U CT_ICES_POS2_GROUP_BLUE[] = {LCTU_PLUS_TO_PWR_H, LCTU_MINUS_TO_PWR_C};
static const Int8U CT_ICES_POS2_GROUP_ORANGE[] = {LCTU_PLUS_TO_PWR_H, LCTU_MINUS_TO_PWR_L};
static const Int8U CT_ICES_POS2_GROUP_PURPLE[] = {LCTU_PLUS_TO_PWR_C, LCTU_MINUS_TO_PWR_H};

#endif // __COMMTABLE_H

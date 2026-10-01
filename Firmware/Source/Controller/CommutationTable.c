// ----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "CommutationTable.h"

// Definitions
#define REGISTER_1		0
#define REGISTER_2		1
#define REGISTER_3		2

// Variables
//
Int32U CycleCounters[COMMUTATION_TABLE_SIZE] = {0};
ContactorSensorState SensorsState[] =
{
	{LCSU_PLUS_TO_PWR_H,  REGISTER_1, BIT0, REGISTER_1, BIT1, false},
	{LCSU_PLUS_TO_PWR_C,  REGISTER_1, BIT4, REGISTER_1, BIT5, false},
	{LCSU_PLUS_TO_PWR_L,  REGISTER_2, BIT0, REGISTER_2, BIT1, false},
	{LCSU_MINUS_TO_PWR_H, REGISTER_1, BIT2, REGISTER_1, BIT3, false},
	{LCSU_MINUS_TO_PWR_C, REGISTER_1, BIT6, REGISTER_1, BIT7, false},
	{LCSU_MINUS_TO_PWR_L, REGISTER_2, BIT2, REGISTER_2, BIT3, false}
};
const Int16U SensorsStateLength = sizeof(SensorsState) / sizeof(SensorsState[0]);

/* Визуализация расположения индексов по регистрам
 *
 * CONTACTORS_REG, BIT0, REG_OUT_1			// 0
 * CONTACTORS_REG, BIT1, REG_OUT_1			// 1
 * CONTACTORS_REG, BIT2, REG_OUT_1			// 2
 * CONTACTORS_REG, BIT3, REG_OUT_1			// 3
 * CONTACTORS_REG, BIT4, REG_OUT_1			// 4
 * CONTACTORS_REG, BIT5, REG_OUT_1			// 5
 * CONTACTORS_REG, BIT6, REG_OUT_1			// 6
 * CONTACTORS_REG, BIT7, REG_OUT_1			// 7
 *
 * CONTACTORS_REG, BIT0, REG_OUT_2			// 8
 * CONTACTORS_REG, BIT1, REG_OUT_2			// 9
 * CONTACTORS_REG, BIT2, REG_OUT_2			// 10
 * CONTACTORS_REG, BIT3, REG_OUT_2			// 11
 * CONTACTORS_REG, BIT4, REG_OUT_2			// 12
 * CONTACTORS_REG, BIT5, REG_OUT_2			// 13
 * CONTACTORS_REG, BIT6, REG_OUT_2			// 14
 * CONTACTORS_REG, BIT7, REG_OUT_2			// 15
 *
 * RELAYS_REG, BIT0, REG_OUT_1				// 16
 * RELAYS_REG, BIT1, REG_OUT_1				// 17
 * RELAYS_REG, BIT2, REG_OUT_1				// 18
 * RELAYS_REG, BIT3, REG_OUT_1				// 19
 * RELAYS_REG, BIT4, REG_OUT_1				// 20
 * RELAYS_REG, BIT5, REG_OUT_1				// 21
 * RELAYS_REG, BIT6, REG_OUT_1				// 22
 * RELAYS_REG, BIT7, REG_OUT_1				// 23
 *
 * RELAYS_REG, BIT0, REG_OUT_2				// 24
 * RELAYS_REG, BIT1, REG_OUT_2				// 25
 * RELAYS_REG, BIT2, REG_OUT_2				// 26
 * RELAYS_REG, BIT3, REG_OUT_2				// 27
 * RELAYS_REG, BIT4, REG_OUT_2				// 28
 * RELAYS_REG, BIT5, REG_OUT_2				// 29
 * RELAYS_REG, BIT6, REG_OUT_2				// 30
 * RELAYS_REG, BIT7, REG_OUT_2				// 31
*/

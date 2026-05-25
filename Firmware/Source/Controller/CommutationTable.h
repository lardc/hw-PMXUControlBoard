// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Types
typedef enum __ContactType
{
	CT_NormalOpened = 0,
	CT_NormalClosed
} ContactType;

typedef struct __InnerCommutationTableItem
{
	Int8U Node;
	Int8U Bit;
	Int8U RegNum;
	ContactType Type;
} const InnerCommutationTableItem;

typedef struct __ContactorsStateTableItem
{
	Int8U BitClose;
	Int8U RegNumClose;
	Int8U BitOpen;
	Int8U RegNumOpen;
} const ContactorsStateTableItem;


// Commutation type
#define	CONTACTOR	0
#define	RELAY		1

// Shift register number (data byte position in full data bytes array)
#define REG1		0
#define REG2		1
#define REG3		2
#define REG4		3
#define REG5		4

#define BITS_PER_REG			8
#define COMM_CHECK_NO_ERROR		0xff

#define NUM_CONTACTOR_COMMUTATIONS				6
#define CONTACTORS_STATE_TABLE_SIZE				(NUM_CONTACTOR_COMMUTATIONS + 1)
#define INNER_COMMUTATION_LAST_ID				15
#define INNER_COMMUTATION_TABLE_SIZE			(INNER_COMMUTATION_LAST_ID + 1)

#define CT_SAVE_TIMEOUT			1800000 // Значение в мс (30 мин)

//Inner Relays
#define PWR_L_TO_GND		0
#define PWR_C_TO_GND		0
#define PWR_H_TO_GND		0
// LCTU
#define LCTU_POS_TO_PWR_H	0
#define LCTU_POS_TO_PWR_C	0
#define LCTU_POS_TO_PWR_L	0

#define LCTU_NEG_TO_PWR_H	0
#define LCTU_NEG_TO_PWR_C	0
#define LCTU_NEG_TO_PWR_L	0
// Contactors
// LCSU
#define LCSU_POS_TO_PWR_H	0
#define LCSU_POS_TO_PWR_C	0
#define LCSU_POS_TO_PWR_L	0

#define LCSU_NEG_TO_PWR_H	0
#define LCSU_NEG_TO_PWR_C	0
#define LCSU_NEG_TO_PWR_L	0

static InnerCommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] = {
		{0, 0, 0, 0},									// 0	// Do not use
		{CONTACTOR, BIT5, REG1, CT_NormalOpened},		// 1	// BUS2 to LCSU+
		{CONTACTOR, BIT4, REG1, CT_NormalOpened},		// 2	// BUS2 to LCSU-
		{CONTACTOR, BIT3, REG2, CT_NormalOpened},		// 3	// BUS2 to TOCU-
		{CONTACTOR, BIT2, REG2, CT_NormalOpened},		// 4	// BUS2 to TOCU+
		{CONTACTOR, BIT3, REG1, CT_NormalOpened},		// 5	// BUS1 to LCSU+
		{CONTACTOR, BIT2, REG1, CT_NormalOpened},		// 6	// BUS1 to LCSU-
		{CONTACTOR, BIT1, REG2, CT_NormalOpened},		// 7	// BUS1 to TOCU-
		{CONTACTOR, BIT0, REG2, CT_NormalOpened},		// 8	// BUS1 to TOCU+
		{CONTACTOR, BIT1, REG1, CT_NormalOpened},		// 9	// BUS3 to LCSU+
		{CONTACTOR, BIT0, REG1, CT_NormalOpened},		// 10	// BUS3 to LCSU-
		{CONTACTOR, BIT7, REG1, CT_NormalOpened},		// 11	// BUS3 to TOCU-
		{CONTACTOR, BIT6, REG1, CT_NormalOpened},		// 12	// BUS3 to TOCU+
		
		{RELAY, BIT0, REG1, CT_NormalOpened},			// 13	// BUS1 to LCTU+
		{RELAY, BIT1, REG1, CT_NormalOpened},			// 14	// BUS3 to LCTU+
		{RELAY, BIT2, REG1, CT_NormalOpened},			// 15	// BUS2 to LCTU-
		//{RELAY, BIT3, REG1, CT_NormalOpened},			// 16	// BUS1 to LCTU-
		//{RELAY, BIT4, REG1, CT_NormalOpened},			// 17	// BUS2 to ST_OUT
		//{RELAY, BIT5, REG1, CT_NormalOpened},			// 18	// BUS3 to ST_OUT
		//{RELAY, BIT6, REG1, CT_NormalOpened},			// 19	// BUS1 to ST_IN
		//{RELAY, BIT7, REG1, CT_NormalClosed},			// 20	// BUS1 to PE
		//{RELAY, BIT0, REG2, CT_NormalClosed},			// 21	// BUS2 to PE
		//{RELAY, BIT1, REG2, CT_NormalClosed},			// 22	// BUS3 to PE

		//{RELAY, BIT4, REG2, CT_NormalOpened},			// 23	// BUS3 to LCTU-
		//{RELAY, BIT6, REG2, CT_NormalOpened},			// 24	// BUS3 to LCTU+
};

static ContactorsStateTableItem ContactorsStateTable[CONTACTORS_STATE_TABLE_SIZE] = {
		{0, 0, 0, 0},									// 0	// Do not use
		{BIT3, REG2, BIT2, REG2},						// 1	// BUS2 to LCSU+
		{BIT1, REG2, BIT0, REG2},						// 2	// BUS2 to LCSU-
		{BIT7, REG3, BIT6, REG3},						// 3	// BUS2 to TOCU-
		{BIT5, REG3, BIT4, REG3},						// 4	// BUS2 to TOCU+
		{BIT7, REG1, BIT6, REG1},						// 5	// BUS1 to LCSU+
		{BIT5, REG1, BIT4, REG1}						// 6	// BUS1 to LCSU-
		//{BIT3, REG3, BIT2, REG3},						// 7	// BUS1 to TOCU-
		//{BIT1, REG3, BIT0, REG3},						// 8	// BUS1 to TOCU+
		//{BIT3, REG1, BIT2, REG1},						// 9	// BUS3 to LCSU+
		//{BIT1, REG1, BIT0, REG1},						// 10	// BUS3 to LCSU-
		//{BIT7, REG2, BIT6, REG2},						// 11	// BUS3 to TOCU-
		//{BIT5, REG2, BIT4, REG2}						// 12	// BUS3 to TOCU+
};

// Main Commutation to GND
static const Int8U CT_DISCON_GND[] = {PWR_L_TO_GND, PWR_C_TO_GND, PWR_H_TO_GND};

// UCE_SAT commutations
static const Int8U CT_UCESAT_POS_FIRST[] = {LCSU_POS_TO_PWR_C, LCSU_NEG_TO_PWR_L}; //Green
static const Int8U CT_UCESAT_POS_SECOND_VAR_ONE[] = {LCSU_POS_TO_PWR_H, LCSU_NEG_TO_PWR_C}; //Blue
static const Int8U CT_UCESAT_POS_SECOND_VAR_TWO[] = {LCSU_POS_TO_PWR_H, LCSU_NEG_TO_PWR_L}; //Orange

// UFW_CHOPPER_DIODE commutations
static const Int8U CT_UFW_POS_FIRST_VAR_ONE[] = {LCSU_POS_TO_PWR_L, LCSU_NEG_TO_PWR_C}; //Green
static const Int8U CT_UFW_POS_FIRST_VAR_TWO[] = {LCSU_POS_TO_PWR_C, LCSU_NEG_TO_PWR_H};	// Blue
static const Int8U CT_UFW_POS_SECOND_VAR_ONE[] = {LCSU_POS_TO_PWR_C, LCSU_NEG_TO_PWR_H}; // Blue
static const Int8U CT_UFW_POS_SECOND_VAR_TWO[] = {LCSU_POS_TO_PWR_L, LCSU_NEG_TO_PWR_H}; //Orange
static const Int8U CT_UFW_POS_SECOND_VAR_THREE[] = {LCSU_POS_TO_PWR_H, LCSU_NEG_TO_PWR_C}; // Purple

// ICES_OR_IRMM commutations
static const Int8U CT_ICES_POS_FIRST_VAR_ONE[] = {LCTU_POS_TO_PWR_C, LCTU_NEG_TO_PWR_L}; //Green
static const Int8U CT_ICES_POS_FIRST_VAR_TWO[] = {LCTU_POS_TO_PWR_H, LCTU_NEG_TO_PWR_C}; // Blue
static const Int8U CT_ICES_POS_SECOND_VAR_ONE[] = {LCTU_POS_TO_PWR_H, LCTU_NEG_TO_PWR_C}; // Blue
static const Int8U CT_ICES_POS_SECOND_VAR_TWO[] = {LCTU_POS_TO_PWR_H, LCTU_NEG_TO_PWR_L}; //Orange
static const Int8U CT_ICES_POS_SECOND_VAR_THREE[] = {LCTU_POS_TO_PWR_C, LCTU_NEG_TO_PWR_H}; // Purple

// 301 arrays
// Default DataArrays
//
static const Int8U CT_DFLT_Relays[] = {0, 0};
static const Int8U CT_DFLT_Contactors[] = {0, 0};

#endif // __COMMTABLE_H

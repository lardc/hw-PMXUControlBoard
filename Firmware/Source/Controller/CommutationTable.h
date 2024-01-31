﻿// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"


// Types
typedef struct __InnerCommutationTableItem
{
	Int8U Type;
	Int8U Bit;
	Int8U RegNum;
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

#define NUM_RELAYS_PER_COMMUTATION				4
#define NUM_CONTACTOR_COMMUTATIONS				12
#define CONTACTORS_STATE_TABLE_SIZE				(2 * NUM_CONTACTOR_COMMUTATIONS)
#define NUM_RELAY_GROUPS_COMMUTATIONS			10
#define INNER_COMMUTATION_TABLE_SIZE 			((NUM_RELAY_GROUPS_COMMUTATIONS * NUM_RELAYS_PER_COMMUTATION) + NUM_CONTACTOR_COMMUTATIONS)

// Inner Contactors commutations (Side1_Side2)
// TOCU HP
#define BUS1_TOCU_N				6
#define BUS1_TOCU_P				7
#define BUS2_TOCU_N				2
#define BUS2_TOCU_P				3
#define BUS3_TOCU_N				10
#define BUS3_TOCU_P				11
// LCSU
#define BUS1_LCSU_N				5
#define BUS1_LCSU_P				4
#define BUS2_LCSU_N				1
#define BUS2_LCSU_P				0
#define BUS3_LCSU_N				9
#define BUS3_LCSU_P				8


// Inner Relays commutations (Side1_Side2_RelayNumber)
// PE commutations
#define BUS1_PE					12
#define BUS2_PE					13
#define BUS3_PE					14

// Selftest source commutations
#define BUS1_STN				15
#define BUS2_STP				16
#define BUS3_STP				17

// LCTU commutations
#define BUS1_LCTUP				20
#define BUS3_LCTUP				21
#define BUS1_LCTUN				18
#define BUS2_LCTUN				19


static InnerCommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] = {
		{CONTACTOR, BIT5, REG1},		// 0	// BUS1 to TOCU+
		{CONTACTOR, BIT4, REG1},		// 1	// BUS1 to TOCU-
		{CONTACTOR, BIT3, REG2},		// 2	// BUS1 to LCSU+
		{CONTACTOR, BIT2, REG2},		// 3	// BUS1 to LCSU-
		{CONTACTOR, BIT3, REG1},		// 4	// BUS2 to TOCU+
		{CONTACTOR, BIT2, REG1},		// 5	// BUS2 to TOCU-
		{CONTACTOR, BIT1, REG2},		// 6	// BUS2 to LCSU+
		{CONTACTOR, BIT0, REG2},		// 7	// BUS2 to LCSU-
		{CONTACTOR, BIT1, REG1},		// 8	// BUS3 to TOCU+
		{CONTACTOR, BIT0, REG1},		// 9	// BUS3 to TOCU-
		{CONTACTOR, BIT7, REG1},		// 10	// BUS3 to LCSU+
		{CONTACTOR, BIT6, REG1},		// 11	// BUS3 to LCSU-
		
		{RELAY, BIT7, REG1},			// 12	// BUS1 to PE
		{RELAY, BIT0, REG2},			// 13	// BUS2 to PE
		{RELAY, BIT1, REG2},			// 14	// BUS3 to PE
		{RELAY, BIT6, REG1},			// 15	// BUS1 to ST-
		{RELAY, BIT4, REG1},			// 16	// BUS2 to ST+
		{RELAY, BIT5, REG1},			// 17	// BUS3 to ST+
		{RELAY, BIT3, REG1},			// 18	// BUS1 to LCTU-
		{RELAY, BIT2, REG1},			// 19	// BUS2 to LCTU-
		{RELAY, BIT0, REG1},			// 20	// BUS1 to LCTU+
		{RELAY, BIT1, REG1},			// 21	// BUS3 to LCTU+
};


// Default DataArrays
static const Int8U CT_DFLT_Relays[] = {0, 0, 0, 0, 0};
static const Int8U CT_DFLT_Contactors[] = {0, 0};

// Main Commutations
static const Int8U CT_NO_PE[] = {BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Ices_Pos1[] = {BUS3_LCTUP, BUS1_LCTUN, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Ices_Pos2[] = {BUS1_LCTUP, BUS2_LCTUN, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Qg_Pos1[] = {BUS3_TOCU_P, BUS1_TOCU_N, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Qg_Pos2[] = {BUS1_TOCU_P, BUS2_TOCU_N, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Vcesat_Pos1[] = {BUS3_LCSU_P, BUS1_LCSU_N, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Vcesat_Pos2[] = {BUS1_LCSU_P, BUS2_LCSU_N, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Vf_Pos1[] = {BUS1_LCSU_P, BUS3_LCSU_N, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Vf_Pos2[] = {BUS2_LCSU_P, BUS1_LCSU_N, BUS1_PE, BUS2_PE, BUS3_PE};

// Continuity Selftest Commutations
static const Int8U CT_ST_PE1[] = {BUS1_STN, BUS2_STP, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_ST_PE2[] = {BUS1_STN, BUS3_STP, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_ST_LCTU1[] = {BUS1_STN, BUS2_STP, BUS3_PE, BUS1_LCTUN, BUS2_LCTUN};
static const Int8U CT_ST_LCTU2[] = {BUS1_STN, BUS3_STP, BUS2_PE, BUS1_LCTUP, BUS3_LCTUP};

static const Int8U CT_ST_TOCU1[] = {BUS1_STN, BUS2_STP, BUS1_TOCU_P, BUS2_TOCU_P, BUS2_PE, BUS3_PE};
static const Int8U CT_ST_TOCU2[] = {BUS1_STN, BUS3_STP, BUS1_TOCU_P, BUS3_TOCU_P, BUS2_PE, BUS3_PE};
static const Int8U CT_ST_TOCU3[] = {BUS1_STN, BUS2_STP, BUS1_TOCU_N, BUS2_TOCU_N, BUS3_PE};
static const Int8U CT_ST_TOCU4[] = {BUS1_STN, BUS3_STP, BUS1_TOCU_N, BUS3_TOCU_N, BUS2_PE};

static const Int8U CT_ST_LCSU1[] = {BUS1_STN, BUS2_STP, BUS1_LCSU_P, BUS2_LCSU_P, BUS2_PE, BUS3_PE};
static const Int8U CT_ST_LCSU2[] = {BUS1_STN, BUS3_STP, BUS1_LCSU_P, BUS3_LCSU_P, BUS2_PE, BUS3_PE};
static const Int8U CT_ST_LCSU3[] = {BUS1_STN, BUS2_STP, BUS1_LCSU_N, BUS2_LCSU_N, BUS3_PE};
static const Int8U CT_ST_LCSU4[] = {BUS1_STN, BUS3_STP, BUS1_LCSU_N, BUS3_LCSU_N, BUS2_PE};

// Relay opening Self Test - relay numbers for checking
static const Int8U CT_ST_RO_PE1[] = {BUS1_PE, BUS2_PE};
static const Int8U CT_ST_RO_PE2[] = {BUS3_PE};
static const Int8U CT_ST_RO_LCTU1[] = {BUS1_LCTUN, BUS2_LCTUN};
static const Int8U CT_ST_RO_LCTU2[] = {BUS1_LCTUP, BUS3_LCTUP};

static ContactorsStateTableItem ContactorsStateTable[CONTACTORS_STATE_TABLE_SIZE] = {
		{BIT2, REG2, BIT3, REG2},			// 0	// BUS1 to TOCU+
		{BIT0, REG2, BIT1, REG2},			// 1	// BUS1 to TOCU-
		{BIT6, REG3, BIT7, REG3},			// 2	// BUS1 to LCSU+
		{BIT4, REG3, BIT5, REG3},			// 3	// BUS1 to LCSU-
		{BIT6, REG1, BIT7, REG1},			// 4	// BUS2 to TOCU+
		{BIT4, REG1, BIT5, REG1},			// 5	// BUS2 to TOCU-
		{BIT2, REG3, BIT3, REG3},			// 6	// BUS2 to LCSU+
		{BIT0, REG3, BIT1, REG3},			// 7	// BUS2 to LCSU-
		{BIT2, REG1, BIT3, REG1},			// 8	// BUS3 to TOCU+
		{BIT0, REG1, BIT1, REG1},			// 9	// BUS3 to TOCU-
		{BIT6, REG2, BIT7, REG2},			// 10	// BUS3 to LCSU+
		{BIT4, REG2, BIT5, REG2}			// 11	// BUS3 to LCSU-
};


#endif // __COMMTABLE_H

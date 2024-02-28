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

#define NUM_RELAYS_PER_COMMUTATION				4
#define NUM_CONTACTOR_COMMUTATIONS				12
#define CONTACTORS_STATE_TABLE_SIZE				(NUM_CONTACTOR_COMMUTATIONS + 1)
#define NUM_RELAY_GROUPS_COMMUTATIONS			10
#define INNER_COMMUTATION_TABLE_SIZE 			((NUM_RELAY_GROUPS_COMMUTATIONS * NUM_RELAYS_PER_COMMUTATION) + NUM_CONTACTOR_COMMUTATIONS + 1)

// Inner Contactors commutations (Side1_Side2)
// TOCU HP
#define BUS1_TOCUN				7
#define BUS1_TOCUP				8
#define BUS2_TOCUN				3
#define BUS2_TOCUP				4
#define BUS3_TOCUN				11
#define BUS3_TOCUP				12
// LCSU
#define BUS1_LCSUN				6
#define BUS1_LCSUP				5
#define BUS2_LCSUN				2
#define BUS2_LCSUP				1
#define BUS3_LCSUN				10
#define BUS3_LCSUP				9


// Inner Relays commutations (Side1_Side2_RelayNumber)
// PE commutations
#define BUS1_PE					13
#define BUS2_PE					14
#define BUS3_PE					15

// Selftest source commutations
#define BUS1_STN				16
#define BUS2_STP				17
#define BUS3_STP				18

// LCTU commutations
#define BUS1_LCTUP				21
#define BUS3_LCTUP				22
#define BUS1_LCTUN				19
#define BUS2_LCTUN				20


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
		
		{RELAY, BIT7, REG1, CT_NormalClosed},			// 13	// BUS1 to PE
		{RELAY, BIT0, REG2, CT_NormalClosed},			// 14	// BUS2 to PE
		{RELAY, BIT1, REG2, CT_NormalClosed},			// 15	// BUS3 to PE
		{RELAY, BIT6, REG1, CT_NormalOpened},			// 16	// BUS1 to ST-
		{RELAY, BIT4, REG1, CT_NormalOpened},			// 17	// BUS2 to ST+
		{RELAY, BIT5, REG1, CT_NormalOpened},			// 18	// BUS3 to ST+
		{RELAY, BIT3, REG1, CT_NormalOpened},			// 19	// BUS1 to LCTU-
		{RELAY, BIT2, REG1, CT_NormalOpened},			// 20	// BUS2 to LCTU-
		{RELAY, BIT0, REG1, CT_NormalOpened},			// 21	// BUS1 to LCTU+
		{RELAY, BIT1, REG1, CT_NormalOpened},			// 22	// BUS3 to LCTU+
};

static ContactorsStateTableItem ContactorsStateTable[CONTACTORS_STATE_TABLE_SIZE] = {
		{0, 0, 0, 0},									// 0	// Do not use
		{BIT3, REG2, BIT2, REG2},						// 1	// BUS2 to LCSU+
		{BIT1, REG2, BIT0, REG2},						// 2	// BUS2 to LCSU-
		{BIT7, REG3, BIT6, REG3},						// 3	// BUS2 to TOCU-
		{BIT5, REG3, BIT4, REG3},						// 4	// BUS2 to TOCU+
		{BIT7, REG1, BIT6, REG1},						// 5	// BUS1 to LCSU+
		{BIT5, REG1, BIT4, REG1},						// 6	// BUS1 to LCSU-
		{BIT3, REG3, BIT2, REG3},						// 7	// BUS1 to TOCU-
		{BIT1, REG3, BIT0, REG3},						// 8	// BUS1 to TOCU+
		{BIT3, REG1, BIT2, REG1},						// 9	// BUS3 to LCSU+
		{BIT1, REG1, BIT0, REG1},						// 10	// BUS3 to LCSU-
		{BIT7, REG2, BIT6, REG2},						// 11	// BUS3 to TOCU-
		{BIT5, REG2, BIT4, REG2}						// 12	// BUS3 to TOCU+
};


// Default DataArrays
//
static const Int8U CT_DFLT_Relays[] = {0, 0};
static const Int8U CT_DFLT_Contactors[] = {0, 0};

// Main Commutations
//
static const Int8U CT_NO_PE[] = {BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Ices_Pos1[] = {BUS1_LCTUP, BUS2_LCTUN, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Ices_Pos2[] = {BUS3_LCTUP, BUS1_LCTUN, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Qg_Pos1[] = {BUS1_TOCUP, BUS2_TOCUN, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Qg_Pos2[] = {BUS3_TOCUP, BUS1_TOCUN, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Vcesat_Pos1[] = {BUS1_LCSUP, BUS2_LCSUN, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Vcesat_Pos2[] = {BUS3_LCSUP, BUS1_LCSUN, BUS1_PE, BUS2_PE, BUS3_PE};

static const Int8U CT_Vf_Pos1[] = {BUS2_LCSUP, BUS1_LCSUN, BUS1_PE, BUS2_PE, BUS3_PE};
static const Int8U CT_Vf_Pos2[] = {BUS1_LCSUP, BUS3_LCSUN, BUS1_PE, BUS2_PE, BUS3_PE};

// Continuity Selftest Commutations
//
static const Int8U CT_ST_LCTU1[] = {BUS3_STP, BUS3_LCTUP, BUS1_LCTUP, BUS1_STN};
static const Int8U CT_ST_LCTU2[] = {BUS2_STP, BUS2_LCTUN, BUS1_LCTUN, BUS1_STN};

static const Int8U CT_ST_PE1[] = {BUS2_STP, BUS2_PE, BUS1_PE, BUS1_STN};
static const Int8U CT_ST_PE2[] = {BUS3_STP, BUS3_PE, BUS1_PE, BUS1_STN};

static const Int8U CT_ST_LCSU1[] = {BUS3_LCSUN, BUS2_LCSUN, BUS2_LCSUP, BUS1_LCSUP};
static const Int8U CT_ST_LCSU2[] = {BUS2_LCSUP, BUS3_LCSUP, BUS3_LCSUN, BUS1_LCSUN};

static const Int8U CT_ST_TOCU1[] = {BUS3_TOCUN, BUS2_TOCUN, BUS2_TOCUP, BUS1_TOCUP};
static const Int8U CT_ST_TOCU2[] = {BUS2_TOCUP, BUS3_TOCUP, BUS3_TOCUN, BUS1_TOCUN};

static const Int8U CT_ST_BUS1_2[] = {BUS1_STN, BUS2_STP};
static const Int8U CT_ST_BUS1_3[] = {BUS1_STN, BUS3_STP};

#endif // __COMMTABLE_H

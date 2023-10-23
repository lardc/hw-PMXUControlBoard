// -----------------------------------------
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
#define BUS1_TOCUN				1
#define BUS1_TOCUP				0
#define BUS2_TOCUN				5
#define BUS2_TOCUP				4
#define BUS3_TOCUN				9
#define BUS3_TOCUP				8
// LCSU
#define BUS1_LCSUN				3
#define BUS1_LCSUP				2
#define BUS2_LCSUN				7
#define BUS2_LCSUP				6
#define BUS3_LCSUN				11
#define BUS3_LCSUP				10


// Inner Relays commutations (Side1_Side2_RelayNumber)
// PE commutations
#define BUS1_PE_1				12
#define BUS1_PE_2				13
#define BUS1_PE_3				14
#define BUS1_PE_4				15

#define BUS2_PE_1				16
#define BUS2_PE_2				17
#define BUS2_PE_3				18
#define BUS2_PE_4				19

#define BUS3_PE_1				20
#define BUS3_PE_2				21
#define BUS3_PE_3				22
#define BUS3_PE_4				23

// Selftest source commutations
#define BUS1_STN_1				24
#define BUS1_STN_2				25
#define BUS1_STN_3				26
#define BUS1_STN_4				27

#define BUS2_STP_1				28
#define BUS2_STP_2				29
#define BUS2_STP_3				30
#define BUS2_STP_4				31

#define BUS3_STP_1				32
#define BUS3_STP_2				33
#define BUS3_STP_3				34
#define BUS3_STP_4				35

// LCTU commutations
#define BUS1_LCTUP_1			44
#define BUS1_LCTUP_2			45
#define BUS1_LCTUP_3			46
#define BUS1_LCTUP_4			47

#define BUS3_LCTUP_1			48
#define BUS3_LCTUP_2			49
#define BUS3_LCTUP_3			50
#define BUS3_LCTUP_4			51

#define BUS1_LCTUN_1			36
#define BUS1_LCTUN_2			37
#define BUS1_LCTUN_3			38
#define BUS1_LCTUN_4			39

#define BUS2_LCTUN_1			40
#define BUS2_LCTUN_2			41
#define BUS2_LCTUN_3			42
#define BUS2_LCTUN_4			43


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
		
		{RELAY, BIT4, REG4},			// 12	// BUS1 to PE_1
		{RELAY, BIT5, REG4},			// 13	// BUS1 to PE_2
		{RELAY, BIT6, REG4},			// 14	// BUS1 to PE_3
		{RELAY, BIT7, REG4},			// 15	// BUS1 to PE_4
		{RELAY, BIT0, REG5},			// 16	// BUS2 to PE_1
		{RELAY, BIT1, REG5},			// 17	// BUS2 to PE_2
		{RELAY, BIT2, REG5},			// 18	// BUS2 to PE_3
		{RELAY, BIT3, REG5},			// 19	// BUS2 to PE_4
		{RELAY, BIT4, REG5},			// 20	// BUS3 toPE_1
		{RELAY, BIT5, REG5},			// 21	// BUS3 to PE_2
		{RELAY, BIT6, REG5},			// 22	// BUS3 to PE_3
		{RELAY, BIT7, REG5},			// 23	// BUS3 to PE_4
		{RELAY, BIT0, REG4},			// 24	// BUS1 to ST-_1
		{RELAY, BIT1, REG4},			// 25	// BUS1 to ST-_2
		{RELAY, BIT2, REG4},			// 26	// BUS1 to ST-_3
		{RELAY, BIT3, REG4},			// 27	// BUS1 to ST-_4
		{RELAY, BIT0, REG3},			// 28	// BUS2 to ST+_1
		{RELAY, BIT1, REG3},			// 29	// BUS2 to ST+_2
		{RELAY, BIT2, REG3},			// 30	// BUS2 to ST+_3
		{RELAY, BIT3, REG3},			// 31	// BUS2 to ST+_4
		{RELAY, BIT4, REG3},			// 32	// BUS3 to ST+_1
		{RELAY, BIT5, REG3},			// 33	// BUS3 to ST+_2
		{RELAY, BIT6, REG3},			// 34	// BUS3 to ST+_3
		{RELAY, BIT7, REG3},			// 35	// BUS3 to ST+_4
		{RELAY, BIT4, REG2},			// 36	// BUS1 to LCTU-_1
		{RELAY, BIT5, REG2},			// 37	// BUS1 to LCTU-_2
		{RELAY, BIT6, REG2},			// 38	// BUS1 to LCTU-_3
		{RELAY, BIT7, REG2},			// 39	// BUS1 to LCTU-_4
		{RELAY, BIT0, REG2},			// 40	// BUS2 to LCTU-_1
		{RELAY, BIT1, REG2},			// 41	// BUS2 to LCTU-_2
		{RELAY, BIT2, REG2},			// 42	// BUS2 to LCTU-_3
		{RELAY, BIT3, REG2},			// 43	// BUS2 to LCTU-_4
		{RELAY, BIT0, REG1},			// 44	// BUS1 to LCTU+_1
		{RELAY, BIT1, REG1},			// 45	// BUS1 to LCTU+_2
		{RELAY, BIT2, REG1},			// 46	// BUS1 to LCTU+_3
		{RELAY, BIT3, REG1},			// 47	// BUS1 to LCTU+_4
		{RELAY, BIT4, REG1},			// 48	// BUS3 to LCTU+_1
		{RELAY, BIT5, REG1},			// 49	// BUS3 to LCTU+_2
		{RELAY, BIT6, REG1},			// 50	// BUS3 to LCTU+_3
		{RELAY, BIT7, REG1}				// 51	// BUS3 to LCTU+_4
};


// Default DataArrays
static const Int8U CT_DFLT_Relays[] = {0, 0, 0, 0, 0};
static const Int8U CT_DFLT_Contactors[] = {0, 0};

// Main Commutations
static const Int8U CT_PE[] = {BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4,
		BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_Ices_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2,
		BUS1_LCTUN_3, BUS1_LCTUN_4};
static const Int8U CT_Ices_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
		BUS2_LCTUN_3, BUS2_LCTUN_4};
static const Int8U CT_Idds_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2,
		BUS1_LCTUN_3, BUS1_LCTUN_4};
static const Int8U CT_Idds_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
BUS2_LCTUN_3, BUS2_LCTUN_4};
static const Int8U CT_Ir_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2,
		BUS1_LCTUN_3, BUS1_LCTUN_4};
static const Int8U CT_Ir_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
		BUS2_LCTUN_3, BUS2_LCTUN_4};
static const Int8U CT_Qg_UP[] = {BUS3_TOCUP, BUS1_TOCUN};
static const Int8U CT_Qg_UP_REV[] = {BUS1_TOCUP, BUS3_TOCUN};
static const Int8U CT_Qg_DOWN[] = {BUS1_TOCUP, BUS2_TOCUN};
static const Int8U CT_Qg_DOWN_REV[] = {BUS2_TOCUP, BUS1_TOCUN};
static const Int8U CT_Vcesat_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
static const Int8U CT_Vcesat_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
static const Int8U CT_Vcesat_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
static const Int8U CT_Vcesat_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
static const Int8U CT_Vsd_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
static const Int8U CT_Vsd_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
static const Int8U CT_Vsd_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
static const Int8U CT_Vsd_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
static const Int8U CT_Rdson_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
static const Int8U CT_Rdson_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
static const Int8U CT_Rdson_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
static const Int8U CT_Rdson_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
static const Int8U CT_Vf_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
static const Int8U CT_Vf_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
static const Int8U CT_Vf_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
static const Int8U CT_Vf_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};


// Continuity Selftest Commutations
static const Int8U CT_ST_PE1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2,
		BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_PE2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2,
		BUS3_PE_3, BUS3_PE_4};

static const Int8U CT_ST_LCTU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4, BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3, BUS1_LCTUN_4,
		BUS2_LCTUN_1, BUS2_LCTUN_2, BUS2_LCTUN_3, BUS2_LCTUN_4};
static const Int8U CT_ST_LCTU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4,
		BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4};

static const Int8U CT_ST_TOCU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS1_TOCUP, BUS2_TOCUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_TOCU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS1_TOCUP, BUS3_TOCUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_TOCU3[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS1_TOCUN, BUS2_TOCUN, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_TOCU4[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS1_TOCUN, BUS3_TOCUN, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4};

static const Int8U CT_ST_LCSU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS1_LCSUP, BUS2_LCSUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_LCSU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS1_LCSUP, BUS3_LCSUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_LCSU3[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3,
		BUS2_STP_4, BUS1_LCSUN, BUS2_LCSUN, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_LCSU4[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3,
		BUS3_STP_4, BUS1_LCSUN, BUS3_LCSUN, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4};

// Relay opening Self Test - relay numbers for checking
static const Int8U CT_ST_RO_PE1[] = {BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3,
		BUS2_PE_4};
static const Int8U CT_ST_RO_PE2[] = {BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
static const Int8U CT_ST_RO_LCTU1[] = {BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3, BUS1_LCTUN_4, BUS2_LCTUN_1,
		BUS2_LCTUN_2, BUS2_LCTUN_3, BUS2_LCTUN_4};
static const Int8U CT_ST_RO_LCTU2[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS3_LCTUP_1,
		BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4};

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

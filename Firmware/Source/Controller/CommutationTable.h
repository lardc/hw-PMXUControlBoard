// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"

// Types
//
typedef struct __InnerCommutationTableItem
{
	Int8U Type;
	Int8U Bit;
	Int8U RegNum;
} InnerCommutationTableItem;
//
typedef struct __ContactorsCommutationFBTableItem
{
	Int8U Bit;
	Int8U RegNum;
} ContactorsCommutationFBTableItem;

//
// Shift registers pins and data bits
#define PIN_1		BIT0
#define PIN_2		BIT1
#define PIN_3		BIT2
#define PIN_4		BIT3
#define	PIN_5		BIT4
#define	PIN_6		BIT5
#define	PIN_7		BIT6
#define	PIN_8		BIT7
//
// Commutation type
#define	CONTACTOR	0
#define	RELAY		1
//
// Shift register number (data byte position in full data bytes array)
#define REG1		0
#define REG2		1
#define REG3		2
#define REG4		3
#define REG5		4
//
#define BITS_PER_REG	8
//
#define NUM_RELAYS_PER_COMMUTATION				4
#define NUM_CONTACTOR_COMMUTATIONS				12
#define CONTACTOR_COMMUTATIONS_FB_TABLE_SIZE	(2 * NUM_CONTACTOR_COMMUTATIONS)
#define NUM_RELAY_COMMUTATIONS					10
#define INNER_COMMUTATION_TABLE_SIZE 			((NUM_RELAY_COMMUTATIONS * NUM_RELAYS_PER_COMMUTATION) + NUM_CONTACTOR_COMMUTATIONS)
//
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
//
//
// Inner Relays commutations (Side1_Side2_RelayNumber)
// PE commutations
#define BUS1_PE_1				12
#define BUS1_PE_2				13
#define BUS1_PE_3				14
#define BUS1_PE_4				15
//
#define BUS2_PE_1				16
#define BUS2_PE_2				17
#define BUS2_PE_3				18
#define BUS2_PE_4				19
//
#define BUS3_PE_1				20
#define BUS3_PE_2				21
#define BUS3_PE_3				22
#define BUS3_PE_4				23
//
// Selftest source commutations
#define BUS1_STN_1				24
#define BUS1_STN_2				25
#define BUS1_STN_3				26
#define BUS1_STN_4				27
//
#define BUS2_STP_1				28
#define BUS2_STP_2				29
#define BUS2_STP_3				30
#define BUS2_STP_4				31
//
#define BUS3_STP_1				32
#define BUS3_STP_2				33
#define BUS3_STP_3				34
#define BUS3_STP_4				35
//
// LCTU commutations
#define BUS1_LCTUP_1			44
#define BUS1_LCTUP_2			45
#define BUS1_LCTUP_3			46
#define BUS1_LCTUP_4			47
//
#define BUS3_LCTUP_1			48
#define BUS3_LCTUP_2			49
#define BUS3_LCTUP_3			50
#define BUS3_LCTUP_4			51
//
#define BUS1_LCTUN_1			36
#define BUS1_LCTUN_2			37
#define BUS1_LCTUN_3			38
#define BUS1_LCTUN_4			39
//
#define BUS2_LCTUN_1			40
#define BUS2_LCTUN_2			41
#define BUS2_LCTUN_3			42
#define BUS2_LCTUN_4			43
//
//
InnerCommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] =
{
		{CONTACTOR, PIN_6, REG1}, 		// 0	// BUS1 to TOCU+
		{CONTACTOR, PIN_5, REG1},		// 1	// BUS1 to TOCU-
		{CONTACTOR, PIN_4, REG2},		// 2	// BUS1 to LCSU+
		{CONTACTOR, PIN_3, REG2},		// 3	// BUS1 to LCSU-
		{CONTACTOR, PIN_4, REG1},		// 4	// BUS2 to TOCU+
		{CONTACTOR, PIN_3, REG1},		// 5	// BUS2 to TOCU-
		{CONTACTOR, PIN_2, REG2},		// 6	// BUS2 to LCSU+
		{CONTACTOR, PIN_1, REG2},		// 7	// BUS2 to LCSU-
		{CONTACTOR, PIN_2, REG1},		// 8	// BUS3 to TOCU+
		{CONTACTOR, PIN_1, REG1},		// 9	// BUS3 to TOCU-
		{CONTACTOR, PIN_8, REG1},		// 10	// BUS3 to LCSU+
		{CONTACTOR, PIN_7, REG1},		// 11	// BUS3 to LCSU-
		//
		{RELAY, PIN_5, REG4},			// 12	// BUS1 to PE_1
		{RELAY, PIN_6, REG4},			// 13	// BUS1 to PE_2
		{RELAY, PIN_7, REG4},			// 14	// BUS1 to PE_3
		{RELAY, PIN_8, REG4},			// 15	// BUS1 to PE_4
		{RELAY, PIN_1, REG5},			// 16	// BUS2 to PE_1
		{RELAY, PIN_2, REG5},			// 17	// BUS2 to PE_2
		{RELAY, PIN_3, REG5},			// 18	// BUS2 to PE_3
		{RELAY, PIN_4, REG5},			// 19	// BUS2 to PE_4
		{RELAY, PIN_5, REG5},			// 20	// BUS3 toPE_1
		{RELAY, PIN_6, REG5},			// 21	// BUS3 to PE_2
		{RELAY, PIN_7, REG5},			// 22	// BUS3 to PE_3
		{RELAY, PIN_8, REG5},			// 23	// BUS3 to PE_4
		{RELAY, PIN_1, REG4},			// 24	// BUS1 to ST-_1
		{RELAY, PIN_2, REG4},			// 25	// BUS1 to ST-_2
		{RELAY, PIN_3, REG4},			// 26	// BUS1 to ST-_3
		{RELAY, PIN_4, REG4},			// 27	// BUS1 to ST-_4
		{RELAY, PIN_1, REG3},			// 28	// BUS2 to ST+_1
		{RELAY, PIN_2, REG3},			// 29	// BUS2 to ST+_2
		{RELAY, PIN_3, REG3},			// 30	// BUS2 to ST+_3
		{RELAY, PIN_4, REG3},			// 31	// BUS2 to ST+_4
		{RELAY, PIN_5, REG3},			// 32	// BUS3 to ST+_1
		{RELAY, PIN_6, REG3},			// 33	// BUS3 to ST+_2
		{RELAY, PIN_7, REG3},			// 34	// BUS3 to ST+_3
		{RELAY, PIN_8, REG3},			// 35	// BUS3 to ST+_4
		{RELAY, PIN_5, REG2},			// 36	// BUS1 to LCTU-_1
		{RELAY, PIN_6, REG2},			// 37	// BUS1 to LCTU-_2
		{RELAY, PIN_7, REG2},			// 38	// BUS1 to LCTU-_3
		{RELAY, PIN_8, REG2},			// 39	// BUS1 to LCTU-_4
		{RELAY, PIN_1, REG2},			// 40	// BUS2 to LCTU-_1
		{RELAY, PIN_2, REG2},			// 41	// BUS2 to LCTU-_2
		{RELAY, PIN_3, REG2},			// 42	// BUS2 to LCTU-_3
		{RELAY, PIN_4, REG2},			// 43	// BUS2 to LCTU-_4
		{RELAY, PIN_1, REG1},			// 44	// BUS1 to LCTU+_1
		{RELAY, PIN_2, REG1},			// 45	// BUS1 to LCTU+_2
		{RELAY, PIN_3, REG1},			// 46	// BUS1 to LCTU+_3
		{RELAY, PIN_4, REG1},			// 47	// BUS1 to LCTU+_4
		{RELAY, PIN_5, REG1},			// 48	// BUS3 to LCTU+_1
		{RELAY, PIN_6, REG1},			// 49	// BUS3 to LCTU+_2
		{RELAY, PIN_7, REG1},			// 50	// BUS3 to LCTU+_3
		{RELAY, PIN_8, REG1}			// 51	// BUS3 to LCTU+_4
};
//
// Default DataArrays
Int8U CT_DFLT_Relays[] = {0, 0, 0, 0, 0};
Int8U CT_DFLT_Contactors[] = {0, 0};
Int8U CT_DFLT_ContactorsFB[] = {0, 0, 0};

// Main Commutations
Int8U CT_PE[] = {BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1,
		BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_Ices_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3,
		BUS1_LCTUN_4};
Int8U CT_Ices_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
		BUS2_LCTUN_3, BUS2_LCTUN_4};
Int8U CT_Idds_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3,
		BUS1_LCTUN_4};
Int8U CT_Idds_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
		BUS2_LCTUN_3, BUS2_LCTUN_4};
Int8U CT_Ir_UP[] = {BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4, BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3,
		BUS1_LCTUN_4};
Int8U CT_Ir_DOWN[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS2_LCTUN_1, BUS2_LCTUN_2, BUS2_LCTUN_3,
		BUS2_LCTUN_4};
Int8U CT_Qg_UP[] = {BUS3_TOCUP, BUS1_TOCUN};
Int8U CT_Qg_UP_REV[] = {BUS1_TOCUP, BUS3_TOCUN};
Int8U CT_Qg_DOWN[] = {BUS1_TOCUP, BUS2_TOCUN};
Int8U CT_Qg_DOWN_REV[] = {BUS2_TOCUP, BUS1_TOCUN};
Int8U CT_Vcesat_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
Int8U CT_Vcesat_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
Int8U CT_Vcesat_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
Int8U CT_Vcesat_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
Int8U CT_Vsd_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
Int8U CT_Vsd_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
Int8U CT_Vsd_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
Int8U CT_Vsd_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
Int8U CT_Rdson_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
Int8U CT_Rdson_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
Int8U CT_Rdson_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
Int8U CT_Rdson_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
Int8U CT_Vf_UP[] = {BUS3_LCSUP, BUS1_LCSUN};
Int8U CT_Vf_UP_REV[] = {BUS1_LCSUP, BUS3_LCSUN};
Int8U CT_Vf_DOWN[] = {BUS1_LCSUP, BUS2_LCSUN};
Int8U CT_Vf_DOWN_REV[] = {BUS2_LCSUP, BUS1_LCSUN};
//
//
// Continuity Selftest Commutations
Int8U CT_ST_PE1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2,
		BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_PE2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2,
		BUS3_PE_3, BUS3_PE_4};
//
Int8U CT_ST_LCTU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4, BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3, BUS1_LCTUN_4,
		BUS2_LCTUN_1, BUS2_LCTUN_2, BUS2_LCTUN_3, BUS2_LCTUN_4};
Int8U CT_ST_LCTU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4,
		BUS3_LCTUP_1, BUS3_LCTUP_2, BUS3_LCTUP_3, BUS3_LCTUP_4};
//
Int8U CT_ST_TOCU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS1_TOCUP, BUS2_TOCUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_TOCU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS1_TOCUP, BUS3_TOCUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_TOCU3[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS1_TOCUN, BUS2_TOCUN, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_TOCU4[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS1_TOCUN, BUS3_TOCUN, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4};
//
Int8U CT_ST_LCSU1[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS1_LCSUP, BUS2_LCSUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_LCSU2[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS1_LCSUP, BUS3_LCSUP, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_LCSU3[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS2_STP_1, BUS2_STP_2, BUS2_STP_3, BUS2_STP_4,
		BUS1_LCSUN, BUS2_LCSUN, BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_LCSU4[] = {BUS1_STN_1, BUS1_STN_2, BUS1_STN_3, BUS1_STN_4, BUS3_STP_1, BUS3_STP_2, BUS3_STP_3, BUS3_STP_4,
		BUS1_LCSUN, BUS3_LCSUN, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4};
//
// Relay opening Self Test - relay numbers for checking
Int8U CT_ST_RO_PE1[] = {BUS1_PE_1, BUS1_PE_2, BUS1_PE_3, BUS1_PE_4, BUS2_PE_1, BUS2_PE_2, BUS2_PE_3, BUS2_PE_4};
Int8U CT_ST_RO_PE2[] = {BUS3_PE_1, BUS3_PE_2, BUS3_PE_3, BUS3_PE_4};
Int8U CT_ST_RO_LCTU1[] = {BUS1_LCTUN_1, BUS1_LCTUN_2, BUS1_LCTUN_3, BUS1_LCTUN_4, BUS2_LCTUN_1, BUS2_LCTUN_2,
		BUS2_LCTUN_3, BUS2_LCTUN_4};
Int8U CT_ST_RO_LCTU2[] = {BUS1_LCTUP_1, BUS1_LCTUP_2, BUS1_LCTUP_3, BUS1_LCTUP_4, BUS3_LCTUP_1, BUS3_LCTUP_2,
		BUS3_LCTUP_3, BUS3_LCTUP_4};
//
//
// Proximity sensors table (Side1_Side2_Position)
//
// TOCU HP
#define BUS1_TOCUN_CLOSE	12
#define BUS1_TOCUP_CLOSE	14
#define BUS2_TOCUN_CLOSE	16
#define BUS2_TOCUP_CLOSE	18
#define BUS3_TOCUN_CLOSE	20
#define BUS3_TOCUP_CLOSE	22
#define BUS1_TOCUN_OPEN		13
#define BUS1_TOCUP_OPEN		15
#define BUS2_TOCUN_OPEN		17
#define BUS2_TOCUP_OPEN		19
#define BUS3_TOCUN_OPEN		21
#define BUS3_TOCUP_OPEN		23
// LCSU
#define BUS1_LCSUN_CLOSE	0
#define BUS1_LCSUP_CLOSE	2
#define BUS2_LCSUN_CLOSE	4
#define BUS2_LCSUP_CLOSE	6
#define BUS3_LCSUN_CLOSE	8
#define BUS3_LCSUP_CLOSE	10
#define BUS1_LCSUN_OPEN		1
#define BUS1_LCSUP_OPEN		3
#define BUS2_LCSUN_OPEN		5
#define BUS2_LCSUP_OPEN		7
#define BUS3_LCSUN_OPEN		9
#define BUS3_LCSUP_OPEN		11
//
ContactorsCommutationFBTableItem ContactorsCommutationFBTable[CONTACTOR_COMMUTATIONS_FB_TABLE_SIZE] =
{
		{PIN_5, REG3}, 			// 0	// BUS1 to LCSU- CLOSE
		{PIN_6, REG3},			// 1	// BUS1 to LCSU- OPEN
		{PIN_7, REG3},			// 2	// BUS1 to LCSU+ CLOSE
		{PIN_8, REG3},			// 3	// BUS1 to LCSU+ OPEN
		{PIN_1, REG3},			// 4	// BUS2 to LCSU- CLOSE
		{PIN_2, REG3},			// 5	// BUS2 to LCSU- OPEN
		{PIN_3, REG3},			// 6	// BUS2 to LCSU+ CLOSE
		{PIN_4, REG3},			// 7	// BUS2 to LCSU+ OPEN
		{PIN_5, REG2},			// 8	// BUS3 to LCSU- CLOSE
		{PIN_6, REG2},			// 9	// BUS3 to LCSU- OPEN
		{PIN_7, REG2},			// 10	// BUS3 to LCSU+ CLOSE
		{PIN_8, REG2},			// 11	// BUS3 to LCSU+ OPEN
		//
		{PIN_1, REG2},			// 12	// BUS1 to TOCU- CLOSE
		{PIN_2, REG2},			// 13	// BUS1 to TOCU- OPEN
		{PIN_3, REG2},			// 14	// BUS1 to TOCU+ CLOSE
		{PIN_4, REG2},			// 15	// BUS1 to TOCU+ OPEN
		{PIN_5, REG1},			// 16	// BUS2 to TOCU- CLOSE
		{PIN_6, REG1},			// 17	// BUS2 to TOCU- OPEN
		{PIN_7, REG1},			// 18	// BUS2 to TOCU+ CLOSE
		{PIN_8, REG1},			// 19	// BUS2 to TOCU+ OPEN
		{PIN_1, REG1},			// 20	// BUS3 to TOCU- CLOSE
		{PIN_2, REG1},			// 21	// BUS3 to TOCU- OPEN
		{PIN_3, REG1},			// 22	// BUS3 to TOCU+ CLOSE
		{PIN_4, REG1}			// 23	// BUS3 to TOCU+ OPEN
};
//

//
#endif // __COMMTABLE_H

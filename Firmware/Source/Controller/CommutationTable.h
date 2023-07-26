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

//  ants
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
#define NUM_RELAYS_PER_COMMUTATION		4
#define NUM_CONTACTOR_COMMUTATIONS		12
#define NUM_RELAY_COMMUTATIONS			10
#define INNER_COMMUTATION_TABLE_SIZE 	((NUM_RELAY_COMMUTATIONS * NUM_RELAYS_PER_COMMUTATION) + NUM_CONTACTOR_COMMUTATIONS)
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
InnerCommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] = {{CONTACTOR, PIN_6, REG1}, // 0	// BUS1 to TOCU+
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
		{RELAY, PIN_5, REG5},			// 20	// BUS3 to PE_1
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
Int8U CT_DFLT_Relays[] = {0,0,0,0,0};
Int8U CT_DFLT_Contactors[] = {0,0};

// Main Commutations
Int8U CT_PE[] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_Ices_UP[] = {48, 49, 50, 51, 36, 37, 38, 39};
Int8U CT_Ices_DOWN[] = {44, 45, 46, 47, 40, 41, 42, 43};
Int8U CT_Idds_UP[] = {48, 49, 50, 51, 36, 37, 38, 39};
Int8U CT_Idds_DOWN[] = {44, 45, 46, 47, 40, 41, 42, 43};
Int8U CT_Ir_UP[] = {48, 49, 50, 51, 36, 37, 38, 39};
Int8U CT_Ir_DOWN[] = {44, 45, 46, 47, 40, 41, 42, 43};
Int8U CT_Qg_UP[] = {8, 1};
Int8U CT_Qg_UP_REV[] = {0, 9};
Int8U CT_Qg_DOWN[] = {0, 5};
Int8U CT_Qg_DOWN_REV[] = {4, 1};
Int8U CT_Vcesat_UP[] = {10, 3};
Int8U CT_Vcesat_UP_REV[] = {2, 11};
Int8U CT_Vcesat_DOWN[] = {2, 7};
Int8U CT_Vcesat_DOWN_REV[] = {6, 3};
Int8U CT_Vsd_UP[] = {10, 3};
Int8U CT_Vsd_UP_REV[] = {2, 11};
Int8U CT_Vsd_DOWN[] = {2, 7};
Int8U CT_Vsd_DOWN_REV[] = {6, 3};
Int8U CT_Rdson_UP[] = {10, 3};
Int8U CT_Rdson_UP_REV[] = {2, 11};
Int8U CT_Rdson_DOWN[] = {2, 7};
Int8U CT_Rdson_DOWN_REV[] = {6, 3};
Int8U CT_Vf_UP[] = {10, 3};
Int8U CT_Vf_UP_REV[] = {2, 11};
Int8U CT_Vf_DOWN[] = {2, 7};
Int8U CT_Vf_DOWN_REV[] = {6, 3};
//
//
// Continuity Selftest Commutations
Int8U CT_ST_PE1[] = {24, 25, 26, 27, 28, 29, 30, 31, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_ST_PE2[] = {24, 25, 26, 27, 32, 33, 34, 35, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
//
Int8U CT_ST_LCTU1[] = {24, 25, 26, 27, 28, 29, 30, 31, 20, 21, 22, 23, 36, 37, 38, 39, 40, 41, 42, 43};
Int8U CT_ST_LCTU2[] = {24, 25, 26, 27, 32, 33, 34, 35, 16, 17, 18, 19, 44, 45, 46, 47, 48, 49, 50, 51};
//
Int8U CT_ST_TOCU1[] = {24, 25, 26, 27, 28, 29, 30, 31, 0, 4, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_ST_TOCU2[] = {24, 25, 26, 27, 32, 33, 34, 35, 0, 8, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_ST_TOCU3[] = {24, 25, 26, 27, 28, 29, 30, 31, 1, 5, 20, 21, 22, 23};
Int8U CT_ST_TOCU4[] = {24, 25, 26, 27, 32, 33, 34, 35, 1, 9, 16, 17, 18, 19};
//
Int8U CT_ST_LCSU1[] = {24, 25, 26, 27, 28, 29, 30, 31, 2, 6, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_ST_LCSU2[] = {24, 25, 26, 27, 32, 33, 34, 35, 2, 10, 16, 17, 18, 19, 20, 21, 22, 23};
Int8U CT_ST_LCSU3[] = {24, 25, 26, 27, 28, 29, 30, 31, 3, 7, 20, 21, 22, 23};
Int8U CT_ST_LCSU4[] = {24, 25, 26, 27, 32, 33, 34, 35, 3, 11, 16, 17, 18, 19};
//
// Relay opening Self Test - relay numbers for checking
Int8U CT_ST_RO_PE1[] = {12, 13, 14, 15, 16, 17, 18, 19};
Int8U CT_ST_RO_PE2[] = {20, 21, 22, 23};
Int8U CT_ST_RO_LCTU1[] = {36, 37, 38, 39, 40, 41, 42, 43};
Int8U CT_ST_RO_LCTU2[] = {44, 45, 46, 47, 48, 49, 50, 51};

#endif // __COMMTABLE_H

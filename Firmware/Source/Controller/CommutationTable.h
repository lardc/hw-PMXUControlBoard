// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"

// Constants
//
// Shift registers pins and data bits
#define PIN_1	BIT0
#define PIN_2	BIT1
#define PIN_3	BIT2
#define PIN_4	BIT3
#define	PIN_5	BIT4
#define	PIN_6	BIT5
#define	PIN_7	BIT6
#define	PIN_8	BIT7
//
// Commutation type
#define	CONTACTOR	0
#define	RELAY		1
//
// Shift register number (data byte position in full data bytes array)
#define REG1	0
#define REG2	1
#define REG3	2
#define REG4	3
#define REG5	4
//
#define NUM_RELAYS_PER_COMMUTATION	4
#define NUM_CONTACTOR_COMMUTATIONS	12
#define NUM_RELAY_COMMUTATIONS		10
#define INNER_COMMUTATION_TABLE_SIZE ((NUM_RELAY_COMMUTATIONS * NUM_RELAYS_PER_COMMUTATION) + NUM_CONTACTOR_COMMUTATIONS)
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
// Selftest commutations
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




//
/*
// Main Commutation
#define MC_C_POT_LSL_POTN		12
#define MC_G_C_POT1				8
#define MC_G_C_POT2				9
#define MC_G_C_POT3				10
#define MC_G_C_POT4				11
#define MC_C_POT_LSL_POTP		24
#define MC_G_GT_G_POT			23
#define MC_G_GT_G				22
#define MC_G_GT_GE				21
#define MC_G_LSL_G				36
#define MC_GE_GT_G				35
#define MC_GE_GT_GE				34
#define MC_G_GE					29
#define MC_GE_LSL_GE			48
#define MC_E_POT_GT_GE_POT		47
#define MC_E_POT_LSL_POTP		46
#define MC_E_POT_LSL_POTN		45
#define MC_C_POT_2_LSL_POTN		68
#define MC_G_2_C_POT1			64
#define MC_G_2_C_POT2			65
#define MC_G_2_C_POT3			66
#define MC_G_2_C_POT4			67
#define MC_C_POT_2_LSL_POTP		80
#define MC_G_2_GT_G_POT			79
#define MC_G_2_GT_G				78
#define MC_G_2_GT_GE			77
#define MC_G_2_LSL_G			92
#define MC_GE_2_GT_G			91
#define MC_GE_2_GT_GE			90
#define MC_G_2_GE				85
#define MC_GE_2_LSL_GE			104
#define MC_E_POT_2_GT_GE_POT	103
#define MC_E_POT_2_LSL_POTP		102
#define MC_E_POT_2_LSL_POTN		101
#define MC_T2_GT_G_POT			145
#define MC_T2_GT_G				144
#define MC_T1_GT_GE_POT			154
#define MC_T1_GT_GE				155
*/
// Types
//
typedef struct __InnerCommutationTableItem
{
	Int8U Type;
	Int8U Bit;
	Int8U RegNum;
} CommutationTableItem;

typedef struct __CommutationTableItem
{
	Int8U BoardNum;
	Int8U Bit;
	Int8U RegNum;
} CommutationTableItem;

// Variables
//
extern const CommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] =
				{
						{CONTACTOR, PIN_6, REG1},			// 0	// BUS1 to TOCU+
						{CONTACTOR, PIN_5, REG1},			// 1	// BUS1 to TOCU-
						{CONTACTOR, PIN_4, REG2},			// 2	// BUS1 to LCSU+
						{CONTACTOR, PIN_3, REG2},			// 3	// BUS1 to LCSU-
						{CONTACTOR, PIN_4, REG1},			// 4	// BUS2 to TOCU+
						{CONTACTOR, PIN_3, REG1},			// 5	// BUS2 to TOCU-
						{CONTACTOR, PIN_2, REG2},			// 6	// BUS2 to LCSU+
						{CONTACTOR, PIN_1, REG2},			// 7	// BUS2 to LCSU-
						{CONTACTOR, PIN_2, REG1},			// 8	// BUS3 to TOCU+
						{CONTACTOR, PIN_1, REG1},			// 9	// BUS3 to TOCU-
						{CONTACTOR, PIN_8, REG1},			// 10	// BUS3 to LCSU+
						{CONTACTOR, PIN_7, REG1},			// 11	// BUS3 to LCSU-
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

#endif // __COMMTABLE_H

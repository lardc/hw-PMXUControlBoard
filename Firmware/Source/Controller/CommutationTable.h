﻿// -----------------------------------------
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
// Main Commutations
#define PE						0
#define Ices_UP					1
#define Ices_DOWN				2
#define Idds_UP					3
#define Idds_DOWN				4
#define Ir_UP					5
#define Ir_DOWN					6
#define Qg_UP					7
#define Qg_UP_REV				8
#define Qg_DOWN					9
#define Qg_DOWN_REV				10
#define Vcesat_UP				11
#define Vcesat_UP_REV			12
#define Vcesat_DOWN				13
#define Vcesat_DOWN_REV			14
#define Vsd_UP					15
#define Vsd_UP_REV				16
#define Vsd_DOWN				17
#define Vsd_DOWN_REV			18
#define Rdson_UP				19
#define Rdson_UP_REV			20
#define Rdson_DOWN				21
#define Rdson_DOWN_REV			22
#define Vf_UP					23
#define Vf_UP_REV				24
#define Vf_DOWN					25
#define Vf_DOWN_REV				26
//
//
// Selftest Commutations
/*
#define PE						0
#define Ices_UP					1
*/

// Types
//
typedef struct __InnerCommutationTableItem
{
	Int8U Type;
	Int8U Bit;
	Int8U RegNum;
} InnerCommutationTableItem;

typedef struct __CommutationTableItem
{
	Int8U BoardNum;
	Int8U Bit;
	Int8U RegNum;
} CommutationTableItem;

// Variables
//
extern const InnerCommutationTableItem InnerCommutationTable[INNER_COMMUTATION_TABLE_SIZE] =
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

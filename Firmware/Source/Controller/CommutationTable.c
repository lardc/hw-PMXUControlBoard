// -----------------------------------------
// Global definitions
// ----------------------------------------

// Header
#include "CommutationTable.h"
/*
// Output pins bindings
// PIN_XY -> where X = number of shift-register, Y = number of pin
#define PIN_A1	BIT0
#define PIN_A2	BIT1
#define PIN_A3	BIT2
#define PIN_A4	BIT3
#define	PIN_A5	BIT4
#define	PIN_A6	BIT5
#define	PIN_A7	BIT6
#define	PIN_A8	BIT7
//
#define PIN_B1	BIT0
#define PIN_B2	BIT1
#define PIN_B3	BIT2
#define PIN_B4	BIT3
#define	PIN_B5	BIT4
#define	PIN_B6	BIT5
#define	PIN_B7	BIT6
#define	PIN_B8	BIT7
//
#define PIN_C1	BIT0
#define PIN_C2	BIT1
#define PIN_C3	BIT2
#define PIN_C4	BIT3
#define	PIN_C5	BIT4
#define	PIN_C6	BIT5
#define	PIN_C7	BIT6
#define	PIN_C8	BIT7
//
#define PIN_D1	BIT0
#define PIN_D2	BIT1
#define PIN_D3	BIT2
#define PIN_D4	BIT3
#define	PIN_D5	BIT4
#define	PIN_D6	BIT5
#define	PIN_D7	BIT6
#define	PIN_D8	BIT7
//
#define PIN_E1	BIT0
#define PIN_E2	BIT1
#define PIN_E3	BIT2
#define PIN_E4	BIT3
#define	PIN_E5	BIT4
#define	PIN_E6	BIT5
#define	PIN_E7	BIT6
#define	PIN_E8	BIT7
//
#define PIN_F1	BIT0
#define PIN_F2	BIT1
#define PIN_F3	BIT2
#define PIN_F4	BIT3
#define	PIN_F5	BIT4
#define	PIN_F6	BIT5
#define	PIN_F7	BIT6
#define	PIN_F8	BIT7
//
#define PIN_G1	BIT0
#define PIN_G2	BIT1
#define PIN_G3	BIT2
#define PIN_G4	BIT3
#define	PIN_G5	BIT4
#define	PIN_G6	BIT5
#define	PIN_G7	BIT6
#define	PIN_G8	BIT7

// Extension board indexes
//---------------------------------
// Board 4 is the most distant extension board
// to the control board (in terms of cable length)
//---------------------------------
//
#define BOARD1	0		// OutHVRelayBoard 1
#define BOARD2	1		// OutHVRelayBoard 2
#define BOARD3	2		// OutThermRelayBoard
#define BOARD4	3		// InputRelayBoard

#define REG1	0
#define REG2	1
#define REG3	2
#define REG4	3
#define REG5	4
#define REG6	5
#define REG7	6
#define REG8	7
#define REG9	8
#define REG10	9
#define REG11	10
#define REG12	11
#define REG13	12
#define REG14	13
#define REG15	14
#define REG16	15
#define REG17	16
#define REG18	17
#define REG19	18
#define REG20	19

// Constants
//
const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE] =
				{
						{BOARD1, PIN_A1, REG1},			// 0	// Collector (C_POT) to PE
						{BOARD1, PIN_A2, REG1},			// 1	// Collector (C_POT) to PE
						{BOARD1, PIN_A3, REG1},			// 2	// Collector (C_POT) to PE
						{BOARD1, PIN_A4, REG1},			// 3	// Collector (C_POT) to PE
						{BOARD1, PIN_A5, REG1},			// 4	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_A6, REG1},			// 5	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_A7, REG1},			// 6	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_A8, REG1},			// 7	// Collector: Commutation of C_POT (Open/Close)
						{BOARD1, PIN_B1, REG2},			// 8	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B2, REG2},			// 9	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B3, REG2},			// 10	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B4, REG2},			// 11	// Gate (G) to Collector (C_POT)
						{BOARD1, PIN_B5, REG2},			// 12	// Collector (C_POT) to LSL_POT-
						{BOARD1, PIN_B6, REG2},			// 13	// Gate (G) to PE
						{BOARD1, PIN_B7, REG2},			// 14	// Gate (G) to PE
						{BOARD1, PIN_B8, REG2},			// 15	// Gate (G) to PE
						{BOARD1, PIN_C1, REG3},			// 16	// Gate (G) to PE
						{BOARD1, PIN_C2, REG3},			// 17	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C3, REG3},			// 18	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C4, REG3},			// 19	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C5, REG3},			// 20	// Gate: Commutation of G (Open/Close)
						{BOARD1, PIN_C6, REG3},			// 21	// Gate (G) to GT_GE
						{BOARD1, PIN_C7, REG3},			// 22	// Gate (G) to GT_G
						{BOARD1, PIN_C8, REG3},			// 23	// Gate (G) to GT_G_POT
						{BOARD1, PIN_D1, REG4},			// 24	// Collector (C_POT) to LSL_POT+
						{BOARD1, PIN_D2, REG4},			// 25	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_D3, REG4},			// 26	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_D4, REG4},			// 27	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_D5, REG4},			// 28	// Gate-Emitter (GE) to PE
						{BOARD1, PIN_D6, REG4},			// 29	// Gate (G) to Gate-Emitter (GE)
						{BOARD1, PIN_D7, REG4},			// 30	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_D8, REG4},			// 31	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_E1, REG5},			// 32	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_E2, REG5},			// 33	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD1, PIN_E3, REG5},			// 34	// Gate-Emitter (GE) to GT_GE
						{BOARD1, PIN_E4, REG5},			// 35	// Gate-Emitter (GE) to GT_G
						{BOARD1, PIN_E5, REG5},			// 36	// Gate (G) to LSL_G
						{BOARD1, PIN_E6, REG5},			// 37	// Emitter (E_POT) to PE
						{BOARD1, PIN_E7, REG5},			// 38	// Emitter (E_POT) to PE
						{BOARD1, PIN_E8, REG5},			// 39	// Emitter (E_POT) to PE
						{BOARD1, PIN_F1, REG6},			// 40	// Emitter (E_POT) to PE
						{BOARD1, PIN_F2, REG6},			// 41	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_F3, REG6},			// 42	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_F4, REG6},			// 43	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_F5, REG6},			// 44	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD1, PIN_F6, REG6},			// 45	// Emitter (E_POT) to LSL_POT-
						{BOARD1, PIN_F7, REG6},			// 46	// Emitter (E_POT) to LSL_POT+
						{BOARD1, PIN_F8, REG6},			// 47	// Emitter (E_POT) to GT_GE_POT
						{BOARD1, PIN_G1, REG7},			// 48	// Gate-Emitter (GE) to LSL_GE
						{BOARD1, PIN_G2, REG7},			// 49	//
						{BOARD1, PIN_G3, REG7},			// 50	//
						{BOARD1, PIN_G4, REG7},			// 51	//
						{BOARD1, PIN_G5, REG7},			// 52	//
						{BOARD1, PIN_G6, REG7},			// 53	//
						{BOARD1, PIN_G7, REG7},			// 54	//
						{BOARD1, PIN_G8, REG7},			// 55	//
						{BOARD2, PIN_A1, REG8},			// 56	// Collector (C_POT) to PE
						{BOARD2, PIN_A2, REG8},			// 57	// Collector (C_POT) to PE
						{BOARD2, PIN_A3, REG8},			// 58	// Collector (C_POT) to PE
						{BOARD2, PIN_A4, REG8},			// 59	// Collector (C_POT) to PE
						{BOARD2, PIN_A5, REG8},			// 60	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_A6, REG8},			// 61	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_A7, REG8},			// 62	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_A8, REG8},			// 63	// Collector: Commutation of C_POT (Open/Close)
						{BOARD2, PIN_B1, REG9},			// 64	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B2, REG9},			// 65	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B3, REG9},			// 66	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B4, REG9},			// 67	// Gate (G) to Collector (C_POT)
						{BOARD2, PIN_B5, REG9},			// 68	// Collector (C_POT) to LSL_POT-
						{BOARD2, PIN_B6, REG9},			// 69	// Gate (G) to PE
						{BOARD2, PIN_B7, REG9},			// 70	// Gate (G) to PE
						{BOARD2, PIN_B8, REG9},			// 71	// Gate (G) to PE
						{BOARD2, PIN_C1, REG10},		// 72	// Gate (G) to PE
						{BOARD2, PIN_C2, REG10},		// 73	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C3, REG10},		// 74	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C4, REG10},		// 75	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C5, REG10},		// 76	// Gate: Commutation of G (Open/Close)
						{BOARD2, PIN_C6, REG10},		// 77	// Gate (G) to GT_GE
						{BOARD2, PIN_C7, REG10},		// 78	// Gate (G) to GT_G
						{BOARD2, PIN_C8, REG10},		// 79	// Gate (G) to GT_G_POT
						{BOARD2, PIN_D1, REG11},		// 80	// Collector (C_POT) to LSL_POT+
						{BOARD2, PIN_D2, REG11},		// 81	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_D3, REG11},		// 82	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_D4, REG11},		// 83	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_D5, REG11},		// 84	// Gate-Emitter (GE) to PE
						{BOARD2, PIN_D6, REG11},		// 85	// Gate (G) to Gate-Emitter (GE)
						{BOARD2, PIN_D7, REG11},		// 86	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_D8, REG11},		// 87	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_E1, REG12},		// 88	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_E2, REG12},		// 89	// Gate-Emitter: Commutation of GE (Open/Close)
						{BOARD2, PIN_E3, REG12},		// 90	// Gate-Emitter (GE) to GT_GE
						{BOARD2, PIN_E4, REG12},		// 91	// Gate-Emitter (GE) to GT_G
						{BOARD2, PIN_E5, REG12},		// 92	// Gate (G) to LSL_G
						{BOARD2, PIN_E6, REG12},		// 93	// Emitter (E_POT) to PE
						{BOARD2, PIN_E7, REG12},		// 94	// Emitter (E_POT) to PE
						{BOARD2, PIN_E8, REG12},		// 95	// Emitter (E_POT) to PE
						{BOARD2, PIN_F1, REG13},		// 96	// Emitter (E_POT) to PE
						{BOARD2, PIN_F2, REG13},		// 97	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_F3, REG13},		// 98	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_F4, REG13},		// 99	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_F5, REG13},		// 100	// Emitter: Commutation of E_POT (Open/Close)
						{BOARD2, PIN_F6, REG13},		// 101	// Emitter (E_POT) to LSL_POT-
						{BOARD2, PIN_F7, REG13},		// 102	// Emitter (E_POT) to LSL_POT+
						{BOARD2, PIN_F8, REG13},		// 103	// Emitter (E_POT) to GT_GE_POT
						{BOARD2, PIN_G1, REG14},		// 104	// Gate-Emitter (GE) to LSL_GE
						{BOARD2, PIN_G2, REG14},		// 105	//
						{BOARD2, PIN_G3, REG14},		// 106	//
						{BOARD2, PIN_G4, REG14},		// 107	//
						{BOARD2, PIN_G5, REG14},		// 108	//
						{BOARD2, PIN_G6, REG14},		// 109	//
						{BOARD2, PIN_G7, REG14},		// 110	//
						{BOARD2, PIN_G8, REG14},		// 111	//
						{BOARD3, PIN_A1, REG15},		// 112	// GT_G to TEST-IN
						{BOARD3, PIN_A2, REG15},		// 113	// GT_GE to TEST-OUT
						{BOARD3, PIN_A3, REG15},		// 114	// GT_G: Commutation of GT_G (Open/Close)
						{BOARD3, PIN_A4, REG15},		// 115	// GT_GE: Commutation of GT_GE (Open/Close)
						{BOARD3, PIN_A5, REG15},		// 116	// GT_G to GT_GE
						{BOARD3, PIN_A6, REG15},		// 117	// GT_G_POT to TEST-IN
						{BOARD3, PIN_A7, REG15},		// 118	// GT_GE_POT to TEST-OUT
						{BOARD3, PIN_A8, REG15},		// 119	// GT_G_POT: Commutation of GT_G_POT (Open/Close)
						{BOARD3, PIN_B1, REG16},		// 120	// GT_GE_POT: Commutation of GT_GE_POT (Open/Close)
						{BOARD3, PIN_B2, REG16},		// 121	// GT_G_POT to GT_GE_POT
						{BOARD3, PIN_B3, REG16},		// 122	// LSL_G to TEST-IN
						{BOARD3, PIN_B4, REG16},		// 123	// LSL_GE to TEST-OUT
						{BOARD3, PIN_B5, REG16},		// 124	// LSL_G: Commutation of LSL_G (Open/Close)
						{BOARD3, PIN_B6, REG16},		// 125	// LSL_GE: Commutation of LSL_GE (Open/Close)
						{BOARD3, PIN_B7, REG16},		// 126	// LSL_G to LSL_GE
						{BOARD3, PIN_B8, REG16},		// 127	// LSL_POT+ to TEST-IN
						{BOARD3, PIN_B1, REG17},		// 128	// LSL_POT- to TEST-OUT
						{BOARD3, PIN_B2, REG17},		// 129	// LSL_POT+: Commutation of LSL_POT+ (Open/Close)
						{BOARD3, PIN_B3, REG17},		// 130	// LSL_POT-: Commutation of LSL_POT- (Open/Close)
						{BOARD3, PIN_B4, REG17},		// 131	// LSL_POT+ to LSL_POT-
						{BOARD3, PIN_B5, REG17},		// 132	//
						{BOARD3, PIN_B6, REG17},		// 133	//
						{BOARD3, PIN_B7, REG17},		// 134	//
						{BOARD3, PIN_B8, REG17},		// 135	//
						{BOARD4, PIN_A1, REG18},		// 136	// Thermistor_2 (T2) to PE
						{BOARD4, PIN_A2, REG18},		// 137	// Thermistor_2 (T2) to PE
						{BOARD4, PIN_A3, REG18},		// 138	// Thermistor_2 (T2) to PE
						{BOARD4, PIN_A4, REG18},		// 139	// Thermistor_2 (T2) to PE
						{BOARD4, PIN_A5, REG18},		// 140	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD4, PIN_A6, REG18},		// 141	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD4, PIN_A7, REG18},		// 142	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD4, PIN_A8, REG18},		// 143	// Thermistor_2: Commutation of T2 (Open/Close)
						{BOARD4, PIN_B1, REG19},		// 144	// T2 to GT_G
						{BOARD4, PIN_B2, REG19},		// 145	// T2 to GT_G_POT
						{BOARD4, PIN_B3, REG19},		// 146	// Thermistor_1 (T1) to PE
						{BOARD4, PIN_B4, REG19},		// 147	// Thermistor_1 (T1) to PE
						{BOARD4, PIN_B5, REG19},		// 148	// Thermistor_1 (T1) to PE
						{BOARD4, PIN_B6, REG19},		// 149	// Thermistor_1 (T1) to PE
						{BOARD4, PIN_B7, REG19},		// 150	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD4, PIN_B8, REG19},		// 151	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD4, PIN_C1, REG20},		// 152	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD4, PIN_C1, REG20},		// 153	// Thermistor_1: Commutation of T1 (Open/Close)
						{BOARD4, PIN_C1, REG20},		// 154	// T1 to GT_GE_POT
						{BOARD4, PIN_C1, REG20},		// 155	// T1 to GT_GE
						{BOARD4, PIN_C1, REG20},		// 156	//
						{BOARD4, PIN_C1, REG20},		// 157	//
						{BOARD4, PIN_C1, REG20},		// 158	//
						{BOARD4, PIN_C1, REG20}			// 159	//
				};


// No more

 */

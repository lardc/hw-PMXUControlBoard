// -----------------------------------------
// Commutation table
// ----------------------------------------

#ifndef __COMMTABLE_H
#define __COMMTABLE_H

// Include
#include "stdinc.h"

/*
// Constants
//
#define NUM_HV_BOARD			2
#define NUM_THERM_BOARD			1
#define NUM_INPUT_BOARD			1
#define COMMUTATION_EXT_BOARDS	(NUM_HV_BOARD + NUM_THERM_BOARD + NUM_INPUT_BOARD)

#define NUM_REGS_HV_BOARD			7
#define NUM_REGS_THERM_BOARD		3
#define NUM_REGS_INPUT_BOARD		3
#define NUM_REGS_TOTAL ((NUM_REGS_HV_BOARD * 2) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD)

#define COMMUTATION_TABLE_SIZE (((NUM_REGS_HV_BOARD * NUM_HV_BOARD) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD) * 8)

//
// Commutation
// Out lines to PE Commutation
#define G_PE1					13
#define G_PE2					14
#define G_PE3					15
#define G_PE4					16
#define C_POT_PE1				0
#define C_POT_PE2				1
#define C_POT_PE3				2
#define C_POT_PE4				3
#define E_POT_PE1				37
#define E_POT_PE2				38
#define E_POT_PE3				39
#define E_POT_PE4				40
#define GE_PE1					25
#define GE_PE2					26
#define GE_PE3					27
#define GE_PE4					28
#define G_2_PE1					69
#define G_2_PE2					70
#define G_2_PE3					71
#define G_2_PE4					72
#define C_POT_2_PE1				56
#define C_POT_2_PE2				57
#define C_POT_2_PE3				58
#define C_POT_2_PE4				59
#define E_POT_2_PE1				93
#define E_POT_2_PE2				94
#define E_POT_2_PE3				95
#define E_POT_2_PE4				96
#define GE_2_PE1				81
#define GE_2_PE2				82
#define GE_2_PE3				83
#define GE_2_PE4				84
#define T2_PE1					136
#define T2_PE2					137
#define T2_PE3					138
#define T2_PE4					139
#define T1_PE1					146
#define T1_PE2					147
#define T1_PE3					148
#define T1_PE4					149
//
// Out Lines Self-Commutation
#define OL_C_POT_COMM1			4
#define OL_C_POT_COMM2			5
#define OL_C_POT_COMM3			6
#define OL_C_POT_COMM4			7

#define OL_G_COMM1				17
#define OL_G_COMM2				18
#define OL_G_COMM3				19
#define OL_G_COMM4				20

#define OL_GE_COMM1				30
#define OL_GE_COMM2				31
#define OL_GE_COMM3				32
#define OL_GE_COMM4				33

#define OL_E_POT_COMM1			41
#define OL_E_POT_COMM2			42
#define OL_E_POT_COMM3			43
#define OL_E_POT_COMM4			44

#define OL_C_POT_2_COMM1		60
#define OL_C_POT_2_COMM2		61
#define OL_C_POT_2_COMM3		62
#define OL_C_POT_2_COMM4		63

#define OL_G_2_COMM1			73
#define OL_G_2_COMM2			74
#define OL_G_2_COMM3			75
#define OL_G_2_COMM4			76

#define OL_GE_2_COMM1			86
#define OL_GE_2_COMM2			87
#define OL_GE_2_COMM3			88
#define OL_GE_2_COMM4			89

#define OL_E_POT_2_COMM1		97
#define OL_E_POT_2_COMM2		98
#define OL_E_POT_2_COMM3		99
#define OL_E_POT_2_COMM4		100

#define OL_T2_COMM1				140
#define OL_T2_COMM2				141
#define OL_T2_COMM3				142
#define OL_T2_COMM4				143

#define OL_T1_COMM1				150
#define OL_T1_COMM2				151
#define OL_T1_COMM3				152
#define OL_T1_COMM4				153
//
// In Lines Self-Commutation
#define IL_GT_G_COMM			114
#define IL_GT_GE_COMM			115
#define IL_GT_G_POT_COMM		119
#define IL_GT_GE_POT_COMM		120
#define IL_LSL_G_COMM			124
#define IL_LSL_GE_COMM			125
#define IL_LSL_POTP_COMM		129
#define IL_LSL_POTN_COMM		130

//
// Self-Test Commutation
#define ST_TI_GT_G				112
#define ST_TI_GT_G_POT			117
#define ST_TI_LSL_G				122
#define ST_TI_LSL_POTP			127
#define ST_TO_GT_GE				113
#define ST_TO_GT_GE_POT			118
#define ST_TO_LSL_GE			123
#define ST_TO_LSL_POTN			128
//
// In Lines Commutation
#define IL_GT_G_GE				116
#define IL_GT_G_GE_POT			121
#define IL_LSL_G_GE				126
#define IL_LSL_POTS				131
//
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

// Types
//
typedef struct __CommutationTableItem
{
	Int8U BoardNum;
	Int8U Bit;
	Int8U RegNum;
} CommutationTableItem;


// Variables
//
extern const CommutationTableItem CommutationTable[COMMUTATION_TABLE_SIZE];

*/
#endif // __COMMTABLE_H

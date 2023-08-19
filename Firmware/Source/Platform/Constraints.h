﻿#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
#define CONTACTORS_COMM_DELAY_MS_MAX	3000
#define CONTACTORS_COMM_DELAY_MS_DFLT	1000
//
#define REG_PRESSURE_ADC_OFFSET_MAX		1
#define REG_PRESSURE_ADC_OFFSET_DFLT	0
//
#define REG_PRESSURE_ADC_K_MAX			1
#define REG_PRESSURE_ADC_K_DFLT			0.003
//
#define REG_PRESSURE_THRESHOLD_MAX		10.0
#define REG_PRESSURE_THRESHOLD_DFLT		3.0
//
#define REG_DFLT_COMM_DELAY_MS_MAX		5000
#define REG_DFLT_COMM_DELAY_MS_DFLT		500
// Types
typedef struct __TableItemConstraint
{
	float Min;
	float Max;
	float Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint Constraint[];

#endif // __CONSTRAINTS_H

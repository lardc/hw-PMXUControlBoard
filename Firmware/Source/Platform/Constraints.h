#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

//Definitions
//
// в мВ
#define SFTST_ALLOWED_VOLTAGE_MIN		0
#define SFTST_ALLOWED_VOLTAGE_MAX		200
#define SFTST_ALLOWED_VOLTAGE_DEF		50
//
#define POS1							1
#define POS2							2

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

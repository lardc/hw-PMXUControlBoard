// Header
#include "StorageDescription.h"
#include "DataTable.h"
#include "Controller.h"

// Variables
RecordDescription StorageDescription[] =
{
	{"Device state",		DT_Int16U, 1},
	{"Last action ID",		DT_Int16U, 1},
	{"Last DUT position",	DT_Int16U, 1},
	{"Last DUT case",		DT_Int16U, 1},
	{"Fault reason",		DT_Int16U, 1},
};

#define SIZE_OF_POINTERS (sizeof(StorageDescription) / sizeof(StorageDescription[0]))
Int32U TablePointers[SIZE_OF_POINTERS ? SIZE_OF_POINTERS : 1] = {0};
const Int16U StorageSize = SIZE_OF_POINTERS;

CounterDescription CounterStorageDescription[] =
{
	{"0. None"},
	{"1. BUS2 to LCSU+"},
	{"2. BUS2 to LCSU-"},
	{"3. BUS2 to TOCU-"},
	{"4. BUS2 to TOCU+"},
	{"5. BUS1 to LCSU+"},
	{"6. BUS1 to LCSU-"},
	{"7. BUS1 to TOCU-"},
	{"8. BUS1 to TOCU+"},
	{"9. BUS3 to LCSU+"},
	{"10. BUS3 to LCSU-"},
	{"11. BUS3 to TOCU-"},
	{"12. BUS3 to TOCU+"},
	{"13. BUS1 to LCTU+"},
	{"14. BUS3 to LCTU+"},
	{"15. BUS2 to LCTU-"},
	{"16. BUS1 to LCTU-"},
	{"17. BUS2 to ST_OUT"},
	{"18. BUS3 to ST_OUT"},
	{"19. BUS1 to ST_IN"},
	{"20. BUS1 to PE"},
	{"21. BUS2 to PE"},
	{"22. BUS3 to PE"},
	{"23. BUS3 to LCTU-"},
	{"24. BUS3 to LCTU+"}
};
CounterData CounterTablePointers[sizeof(CounterStorageDescription) / sizeof(CounterStorageDescription[0])] = {0};
const Int16U CounterStorageSize = sizeof(CounterStorageDescription) / sizeof(CounterStorageDescription[0]);

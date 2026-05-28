// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "CommutationTable.h"
#include "LowLevel.h"
#include "Delay.h"
#include "DataTable.h"

// Диапазоны регистров в общем массиве CurrentOutputValues[NUM_REGS_TOTAL].
// Порядок согласован с REG_* в CommutationTable.c
#define ZCRD_CONTACTORS_REG_FIRST		0
#define ZCRD_CONTACTORS_REG_COUNT		NUM_REGS_CONTACTORS
//
#define ZCRD_RELAYS_REG_FIRST			(ZCRD_CONTACTORS_REG_FIRST + ZCRD_CONTACTORS_REG_FIRST)
#define ZCRD_RELAYS_REG_COUNT			NUM_REGS_RELAYS

// Индексы CS для LL_SPI_LatchBoard
#define ZCRD_CS_CONTACTORS				0
#define ZCRD_CS_RELAYS					1

// Variables
//
static uint8_t CurrentOutputValues[NUM_REGS_TOTAL] = {0};

// Functions prototypes
//
static void ZcRD_ShiftAndLatch(Int8U CS, Int8U FirstReg, Int8U RegCount);
static Int8U ZcRD_GetRegNum(Int8U ID);
static Int8U ZcRD_GetBitmask(Int8U ID);

// Functions
//
void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	ZcRD_RegisterFlushWrite();
	DELAY_US(COMM_DELAY_MS * 1000L);
}
// ----------------------------------------

static Int8U ZcRD_GetRegNum(Int8U ID)
{
	return ID / 8;
}
// ----------------------------------------

static Int8U ZcRD_GetBitmask(Int8U ID)
{
	return 1 << (ID % 8);
}
// ----------------------------------------

void ZcRD_OutputValuesComposeArray(const Int8U* Array, Int8U ArrayLength)
{
	for(int i = 0; i < ArrayLength; i++)
		ZcRD_OutputValuesCompose(Array[i], true);
}
// ----------------------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	Int8U RegNum = ZcRD_GetRegNum(TableID);
	Int8U BitMask = ZcRD_GetBitmask(TableID);

	if(TurnOn)
		CurrentOutputValues[RegNum] |= BitMask;
	else
		CurrentOutputValues[RegNum] &= ~BitMask;
}
// ----------------------------------------

void ZcRD_OutputValuesReset()
{
	for (uint8_t i = 0; i < NUM_REGS_TOTAL; ++i)
		CurrentOutputValues[i] = 0;
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	static uint8_t PrevCurrentOutputValues[NUM_REGS_TOTAL] = {0};

	// Аппаратный SPI1, два независимых CS — каждая ветка выгружается отдельной транзакцией.
	// SFT_ENABLE во время штатной выгрузки не трогаем: выход сдвигового регистра меняется
	// только в момент защёлки (CS-импульс). OE управляется аппаратно контуром безопасности.
	ZcRD_ShiftAndLatch(ZCRD_CS_CONTACTORS, ZCRD_CONTACTORS_REG_FIRST, ZCRD_CONTACTORS_REG_COUNT);
	ZcRD_ShiftAndLatch(ZCRD_CS_RELAYS, ZCRD_RELAYS_REG_FIRST, ZCRD_RELAYS_REG_COUNT);

	// Учёт ресурса: инкремент счётчика при каждом изменении состояния бита.
	for(Int16U i = 0; i < COMMUTATION_TABLE_SIZE; ++i)
	{
		Int8U RegNum = ZcRD_GetRegNum(i);
		Int8U BitMask = ZcRD_GetBitmask(i);

		if((PrevCurrentOutputValues[RegNum] & BitMask) != (CurrentOutputValues[RegNum] & BitMask)
				&& (PrevCurrentOutputValues[RegNum] & BitMask) == 0)
			CycleCounters[i]++;
	}

	for(Int16U i = 0; i < NUM_REGS_TOTAL; ++i)
		PrevCurrentOutputValues[i] = CurrentOutputValues[i];
	DELAY_US(COMM_DELAY_MS * 1000L);
}
// ----------------------------------------

static void ZcRD_ShiftAndLatch(Int8U CS, Int8U FirstReg, Int8U RegCount)
{
	// Байты выгружаются от последнего регистра к первому — чипы каскадированы,
	// и первая отправленная порция окажется в самом дальнем регистре.
	for (int8_t i = (int8_t)(FirstReg + RegCount) - 1; i >= (int8_t)FirstReg; i--)
		LL_SPI_WriteByte(CurrentOutputValues[i]);

	LL_SPI_LatchBoard(CS);
}
// ----------------------------------------

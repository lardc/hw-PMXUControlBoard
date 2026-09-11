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
#define ZCRD_RELAYS_REG_FIRST			(ZCRD_CONTACTORS_REG_FIRST + ZCRD_CONTACTORS_REG_COUNT)
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

	for(uint8_t i = 0; i < SensorsStateLength; i++)
	{
		if(SensorsState[i].Index == TableID)
		{
			SensorsState[i].IsClosed = TurnOn;
			break;
		}
	}
}
// ----------------------------------------

void ZcRD_OutputValuesReset()
{
	for(uint8_t i = 0; i < NUM_REGS_TOTAL; i++)
		CurrentOutputValues[i] = 0;

	for(uint8_t i = 0; i < SensorsStateLength; i++)
		SensorsState[i].IsClosed = false;
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

static bool ZcRD_GetSensorBit(const Int8U* SensorRegs, Int8U RegNum, Int8U BitMask)
{
	return (SensorRegs[RegNum] & BitMask) != 0;
}
// ----------------------------------------

static bool ZcRD_IsSensorMatching(const ContactorSensorState* Sensor, const Int8U* SensorRegs)
{
	bool CloseBit = ZcRD_GetSensorBit(SensorRegs, Sensor->SensorRegNumClose, Sensor->SensorBitClose);
	bool OpenBit = ZcRD_GetSensorBit(SensorRegs, Sensor->SensorRegNumOpen, Sensor->SensorBitOpen);

	if(Sensor->IsClosed)
		return CloseBit && !OpenBit;

	return !CloseBit && OpenBit;
}
// ----------------------------------------

Int32U ZcRD_CommutationCheck()
{
	Int8U SensorRegs[NUM_REGS_SENSORS_SPI2];
	Int32U Mask = 0;

	LL_SPI_ReadArray(SensorRegs, NUM_REGS_SENSORS_SPI2);

	DataTable[REG_SENSOR_SPI2_BYTE0] = (float)SensorRegs[0];
	DataTable[REG_SENSOR_SPI2_BYTE1] = (float)SensorRegs[1];
	DataTable[REG_SENSOR_SPI2_BYTE2] = (float)SensorRegs[2];

	for(Int16U i = 0; i < SensorsStateLength; ++i)
	{
		if(!ZcRD_IsSensorMatching(&SensorsState[i], SensorRegs))
			Mask |= (Int32U)(1UL << SensorsState[i].Index);
	}

	return Mask;
}
// ----------------------------------------

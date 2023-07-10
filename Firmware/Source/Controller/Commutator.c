// -----------------------------------------
// Commutation logic
// ----------------------------------------

// Header
#include "Commutator.h"
//
#include "ZcRegistersDriver.h"
#include "DeviceObjectDictionary.h"
#include "CommutationTable.h"
#include "Global.h"
#include "DataTable.h"
#include "Delay.h"
/*
// Variables
//
static Int16U OldActionID = ACT_COMM_NONE;
static Int16U OldPostion = 0;

// Functions
//
void COMM_DisconnectPE()
{
	ZcRD_OutputValuesCompose(C_POT_PE1, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE2, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE3, TRUE);
	ZcRD_OutputValuesCompose(C_POT_PE4, TRUE);

	ZcRD_OutputValuesCompose(G_PE1, TRUE);
	ZcRD_OutputValuesCompose(G_PE2, TRUE);
	ZcRD_OutputValuesCompose(G_PE3, TRUE);
	ZcRD_OutputValuesCompose(G_PE4, TRUE);

	ZcRD_OutputValuesCompose(GE_PE1, TRUE);
	ZcRD_OutputValuesCompose(GE_PE2, TRUE);
	ZcRD_OutputValuesCompose(GE_PE3, TRUE);
	ZcRD_OutputValuesCompose(GE_PE4, TRUE);

	ZcRD_OutputValuesCompose(E_POT_PE1, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE2, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE3, TRUE);
	ZcRD_OutputValuesCompose(E_POT_PE4, TRUE);

	ZcRD_OutputValuesCompose(C_POT_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(C_POT_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(G_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(G_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(GE_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(GE_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(E_POT_2_PE1, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE2, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE3, TRUE);
	ZcRD_OutputValuesCompose(E_POT_2_PE4, TRUE);

	ZcRD_OutputValuesCompose(T1_PE1, TRUE);
	ZcRD_OutputValuesCompose(T1_PE2, TRUE);
	ZcRD_OutputValuesCompose(T1_PE3, TRUE);
	ZcRD_OutputValuesCompose(T1_PE4, TRUE);

	ZcRD_OutputValuesCompose(T2_PE1, TRUE);
	ZcRD_OutputValuesCompose(T2_PE2, TRUE);
	ZcRD_OutputValuesCompose(T2_PE3, TRUE);
	ZcRD_OutputValuesCompose(T2_PE4, TRUE);
}
// ----------------------------------------

void COMM_Commutate(Int16U ActionID)
{
	if (ActionID == OldActionID && \
			(DataTable[REG_MEASUREMENT_POSITION] == OldPostion || \
					OldActionID == ACT_COMM_NONE || OldActionID == ACT_COMM_NO_PE || OldActionID == ACT_COMM_THERMISTOR))
		return;

	switch(ActionID)
	{
		case ACT_COMM_NONE:
			OldPostion = 0;
			ZcRD_RegisterReset();
			break;

		case ACT_COMM_ILEAK_GATE_EMITTER_POS_PULSE:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();
					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);

					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTN, TRUE);

					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_ILEAK_GATE_EMITTER_NEG_PULSE:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTN, TRUE);

					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTN, TRUE);

					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_UTH_GATE_EMITTER:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT3, TRUE);
					ZcRD_OutputValuesCompose(MC_G_C_POT4, TRUE);

					ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT1, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT2, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT3, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_C_POT4, TRUE);

					ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_Q_GATE:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_GT_G, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_GT_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_GT_GE_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_USAT_COLLECTOR_EMITTER:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_LSL_G, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_LSL_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTN, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_LSL_G, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_LSL_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTN, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_UFW_CHOPPER_DIODE:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(OL_G_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_LSL_G, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_LSL_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_C_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_LSL_POTN, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_E_POT_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(OL_G_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_G_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_G_2_LSL_G, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_G_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_GE_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_GE_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_GE_2_LSL_GE, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_GE_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_C_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_C_POT_2_LSL_POTN, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTN_COMM, TRUE);

					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM1, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM2, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM3, TRUE);
					ZcRD_OutputValuesCompose(OL_E_POT_2_COMM4, TRUE);
					ZcRD_OutputValuesCompose(MC_E_POT_2_LSL_POTP, TRUE);
					ZcRD_OutputValuesCompose(IL_LSL_POTP_COMM, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_ILEAK_COLLECTOR_EMITTER:
			{
				if (DataTable[REG_MEASUREMENT_POSITION] == 1)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 1;

					ZcRD_OutputValuesCompose(MC_G_GE, TRUE);

					ZcRD_RegisterFlushWrite();
				}
				else if (DataTable[REG_MEASUREMENT_POSITION] == 2)
				{
					ZcRD_OutputValuesReset();

					COMM_DisconnectPE();

					OldPostion = 2;

					ZcRD_OutputValuesCompose(MC_G_2_GE, TRUE);

					ZcRD_RegisterFlushWrite();
				}
			}
			break;

		case ACT_COMM_THERMISTOR:
			{
				ZcRD_OutputValuesReset();

				COMM_DisconnectPE();

				OldPostion = 0;

				ZcRD_OutputValuesCompose(OL_T1_COMM1, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM2, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM3, TRUE);
				ZcRD_OutputValuesCompose(OL_T1_COMM4, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM1, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM2, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM3, TRUE);
				ZcRD_OutputValuesCompose(OL_T2_COMM4, TRUE);

				ZcRD_OutputValuesCompose(MC_T2_GT_G, TRUE);
				ZcRD_OutputValuesCompose(MC_T1_GT_GE, TRUE);
				ZcRD_OutputValuesCompose(MC_T2_GT_G_POT, TRUE);
				ZcRD_OutputValuesCompose(MC_T1_GT_GE_POT, TRUE);

				ZcRD_RegisterFlushWrite();
			}
			break;

		case ACT_COMM_NO_PE:
			{
				OldPostion = 0;
				ZcRD_OutputValuesReset();
				COMM_DisconnectPE();
				ZcRD_RegisterFlushWrite();
			}
			break;

		default:
			break;
	}

	OldActionID = ActionID;
}
// ----------------------------------------
*/

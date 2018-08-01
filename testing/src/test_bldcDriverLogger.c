/*
 * test_bldcDriverSerializer.c
 *
 *  Created on: Jul 20, 2018
 *      Author: simon
 */

// =============== Includes ==============================================
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "bldcDriverSerializer_logger.h"
#include "serializer.h"

// =============== Defines ===============================================

// =============== Variables =============================================
static uint32_t timestamp_testvalue = 123456789;

static EventAttr loggingIsEnabled_testvalue = { 0 };
static EventAttr compA_IR_testvalue = { 0 };
static EventAttr compB_IR_testvalue = { 0 };
static EventAttr compC_IR_testvalue = { 0 };

static NrAttr_int32 currentA_testvalue = { 31, 0 };
static NrAttr_int32 currentB_testvalue = { -22, 0 };
static NrAttr_uint32 currentRangeA_testvalue = { 7, 0 };
static NrAttr_uint32 currentRangeB_testvalue = { 12, 0 };
static NrAttr_uint32 absCurrentSetPoint_testvalue = { 30, 0 };
static NrAttr_uint32 dutyCycle_testvalue = { 1250, 0 };
static NrAttr_int32 currentControllerOutput_testvalue = { -6, 0 };

static NrAttr_uint32 absRotorPosEncoder_testvalue = { 125, 0 };
static NrAttr_int32 rotorPosEncoder_testvalue = { -5, 0 };
static NrAttr_int32 rotorPosSensorless_testvalue = { 8, 0 };
static NrAttr_int32 rotorPosControllerOutput_testvalue = { -1, 0 };

static NrAttr_int32 time60Deg_testvalue = { 18970, 0 };
static NrAttr_int32 cycleTime_testvalue = { 158794, 0 };
static NrAttr_uint32 loggingConfiguration_testvalue = { 0b101010101010101010, 0 };

static StringAttr debugMsg_testvalue;
static StringAttr infoMsg_testvalue;
static StringAttr errorMsg_testvalue;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
// --------------- test.h ----------------------------------------------------------------------------------------
void startTest_bldcDriverLogger() {
#ifndef LOGGER_TX
	printf("logger TX not enabled");
	assert(0);
#endif /* LOGGER_TX */
#ifndef LOGGER_RX
	printf("logger RX not enabled");
	assert(0);
#endif /* LOGGER_TX */

	debugMsg_testvalue.pValue = "This is a debug message.";
	debugMsg_testvalue.flag = 0;
	infoMsg_testvalue.pValue = "This is a info message.";
	infoMsg_testvalue.flag = 0;
	errorMsg_testvalue.pValue = "This is a error message.";
	errorMsg_testvalue.flag = 0;

	startLoggingPackage(timestamp_testvalue);

	assert(add_loggingIsEnabled() == SUCCESSFUL);
	assert(add_CompA_IR() == SUCCESSFUL);
	assert(add_CompB_IR() == SUCCESSFUL);
	assert(add_CompC_IR() == SUCCESSFUL);

	// - numbers
	assert(add_CurrentA(currentA_testvalue.value) == SUCCESSFUL);
	assert(add_CurrentB(currentB_testvalue.value) == SUCCESSFUL);
	assert(add_CurrentRangeA(currentRangeA_testvalue.value) == SUCCESSFUL);
	assert(add_CurrentRangeB(currentRangeB_testvalue.value) == SUCCESSFUL);
	assert(add_AbsCurrentSetPoint(absCurrentSetPoint_testvalue.value) == SUCCESSFUL);
	assert(add_DutyCycle(dutyCycle_testvalue.value) == SUCCESSFUL);
	assert(add_CurrentControllerOutput(currentControllerOutput_testvalue.value) == SUCCESSFUL);

	assert(add_AbsRotorPosEncoder(absRotorPosEncoder_testvalue.value) == SUCCESSFUL);
	assert(add_RotorPosEncoder(rotorPosEncoder_testvalue.value) == SUCCESSFUL);
	assert(add_RotorPosSensorless(rotorPosSensorless_testvalue.value) == SUCCESSFUL);
	assert(add_RotorPosControllerOutput(rotorPosControllerOutput_testvalue.value) == SUCCESSFUL);

	assert(add_Time60Deg(time60Deg_testvalue.value) == SUCCESSFUL);
	assert(add_CycleTime(cycleTime_testvalue.value) == SUCCESSFUL);
	assert(add_loggingConfiguration(loggingConfiguration_testvalue.value) == SUCCESSFUL);

	// - messages
	assert(add_DebugMsg(debugMsg_testvalue.pValue) == SUCCESSFUL);
	assert(add_InfoMsg(infoMsg_testvalue.pValue) == SUCCESSFUL);
	assert(add_ErrorMsg(errorMsg_testvalue.pValue) == SUCCESSFUL);

	closePackage();
}

void analyzeFlags_bldcDriverLogger() {
	assert(loggingIsEnabled_testvalue.flag);
	assert(compA_IR_testvalue.flag);
	assert(compB_IR_testvalue.flag);
	assert(compC_IR_testvalue.flag);

	assert(currentA_testvalue.flag);
	assert(currentB_testvalue.flag);
	assert(currentRangeA_testvalue.flag);
	assert(currentRangeB_testvalue.flag);
	assert(absCurrentSetPoint_testvalue.flag);
	assert(dutyCycle_testvalue.flag);
	assert(currentControllerOutput_testvalue.flag);

	assert(absRotorPosEncoder_testvalue.flag);
	assert(rotorPosEncoder_testvalue.flag);
	assert(rotorPosSensorless_testvalue.flag);
	assert(rotorPosControllerOutput_testvalue.flag);

	assert(time60Deg_testvalue.flag);
	assert(cycleTime_testvalue.flag);
	assert(loggingConfiguration_testvalue.flag);

	assert(debugMsg_testvalue.flag);
	assert(infoMsg_testvalue.flag);
	assert(errorMsg_testvalue.flag);
}
// --------------- bldcDriverSerializer_logger.h -----------------------------------------------------------------------
void loggingIsEnabled(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	EventAttr *temp = &loggingIsEnabled_testvalue;
	temp->flag = 1;
}

void compA_IR(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	EventAttr *temp = &compA_IR_testvalue;
	temp->flag = 1;
}
void compB_IR(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	EventAttr *temp = &compB_IR_testvalue;
	temp->flag = 1;
}
void compC_IR(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	EventAttr *temp = &compC_IR_testvalue;
	temp->flag = 1;
}

void currentA(int32_t current, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &currentA_testvalue;
	assert(current == temp->value);
	temp->flag = 1;
}
void currentB(int32_t current, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &currentB_testvalue;
	assert(current == temp->value);
	temp->flag = 1;
}
void currentRangeA(uint32_t range, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &currentRangeA_testvalue;
	assert(range == temp->value);
	temp->flag = 1;
}
void currentRangeB(uint32_t range, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &currentRangeB_testvalue;
	assert(range == temp->value);
	temp->flag = 1;
}
void absCurrentSetPoint(uint32_t setpoint, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &absCurrentSetPoint_testvalue;
	assert(setpoint == temp->value);
	temp->flag = 1;
}
void dutyCycle(uint32_t dutyCycle, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &dutyCycle_testvalue;
	assert(dutyCycle == temp->value);
	temp->flag = 1;
}
void currentControllerOutput(int32_t controllerOut, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &currentControllerOutput_testvalue;
	assert(controllerOut == temp->value);
	temp->flag = 1;
}

void absRotorPosEncoder(uint32_t pos, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &absRotorPosEncoder_testvalue;
	assert(pos == temp->value);
	temp->flag = 1;
}
void rotorPosEncoder(int32_t pos, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &rotorPosEncoder_testvalue;
	assert(pos == temp->value);
	temp->flag = 1;
}
void rotorPosSensorless(int32_t pos, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &rotorPosSensorless_testvalue;
	assert(pos == temp->value);
	temp->flag = 1;
}
void rotorPosControllerOutput(int32_t controllerOut, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &rotorPosControllerOutput_testvalue;
	assert(controllerOut == temp->value);
	temp->flag = 1;
}

void time60Deg(uint32_t t60deg, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &time60Deg_testvalue;
	assert(t60deg == temp->value);
	temp->flag = 1;
}
void cycleTime(uint32_t cycletime, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_int32 *temp = &cycleTime_testvalue;
	assert(cycletime == temp->value);
	temp->flag = 1;
}
void loggingConfiguration(uint32_t config, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	NrAttr_uint32 *temp = &loggingConfiguration_testvalue;
	assert(config == temp->value);
	temp->flag = 1;
}

void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	StringAttr *temp = &debugMsg_testvalue;
	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == temp->pValue[cnt]);
	}
	temp->flag = 1;
}
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	StringAttr *temp = &infoMsg_testvalue;
	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == temp->pValue[cnt]);
	}
	temp->flag = 1;
}
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	StringAttr *temp = &errorMsg_testvalue;
	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == temp->pValue[cnt]);
	}
	temp->flag = 1;
}


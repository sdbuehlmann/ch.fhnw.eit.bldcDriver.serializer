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

#include "bldcDriverSerializer.h"
#include "bldcDriverSerializer_logger.h"

// =============== Defines ===============================================

// =============== Variables =============================================
static uint8_t buffer[500];
static uint8_t bufferCnt = 0;

static uint32_t serialized_timestamp = 123456789;

static int32_t serialized_currentA = 123;
static int32_t serialized_currentB = -321;
static uint32_t serialized_currentRangeA = 31;
static uint32_t serialized_currentRangeB = 11;
static uint32_t serialized_absCurrentSP = 165;
static uint32_t serialized_dutyCycle = 1089;
static int32_t serialized_currentContOut = -7;

static uint32_t serialized_absRotPosEncoder = 301;
static int32_t serialized_rotPosEncoder = -8;
static int32_t serialized_rotPosSensLess = -5;
static int32_t serialized_rotPosContOut = -1;

static uint32_t serialized_entryState = 5;
static uint32_t serialized_t60Deg = 1589;
static uint32_t serialized_cycletime = 58974;

static uint8_t serialized_debugMsg[] = "This is a debug message.";
static uint8_t serialized_infoMsg[] = "This is a info message.";
static uint8_t serialized_errorMsg[] = "This is a error message.";

// flags
static uint8_t flag_mainReset = 0;
static uint8_t flag_compA = 0;
static uint8_t flag_compB = 0;
static uint8_t flag_compC = 0;
static uint8_t flag_loggerBufferOverflow = 0;

static uint8_t flag_currentA = 0;
static uint8_t flag_currentB = 0;
static uint8_t flag_currentRangeA = 0;
static uint8_t flag_currentRangeB = 0;
static uint8_t flag_absCurrentSP = 0;
static uint8_t flag_dutyCycle = 0;
static uint8_t flag_currentContOut = 0;

static uint8_t flag_absRotPosEncoder = 0;
static uint8_t flag_rotPosEncoder = 0;
static uint8_t flag_rotPosSensLess = 0;
static uint8_t flag_rotPosContOut = 0;

static uint8_t flag_entryState = 0;
static uint8_t flag_t60Deg = 0;
static uint8_t flag_cycletime = 0;

static uint8_t flag_debugMsg = 0;
static uint8_t flag_infoMsg = 0;
static uint8_t flag_errorMsg = 0;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
int main(void) {
	startLoggingPackage(serialized_timestamp);

	add_MainReset();
	add_CompA_IR();
	add_CompB_IR();
	add_CompC_IR();
	add_LoggerBufferOverflow();

	// - numbers
	add_CurrentA(serialized_currentA);
	add_CurrentB(serialized_currentB);
	add_CurrentRangeA(serialized_currentRangeA);
	add_CurrentRangeB(serialized_currentRangeB);
	add_AbsCurrentSetPoint(serialized_absCurrentSP);
	add_DutyCycle(serialized_dutyCycle);
	add_CurrentControllerOutput(serialized_currentContOut);

	add_AbsRotorPosEncoder(serialized_absRotPosEncoder);
	add_RotorPosEncoder(serialized_rotPosEncoder);
	add_RotorPosSensorless(serialized_rotPosSensLess);
	add_RotorPosControllerOutput(serialized_rotPosContOut);

	add_EntryState(serialized_entryState);
	add_Time60Deg(serialized_t60Deg);
	add_CycleTime(serialized_cycletime);

	// - messages
	add_DebugMsg(serialized_debugMsg);
	add_InfoMsg(serialized_infoMsg);
	add_ErrorMsg(serialized_errorMsg);

	closePackage();

	for (uint8_t cnt = 0; cnt < bufferCnt; cnt++) {
		handleIncomming(buffer[cnt]);
	}

	// check flags
	assert(flag_mainReset);

	assert(flag_compA);
	assert(flag_compB);
	assert(flag_compC);
	assert(flag_loggerBufferOverflow);

	assert(flag_currentA);
	assert(flag_currentB);
	assert(flag_currentRangeA);
	assert(flag_currentRangeB);
	assert(flag_absCurrentSP);
	assert(flag_dutyCycle);
	assert(flag_currentContOut);

	assert(flag_absRotPosEncoder);
	assert(flag_rotPosEncoder);
	assert(flag_rotPosSensLess);
	assert(flag_rotPosContOut);

	assert(flag_entryState);
	assert(flag_t60Deg);
	assert(flag_cycletime);

	assert(flag_debugMsg);
	assert(flag_infoMsg);
	assert(flag_errorMsg);

	printf("passed all tests successfully");
}

void handleOutgoing(uint8_t data) {
	buffer[bufferCnt] = data;
	bufferCnt++;
}

// logging
void mainReset(uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	flag_mainReset = 1;
}
void compA_IR(uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	flag_compA = 1;
}
void compB_IR(uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	flag_compB = 1;
}
void compC_IR(uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	flag_compC = 1;
}
void loggerBufferOverflow(uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	flag_loggerBufferOverflow = 1;
}

void currentA(int32_t current, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(current == serialized_currentA);
	flag_currentA = 1;
}
void currentB(int32_t current, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(current == serialized_currentB);
	flag_currentB = 1;
}
void currentRangeA(uint32_t range, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(range == serialized_currentRangeA);
	flag_currentRangeA = 1;
}
void currentRangeB(uint32_t range, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(range == serialized_currentRangeB);
	flag_currentRangeB = 1;
}
void absCurrentSetPoint(uint32_t setpoint, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(setpoint == serialized_absCurrentSP);
	flag_absCurrentSP = 1;
}
void dutyCycle(uint32_t dutyCycle, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(dutyCycle == serialized_dutyCycle);
	flag_dutyCycle = 1;
}
void currentControllerOutput(int32_t controllerOut, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(controllerOut == serialized_currentContOut);
	flag_currentContOut = 1;
}

void absRotorPosEncoder(uint32_t pos, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(pos == serialized_absRotPosEncoder);
	flag_absRotPosEncoder = 1;
}
void rotorPosEncoder(int32_t pos, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(pos == serialized_rotPosEncoder);
	flag_rotPosEncoder = 1;
}
void rotorPosSensorless(int32_t pos, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(pos == serialized_rotPosSensLess);
	flag_rotPosSensLess = 1;
}
void rotorPosControllerOutput(int32_t controllerOut, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(controllerOut == serialized_rotPosContOut);
	flag_rotPosContOut = 1;
}

void time60Deg(int32_t t60deg, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(t60deg == serialized_t60Deg);
	flag_t60Deg = 1;
}
void cycleTime(int32_t cycletime, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(cycletime == serialized_cycletime);
	flag_cycletime = 1;
}
void entryState(uint32_t state, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);
	assert(state == serialized_entryState);
	flag_entryState = 1;
}

void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);

	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == serialized_debugMsg[cnt]);
	}
	flag_debugMsg = 1;
}
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);

	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == serialized_infoMsg[cnt]);
	}
	flag_infoMsg = 1;

}
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	assert(timestamp == serialized_timestamp);

	for (uint8_t cnt = 0; cnt < lenght; cnt++) {
		assert(msg[cnt] == serialized_errorMsg[cnt]);
	}
	flag_errorMsg = 1;

}

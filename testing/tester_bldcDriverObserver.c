/*
 * tester_bldcDriverObserver.c
 *
 *  Created on: Jul 24, 2018
 *      Author: simon
 */
// =============== Includes ==============================================
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "bldcDriverSerializer.h"
#include "bldcDriverSerializer_observer.h"

// =============== Defines ===============================================

// =============== Variables =============================================
static uint8_t buffer[500];
static uint8_t bufferCnt = 0;

static uint32_t timestamp_testvalue = 123456789;

static EventAttr serialOperatingModeIsEnabled_testvalue = { 0 };
static EventAttr serialOperatingModeIsDisabled_testvalue = { 0 };
static EventAttr driverIsEnabled_testvalue = { 0 };
static EventAttr driverIsDisabled_testvalue = { 0 };
static EventAttr positiveTorqueIsSelected_testvalue = { 0 };
static EventAttr negativeTorqueIsSelected_testvalue = { 0 };
static EventAttr rotadeClockwiseIsSelected_testvalue = { 0 };
static EventAttr rotadeCounterclockwiseIsSelected_testvalue = { 0 };
static EventAttr driverReseted_testvalue = { 0 };
static EventAttr bufferOverflow_testvalue = { 0 };

static NrAttr_uint32 encoderCalibrationValue_testvalue = { 120, 0 };
static NrAttr_uint8 entryState_testvalue = { 7, 0 };
static NrAttr_uint8 positiveTorqueLevel_testvalue = { 73, 0 };
static NrAttr_uint8 negativeTorqueLevel_testvalue = { 55, 0 };
static NrAttr_uint8 maxAbsPhaseCurrent_testvalue = { 17, 0 };
static NrAttr_uint8 timing_testvalue = { 12, 0 };
static NrAttr_uint32 rotorpositionControllerPParam_testvalue = { 512, 0 };
static NrAttr_uint32 rotorpositionControllerIParam_testvalue = { 128, 0 };

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
int main(void) {
#ifndef OBSERVER_TX
	printf("logger TX not enabled");
	assert(0);
#endif /* LOGGER_TX */
#ifndef OBSERVER_RX
	printf("logger RX not enabled");
	assert(0);
#endif /* LOGGER_TX */

	startObservingPackage(timestamp_testvalue);

	add_serialOperatingModeIsEnabled();
	add_serialOperatingModeIsDisabled();
	add_driverIsEnabled();
	add_driverIsDisabled();
	add_positiveTorqueIsSelected();
	add_negativeTorqueIsSelected();
	add_rotadeClockwiseIsSelected();
	add_rotadeCounterclockwiseIsSelected();
	add_driverReseted();
	add_bufferOverflow();

	add_encoderCalibrationValue(encoderCalibrationValue_testvalue.value);
	add_entryState(entryState_testvalue.value);
	add_positiveTorqueLevel(positiveTorqueLevel_testvalue.value);
	add_negativeTorqueLevel(negativeTorqueLevel_testvalue.value);
	add_maxAbsPhaseCurrent(maxAbsPhaseCurrent_testvalue.value);
	add_timing(timing_testvalue.value);
	add_rotorpositionControllerPParam(
			rotorpositionControllerPParam_testvalue.value);
	add_rotorpositionControllerIParam(
			rotorpositionControllerIParam_testvalue.value);

	closePackage();

	for (uint8_t cnt = 0; cnt < bufferCnt; cnt++) {
		handleIncomming(buffer[cnt]);
	}

	// check flags
	add_serialOperatingModeIsEnabled(
			serialOperatingModeIsEnabled_testvalue.flag);
	add_serialOperatingModeIsDisabled(
			serialOperatingModeIsDisabled_testvalue.flag);
	add_driverIsEnabled(driverIsEnabled_testvalue.flag);
	add_driverIsDisabled(driverIsDisabled_testvalue.flag);
	add_positiveTorqueIsSelected(positiveTorqueIsSelected_testvalue.flag);
	add_negativeTorqueIsSelected(negativeTorqueIsSelected_testvalue.flag);
	add_rotadeClockwiseIsSelected(rotadeClockwiseIsSelected_testvalue.flag);
	add_rotadeCounterclockwiseIsSelected(
			rotadeCounterclockwiseIsSelected_testvalue.flag);
	add_driverReseted(driverReseted_testvalue.flag);
	add_bufferOverflow(bufferOverflow_testvalue.flag);

	add_encoderCalibrationValue(encoderCalibrationValue_testvalue.flag);
	add_entryState(entryState_testvalue.flag);
	add_positiveTorqueLevel(positiveTorqueLevel_testvalue.flag);
	add_negativeTorqueLevel(negativeTorqueLevel_testvalue.flag);
	add_maxAbsPhaseCurrent(maxAbsPhaseCurrent_testvalue.flag);
	add_timing(timing_testvalue.flag);
	add_rotorpositionControllerPParam(
			rotorpositionControllerPParam_testvalue.flag);
	add_rotorpositionControllerIParam(
			rotorpositionControllerIParam_testvalue.flag);

	printf("passed all tests successfully");
}

void handleOutgoing(uint8_t data) {
	buffer[bufferCnt] = data;
	bufferCnt++;
}

// ____RX____ (if supported, functions has to be implemented from user)
void serialOperatingModeIsEnabled(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	serialOperatingModeIsEnabled_testvalue.flag = 1;
}
void serialOperatingModeIsDisabled(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
		serialOperatingModeIsDisabled_testvalue.flag = 1;
}
void driverIsEnabled(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	driverIsEnabled_testvalue.flag = 1;
}
void driverIsDisabled(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	driverIsDisabled_testvalue.flag = 1;
}
void positiveTorqueIsSelected(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	positiveTorqueIsSelected_testvalue.flag = 1;
}
void negativeTorqueIsSelected(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	negativeTorqueIsSelected_testvalue.flag = 1;
}
void rotadeClockwiseIsSelected(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	rotadeClockwiseIsSelected_testvalue.flag = 1;
}
void rotadeCounterclockwiseIsSelected(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	rotadeCounterclockwiseIsSelected_testvalue.flag = 1;
}
void driverReseted(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	driverReseted_testvalue.flag = 1;
}
void bufferOverflow(uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	bufferOverflow_testvalue.flag = 1;
}

void encoderCalibrationValue(uint32_t calibrationValue, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(calibrationValue == encoderCalibrationValue_testvalue.value);
	encoderCalibrationValue_testvalue.flag = 1;
}
void entryState(uint8_t state, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(state == entryState_testvalue.value);
	entryState_testvalue.flag = 1;
}
void positiveTorqueLevel(uint8_t level, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(level == positiveTorqueLevel_testvalue.value);
	positiveTorqueLevel_testvalue.flag = 1;
}
void negativeTorqueLevel(uint8_t level, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(level == negativeTorqueLevel_testvalue.value);
	negativeTorqueLevel_testvalue.flag = 1;
}
void maxAbsPhaseCurrent(uint8_t current, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(current == maxAbsPhaseCurrent_testvalue.value);
	maxAbsPhaseCurrent_testvalue.flag = 1;
}
void timing(uint8_t timing, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(timing == timing_testvalue.value);
	timing_testvalue.flag = 1;
}
void rotorpositionControllerPParam(uint32_t pParam, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(pParam == rotorpositionControllerPParam_testvalue.value);
	rotorpositionControllerPParam_testvalue.flag = 1;
}
void rotorpositionControllerIParam(uint32_t iParam, uint32_t timestamp) {
	assert(timestamp == timestamp_testvalue);
	assert(iParam == rotorpositionControllerIParam_testvalue.value);
	rotorpositionControllerIParam_testvalue.flag = 1;
}


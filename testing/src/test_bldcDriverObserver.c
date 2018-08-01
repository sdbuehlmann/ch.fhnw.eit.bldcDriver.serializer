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
#include "serializer.h"
#include "bldcDriverSerializer_observer.h"

// =============== Defines ===============================================

// =============== Variables =============================================
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
void startTest_bldcDriverObserver() {
#ifndef OBSERVER_TX
	printf("logger TX not enabled");
	assert(0);
#endif /* LOGGER_TX */
#ifndef OBSERVER_RX
	printf("logger RX not enabled");
	assert(0);
#endif /* LOGGER_TX */

	startObservingPackage(timestamp_testvalue);

	assert(add_serialOperatingModeIsEnabled() == SUCCESSFUL);
	assert(add_serialOperatingModeIsDisabled() == SUCCESSFUL);
	assert(add_driverIsEnabled() == SUCCESSFUL);
	assert(add_driverIsDisabled() == SUCCESSFUL);
	assert(add_positiveTorqueIsSelected() == SUCCESSFUL);
	assert(add_negativeTorqueIsSelected() == SUCCESSFUL);
	assert(add_rotadeClockwiseIsSelected() == SUCCESSFUL);
	assert(add_rotadeCounterclockwiseIsSelected() == SUCCESSFUL);
	assert(add_driverReseted() == SUCCESSFUL);
	assert(add_bufferOverflow() == SUCCESSFUL);

	assert(add_encoderCalibrationValue(encoderCalibrationValue_testvalue.value) == SUCCESSFUL);
	assert(add_entryState(entryState_testvalue.value) == SUCCESSFUL);
	assert(add_positiveTorqueLevel(positiveTorqueLevel_testvalue.value) == SUCCESSFUL);
	assert(add_negativeTorqueLevel(negativeTorqueLevel_testvalue.value) == SUCCESSFUL);
	assert(add_maxAbsPhaseCurrent(maxAbsPhaseCurrent_testvalue.value) == SUCCESSFUL);
	assert(add_timing(timing_testvalue.value) == SUCCESSFUL);
	assert(add_rotorpositionControllerPParam(rotorpositionControllerPParam_testvalue.value) == SUCCESSFUL);
	assert(add_rotorpositionControllerIParam(rotorpositionControllerIParam_testvalue.value) == SUCCESSFUL);

	closePackage();
}

void analyzeFlags_bldcDriverObserver() {
	assert(serialOperatingModeIsEnabled_testvalue.flag);
	assert(serialOperatingModeIsDisabled_testvalue.flag);
	assert(driverIsEnabled_testvalue.flag);
	assert(driverIsDisabled_testvalue.flag);
	assert(positiveTorqueIsSelected_testvalue.flag);
	assert(negativeTorqueIsSelected_testvalue.flag);
	assert(rotadeClockwiseIsSelected_testvalue.flag);
	assert(rotadeCounterclockwiseIsSelected_testvalue.flag);
	assert(driverReseted_testvalue.flag);
	assert(bufferOverflow_testvalue.flag);

	assert(encoderCalibrationValue_testvalue.flag);
	assert(entryState_testvalue.flag);
	assert(positiveTorqueLevel_testvalue.flag);
	assert(negativeTorqueLevel_testvalue.flag);
	assert(maxAbsPhaseCurrent_testvalue.flag);
	assert(timing_testvalue.flag);
	assert(rotorpositionControllerPParam_testvalue.flag);
	assert(rotorpositionControllerIParam_testvalue.flag);
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

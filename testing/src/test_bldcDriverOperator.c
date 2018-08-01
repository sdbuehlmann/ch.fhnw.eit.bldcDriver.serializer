/*
 * test_bldcDriverOperator.c
 *
 *  Created on: Jul 21, 2018
 *      Author: simon
 */

// =============== Includes ==============================================
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "test.h"
#include "bldcDriverSerializer.h"
#include "bldcDriverSerializer_operator.h"
#include "serializer.h"
#include "serializerPrinter.h"

// =============== Defines ===============================================

// =============== Variables =============================================
static EventAttr enableSerialOperationgMode_testvalue = { 0 };
static EventAttr enableLogging_testvalue = { 0 };
static EventAttr enableDriver_testvalue = { 0 };
static EventAttr disableDriver_testvalue = { 0 };
static EventAttr selectPositiveTorque_testvalue = { 0 };
static EventAttr selectNegativeTorque_testvalue = { 0 };
static EventAttr rotadeClockwise_testvalue = { 0 };
static EventAttr rotadeCounterclockwise_testvalue = { 0 };
static EventAttr getObservingInfos_testvalue = { 0 };
static EventAttr getLoggingConfig_testvalue = { 0 };

static NrAttr_uint8 setPositiveTorqueLevel_testvalue = { 25, 0 };
static NrAttr_uint8 setNegativeTorqueLevel_testvalue = { 33, 0 };
static NrAttr_uint8 setMaxPhaseCurrent_testvalue = { 15, 0 };

static NrAttr_uint8 setTiming_testvalue = { 12, 0 };
static NrAttr_uint32 setRotorPosControllerPParam_testvalue = { 1587, 0 };
static NrAttr_uint32 setRotorPosControllerIParam_testvalue = { 8974, 0 };
static NrAttr_uint32 setLoggingConfig_testvalue = { 0b10101010101010101010101010101010, 0 };

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
// --------------- test.h --------------------------------------------------------------------------------------------
void startTest_bldcDriverOperator() {
#ifndef OPERATOR_TX
	printf("TX not enabled");
	assert(0);
#endif /* OPERATOR_TX */
#ifndef OPERATOR_RX
	printf("RX not enabled");
	assert(0);
#endif /* OPERATOR_RX */

	startOperatorPackage();

	assert(add_enableSerialOperatingMode() == SUCCESSFUL);
	assert(add_enableLogging() == SUCCESSFUL);
	assert(add_EnableDriver() == SUCCESSFUL);
	assert(add_DisableDriver() == SUCCESSFUL);
	assert(add_SelectPositiveTorque() == SUCCESSFUL);
	assert(add_SelectNegativeTorque() == SUCCESSFUL);
	assert(add_rotadeClockwise() == SUCCESSFUL);
	assert(add_rotadeCounterclockwise() == SUCCESSFUL);
	assert(add_getObservingInfos() == SUCCESSFUL);
	assert(add_getLoggingConfig() == SUCCESSFUL);

	assert(add_SetPositiveTorqueLevel(setPositiveTorqueLevel_testvalue.value) == SUCCESSFUL);
	assert(add_SetNegativeTorqueLevel(setNegativeTorqueLevel_testvalue.value) == SUCCESSFUL);
	assert(add_SetMaxPhaseCurrent(setMaxPhaseCurrent_testvalue.value) == SUCCESSFUL);

	assert(add_SetTiming(setTiming_testvalue.value) == SUCCESSFUL);
	assert(add_SetRotorPosController_pParam( setRotorPosControllerPParam_testvalue.value) == SUCCESSFUL);
	assert(add_SetRotorPosController_iParam( setRotorPosControllerIParam_testvalue.value) == SUCCESSFUL);
	assert(add_setLoggingConfig(setLoggingConfig_testvalue.value) == SUCCESSFUL);

	assert(closePackage() == SUCCESSFUL);
}

void analyzeFlags_bldcDriverOperator() {
	assert(enableSerialOperationgMode_testvalue.flag);
	assert(enableLogging_testvalue.flag);
	assert(enableDriver_testvalue.flag);
	assert(disableDriver_testvalue.flag);
	assert(selectPositiveTorque_testvalue.flag);
	assert(selectNegativeTorque_testvalue.flag);
	assert(rotadeClockwise_testvalue.flag);
	assert(rotadeCounterclockwise_testvalue.flag);
	assert(getObservingInfos_testvalue.flag);
	assert(getLoggingConfig_testvalue.flag);

	assert(setPositiveTorqueLevel_testvalue.flag);
	assert(setNegativeTorqueLevel_testvalue.flag);
	assert(setMaxPhaseCurrent_testvalue.flag);

	assert(setTiming_testvalue.flag);
	assert(setRotorPosControllerPParam_testvalue.flag);
	assert(setRotorPosControllerIParam_testvalue.flag);
	assert(setLoggingConfig_testvalue.flag);
}

// --------------- bldcDriverSerializer_operator.h ---------------------------------------------------------------------
void enableSerialOperationgMode() {
	EventAttr *temp = &enableSerialOperationgMode_testvalue;
	temp->flag = 1;
}
void enableLogging() {
	EventAttr *temp = &enableLogging_testvalue;
	temp->flag = 1;
}
void enableDriver() {
	EventAttr *temp = &enableDriver_testvalue;
	temp->flag = 1;
}
void disableDriver() {
	EventAttr *temp = &disableDriver_testvalue;
	temp->flag = 1;
}
void selectPositiveTorque() {
	EventAttr *temp = &selectPositiveTorque_testvalue;
	temp->flag = 1;
}
void selectNegativeTorque() {
	EventAttr *temp = &selectNegativeTorque_testvalue;
	temp->flag = 1;
}
void rotadeClockwise() {
	EventAttr *temp = &rotadeClockwise_testvalue;
	temp->flag = 1;
}
void rotadeCounterclockwise() {
	EventAttr *temp = &rotadeCounterclockwise_testvalue;
	temp->flag = 1;
}
void getObservingInfos() {
	EventAttr *temp = &getObservingInfos_testvalue;
	temp->flag = 1;
}
void getLoggingConfig() {
	EventAttr *temp = &getLoggingConfig_testvalue;
	temp->flag = 1;
}

void setPositiveTorqueLevel(uint8_t level) {
	NrAttr_uint8 *temp = &setPositiveTorqueLevel_testvalue;
	assert(level == temp->value);
	temp->flag = 1;
}
void setNegativeTorqueLevel(uint8_t level) {
	NrAttr_uint8 *temp = &setNegativeTorqueLevel_testvalue;
	assert(level == temp->value);
	temp->flag = 1;
}
void setMaxPhaseCurrent(uint8_t current) {
	NrAttr_uint8 *temp = &setMaxPhaseCurrent_testvalue;
	assert(current == temp->value);
	temp->flag = 1;
}

void setTiming(uint8_t timing) {
	NrAttr_uint8 *temp = &setTiming_testvalue;
	assert(timing == temp->value);
	temp->flag = 1;
}
void setRotorPosController_pParam(uint32_t pParam) {
	NrAttr_uint32 *temp = &setRotorPosControllerPParam_testvalue;
	assert(pParam == temp->value);
	temp->flag = 1;
}
void setRotorPosController_iParam(uint32_t iParam) {
	NrAttr_uint32 *temp = &setRotorPosControllerIParam_testvalue;
	assert(iParam == temp->value);
	temp->flag = 1;
}
void setLoggingConfig(uint32_t config) {
	NrAttr_uint32 *temp = &setLoggingConfig_testvalue;
	assert(config == temp->value);
	temp->flag = 1;
}


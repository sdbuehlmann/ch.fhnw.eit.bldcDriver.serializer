/*
 * test_bldcDriverOperator.c
 *
 *  Created on: Jul 21, 2018
 *      Author: simon
 */


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

// =============== Defines ===============================================

// =============== Variables =============================================
static uint8_t buffer[500];
static uint8_t bufferCnt = 0;

static uint8_t serialized_posTorqueLevel = 123;
static uint8_t serialized_negTorqueLevel = -321;
static uint8_t serialized_maxPhaseCurrent = 31;

static uint8_t serialized_timing = 11;
static uint8_t serialized_rotPosContPParam = 165;
static uint8_t serialized_rotPosContIParam = 1089;

// flags
static uint8_t flag_enableSerialOperatingMode = 0;
static uint8_t flag_enableDriver = 0;
static uint8_t flag_disableDriver = 0;
static uint8_t flag_selectPositiveTorque = 0;
static uint8_t flag_selectNegativeTorque = 0;

static uint8_t flag_posTorqueLevel = 0;
static uint8_t flag_negTorqueLevel = 0;
static uint8_t flag_maxPhaseCurrent = 0;
static uint8_t flag_timing = 0;
static uint8_t flag_rotPosContPParam = 0;
static uint8_t flag_rotPosContIParam = 0;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
int main(void) {
	operator_startPackage();

	 operator_EnableSerialOperatingMode();
	 operator_EnableDriver();
	 operator_DisableDriver();
	 operator_SelectPositiveTorque();
	 operator_SelectNegativeTorque();

	 operator_SetPositiveTorqueLevel(serialized_posTorqueLevel);
	 operator_SetNegativeTorqueLevel(serialized_negTorqueLevel);
	 operator_SetMaxPhaseCurrent(serialized_maxPhaseCurrent);

	 operator_SetTiming(serialized_timing);
	 operator_SetRotorPosController_pParam(serialized_rotPosContPParam);
	 operator_SetRotorPosController_iParam(serialized_rotPosContIParam);

	closePackage();

	for (uint8_t cnt = 0; cnt < bufferCnt; cnt++) {
		deserialize(buffer[cnt]);
	}

	// check flags
	assert(flag_enableSerialOperatingMode);
	assert(flag_enableDriver);
	assert(flag_disableDriver);
	assert(flag_selectPositiveTorque);
	assert(flag_selectNegativeTorque);

	assert(flag_posTorqueLevel);
	assert(flag_negTorqueLevel);
	assert(flag_maxPhaseCurrent);
	assert(flag_timing);
	assert(flag_rotPosContPParam);
	assert(flag_rotPosContIParam);

	printf("passed all tests successfully");
}

void handleSerialized(uint8_t data) {
	buffer[bufferCnt] = data;
	bufferCnt++;
}

void enableSerialOperationgMode(){
	flag_enableSerialOperatingMode = 1;
}
void enableDriver(){
	flag_enableDriver = 1;
}
void disableDriver(){
	flag_disableDriver = 1;
}
void selectPositiveTorque(){
	flag_selectPositiveTorque = 1;
}
void selectNegativeTorque(){
	flag_selectNegativeTorque = 1;
}

void setPositiveTorqueLevel(uint8_t level){
	assert(level == serialized_posTorqueLevel);
	flag_posTorqueLevel = 1;
}
void setNegativeTorqueLevel(uint8_t level){
	assert(level == serialized_negTorqueLevel);
	flag_negTorqueLevel = 1;
}
void setMaxPhaseCurrent(uint8_t current){
	assert(current == serialized_maxPhaseCurrent);
	flag_maxPhaseCurrent = 1;
}

void setTiming(int8_t timing){
	assert(timing == serialized_timing);
	flag_timing = 1;
}
void setRotorPosController_pParam(uint32_t pParam){
	assert(pParam == serialized_rotPosContPParam);
	flag_rotPosContPParam = 1;
}
void setRotorPosController_iParam(uint32_t iParam){
	assert(iParam == serialized_rotPosContIParam);
	flag_rotPosContIParam = 1;
}

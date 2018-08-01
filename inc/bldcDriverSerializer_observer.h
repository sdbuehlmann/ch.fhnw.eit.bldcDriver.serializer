/*
 * bldcDriverSerializer_observer.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_OBSERVER_H_
#define INC_BLDCDRIVERSERIALIZER_OBSERVER_H_

#include "serializerConfig.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef OBSERVER_RX
	void serialOperatingModeIsEnabled(uint32_t timestamp);
	void serialOperatingModeIsDisabled(uint32_t timestamp);
	void driverIsEnabled(uint32_t timestamp);
	void driverIsDisabled(uint32_t timestamp);
	void positiveTorqueIsSelected(uint32_t timestamp);
	void negativeTorqueIsSelected(uint32_t timestamp);
	void rotadeClockwiseIsSelected(uint32_t timestamp);
	void rotadeCounterclockwiseIsSelected(uint32_t timestamp);
	void driverReseted(uint32_t timestamp);
	void bufferOverflow(uint32_t timestamp);

	void encoderCalibrationValue(uint32_t calibrationValue, uint32_t timestamp);
	void entryState(uint8_t state, uint32_t timestamp);
	void positiveTorqueLevel(uint8_t level, uint32_t timestamp);
	void negativeTorqueLevel(uint8_t level, uint32_t timestamp);
	void maxAbsPhaseCurrent(uint8_t current, uint32_t timestamp);
	void timing(uint8_t timing, uint32_t timestamp);
	void rotorpositionControllerPParam(uint32_t pParam, uint32_t timestamp);
	void rotorpositionControllerIParam(uint32_t iParam, uint32_t timestamp);
#endif

// ____TX____
#ifdef OBSERVER_TX
	void startObservingPackage(uint32_t timestamp);

	int8_t add_serialOperatingModeIsEnabled();
	int8_t add_serialOperatingModeIsDisabled();
	int8_t add_driverIsEnabled();
	int8_t add_driverIsDisabled();
	int8_t add_positiveTorqueIsSelected();
	int8_t add_negativeTorqueIsSelected();
	int8_t add_rotadeClockwiseIsSelected();
	int8_t add_rotadeCounterclockwiseIsSelected();
	int8_t add_driverReseted();
	int8_t add_bufferOverflow();

	int8_t add_encoderCalibrationValue(uint32_t calibrationValue);
	int8_t add_entryState(uint8_t state);
	int8_t add_positiveTorqueLevel(uint8_t level);
	int8_t add_negativeTorqueLevel(uint8_t level);
	int8_t add_maxAbsPhaseCurrent(uint8_t current);
	int8_t add_timing(uint8_t timing);
	int8_t add_rotorpositionControllerPParam(uint32_t pParam);
	int8_t add_rotorpositionControllerIParam(uint32_t iParam);
#endif



#endif /* INC_BLDCDRIVERSERIALIZER_OBSERVER_H_ */

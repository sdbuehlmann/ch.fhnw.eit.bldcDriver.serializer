/*
 * bldcDriverSerializer_observer.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_OBSERVER_H_
#define INC_BLDCDRIVERSERIALIZER_OBSERVER_H_

#include "bldcDriverSerializer.h"

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

	void add_serialOperatingModeIsEnabled();
	void add_serialOperatingModeIsDisabled();
	void add_driverIsEnabled();
	void add_driverIsDisabled();
	void add_positiveTorqueIsSelected();
	void add_negativeTorqueIsSelected();
	void add_rotadeClockwiseIsSelected();
	void add_rotadeCounterclockwiseIsSelected();
	void add_driverReseted();
	void add_bufferOverflow();

	void add_encoderCalibrationValue(uint32_t calibrationValue);
	void add_entryState(uint8_t state);
	void add_positiveTorqueLevel(uint8_t level);
	void add_negativeTorqueLevel(uint8_t level);
	void add_maxAbsPhaseCurrent(uint8_t current);
	void add_timing(uint8_t timing);
	void add_rotorpositionControllerPParam(uint32_t pParam);
	void add_rotorpositionControllerIParam(uint32_t iParam);
#endif



#endif /* INC_BLDCDRIVERSERIALIZER_OBSERVER_H_ */

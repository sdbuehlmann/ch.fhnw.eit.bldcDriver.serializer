/*
 * bldcDriverCom.c
 *
 *  Created on: Jul 19, 2018
 *      Author: simon
 */
// =============== Includes ==============================================
#include "serializer.h"
#include "serializerConfig.h"
#include "bldcDriverSerializer_logger.h"
#include "bldcDriverSerializer_operator.h"
#include "bldcDriverSerializer_observer.h"

// =============== Defines ===============================================
// __start flags__
#define HANDLE_LOGGER_DATA						handleXPackageData
#define START_LOGGER_PACKAGE					openXPackage

#define HANDLE_OPERATOR_DATA					handleYPackageData
#define START_OPERATOR_PACKAGE					openYPackage

#define HANDLE_OBSERVER_DATA					handleZPackageData
#define START_OBSERVER_PACKAGE					openZPackage

// __logger attributes_________________________________________________________________________
#define LOG_ATTR_LOGGING_ENABLED							ATTR_1

#define LOG_ATTR_COMP_A_IRQ 								ATTR_2
#define LOG_ATTR_COMP_B_IRQ									ATTR_3
#define LOG_ATTR_COMP_C_IRQ 								ATTR_4

#define LOG_ATTR_MSG_DEBUG 									ATTR_5
#define LOG_ATTR_MSG_INFO 									ATTR_6
#define LOG_ATTR_MSG_ERROR 									ATTR_7

#define LOG_ATTR_CURRENT_A 									ATTR_8
#define LOG_ATTR_CURRENT_B									ATTR_9
#define LOG_ATTR_CURRENT_A_RANGE 							ATTR_10
#define LOG_ATTR_CURRENT_B_RANGE 							ATTR_11
#define LOG_ATTR_ABS_PHASECURRENT_SETPOINT					ATTR_12
#define LOG_ATTR_DUTYCYCLE									ATTR_13
#define LOG_ATTR_CURRENT_CONTROLER_OUT						ATTR_14

#define LOG_ATTR_ROTORPOS_ENCODER_ABS						ATTR_15
#define LOG_ATTR_ROTORPOS_ENCODER							ATTR_16
#define LOG_ATTR_ROTORPOS_SENSORLESS						ATTR_17
#define LOG_ATTR_ROTORPOS_CONTROLLER_OUT					ATTR_18

#define LOG_ATTR_TIME_60DEG									ATTR_19
#define LOG_ATTR_CYCLE_TIME									ATTR_20
#define LOG_ATTR_LOGGING_CONFIGURATION						ATTR_21

// __operator attributes_________________________________________________________________________
// events
#define OPR_ATTR_ENABLE_SERIAL_OPERATING					ATTR_1
#define OPR_ATTR_ENABLELOGGING								ATTR_2
#define OPR_ATTR_ENABLE_DRIVER								ATTR_3
#define OPR_ATTR_DISABLE_DRIVER								ATTR_4
#define OPR_ATTR_SELECT_POS_TORQUE		 					ATTR_5
#define OPR_ATTR_SELECT_NEG_TORQUE		 					ATTR_6
#define OPR_ATTR_SET_ROTADE_CLOCKWISE		 				ATTR_7
#define OPR_ATTR_SET_ROTADE_COUNTERCLOCKWISE		 		ATTR_8
#define OPR_ATTR_GET_OBSERVING_INFOS		 				ATTR_9
#define OPR_ATTR_GET_LOGGING_CONFIG		 					ATTR_10

// unsigned
#define OPR_ATTR_SET_POS_TORQUE_LEVEL 						ATTR_11
#define OPR_ATTR_SET_NEG_TORQUE_LEVEL						ATTR_12
#define OPR_ATTR_SET_MAX_PHASE_CURRENT						ATTR_13

#define OPR_ATTR_TIMING 									ATTR_14
#define OPR_ATTR_SET_ROTORPOS_CONT_P_PARAM					ATTR_15
#define OPR_ATTR_SET_ROTORPOS_CONT_I_PARAM					ATTR_16
#define OPR_ATTR_SET_LOGGING_CONFIG							ATTR_17

// __observer attributes_________________________________________________________________________
// events
#define OBS_ATTR_SERIAL_OPERATING_MODE_IS_ENABLED			ATTR_1
#define OBS_ATTR_SERIAL_OPERATING_MODE_IS_DISABLED			ATTR_2
#define OBS_ATTR_DRIVER_IS_DISABLED							ATTR_3
#define OBS_ATTR_DRIVER_IS_ENABLED							ATTR_4
#define OBS_ATTR_POS_TORQUE_IS_SELECTED		 				ATTR_5
#define OBS_ATTR_NEG_TORQUE_IS_SELECTED		 				ATTR_6
#define OBS_ATTR_ROT_CLOCKWISE_IS_SELECTED		 			ATTR_7
#define OBS_ATTR_ROT_COUNTERCLOCKWISE_IS_SELECTED		 	ATTR_8
#define OBS_ATTR_DRIVER_RESETED								ATTR_9
#define OBS_ATTR_BUFFER_OVERFLOW							ATTR_10

// unsigned
#define OBS_ATTR_ENCODER_CALIBRATION 						ATTR_11
#define OBS_ATTR_ENTRY_STATE								ATTR_12
#define OBS_ATTR_POSITIVE_TORQUE_LEVEL						ATTR_13
#define OBS_ATTR_NEGATIVE_TORQUE_LEVEL						ATTR_14
#define OBS_ATTR_MAX_PHASE_CURRENT							ATTR_15
#define OBS_ATTR_TIMING										ATTR_16
#define OBS_ATTR_ROTORPOS_CONT_P_PARAM						ATTR_17
#define OBS_ATTR_ROTORPOS_CONT_I_PARAM						ATTR_18

// =============== Variables =============================================

// =============== Functions =============================================

// ____RX____
void HANDLE_LOGGER_DATA(uint32_t timestamp, uint8_t attr, uint8_t data[], uint8_t nrData) {
#ifdef LOGGER_RX

	switch (attr) {
	// events
	case LOG_ATTR_LOGGING_ENABLED:
		loggingIsEnabled(timestamp);
		break;
	case LOG_ATTR_COMP_A_IRQ:
		compA_IR(timestamp);
		break;
	case LOG_ATTR_COMP_B_IRQ:
		compB_IR(timestamp);
		break;
	case LOG_ATTR_COMP_C_IRQ:
		compC_IR(timestamp);
		break;

		// string
	case LOG_ATTR_MSG_DEBUG:
		debugMsg(decode_string(data, nrData), nrData, timestamp);
		break;
	case LOG_ATTR_MSG_INFO:
		infoMsg(decode_string(data, nrData), nrData, timestamp);
		break;
	case LOG_ATTR_MSG_ERROR:
		errorMsg(decode_string(data, nrData), nrData, timestamp);
		break;

		// unsigned
	case LOG_ATTR_CURRENT_A_RANGE:
		currentRangeA(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_CURRENT_B_RANGE:
		currentRangeB(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_ABS_PHASECURRENT_SETPOINT:
		absCurrentSetPoint(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_DUTYCYCLE:
		dutyCycle(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_ROTORPOS_ENCODER_ABS:
		absRotorPosEncoder(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_TIME_60DEG:
		time60Deg(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_CYCLE_TIME:
		cycleTime(decode_unsigned(data, nrData), timestamp);
		break;
	case LOG_ATTR_LOGGING_CONFIGURATION:
		loggingConfiguration(decode_unsigned(data, nrData), timestamp);
		break;

		// signed
	case LOG_ATTR_CURRENT_A:
		currentA(decode_signed(data, nrData), timestamp);
		break;
	case LOG_ATTR_CURRENT_B:
		currentB(decode_signed(data, nrData), timestamp);
		break;
	case LOG_ATTR_CURRENT_CONTROLER_OUT:
		currentControllerOutput(decode_signed(data, nrData), timestamp);
		break;
	case LOG_ATTR_ROTORPOS_ENCODER:
		rotorPosEncoder(decode_signed(data, nrData), timestamp);
		break;
	case LOG_ATTR_ROTORPOS_SENSORLESS:
		rotorPosSensorless(decode_signed(data, nrData), timestamp);
		break;
	case LOG_ATTR_ROTORPOS_CONTROLLER_OUT:
		rotorPosControllerOutput(decode_signed(data, nrData), timestamp);
		break;

	default:
		// do nothing
		break;
	}

#endif /* LOGGER_RX */
}
void HANDLE_OPERATOR_DATA(uint32_t timestamp, uint8_t attr, uint8_t data[], uint8_t nrData) {
#ifdef OPERATOR_RX

	switch (attr) {
	// events
	case OPR_ATTR_ENABLE_SERIAL_OPERATING:
		enableSerialOperationgMode();
		break;
	case OPR_ATTR_ENABLELOGGING:
		enableLogging();
		break;
	case OPR_ATTR_ENABLE_DRIVER:
		enableDriver();
		break;
	case OPR_ATTR_DISABLE_DRIVER:
		disableDriver();
		break;
	case OPR_ATTR_SELECT_POS_TORQUE:
		selectPositiveTorque();
		break;
	case OPR_ATTR_SELECT_NEG_TORQUE:
		selectNegativeTorque();
		break;
	case OPR_ATTR_SET_ROTADE_CLOCKWISE:
		rotadeClockwise();
		break;
	case OPR_ATTR_SET_ROTADE_COUNTERCLOCKWISE:
		rotadeCounterclockwise();
		break;
	case OPR_ATTR_GET_OBSERVING_INFOS:
		getObservingInfos();
		break;
	case OPR_ATTR_GET_LOGGING_CONFIG:
		getLoggingConfig();
		break;

		// string -> no attributes

		// unsigned
	case OPR_ATTR_SET_POS_TORQUE_LEVEL:
		setPositiveTorqueLevel((uint8_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_SET_NEG_TORQUE_LEVEL:
		setNegativeTorqueLevel((uint8_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_SET_MAX_PHASE_CURRENT:
		setMaxPhaseCurrent((uint8_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_TIMING:
		setTiming((uint8_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_SET_ROTORPOS_CONT_P_PARAM:
		setRotorPosController_pParam((uint32_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_SET_ROTORPOS_CONT_I_PARAM:
		setRotorPosController_iParam((uint32_t) decode_unsigned(data, nrData));
		break;
	case OPR_ATTR_SET_LOGGING_CONFIG:
		setLoggingConfig(decode_unsigned(data, nrData));
		break;

		// signed -> no attributes

	default:
		// do nothing
		break;
	}

#endif /* OPERATOR_RX */

}
void HANDLE_OBSERVER_DATA(uint32_t timestamp, uint8_t attr, uint8_t data[], uint8_t nrData) {
#ifdef OBSERVER_RX

	switch (attr) {
	// events
	case OBS_ATTR_SERIAL_OPERATING_MODE_IS_ENABLED:
		serialOperatingModeIsEnabled(timestamp);
		break;
	case OBS_ATTR_SERIAL_OPERATING_MODE_IS_DISABLED:
		serialOperatingModeIsDisabled(timestamp);
		break;
	case OBS_ATTR_DRIVER_IS_DISABLED:
		driverIsDisabled(timestamp);
		break;
	case OBS_ATTR_DRIVER_IS_ENABLED:
		driverIsEnabled(timestamp);
		break;
	case OBS_ATTR_POS_TORQUE_IS_SELECTED:
		positiveTorqueIsSelected(timestamp);
		break;
	case OBS_ATTR_NEG_TORQUE_IS_SELECTED:
		negativeTorqueIsSelected(timestamp);
		break;
	case OBS_ATTR_ROT_CLOCKWISE_IS_SELECTED:
		rotadeClockwiseIsSelected(timestamp);
		break;
	case OBS_ATTR_ROT_COUNTERCLOCKWISE_IS_SELECTED:
		rotadeCounterclockwiseIsSelected(timestamp);
		break;
	case OBS_ATTR_DRIVER_RESETED:
		driverReseted(timestamp);
		break;
	case OBS_ATTR_BUFFER_OVERFLOW:
		bufferOverflow(timestamp);
		break;

		// string -> no attributes

		// unsigned
	case OBS_ATTR_ENCODER_CALIBRATION:
		encoderCalibrationValue(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_ENTRY_STATE:
		entryState(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_POSITIVE_TORQUE_LEVEL:
		positiveTorqueLevel(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_NEGATIVE_TORQUE_LEVEL:
		negativeTorqueLevel(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_MAX_PHASE_CURRENT:
		maxAbsPhaseCurrent(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_TIMING:
		timing(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_ROTORPOS_CONT_P_PARAM:
		rotorpositionControllerPParam(decode_unsigned(data, nrData), timestamp);
		break;
	case OBS_ATTR_ROTORPOS_CONT_I_PARAM:
		rotorpositionControllerIParam(decode_unsigned(data, nrData), timestamp);
		break;

		// signed -> no attributes

	default:
		// do nothing
		break;
	}

#endif /* OBSERVER_RX */
}

// ____TX____
#ifdef LOGGER_TX
void startLoggingPackage(uint32_t timestamp) {
	START_LOGGER_PACKAGE(timestamp);
}

// - events
int8_t add_loggingIsEnabled() {
	return addEvent(LOG_ATTR_LOGGING_ENABLED);
}
int8_t add_CompA_IR() {
	return addEvent(LOG_ATTR_COMP_A_IRQ);
}
int8_t add_CompB_IR() {
	return addEvent(LOG_ATTR_COMP_B_IRQ);
}
int8_t add_CompC_IR() {
	return addEvent(LOG_ATTR_COMP_C_IRQ);
}

// - numbers
int8_t add_CurrentA(int32_t current) {
	return addSigned(LOG_ATTR_CURRENT_A, current);
}
int8_t add_CurrentB(int32_t current) {
	return addSigned(LOG_ATTR_CURRENT_B, current);
}
int8_t add_CurrentRangeA(uint32_t range) {
	return addUnsigned(LOG_ATTR_CURRENT_A_RANGE, range);
}
int8_t add_CurrentRangeB(uint32_t range) {
	return addUnsigned(LOG_ATTR_CURRENT_B_RANGE, range);
}
int8_t add_AbsCurrentSetPoint(uint32_t setpoint) {
	return addUnsigned(LOG_ATTR_ABS_PHASECURRENT_SETPOINT, setpoint);
}
int8_t add_DutyCycle(uint32_t dutyCycle) {
	return addUnsigned(LOG_ATTR_DUTYCYCLE, dutyCycle);
}
int8_t add_CurrentControllerOutput(int32_t controllerOut) {
	return addSigned(LOG_ATTR_CURRENT_CONTROLER_OUT, controllerOut);
}

int8_t add_AbsRotorPosEncoder(uint32_t pos) {
	return addUnsigned(LOG_ATTR_ROTORPOS_ENCODER_ABS, pos);
}
int8_t add_RotorPosEncoder(int32_t pos) {
	return addSigned(LOG_ATTR_ROTORPOS_ENCODER, pos);
}
int8_t add_RotorPosSensorless(int32_t pos) {
	return addSigned(LOG_ATTR_ROTORPOS_SENSORLESS, pos);
}
int8_t add_RotorPosControllerOutput(int32_t controllerOut) {
	return addSigned(LOG_ATTR_ROTORPOS_CONTROLLER_OUT, controllerOut);
}

int8_t add_Time60Deg(uint32_t t60deg) {
	return addUnsigned(LOG_ATTR_TIME_60DEG, t60deg);
}
int8_t add_CycleTime(uint32_t cycletime) {
	return addUnsigned(LOG_ATTR_CYCLE_TIME, cycletime);
}
int8_t add_loggingConfiguration(uint32_t config) {
	return addUnsigned(LOG_ATTR_LOGGING_CONFIGURATION, config);
}

// - messages
int8_t add_DebugMsg(uint8_t msg[]) {
	return addMsg(LOG_ATTR_MSG_DEBUG, msg);
}
int8_t add_InfoMsg(uint8_t msg[]) {
	return addMsg(LOG_ATTR_MSG_INFO, msg);
}
int8_t add_ErrorMsg(uint8_t msg[]) {
	return addMsg(LOG_ATTR_MSG_ERROR, msg);
}
#endif /* LOGGER_TX */

#ifdef OPERATOR_TX
void startOperatorPackage() {
	START_OPERATOR_PACKAGE(0);
}
int8_t add_enableSerialOperatingMode() {
	return addEvent(OPR_ATTR_ENABLE_SERIAL_OPERATING);
}
int8_t add_enableLogging() {
	return addEvent(OPR_ATTR_ENABLELOGGING);
}
int8_t add_EnableDriver() {
	return addEvent(OPR_ATTR_ENABLE_DRIVER);
}
int8_t add_DisableDriver() {
	return addEvent(OPR_ATTR_DISABLE_DRIVER);
}
int8_t add_SelectPositiveTorque() {
	return addEvent(OPR_ATTR_SELECT_POS_TORQUE);
}
int8_t add_SelectNegativeTorque() {
	return addEvent(OPR_ATTR_SELECT_NEG_TORQUE);
}
int8_t add_rotadeClockwise() {
	return addEvent(OPR_ATTR_SET_ROTADE_CLOCKWISE);
}
int8_t add_rotadeCounterclockwise() {
	return addEvent(OPR_ATTR_SET_ROTADE_COUNTERCLOCKWISE);
}
int8_t add_getObservingInfos() {
	return addEvent(OPR_ATTR_GET_OBSERVING_INFOS);
}
int8_t add_getLoggingConfig() {
	return addEvent(OPR_ATTR_GET_LOGGING_CONFIG);
}

int8_t add_SetPositiveTorqueLevel(uint8_t level) {
	return addUnsigned(OPR_ATTR_SET_POS_TORQUE_LEVEL, level);
}
int8_t add_SetNegativeTorqueLevel(uint8_t level) {
	return addUnsigned(OPR_ATTR_SET_NEG_TORQUE_LEVEL, level);
}
int8_t add_SetMaxPhaseCurrent(uint8_t current) {
	return addUnsigned(OPR_ATTR_SET_MAX_PHASE_CURRENT, current);
}

int8_t add_SetTiming(uint8_t timing) {
	return addUnsigned(OPR_ATTR_TIMING, timing);
}
int8_t add_SetRotorPosController_pParam(uint32_t pParam) {
	return addUnsigned(OPR_ATTR_SET_ROTORPOS_CONT_P_PARAM, pParam);
}
int8_t add_SetRotorPosController_iParam(uint32_t iParam) {
	return addUnsigned(OPR_ATTR_SET_ROTORPOS_CONT_I_PARAM, iParam);
}
int8_t add_setLoggingConfig(uint32_t config) {
	return addUnsigned(OPR_ATTR_SET_LOGGING_CONFIG, config);
}
#endif /* OPERATOR_TX */

#ifdef OBSERVER_TX
void startObservingPackage(uint32_t timestamp) {
	START_OBSERVER_PACKAGE(timestamp);
}

// events
int8_t add_serialOperatingModeIsEnabled() {
	return addEvent(OBS_ATTR_SERIAL_OPERATING_MODE_IS_ENABLED);
}
int8_t add_serialOperatingModeIsDisabled() {
	return addEvent(OBS_ATTR_SERIAL_OPERATING_MODE_IS_DISABLED);
}
int8_t add_driverIsEnabled() {
	return addEvent(OBS_ATTR_DRIVER_IS_ENABLED);
}
int8_t add_driverIsDisabled() {
	return addEvent(OBS_ATTR_DRIVER_IS_DISABLED);
}
int8_t add_positiveTorqueIsSelected() {
	return addEvent(OBS_ATTR_POS_TORQUE_IS_SELECTED);
}
int8_t add_negativeTorqueIsSelected() {
	return addEvent(OBS_ATTR_NEG_TORQUE_IS_SELECTED);
}
int8_t add_rotadeClockwiseIsSelected() {
	return addEvent(OBS_ATTR_ROT_CLOCKWISE_IS_SELECTED);
}
int8_t add_rotadeCounterclockwiseIsSelected() {
	return addEvent(OBS_ATTR_ROT_COUNTERCLOCKWISE_IS_SELECTED);
}
int8_t add_driverReseted() {
	return addEvent(OBS_ATTR_DRIVER_RESETED);
}
int8_t add_bufferOverflow() {
	return addEvent(OBS_ATTR_BUFFER_OVERFLOW);
}

// numbers
int8_t add_encoderCalibrationValue(uint32_t calibrationValue) {
	return addUnsigned(OBS_ATTR_ENCODER_CALIBRATION, calibrationValue);
}
int8_t add_entryState(uint8_t state) {
	return addUnsigned(OBS_ATTR_ENTRY_STATE, state);
}
int8_t add_positiveTorqueLevel(uint8_t level) {
	return addUnsigned(OBS_ATTR_POSITIVE_TORQUE_LEVEL, level);
}
int8_t add_negativeTorqueLevel(uint8_t level) {
	return addUnsigned(OBS_ATTR_NEGATIVE_TORQUE_LEVEL, level);
}
int8_t add_maxAbsPhaseCurrent(uint8_t current) {
	return addUnsigned(OBS_ATTR_MAX_PHASE_CURRENT, current);
}
int8_t add_timing(uint8_t timing) {
	return addUnsigned(OBS_ATTR_TIMING, timing);
}
int8_t add_rotorpositionControllerPParam(uint32_t pParam) {
	return addUnsigned(OBS_ATTR_ROTORPOS_CONT_P_PARAM, pParam);
}
int8_t add_rotorpositionControllerIParam(uint32_t iParam) {
	return addUnsigned(OBS_ATTR_ROTORPOS_CONT_I_PARAM, iParam);
}
#endif /* OPERATOR_TX */

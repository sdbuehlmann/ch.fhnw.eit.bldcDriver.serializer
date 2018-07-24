/*
 * bldcDriverCom.c
 *
 *  Created on: Jul 19, 2018
 *      Author: simon
 */
// =============== Includes ==============================================
#include "serializer.h"
#include "bldcDriverSerializer_logger.h"
#include "bldcDriverSerializer_operator.h"
#include "bldcDriverSerializer_observer.h"

// =============== Defines ===============================================
// __start flags__
#define HANDLE_LOGGER_DATA						handleDataFromXPackage
#define START_LOGGER_PACKAGE					send_startFlagX

#define HANDLE_OPERATOR_DATA					handleDataFromYPackage
#define START_OPERATOR_PACKAGE					send_startFlagY

#define HANDLE_OBSERVER_DATA					handleDataFromZPackage
#define START_OBSERVER_PACKAGE					send_startFlagZ

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

// =============== Function declarations =================================

// ____RX____
void HANDLE_LOGGER_DATA(uint8_t attr, uint32_t timestamp, uint8_t data[],
		uint8_t nrData) {
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
void HANDLE_OPERATOR_DATA(uint8_t attr, uint32_t timestamp, uint8_t data[],
		uint8_t nrData) {
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
void HANDLE_OBSERVER_DATA(uint8_t attr, uint32_t timestamp, uint8_t data[],
		uint8_t nrData) {
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
void addToStream(uint8_t data) {
	handleOutgoing(data);
}
void handleIncomming(uint8_t inData) {
	deserialize(inData);
}

void closePackage() {
	send_endFlag();
}

#ifdef LOGGER_TX
void startLoggingPackage(uint32_t timestamp) {
	START_LOGGER_PACKAGE();
	send_unsigned(timestamp, 4);
}

// - events
void add_loggingIsEnabled() {
	send_attribute(LOG_ATTR_LOGGING_ENABLED);
}
void add_CompA_IR() {
	send_attribute(LOG_ATTR_COMP_A_IRQ);
}
void add_CompB_IR() {
	send_attribute(LOG_ATTR_COMP_B_IRQ);
}
void add_CompC_IR() {
	send_attribute(LOG_ATTR_COMP_C_IRQ);
}

// - numbers
void add_CurrentA(int32_t current) {
	send_attribute(LOG_ATTR_CURRENT_A);
	send_signed(current, 4);
}
void add_CurrentB(int32_t current) {
	send_attribute(LOG_ATTR_CURRENT_B);
	send_signed(current, 4);
}
void add_CurrentRangeA(uint32_t range) {
	send_attribute(LOG_ATTR_CURRENT_A_RANGE);
	send_unsigned(range, 4);
}
void add_CurrentRangeB(uint32_t range) {
	send_attribute(LOG_ATTR_CURRENT_B_RANGE);
	send_unsigned(range, 4);
}
void add_AbsCurrentSetPoint(uint32_t setpoint) {
	send_attribute(LOG_ATTR_ABS_PHASECURRENT_SETPOINT);
	send_unsigned(setpoint, 4);
}
void add_DutyCycle(uint32_t dutyCycle) {
	send_attribute(LOG_ATTR_DUTYCYCLE);
	send_unsigned(dutyCycle, 4);
}
void add_CurrentControllerOutput(int32_t controllerOut) {
	send_attribute(LOG_ATTR_CURRENT_CONTROLER_OUT);
	send_signed(controllerOut, 4);
}

void add_AbsRotorPosEncoder(uint32_t pos) {
	send_attribute(LOG_ATTR_ROTORPOS_ENCODER_ABS);
	send_unsigned(pos, 4);
}
void add_RotorPosEncoder(int32_t pos) {
	send_attribute(LOG_ATTR_ROTORPOS_ENCODER);
	send_signed(pos, 4);
}
void add_RotorPosSensorless(int32_t pos) {
	send_attribute(LOG_ATTR_ROTORPOS_SENSORLESS);
	send_signed(pos, 4);
}
void add_RotorPosControllerOutput(int32_t controllerOut) {
	send_attribute(LOG_ATTR_ROTORPOS_CONTROLLER_OUT);
	send_signed(controllerOut, 4);
}

void add_Time60Deg(int32_t t60deg) {
	send_attribute(LOG_ATTR_TIME_60DEG);
	send_signed(t60deg, 4);
}
void add_CycleTime(int32_t cycletime) {
	send_attribute(LOG_ATTR_CYCLE_TIME);
	send_signed(cycletime, 4);
}
void add_loggingConfiguration(uint32_t config) {
	send_attribute(LOG_ATTR_LOGGING_CONFIGURATION);
	send_signed(config, 4);
}

// - messages
void add_DebugMsg(uint8_t msg[]) {
	send_attribute(LOG_ATTR_MSG_DEBUG);
	send_string(msg);
}
void add_InfoMsg(uint8_t msg[]) {
	send_attribute(LOG_ATTR_MSG_INFO);
	send_string(msg);
}
void add_ErrorMsg(uint8_t msg[]) {
	send_attribute(LOG_ATTR_MSG_ERROR);
	send_string(msg);
}
#endif /* LOGGER_TX */

#ifdef OPERATOR_TX
void startOperatorPackage() {
	START_OPERATOR_PACKAGE();
}
/* ToDo: https://git-scm.com/book/de/v1/Git-Tools-Submodule */
void add_enableSerialOperatingMode() {
	send_attribute(OPR_ATTR_ENABLE_SERIAL_OPERATING);
}
void add_enableLogging(){
	send_attribute(OPR_ATTR_ENABLELOGGING);
}
void add_EnableDriver() {
	send_attribute(OPR_ATTR_ENABLE_DRIVER);
}
void add_DisableDriver() {
	send_attribute(OPR_ATTR_DISABLE_DRIVER);
}
void add_SelectPositiveTorque() {
	send_attribute(OPR_ATTR_SELECT_POS_TORQUE);
}
void add_SelectNegativeTorque() {
	send_attribute(OPR_ATTR_SELECT_NEG_TORQUE);
}
void add_rotadeClockwise(){
	send_attribute(OPR_ATTR_SET_ROTADE_CLOCKWISE);
}
void add_rotadeCounterclockwise(){
	send_attribute(OPR_ATTR_SET_ROTADE_COUNTERCLOCKWISE);
}
void add_getObservingInfos(){
	send_attribute(OPR_ATTR_GET_OBSERVING_INFOS);
}
void add_getLoggingConfig(){
	send_attribute(OPR_ATTR_GET_LOGGING_CONFIG);
}

void add_SetPositiveTorqueLevel(uint8_t level) {
	send_attribute(OPR_ATTR_SET_POS_TORQUE_LEVEL);
	send_unsigned(level, 1);
}
void add_SetNegativeTorqueLevel(uint8_t level) {
	send_attribute(OPR_ATTR_SET_NEG_TORQUE_LEVEL);
	send_unsigned(level, 1);
}
void add_SetMaxPhaseCurrent(uint8_t level) {
	send_attribute(OPR_ATTR_SET_MAX_PHASE_CURRENT);
	send_unsigned(level, 1);
}

void add_SetTiming(uint8_t timing) {
	send_attribute(OPR_ATTR_TIMING);
	send_unsigned(timing, 1);
}
void add_SetRotorPosController_pParam(uint32_t pParam) {
	send_attribute(OPR_ATTR_SET_ROTORPOS_CONT_P_PARAM);
	send_unsigned(pParam, 4);
}
void add_SetRotorPosController_iParam(uint32_t iParam) {
	send_attribute(OPR_ATTR_SET_ROTORPOS_CONT_I_PARAM);
	send_unsigned(iParam, 4);
}
void add_setLoggingConfig(uint32_t config){
	send_attribute(OPR_ATTR_SET_LOGGING_CONFIG);
	send_unsigned(config, 4);
}
#endif /* OPERATOR_TX */

#ifdef OBSERVER_TX
void startObservingPackage(uint32_t timestamp) {
	START_OBSERVER_PACKAGE();
	send_unsigned(timestamp, 4);
}

// events
void add_serialOperatingModeIsEnabled() {
	send_attribute(OBS_ATTR_SERIAL_OPERATING_MODE_IS_ENABLED);
}
void add_serialOperatingModeIsDisabled() {
	send_attribute(OBS_ATTR_SERIAL_OPERATING_MODE_IS_DISABLED);
}
void add_driverIsEnabled() {
	send_attribute(OBS_ATTR_DRIVER_IS_ENABLED);
}
void add_driverIsDisabled() {
	send_attribute(OBS_ATTR_DRIVER_IS_DISABLED);
}
void add_positiveTorqueIsSelected() {
	send_attribute(OBS_ATTR_POS_TORQUE_IS_SELECTED);
}
void add_negativeTorqueIsSelected() {
	send_attribute(OBS_ATTR_NEG_TORQUE_IS_SELECTED);
}
void add_rotadeClockwiseIsSelected() {
	send_attribute(OBS_ATTR_ROT_CLOCKWISE_IS_SELECTED);
}
void add_rotadeCounterclockwiseIsSelected() {
	send_attribute(OBS_ATTR_ROT_COUNTERCLOCKWISE_IS_SELECTED);
}
void add_driverReseted() {
	send_attribute(OBS_ATTR_DRIVER_RESETED);
}
void add_bufferOverflow() {
	send_attribute(OBS_ATTR_BUFFER_OVERFLOW);
}

// numbers
void add_encoderCalibrationValue(uint32_t calibrationValue) {
	send_attribute(OBS_ATTR_ENCODER_CALIBRATION);
	send_unsigned(calibrationValue, 4);
}
void add_entryState(uint8_t state) {
	send_attribute(OBS_ATTR_ENTRY_STATE);
	send_unsigned(state, 1);
}
void add_positiveTorqueLevel(uint8_t level) {
	send_attribute(OBS_ATTR_POSITIVE_TORQUE_LEVEL);
	send_unsigned(level, 1);
}
void add_negativeTorqueLevel(uint8_t level) {
	send_attribute(OBS_ATTR_NEGATIVE_TORQUE_LEVEL);
	send_unsigned(level, 1);
}
void add_maxAbsPhaseCurrent(uint8_t current) {
	send_attribute(OBS_ATTR_MAX_PHASE_CURRENT);
	send_unsigned(current, 1);
}
void add_timing(uint8_t timing) {
	send_attribute(OBS_ATTR_TIMING);
	send_unsigned(timing, 1);
}
void add_rotorpositionControllerPParam(uint32_t pParam) {
	send_attribute(OBS_ATTR_ROTORPOS_CONT_P_PARAM);
	send_unsigned(pParam, 4);
}
void add_rotorpositionControllerIParam(uint32_t iParam) {
	send_attribute(OBS_ATTR_ROTORPOS_CONT_I_PARAM);
	send_unsigned(iParam, 4);
}
#endif /* OPERATOR_TX */

/*
 * bldcDriverCom.c
 *
 *  Created on: Jul 19, 2018
 *      Author: simon
 */
// =============== Includes ==============================================
#include <serializer.h>
#include <bldcDriverSerializer.h>

// =============== Defines ===============================================
// __start flags__
#define LOGGER_START_FLAG						START_CONTROL_FLAG_X
#define SET_LOGGER_FLAG							send_startFlagX()

#define OPERATOR_START_FLAG						START_CONTROL_FLAG_Y
#define SET_OPERATOR_FLAG						send_startFlagY()

#define OBSERVER_START_FLAG						START_CONTROL_FLAG_Z
#define SET_OBSERVER_FLAG						send_startFlagZ()

// __logger attributes__
// events
#define ATTR_MAIN_RESET							FIRST_ATTRIBUTE_CHAR
#define ATTR_COMP_A_IRQ 						ATTR_MAIN_RESET + 1
#define ATTR_COMP_B_IRQ							ATTR_COMP_A_IRQ + 1
#define ATTR_COMP_C_IRQ 						ATTR_COMP_B_IRQ + 1
#define ATTR_LOG_BUFFER_OVERFLOW 				ATTR_COMP_C_IRQ + 1

// strings
#define ATTR_MSG_DEBUG 							ATTR_LOG_BUFFER_OVERFLOW + 1
#define ATTR_MSG_INFO 							ATTR_MSG_DEBUG + 1
#define ATTR_MSG_ERROR 							ATTR_MSG_INFO + 1

// data
#define ATTR_CURRENT_A 							ATTR_MSG_ERROR + 1
#define ATTR_CURRENT_B							ATTR_CURRENT_A + 1
#define ATTR_CURRENT_A_RANGE 					ATTR_CURRENT_B + 1
#define ATTR_CURRENT_B_RANGE 					ATTR_CURRENT_A_RANGE + 1
#define ATTR_ABS_PHASECURRENT_SETPOINT			ATTR_CURRENT_B_RANGE + 1
#define ATTR_DUTYCYCLE							ATTR_ABS_PHASECURRENT_SETPOINT + 1
#define ATTR_CURRENT_CONTROLER_OUT				ATTR_DUTYCYCLE + 1

#define ATTR_ROTORPOS_ENCODER_ABS				ATTR_CURRENT_CONTROLER_OUT + 1
#define ATTR_ROTORPOS_ENCODER					ATTR_ROTORPOS_ENCODER_ABS + 1
#define ATTR_ROTORPOS_SENSORLESS				ATTR_ROTORPOS_ENCODER + 1
#define ATTR_TIME_60DEG							ATTR_ROTORPOS_SENSORLESS + 1
#define ATTR_ROTORPOS_CONTROLLER_OUT			ATTR_TIME_60DEG + 1

#define ATTR_CYCLE_TIME							ATTR_ROTORPOS_CONTROLLER_OUT + 1
#define ATTR_ENTRY_STATE						ATTR_CYCLE_TIME + 1

// __operator attributes__
// events
#define ATTR_ENABLE_SERIAL_OPERATING			FIRST_ATTRIBUTE_CHAR
#define ATTR_ENABLE_DRIVER						ATTR_ENABLE_SERIAL_OPERATING + 1
#define ATTR_DISABLE_DRIVER						ATTR_ENABLE_DRIVER + 1
#define ATTR_SELECT_POS_TORQUE		 			ATTR_DISABLE_DRIVER + 1
#define ATTR_SELECT_NEG_TORQUE		 			ATTR_SELECT_POS_TORQUE + 1

// unsigned
#define ATTR_SET_POS_TORQUE_LEVEL 				ATTR_SELECT_NEG_TORQUE + 1
#define ATTR_SET_NEG_TORQUE_LEVEL				ATTR_SET_POS_TORQUE_LEVEL + 1
#define ATTR_SET_MAX_PHASE_CURRENT				ATTR_SET_NEG_TORQUE_LEVEL + 1

#define ATTR_TIMING 							ATTR_SET_MAX_PHASE_CURRENT + 1
#define ATTR_ROTORPOS_CONT_P_PARAM				ATTR_TIMING + 1
#define ATTR_ROTORPOS_CONT_I_PARAM				ATTR_ROTORPOS_CONT_P_PARAM + 1

// =============== Variables =============================================

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== TX ====================================================

void startObservingPackage() {
	SET_OBSERVER_FLAG;
}

void closePackage() {
	send_endFlag();
	/* ToDo EndFlag entfernen, bringt nichts und kostet ein übetragenes Byte */
}

// logger
#ifdef LOGGER_TX
void startLoggingPackage(uint32_t timestamp) {
	SET_LOGGER_FLAG;
	send_unsigned(timestamp);
}

// - events
void addToPackage_MainReset() {
	send_attribute(ATTR_MAIN_RESET);
}
void addToPackage_CompA_IR() {
	send_attribute(ATTR_COMP_A_IRQ);
}
void addToPackage_CompB_IR() {
	send_attribute(ATTR_COMP_B_IRQ);
}
void addToPackage_CompC_IR() {
	send_attribute(ATTR_COMP_C_IRQ);
}
void addToPackage_LoggerBufferOverflow() {
	send_attribute(ATTR_LOG_BUFFER_OVERFLOW);
}

// - numbers
void addToPackage_CurrentA(int32_t current) {
	send_attribute(ATTR_CURRENT_A);
	send_signed(current);
}
void addToPackage_CurrentB(int32_t current) {
	send_attribute(ATTR_CURRENT_B);
	send_signed(current);
}
void addToPackage_CurrentRangeA(uint32_t range) {
	send_attribute(ATTR_CURRENT_A_RANGE);
	send_unsigned(range);
}
void addToPackage_CurrentRangeB(uint32_t range) {
	send_attribute(ATTR_CURRENT_B_RANGE);
	send_unsigned(range);
}
void addToPackage_AbsCurrentSetPoint(uint32_t setpoint) {
	send_attribute(ATTR_ABS_PHASECURRENT_SETPOINT);
	send_unsigned(setpoint);
}
void addToPackage_DutyCycle(uint32_t dutyCycle) {
	send_attribute(ATTR_DUTYCYCLE);
	send_unsigned(dutyCycle);
}
void addToPackage_CurrentControllerOutput(int32_t controllerOut) {
	send_attribute(ATTR_CURRENT_CONTROLER_OUT);
	send_signed(controllerOut);
}

void addToPackage_AbsRotorPosEncoder(uint32_t pos) {
	send_attribute(ATTR_ROTORPOS_ENCODER_ABS);
	send_unsigned(pos);
}
void addToPackage_RotorPosEncoder(int32_t pos) {
	send_attribute(ATTR_ROTORPOS_ENCODER);
	send_signed(pos);
}
void addToPackage_RotorPosSensorless(int32_t pos) {
	send_attribute(ATTR_ROTORPOS_SENSORLESS);
	send_signed(pos);
}
void addToPackage_RotorPosControllerOutput(int32_t controllerOut) {
	send_attribute(ATTR_ROTORPOS_CONTROLLER_OUT);
	send_signed(controllerOut);
}

void addToPackage_EntryState(uint32_t state) {
	send_attribute(ATTR_ENTRY_STATE);
	send_signed(state);
}
void addToPackage_Time60Deg(int32_t t60deg) {
	send_attribute(ATTR_TIME_60DEG);
	send_signed(t60deg);
}
void addToPackage_CycleTime(int32_t cycletime) {
	send_attribute(ATTR_CYCLE_TIME);
	send_signed(cycletime);
}

// - messages
void addToPackage_DebugMsg(uint8_t msg[]) {
	send_attribute(ATTR_MSG_DEBUG);
	send_string(msg);
}
void addToPackage_InfoMsg(uint8_t msg[]) {
	send_attribute(ATTR_MSG_INFO);
	send_string(msg);
}
void addToPackage_ErrorMsg(uint8_t msg[]) {
	send_attribute(ATTR_MSG_ERROR);
	send_string(msg);
}
#endif /* LOGGER_TX */

#ifdef OPERATOR_TX
void operator_startPackage(){
	SET_OPERATOR_FLAG;
}

void operator_EnableSerialOperatingMode(){
	send_attribute(ATTR_ENABLE_SERIAL_OPERATING);
}
void operator_EnableDriver(){
	send_attribute(ATTR_ENABLE_DRIVER);
}
void operator_DisableDriver(){
	send_attribute(ATTR_DISABLE_DRIVER);
}
void operator_SelectPositiveTorque(){
	send_attribute(ATTR_SELECT_POS_TORQUE);
}
void operator_SelectNegativeTorque(){
	send_attribute(ATTR_SELECT_NEG_TORQUE);
}

void operator_SetPositiveTorqueLevel(uint8_t level){
	send_attribute(ATTR_SET_POS_TORQUE_LEVEL);
	send_unsigned(level, 1);
	/* ToDo unterscheidung von 8bit & 32bit --> sonst Fehler beim Maskieren (Es werden benachbarte Speicherplätze mitgesendet) */
}
void operator_SetNegativeTorqueLevel(uint8_t level){
	send_attribute(ATTR_SET_NEG_TORQUE_LEVEL);
	send_unsigned(level, 1);
}
void operator_SetMaxPhaseCurrent(uint8_t level){
	send_attribute(ATTR_SET_MAX_PHASE_CURRENT);
	send_unsigned(level, 1);
}

void operator_SetTiming(uint8_t timing){
	send_attribute(ATTR_TIMING);
	send_unsigned(timing, 1);
}
void operator_SetRotorPosController_pParam(uint32_t pParam){
	send_attribute(ATTR_ROTORPOS_CONT_P_PARAM);
	send_unsigned(pParam, 4);
}
void operator_SetRotorPosController_iParam(uint32_t iParam){
	send_attribute(ATTR_ROTORPOS_CONT_I_PARAM);
	send_unsigned(iParam, 4);
}
#endif /* OPERATOR_TX */

// RX
void eventReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol) {

	switch (startFlag) {

#ifdef LOGGER_RX
	case LOGGER_START_FLAG: {

		switch (symbol) {
		case ATTR_MAIN_RESET:
			mainReset(timestamp);
			break;
		case ATTR_COMP_A_IRQ:
			compA_IR(timestamp);
			break;
		case ATTR_COMP_B_IRQ:
			compB_IR(timestamp);
			break;
		case ATTR_COMP_C_IRQ:
			compC_IR(timestamp);
			break;
		case ATTR_LOG_BUFFER_OVERFLOW:
			loggerBufferOverflow(timestamp);
			break;
		default:
			// do nothing
			break;
		}
	}
		break;
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG: {

		switch (symbol) {
		case ATTR_ENABLE_SERIAL_OPERATING:
			enableSerialOperationgMode();
			break;
		case ATTR_ENABLE_DRIVER:
			enableDriver();
			break;
		case ATTR_DISABLE_DRIVER:
			disableDriver();
			break;
		case ATTR_SELECT_POS_TORQUE:
			selectPositiveTorque();
			break;
		case ATTR_SELECT_NEG_TORQUE:
			selectNegativeTorque();
			break;
		default:
			// do nothing
			break;
		}
	}
		break;
#endif
#ifdef OBSERVER_RX
		case OBSERVER_START_FLAG: {

		}
		break;
#endif
	default:
		// do nothing
		break;
	}
}
void msgReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol,
		uint8_t msg[], uint8_t lenght) {

	switch (startFlag) {

#ifdef LOGGER_RX
	case LOGGER_START_FLAG: {

		switch (symbol) {
		case ATTR_MSG_DEBUG:
			debugMsg(msg, lenght, timestamp);
			break;
		case ATTR_MSG_INFO:
			infoMsg(msg, lenght, timestamp);
			break;
		case ATTR_MSG_ERROR:
			errorMsg(msg, lenght, timestamp);
			break;
		default:
			break;
		}
	}
		break;
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG: {
		// no messages attributes
	}
		break;
#endif
#ifdef OBSERVER_RX
		case OPERATOR_START_FLAG: {

		}break;
#endif

	}
}
void unsignedReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol,
		uint32_t data) {

	switch (startFlag) {

#ifdef LOGGER_RX
	case LOGGER_START_FLAG: {

		switch (symbol) {
		case ATTR_CURRENT_A_RANGE:
			currentRangeA(data, timestamp);
			break;
		case ATTR_CURRENT_B_RANGE:
			currentRangeB(data, timestamp);
			break;
		case ATTR_ABS_PHASECURRENT_SETPOINT:
			absCurrentSetPoint(data, timestamp);
			break;
		case ATTR_DUTYCYCLE:
			dutyCycle(data, timestamp);
			break;
		case ATTR_ROTORPOS_ENCODER_ABS:
			absRotorPosEncoder(data, timestamp);
			break;
		case ATTR_TIME_60DEG:
			time60Deg(data, timestamp);
			break;
		case ATTR_CYCLE_TIME:
			cycleTime(data, timestamp);
			break;
		case ATTR_ENTRY_STATE:
			entryState(data, timestamp);
			break;
		default:
			// do nothing
			break;
		}
	}
		break;
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG: {

		switch (symbol) {
		case ATTR_SET_POS_TORQUE_LEVEL:
			setPositiveTorqueLevel((uint8_t) data);
			break;
		case ATTR_SET_NEG_TORQUE_LEVEL:
			setNegativeTorqueLevel((uint8_t) data);
			break;
		case ATTR_SET_MAX_PHASE_CURRENT:
			setMaxPhaseCurrent((uint8_t) data);
			break;
		case ATTR_TIMING:
			setTiming((uint8_t) data);
			break;
		case ATTR_ROTORPOS_CONT_P_PARAM:
			setRotorPosController_pParam((uint8_t) data);
			break;
		case ATTR_ROTORPOS_CONT_I_PARAM:
			setRotorPosController_iParam((uint8_t) data);
			break;
		default:
			// do nothing
			break;
		}
	}
		break;
#endif
#ifdef OBSERVER_RX
		case OPERATOR_START_FLAG: {

		}break;
#endif

	}
}
void signedReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol,
		uint32_t data) {
	switch (startFlag) {

#ifdef LOGGER_RX
	case LOGGER_START_FLAG: {

		switch (symbol) {
		case ATTR_CURRENT_A:
			currentA(data, timestamp);
			break;
		case ATTR_CURRENT_B:
			currentB(data, timestamp);
			break;
		case ATTR_CURRENT_CONTROLER_OUT:
			currentControllerOutput(data, timestamp);
			break;
		case ATTR_ROTORPOS_ENCODER:
			rotorPosEncoder(data, timestamp);
			break;
		case ATTR_ROTORPOS_SENSORLESS:
			rotorPosSensorless(data, timestamp);
			break;
		case ATTR_ROTORPOS_CONTROLLER_OUT:
			rotorPosControllerOutput(data, timestamp);
			break;
		default:
			// do nothing
			break;
		}
	}
		break;
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG: {
		// no messages attributes
	}
		break;
#endif
#ifdef OBSERVER_RX
		case OPERATOR_START_FLAG: {

		}break;
#endif

	}
}

uint8_t is_a_event_attribute(uint8_t startFlag, uint8_t data) {
	switch (startFlag) {
#ifdef LOGGER_RX
	case LOGGER_START_FLAG:
		return (data == ATTR_MAIN_RESET
					|| data == ATTR_COMP_A_IRQ
					|| data == ATTR_COMP_B_IRQ
					|| data == ATTR_COMP_C_IRQ
					|| data == ATTR_LOG_BUFFER_OVERFLOW);
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG:
		return (data == ATTR_ENABLE_SERIAL_OPERATING
					|| data == ATTR_ENABLE_DRIVER
					|| data == ATTR_DISABLE_DRIVER
					|| data == ATTR_SELECT_POS_TORQUE
					|| data == ATTR_SELECT_NEG_TORQUE);
#endif
#ifdef OBSERVER_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif

		default:
			return 0;
	}
}
uint8_t is_a_msg_attribute(uint8_t startFlag, uint8_t data) {
	switch (startFlag) {
#ifdef LOGGER_RX
	case LOGGER_START_FLAG:
		return (data == ATTR_MSG_DEBUG
					|| data == ATTR_MSG_INFO
					|| data == ATTR_MSG_ERROR);
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif
#ifdef OBSERVER_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif

		default:
			return 0;
	}
}
uint8_t is_a_unsigned_attribute(uint8_t startFlag, uint8_t data) {
	switch (startFlag) {
#ifdef LOGGER_RX
	case LOGGER_START_FLAG:
		return (data == ATTR_CURRENT_A_RANGE
					|| data == ATTR_CURRENT_B_RANGE
					|| data == ATTR_ABS_PHASECURRENT_SETPOINT
					|| data == ATTR_DUTYCYCLE
					|| data == ATTR_ROTORPOS_ENCODER_ABS
					|| data == ATTR_TIME_60DEG
					|| data == ATTR_CYCLE_TIME
					|| data == ATTR_ENTRY_STATE);
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG:
		return (data == ATTR_SET_POS_TORQUE_LEVEL
					|| data == ATTR_SET_NEG_TORQUE_LEVEL
					|| data == ATTR_SET_MAX_PHASE_CURRENT
					|| data == ATTR_TIMING
					|| data == ATTR_ROTORPOS_CONT_P_PARAM
					|| data == ATTR_ROTORPOS_CONT_I_PARAM);
#endif
#ifdef OBSERVER_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif

		default:
			return 0;
	}
}
uint8_t is_a_signed_attribute(uint8_t startFlag, uint8_t data) {
	switch (startFlag) {
#ifdef LOGGER_RX
	case LOGGER_START_FLAG:
		return (data == ATTR_CURRENT_A || data == ATTR_CURRENT_B
					|| data == ATTR_CURRENT_CONTROLER_OUT
					|| data == ATTR_ROTORPOS_ENCODER || data == ATTR_ROTORPOS_SENSORLESS
					|| data == ATTR_ROTORPOS_CONTROLLER_OUT);
#endif
#ifdef OPERATOR_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif
#ifdef OBSERVER_RX
	case OPERATOR_START_FLAG:
		return 0;
#endif

		default:
			return 0;
	}
}

void store(uint8_t data) {
	handleSerialized(data);
}

void deserialize(uint8_t data) {
	decode(data);
}

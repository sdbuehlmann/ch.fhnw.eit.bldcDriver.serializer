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
// __attribute chars__
#define FIRST_CONTROL_CHAR 3
#define LAST_CONTROL_CHAR 27

// events symbols
#define ATTR_MAIN_RESET							3
#define ATTR_COMP_A_IRQ 						4
#define ATTR_COMP_B_IRQ							5
#define ATTR_COMP_C_IRQ 						6
#define ATTR_LOG_BUFFER_OVERFLOW 				7

// strings symbols
#define ATTR_MSG_DEBUG 							8
#define ATTR_MSG_INFO 							9
#define ATTR_MSG_ERROR 							10

// data symbols
#define ATTR_CURRENT_A 							11
#define ATTR_CURRENT_B							12
#define ATTR_CURRENT_A_RANGE 					13
#define ATTR_CURRENT_B_RANGE 					14
#define ATTR_ABS_PHASECURRENT_SETPOINT			15
#define ATTR_DUTYCYCLE							17
#define ATTR_CURRENT_CONTROLER_OUT				18

#define ATTR_ROTORPOS_ENCODER_ABS				20
#define ATTR_ROTORPOS_ENCODER					21
#define ATTR_ROTORPOS_SENSORLESS				22
#define ATTR_TIME_60DEG							23
#define ATTR_ROTORPOS_CONTROLLER_OUT			24

#define ATTR_CYCLE_TIME							25
#define ATTR_ENTRY_STATE						27

// __normal ascii__
#define FIRST_ASCII_CHAR 32
#define LAST_ASCII_CHAR 127

// __numbers__
#define FIRST_NUMBER 0b10000000

// =============== Variables =============================================

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== TX ====================================================
void startLoggingPackage(uint32_t timestamp){
	send_startFlag();
	send_unsigned(timestamp);
}
void startObservingPackage(){
	send_startFlag();
}
void startControllingPackage(){
	send_startFlag();
}

void closePackage(){
	send_endFlag();
}

// logging
// - events
void addToPackage_MainReset(){
	send_attribute(ATTR_MAIN_RESET);
}
void addToPackage_CompA_IR(){
	send_attribute(ATTR_COMP_A_IRQ);
}
void addToPackage_CompB_IR(){
	send_attribute(ATTR_COMP_B_IRQ);
}
void addToPackage_CompC_IR(){
	send_attribute(ATTR_COMP_C_IRQ);
}
void addToPackage_LoggerBufferOverflow(){
	send_attribute(ATTR_LOG_BUFFER_OVERFLOW);
}

// - numbers
void addToPackage_CurrentA(int32_t current){
	send_attribute(ATTR_CURRENT_A);
	send_signed(current);
}
void addToPackage_CurrentB(int32_t current){
	send_attribute(ATTR_CURRENT_B);
	send_signed(current);
}
void addToPackage_CurrentRangeA(uint32_t range){
	send_attribute(ATTR_CURRENT_A_RANGE);
	send_unsigned(range);
}
void addToPackage_CurrentRangeB(uint32_t range){
	send_attribute(ATTR_CURRENT_B_RANGE);
	send_unsigned(range);
}
void addToPackage_AbsCurrentSetPoint(uint32_t setpoint){
	send_attribute(ATTR_ABS_PHASECURRENT_SETPOINT);
	send_unsigned(setpoint);
}
void addToPackage_DutyCycle(uint32_t dutyCycle){
	send_attribute(ATTR_DUTYCYCLE);
	send_unsigned(dutyCycle);
}
void addToPackage_CurrentControllerOutput(int32_t controllerOut){
	send_attribute(ATTR_CURRENT_CONTROLER_OUT);
	send_signed(controllerOut);
}

void addToPackage_AbsRotorPosEncoder(uint32_t pos){
	send_attribute(ATTR_ROTORPOS_ENCODER_ABS);
	send_unsigned(pos);
}
void addToPackage_RotorPosEncoder(int32_t pos){
	send_attribute(ATTR_ROTORPOS_ENCODER);
	send_signed(pos);
}
void addToPackage_RotorPosSensorless(int32_t pos){
	send_attribute(ATTR_ROTORPOS_SENSORLESS);
	send_signed(pos);
}
void addToPackage_RotorPosControllerOutput(int32_t controllerOut){
	send_attribute(ATTR_ROTORPOS_CONTROLLER_OUT);
	send_signed(controllerOut);
}

void addToPackage_Time60Deg(int32_t t60deg){
	send_attribute(ATTR_TIME_60DEG);
	send_signed(t60deg);
}
void addToPackage_CycleTime(int32_t cycletime){
	send_attribute(ATTR_CYCLE_TIME);
	send_signed(cycletime);
}

// - messages
void addToPackage_DebugMsg(uint8_t msg[]){
	send_attribute(ATTR_MSG_DEBUG);
	send_string(msg);
}
void addToPackage_InfoMsg(uint8_t msg[]){
	send_attribute(ATTR_MSG_INFO);
	send_string(msg);
}
void addToPackage_ErrorMsg(uint8_t msg[]){
	send_attribute(ATTR_MSG_ERROR);
	send_string(msg);
}

// RX
void eventReceived(uint32_t timestamp, uint8_t symbol){
	switch(symbol){
	case ATTR_MAIN_RESET:
		loggerBufferOverflow(timestamp);
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
void msgReceived(uint32_t timestamp, uint8_t symbol, uint8_t msg[], uint8_t lenght){
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
void unsignedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data){
	switch(symbol){
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
void signedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data){
	switch(symbol){
		case ATTR_CURRENT_A:
			currentA(data, timestamp);
			break;
		case ATTR_CURRENT_B:
			currentB(data, timestamp);
			break;
		case ATTR_CURRENT_CONTROLER_OUT:
			currentControllerOutput(data, timestamp);
			break;
		case ATTR_ROTORPOS_SENSORLESS:
			rotorPosEncoder(data, timestamp);
			break;
		case ATTR_ROTORPOS_CONTROLLER_OUT:
			rotorPosSensorless(data, timestamp);
			break;
		default:
			// do nothing
			break;
		}
}

uint8_t is_a_event_attribute(uint8_t data){
	return (data == ATTR_MAIN_RESET ||
			data == ATTR_COMP_A_IRQ ||
			data == ATTR_COMP_B_IRQ ||
			data == ATTR_COMP_C_IRQ ||
			data == ATTR_LOG_BUFFER_OVERFLOW);
}
uint8_t is_a_msg_attribute(uint8_t data){
	return (data == ATTR_MSG_DEBUG ||
				data == ATTR_MSG_INFO ||
				data == ATTR_MSG_ERROR);
}
uint8_t is_a_unsigned_attribute(uint8_t data){
	return (data == ATTR_CURRENT_A_RANGE ||
				data == ATTR_CURRENT_B_RANGE ||
				data == ATTR_ABS_PHASECURRENT_SETPOINT ||
				data == ATTR_DUTYCYCLE ||
				data == ATTR_ROTORPOS_ENCODER_ABS ||
				data == ATTR_TIME_60DEG ||
				data == ATTR_CYCLE_TIME ||
				data == ATTR_ENTRY_STATE);
}
uint8_t is_a_signed_attribute(uint8_t data){
	return (data == ATTR_CURRENT_A ||
				data == ATTR_CURRENT_B ||
				data == ATTR_CURRENT_CONTROLER_OUT ||
				data == ATTR_ROTORPOS_ENCODER ||
				data == ATTR_ROTORPOS_SENSORLESS ||
				data == ATTR_ROTORPOS_CONTROLLER_OUT);
}

void send(uint8_t data){
	transferByte(data);
}

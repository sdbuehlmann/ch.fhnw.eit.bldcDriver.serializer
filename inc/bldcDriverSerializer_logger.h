/*
 * bldcDriverSerializer_logger.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_LOGGER_H_
#define INC_BLDCDRIVERSERIALIZER_LOGGER_H_

#include "bldcDriverSerializer.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef LOGGER_RX
void mainReset(uint32_t timestamp);
void compA_IR(uint32_t timestamp);
void compB_IR(uint32_t timestamp);
void compC_IR(uint32_t timestamp);
void loggerBufferOverflow(uint32_t timestamp);

void currentA(int32_t current, uint32_t timestamp);
void currentB(int32_t current, uint32_t timestamp);
void currentRangeA(uint32_t range, uint32_t timestamp);
void currentRangeB(uint32_t range, uint32_t timestamp);
void absCurrentSetPoint(uint32_t setpoint, uint32_t timestamp);
void dutyCycle(uint32_t dutyCycle, uint32_t timestamp);
void currentControllerOutput(int32_t controllerOut, uint32_t timestamp);

void absRotorPosEncoder(uint32_t pos, uint32_t timestamp);
void rotorPosEncoder(int32_t pos, uint32_t timestamp);
void rotorPosSensorless(int32_t pos, uint32_t timestamp);
void rotorPosControllerOutput(int32_t controllerOut, uint32_t timestamp);

void time60Deg(int32_t t60deg, uint32_t timestamp);
void cycleTime(int32_t cycletime, uint32_t timestamp);
void entryState(uint32_t state, uint32_t timestamp);

void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
#endif

// ____TX____
#ifdef LOGGER_TX
void startLoggingPackage(uint32_t timestamp);

// events
void add_MainReset();
void add_CompA_IR();
void add_CompB_IR();
void add_CompC_IR();
void add_LoggerBufferOverflow();

// numbers
void add_CurrentA(int32_t current);
void add_CurrentB(int32_t current);
void add_CurrentRangeA(uint32_t range);
void add_CurrentRangeB(uint32_t range);
void add_AbsCurrentSetPoint(uint32_t setpoint);
void add_DutyCycle(uint32_t dutyCycle);
void add_CurrentControllerOutput(int32_t controllerOut);

void add_AbsRotorPosEncoder(uint32_t pos);
void add_RotorPosEncoder(int32_t pos);
void add_RotorPosSensorless(int32_t pos);
void add_RotorPosControllerOutput(int32_t controllerOut);

void add_EntryState(uint32_t state);
void add_Time60Deg(int32_t t60deg);
void add_CycleTime(int32_t cycletime);

// messages
void add_DebugMsg(uint8_t msg[]);
void add_InfoMsg(uint8_t msg[]);
void add_ErrorMsg(uint8_t msg[]);
#endif

#endif /* INC_BLDCDRIVERSERIALIZER_LOGGER_H_ */

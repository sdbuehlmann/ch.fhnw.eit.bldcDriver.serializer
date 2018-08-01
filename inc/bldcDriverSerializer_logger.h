/*
 * bldcDriverSerializer_logger.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_LOGGER_H_
#define INC_BLDCDRIVERSERIALIZER_LOGGER_H_

#include "serializerConfig.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef LOGGER_RX

void loggingIsEnabled(uint32_t timestamp);
void compA_IR(uint32_t timestamp);
void compB_IR(uint32_t timestamp);
void compC_IR(uint32_t timestamp);

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

void time60Deg(uint32_t t60deg, uint32_t timestamp);
void cycleTime(uint32_t cycletime, uint32_t timestamp);
void loggingConfiguration(uint32_t config, uint32_t timestamp);

void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
#endif

// ____TX____
#ifdef LOGGER_TX
void startLoggingPackage();

int8_t add_loggingIsEnabled();
int8_t add_compA_IR();
int8_t add_compB_IR();
int8_t add_compC_IR();

int8_t add_currentA(int32_t current);
int8_t add_currentB(int32_t current);
int8_t add_currentRangeA(uint32_t range);
int8_t add_currentRangeB(uint32_t range);
int8_t add_absCurrentSetPoint(uint32_t setpoint);
int8_t add_dutyCycle(uint32_t dutyCycle);
int8_t add_currentControllerOutput(int32_t controllerOut);

int8_t add_absRotorPosEncoder(uint32_t pos);
int8_t add_rotorPosEncoder(int32_t pos);
int8_t add_rotorPosSensorless(int32_t pos);
int8_t add_rotorPosControllerOutput(int32_t controllerOut);

int8_t add_time60Deg(uint32_t t60deg);
int8_t add_cycleTime(uint32_t cycletime);
int8_t add_loggingConfiguration(uint32_t config);

int8_t add_debugMsg(uint8_t msg[], uint8_t lenght);
int8_t add_infoMsg(uint8_t msg[], uint8_t lenght);
int8_t add_errorMsg(uint8_t msg[], uint8_t lenght);
#endif

#endif /* INC_BLDCDRIVERSERIALIZER_LOGGER_H_ */

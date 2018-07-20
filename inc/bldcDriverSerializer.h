/*
 * bldcDriverCom.h
 *
 *  Created on: Jul 20, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_H_
#define INC_BLDCDRIVERSERIALIZER_H_

#include <stdint.h>

//========== functions has to be implemented from user =============================
void transferByte(uint8_t data);

// logging
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
//==================================================================================

void startLoggingPackage(uint32_t timestamp);
void startObservingPackage();
void startControllingPackage();

void closePackage();

// logging:
// - events
void addToPackage_MainReset();
void addToPackage_CompA_IR();
void addToPackage_CompB_IR();
void addToPackage_CompC_IR();
void addToPackage_LoggerBufferOverflow();

// - numbers
void addToPackage_CurrentA(int32_t current);
void addToPackage_CurrentB(int32_t current);
void addToPackage_CurrentRangeA(uint32_t range);
void addToPackage_CurrentRangeB(uint32_t range);
void addToPackage_AbsCurrentSetPoint(uint32_t setpoint);
void addToPackage_DutyCycle(uint32_t dutyCycle);
void addToPackage_CurrentControllerOutput(int32_t controllerOut);

void addToPackage_AbsRotorPosEncoder(uint32_t pos);
void addToPackage_RotorPosEncoder(int32_t pos);
void addToPackage_RotorPosSensorless(int32_t pos);
void addToPackage_RotorPosControllerOutput(int32_t controllerOut);

void addToPackage_EntryState(uint32_t state);
void addToPackage_Time60Deg(int32_t t60deg);
void addToPackage_CycleTime(int32_t cycletime);

// - messages
void addToPackage_DebugMsg(uint8_t msg[]);
void addToPackage_InfoMsg(uint8_t msg[]);
void addToPackage_ErrorMsg(uint8_t msg[]);

// observing

// controlli
#endif

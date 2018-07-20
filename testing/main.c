
// =============== Includes ==============================================
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <bldcDriverSerializer.h>

// =============== Defines ===============================================
#define TEST_ENCODING


// =============== Variables =============================================

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
int main(){

	printf("Passed all tests successfully.");

	/*
	 * startLogPackage(timestamp);
	 * add_CompA_IR();
	 * add_absPhaseCurrent(current);
	 * add_currentPhaseA(currentA);
	 * completePackage();
	 */
}

void transferByte(uint8_t data){

}

// logging
void mainReset(uint32_t timestamp){

}
void compA_IR(uint32_t timestamp){

}
void compB_IR(uint32_t timestamp){

}
void compC_IR(uint32_t timestamp){

}
void loggerBufferOverflow(uint32_t timestamp){

}

void currentA(int32_t current, uint32_t timestamp){

}
void currentB(int32_t current, uint32_t timestamp){

}
void currentRangeA(uint32_t range, uint32_t timestamp){

}
void currentRangeB(uint32_t range, uint32_t timestamp){

}
void absCurrentSetPoint(uint32_t setpoint, uint32_t timestamp){

}
void dutyCycle(uint32_t dutyCycle, uint32_t timestamp){

}
void currentControllerOutput(int32_t controllerOut, uint32_t timestamp){

}

void absRotorPosEncoder(uint32_t pos, uint32_t timestamp){

}
void rotorPosEncoder(int32_t pos, uint32_t timestamp){

}
void rotorPosSensorless(int32_t pos, uint32_t timestamp){

}
void rotorPosControllerOutput(int32_t controllerOut, uint32_t timestamp){

}

void time60Deg(int32_t t60deg, uint32_t timestamp){

}
void cycleTime(int32_t cycletime, uint32_t timestamp){

}
void entryState(uint32_t state, uint32_t timestamp){

}

void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp){

}
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp){

}
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp){

}

/*
 * test_serializer.c
 *
 *  Created on: Jul 20, 2018
 *      Author: simon
 */

// =============== Includes ==============================================
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "serializer.h"
#include "test.h"

// =============== Defines ===============================================

// =============== Variables =============================================
static uint8_t buffer[200];
static uint8_t bufferCnt = 0;

static uint32_t packageIDToSend;
static uint8_t attrToSend;
static uint32_t unsignedToSend;
static uint32_t unsignedReceived;
static int32_t signedToSend;
static int32_t signedReceived;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
void startTest_serializer() {

	// ---------- Unsigned -----------------------------------------------
	// Test 1: Unsigned (upper limit)
	packageIDToSend = 0xFFFFFFFF;
	attrToSend = ATTR_27;
	unsignedToSend = 0xFFFFFFFF;

	openXPackage(packageIDToSend);
	assert(addUnsigned(attrToSend, unsignedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// Test 2: Unsigned (lower limit)
	packageIDToSend = 0;
	attrToSend = ATTR_1;
	unsignedToSend = 0;

	openXPackage(packageIDToSend);
	assert(addUnsigned(attrToSend, unsignedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// Test 3: Unsigned (random)
	packageIDToSend = 158749;
	attrToSend = ATTR_18;
	unsignedToSend = 89754;

	openXPackage(packageIDToSend);
	assert(addUnsigned(attrToSend, unsignedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// ---------- Signed -----------------------------------------------
	// Test 4: Upper limit
	packageIDToSend = 0xFFFFFFFF;
	attrToSend = ATTR_27;
	signedToSend = 2147483647;

	openYPackage(packageIDToSend);
	assert(addSigned(attrToSend, signedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// Test 2: Lower limit
	packageIDToSend = 0;
	attrToSend = ATTR_1;
	signedToSend = -2147483647;

	openYPackage(packageIDToSend);
	assert(addSigned(attrToSend, signedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// Test 3: Random
	packageIDToSend = 8971238;
	attrToSend = ATTR_7;
	signedToSend = -872;

	openYPackage(packageIDToSend);
	assert(addSigned(attrToSend, signedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	// Test 4: Random
	packageIDToSend = 87;
	attrToSend = ATTR_11;
	signedToSend = 0;

	openYPackage(packageIDToSend);
	assert(addSigned(attrToSend, signedToSend) == SUCCESSFUL);
	assert(closePackage() == SUCCESSFUL);

	/*unsignedToSend = 123456789;
	 send_unsigned(unsignedToSend);
	 unsignedReceived = decode_unsigned(buffer, 4);
	 assert(unsignedReceived == unsignedToSend);
	 bufferCnt = 0; // reset buffer

	 unsignedToSend = 10;
	 send_unsigned(unsignedToSend);
	 unsignedReceived = decode_unsigned(buffer, 1);
	 assert(unsignedReceived == unsignedToSend);
	 bufferCnt = 0; // reset buffer

	 unsignedToSend = 0;
	 send_unsigned(unsignedToSend);
	 unsignedReceived = decode_unsigned(buffer, 1);
	 assert(unsignedReceived == unsignedToSend);
	 bufferCnt = 0; // reset buffer

	 // signed
	 signedToSend = -123456789;
	 send_signed(signedToSend);
	 signedReceived = decode_signed(buffer, 5);
	 assert(signedReceived == signedToSend);
	 bufferCnt = 0; // reset buffer*/
}

// --------------- serializer.h ---------------------------------------------------------------------------------------------
void handleXPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData) {
	// handle unsigned
	assert(packageID == packageIDToSend);
	assert(attr == attrToSend);
	uint32_t received = decode_unsigned(data, nrData);
	assert(received == unsignedToSend);
}
void handleYPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData) {
	// handle signed
	assert(packageID == packageIDToSend);
	assert(attr == attrToSend);
	int32_t received = decode_signed(data, nrData);
	assert(received == signedToSend);
}
void handleZPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData) {

}

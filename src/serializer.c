// =============== Includes ==============================================
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "serializer.h"
#include "serializerPrinter.h"

// =============== Defines ===============================================
#define FIRST_ATTRIBUTE									ATTR_1
#define LAST_ATTRIBUTE									ATTR_27

#define FIRST_ASCII_CHAR 								32
#define LAST_ASCII_CHAR 								0b01111111

#define FIRST_NUMBER 									0b10000000

#define MAX_PACKAGE_SIZE								255 //bytes

// =============== Typdefs ===============================================
typedef enum {
	deserializerState_deserializeID, deserializerState_deserializeAttr, deserializerState_deserializeData
} DeserializerState;

typedef enum {
	bufferPackageState_waitForStartFlag, bufferPackageState_bufferIn
} BufferPackageState;

// =============== Variables =============================================
static BufferPackageState bufferPackageState = bufferPackageState_waitForStartFlag;
static uint32_t formatErrorCnt = 0;

static uint8_t outBuffer[MAX_PACKAGE_SIZE];
static uint8_t outBufferCnt = 0;
// =============== Function pointers =====================================

// =============== Function declarations =================================
static int8_t serializeUnsigned(uint32_t number);
static int8_t serializeSigned(int32_t number);
static int8_t serializeMsg(uint8_t *pMsg);
static int8_t addToOutBuffer(uint8_t data);

static uint8_t deserializePackage(uint8_t nrBytes, uint8_t packageBuffer[]);

// =============== Functions =============================================
// serialize
static int8_t serializeUnsigned(uint32_t number) {
	for (uint32_t cnt = 0; cnt < 5; cnt++) {
		uint8_t temp = number & 0b01111111; // store last 7 bits
		temp = temp | 0b10000000; // set first bit

		if (addToOutBuffer(temp) != SUCCESSFUL) {
			return ERROR;
		}

		number = number >> 7; // unsigned --> zeros added
		if (number == 0) {
			return SUCCESSFUL;
		}
	}

	return SUCCESSFUL;
}
static int8_t serializeSigned(int32_t number) {
	return serializeUnsigned((uint32_t) number);
}
static int8_t serializeMsg(uint8_t *pMsg) {
	while (1) {
		if (*pMsg == 0) {
			return SUCCESSFUL;
		}

		if (addToOutBuffer(*pMsg) != SUCCESSFUL) {
			return ERROR;
		}

		pMsg++;
	}
}
static int8_t addToOutBuffer(uint8_t data) {
	if (outBufferCnt <= MAX_PACKAGE_SIZE) {
		outBuffer[outBufferCnt] = data;
		outBufferCnt++;

		return SUCCESSFUL;
	} else {
		return ERROR;
	}
}

void openXPackage(uint32_t packageID) {
	outBuffer[0] = START_CONTROL_FLAG_X;
	outBufferCnt = 1;
	serializeUnsigned(packageID);
}
void openYPackage(uint32_t packageID) {
	outBuffer[0] = START_CONTROL_FLAG_Y;
	outBufferCnt = 1;
	serializeUnsigned(packageID);
}
void openZPackage(uint32_t packageID) {
	outBuffer[0] = START_CONTROL_FLAG_Z;
	outBufferCnt = 1;
	serializeUnsigned(packageID);
}
int8_t addEvent(uint8_t attr) {
	return addToOutBuffer(attr);
}
int8_t addUnsigned(uint8_t attr, uint32_t number) {
	if (addToOutBuffer(attr) != SUCCESSFUL || serializeUnsigned(number) != SUCCESSFUL) {
		return ERROR;
	}
	return SUCCESSFUL;
}
int8_t addSigned(uint8_t attr, int32_t number) {
	if (addToOutBuffer(attr) != SUCCESSFUL || serializeSigned(number) != SUCCESSFUL) {
		return ERROR;
	}
	return SUCCESSFUL;
}
int8_t addMsg(uint8_t attr, uint8_t msg[]) {
	if (addToOutBuffer(attr) != SUCCESSFUL || serializeMsg(msg) != SUCCESSFUL) {
		return ERROR;
	}
	return SUCCESSFUL;
}
int8_t closePackage() {
	if (addToOutBuffer(END_CONTROL_FLAG) != SUCCESSFUL) {
		return ERROR;
	}

	handleOutgoingPackage(outBuffer, outBufferCnt);
	return SUCCESSFUL;
}

// deserialize
uint32_t decode_unsigned(uint8_t data[], uint8_t nrData) {
	int32_t number = 0;

	for (uint8_t cnt = 0; cnt < nrData; cnt++) {

		// shift byte in its place
		number = number << 7;

		uint8_t temp = data[nrData - (cnt + 1)] & 0b01111111; // read buffer from behind, store last 7 bits
		number = number + temp;
	}

	return number;
}
int32_t decode_signed(uint8_t data[], uint8_t nrData) {
	return (int32_t) decode_unsigned(data, nrData);
}
uint8_t * decode_string(uint8_t data[], uint8_t nrData) {
	return data;
}

uint8_t is_start_flag(uint8_t data) {
	return (data == START_CONTROL_FLAG_X || data == START_CONTROL_FLAG_Y || data == START_CONTROL_FLAG_Z);
}
uint8_t is_end_flag(uint8_t data) {
	return (data == END_CONTROL_FLAG);
}
uint8_t is_payload(uint8_t data) {
	return (data >= FIRST_ASCII_CHAR || data == 0);
}
uint8_t is_attribute(uint8_t data) {
	return (data >= FIRST_ATTRIBUTE && data <= LAST_ATTRIBUTE);
}

uint8_t bufferIncommingData(uint8_t receivedByte) {
	// buffer package
	static uint8_t packageBuffer[MAX_PACKAGE_SIZE];
	static uint8_t byteCnt;

	switch (bufferPackageState) {
	case bufferPackageState_waitForStartFlag:
		if (is_start_flag(receivedByte)) {
			// package start
			byteCnt = 0;
			packageBuffer[byteCnt] = receivedByte;
			byteCnt++;

			bufferPackageState = bufferPackageState_bufferIn;
		}
		break;

	case bufferPackageState_bufferIn:
		packageBuffer[byteCnt] = receivedByte;
		byteCnt++;

		if (is_end_flag(receivedByte)) {
			// package end
			bufferPackageState = bufferPackageState_waitForStartFlag;

			deserializePackage(byteCnt, packageBuffer);
		}

		if (byteCnt > MAX_PACKAGE_SIZE) {
			// package too big
			bufferPackageState = bufferPackageState_waitForStartFlag;
			return ERROR;
		}
		break;
	}

	return 0;
}

uint8_t deserializePackage(uint8_t nrBytes, uint8_t packageBuffer[]) {
	DeserializerState state = deserializerState_deserializeID;

	uint8_t dataBuffer[MAX_PACKAGE_SIZE];
	uint8_t dataBufferCnt = 0;

	uint8_t lastAttribute = 0;
	uint32_t id = 0;

	printControlFlag(packageBuffer[0]);

	for (uint8_t cnt = 1; cnt < nrBytes; cnt++) {
		// receive package id
		switch (state) {
		case deserializerState_deserializeID:
			if (is_payload(packageBuffer[cnt])) {
				dataBuffer[dataBufferCnt] = packageBuffer[cnt];
				dataBufferCnt++;

				printBinary(packageBuffer[cnt]);
			} else {
				id = decode_unsigned(dataBuffer, dataBufferCnt);
				dataBufferCnt = 0;

				state = deserializerState_deserializeAttr;

				cnt = cnt - 1; // same element from buffer again (is not id)
			}
			break;

		case deserializerState_deserializeAttr:
			if (is_attribute(packageBuffer[cnt])) {
				lastAttribute = packageBuffer[cnt];

				printAttribute(lastAttribute);
				state = deserializerState_deserializeData;
			} else if (is_end_flag(packageBuffer[cnt])) {
				// end of package
				printControlFlag(packageBuffer[cnt]);
				return SUCCESSFUL;
			} else {
				// error: invalid format
				formatErrorCnt++;
				return ERROR;
			}
			break;

		case deserializerState_deserializeData:
			if (is_payload(packageBuffer[cnt])) {
				dataBuffer[dataBufferCnt] = packageBuffer[cnt];
				dataBufferCnt++;

				printBinary(packageBuffer[cnt]);
			} else {
				switch (packageBuffer[0]) {
				case START_CONTROL_FLAG_X:
					handleXPackageData(id, lastAttribute, dataBuffer, dataBufferCnt);
					break;
				case START_CONTROL_FLAG_Y:
					handleYPackageData(id, lastAttribute, dataBuffer, dataBufferCnt);
					break;
				case START_CONTROL_FLAG_Z:
					handleZPackageData(id, lastAttribute, dataBuffer, dataBufferCnt);
					break;
				}

				state = deserializerState_deserializeAttr;
				lastAttribute = 0;
				dataBufferCnt = 0;

				cnt = cnt - 1; // same element from buffer again (is not payload)
			}
			break;
		}
	}

	return SUCCESSFUL;
}

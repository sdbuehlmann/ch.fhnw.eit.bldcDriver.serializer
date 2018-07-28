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

// =============== Typdefs ===============================================
typedef enum {
	standby, receive_timestamp, receive_attr, receive_data
} State;

// =============== Variables =============================================
static State state = standby;

static uint8_t buffer[200];
static uint8_t bufferCnt = 0;

static uint32_t formatErrorCnt = 0;

static uint8_t lastType = 0;
static uint8_t lastAttribute = 0;
static uint32_t lastTimestamp = 0;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
// serialize
void send_startFlagX() {
	addToStream(START_CONTROL_FLAG_X);
}
void send_startFlagY() {
	addToStream(START_CONTROL_FLAG_Y);
}
void send_startFlagZ() {
	addToStream(START_CONTROL_FLAG_Z);
}
void send_endFlag() {
	addToStream(END_CONTROL_FLAG);
}
void send_attribute(uint8_t attr) {
	addToStream(attr);
}
void send_byte(uint8_t data) {
	addToStream(data);
}
void send_unsigned(uint32_t number, uint8_t nrMaxBytes) {
	for (uint32_t cnt = 0; cnt < 5; cnt++) {
		uint8_t temp = number & 0b01111111; // store last 7 bits
		temp = temp | 0b10000000; // set first bit

		addToStream(temp);

		number = number >> 7; // unsigned --> zeros added
		if (number == 0) {
			return;
		}
	}
}
void send_signed(int32_t number, uint8_t nrMaxBytes) {
	send_unsigned((uint32_t) number, nrMaxBytes);
}
void send_string(uint8_t *pMsg) {
	while (1) {
		if (*pMsg == 0) {
			return;
		}

		addToStream(*pMsg);

		pMsg++;
	}
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

void deserialize(uint8_t receivedByte) {

	switch (state) {
	case standby: {
		if (is_start_flag(receivedByte)) {
			lastType = receivedByte;

			printControlFlag(lastType);
			state = receive_timestamp;
		}
	}
		break;

	case receive_timestamp: {
		if (is_payload(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			printBinary(receivedByte);
		} else {
			lastTimestamp = decode_unsigned(buffer, bufferCnt);
			bufferCnt = 0;

			state = receive_attr;

			deserialize(receivedByte); // recursion
		}

	}
		break;

	case receive_attr: {
		if (is_attribute(receivedByte)) {
			lastAttribute = receivedByte;

			printAttribute(receivedByte);
			state = receive_data;
		} else if (is_end_flag(receivedByte)) {
			// end of package
			printControlFlag(receivedByte);
			state = standby;
		} else {
			// error: invalid format
			formatErrorCnt++;

			state = standby;
		}
	}
		break;

	case receive_data: {
		if (is_payload(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			printBinary(receivedByte);
		} else {

			switch (lastType) {
			case START_CONTROL_FLAG_X:
				handleDataFromXPackage(lastAttribute, lastTimestamp, buffer, bufferCnt);
				break;
			case START_CONTROL_FLAG_Y:
				handleDataFromYPackage(lastAttribute, lastTimestamp, buffer, bufferCnt);
				break;
			case START_CONTROL_FLAG_Z:
				handleDataFromZPackage(lastAttribute, lastTimestamp, buffer, bufferCnt);
				break;
			}

			state = receive_attr;
			lastAttribute = 0;
			bufferCnt = 0;

			deserialize(receivedByte); // recursion
		}
	}
		break;

	}
}




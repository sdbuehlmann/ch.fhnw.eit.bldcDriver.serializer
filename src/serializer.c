// =============== Includes ==============================================
#include <serializer.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


// =============== Defines ===============================================
#define START_CONTROL_FLAG_1							1
#define START_CONTROL_FLAG_2							2
#define START_CONTROL_FLAG_3							3
#define END_CONTROL_FLAG								4

#define FIRST_ATTRIBUTE_CHAR							5
#define LAST_ATTRIBUTE_CHAR								31

#define FIRST_ASCII_CHAR 								32
#define LAST_ASCII_CHAR 								0b01111111

#define FIRST_NUMBER 									0b10000000

// =============== Typdefs ===============================================
typedef enum {
	standby,
	receive_timestamp,
	receive_event,
	receive_msg,
	receive_unsigned,
	receive_signed
} State;

// =============== Variables =============================================
State state = standby;

static uint8_t buffer[200];
static uint8_t bufferCnt = 0;

static uint32_t timestamp = 0;
static uint8_t lastAttribute = 0;

// =============== Function pointers =====================================

// =============== Function declarations =================================
void decode(uint8_t data);
void changeState(uint8_t attribute);

// =============== Functions =============================================
void send_startFlag(){
	send(START_CONTROL_FLAG_1);
}
void send_endFlag(){
	send(END_CONTROL_FLAG);
}
void send_attribute(uint8_t attr){
	send(attr);
}
void send_byte(uint8_t data){
	send(data);
}
void send_unsigned(uint32_t number) {
	for (uint32_t cnt = 0; cnt < 5; cnt++) {
		uint8_t temp = number & 0b01111111; // store last 7 bits
		temp = temp | 0b10000000; // set first bit

		send(temp);

		number = number >> 7; // unsigned --> zeros added
		if (number == 0) {
			return;
		}
	}
}
void send_signed(int32_t number) {
	send_unsigned((uint32_t) number);
}
void send_string(uint8_t *pMsg) {
	while (1) {
		if (*pMsg == 0) {
			return;
		}

		send(*pMsg);

		pMsg++;
	}
}

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

uint8_t is_a_number(uint8_t data) {
	return (data >= FIRST_NUMBER);
}
uint8_t is_a_control_flag(uint8_t data) {
	return (data == START_CONTROL_FLAG_1 ||
			data == START_CONTROL_FLAG_2 ||
			data == START_CONTROL_FLAG_3 ||
			data == END_CONTROL_FLAG);
}
uint8_t is_a_ascii_char(uint8_t data) {
	return (data >= FIRST_ASCII_CHAR && data <= LAST_ASCII_CHAR);
}

void changeState(uint8_t attribute) {
	lastAttribute = attribute;
	bufferCnt = 0;

	if (is_a_event_attribute(attribute)) {
		state = receive_event;
	} else if (is_a_unsigned_attribute(attribute)) {
		state = receive_unsigned;
	} else if (is_a_signed_attribute(attribute)) {
		state = receive_signed;
	} else if (is_a_msg_attribute(attribute)) {
		state = receive_msg;
	} else {
		timestamp = 0;
		state = standby;
	}
}

void decode(uint8_t receivedByte) {
	switch (state) {
	case standby: {
		if (receivedByte == START_CONTROL_FLAG_1) {
			state = receive_timestamp;
		}
	}
		break;
	case receive_timestamp: {
		if (is_a_number(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			return;
		}

		timestamp = decode_unsigned(buffer, bufferCnt);

		changeState(receivedByte);

	}
		break;
	case receive_event: {
		eventReceived(timestamp, lastAttribute);

		changeState(receivedByte);
	}
		break;
	case receive_msg: {
		if (is_a_ascii_char(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			return;
		}

		msgReceived(timestamp, lastAttribute, buffer, bufferCnt);

		changeState(receivedByte);
	}
		break;
	case receive_unsigned: {
		if (is_a_number(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			return;
		}

		uint32_t value = decode_unsigned(buffer, bufferCnt);
		unsignedReceived(timestamp, lastAttribute, value);

		changeState(receivedByte);
	}
		break;
	case receive_signed: {
		if (is_a_number(receivedByte)) {
			buffer[bufferCnt] = receivedByte;
			bufferCnt++;

			return;
		}

		int32_t value = decode_signed(buffer, bufferCnt);
		signedReceived(timestamp, lastAttribute, value);

		changeState(receivedByte);
	}
		break;
	}
}

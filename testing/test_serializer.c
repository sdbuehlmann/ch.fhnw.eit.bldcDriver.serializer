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

// =============== Defines ===============================================

// =============== Variables =============================================
static uint8_t buffer[200];
static uint8_t bufferCnt = 0;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================
void main() {
	uint32_t unsignedToSend;
	uint32_t unsignedReceived;
	int32_t signedToSend;
	int32_t signedReceived;

	// unsigned
	unsignedToSend = 123456789;
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
	bufferCnt = 0; // reset buffer

	printf("passed all tests successfully");
}

void send(uint8_t data) {
	buffer[bufferCnt] = data;
	bufferCnt++;
}

void eventReceived(uint32_t timestamp, uint8_t symbol) {

}
void msgReceived(uint32_t timestamp, uint8_t symbol, uint8_t msg[],
		uint8_t lenght) {

}
void unsignedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data) {

}
void signedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data) {

}

uint8_t is_a_event_attribute(uint8_t data) {
	return 1;
}
uint8_t is_a_msg_attribute(uint8_t data) {
	return 1;
}
uint8_t is_a_unsigned_attribute(uint8_t data) {
	return 1;
}
uint8_t is_a_signed_attribute(uint8_t data) {
	return 1;
}


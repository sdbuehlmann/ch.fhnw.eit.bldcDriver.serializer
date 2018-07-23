/*
 * serialCom.h
 *
 *  Created on: Jul 19, 2018
 *      Author: simon
 */

#ifndef INC_SERIALIZER_H_
#define INC_SERIALIZER_H_

#include <stdint.h>

// =============== Defines ===============================================
#define START_CONTROL_FLAG_X							1
#define START_CONTROL_FLAG_Y							2
#define START_CONTROL_FLAG_Z							3

#define FIRST_ATTRIBUTE_CHAR							5
#define LAST_ATTRIBUTE_CHAR								31

//========== functions has to be implemented from user =============================
void eventReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol);
void msgReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol, uint8_t msg[], uint8_t lenght);
void unsignedReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol, uint32_t data);
void signedReceived(uint32_t timestamp, uint8_t startFlag, uint8_t symbol, uint32_t data);

uint8_t is_a_event_attribute(uint8_t startFlag, uint8_t data);
uint8_t is_a_msg_attribute(uint8_t startFlag, uint8_t data);
uint8_t is_a_unsigned_attribute(uint8_t startFlag, uint8_t data);
uint8_t is_a_signed_attribute(uint8_t startFlag, uint8_t data);

void store(uint8_t data);
//==================================================================================

void decode(uint8_t data);

void send_startFlagX();
void send_startFlagY();
void send_startFlagZ();
void send_endFlag();
void send_attribute(uint8_t attr);
void send_byte(uint8_t data);
void send_unsigned(uint32_t number, uint8_t nrMaxBytes);
void send_signed(int32_t number, uint8_t nrMaxBytes);
void send_string(uint8_t *pMsg);

uint32_t decode_unsigned(uint8_t data[], uint8_t nrData);
int32_t decode_signed(uint8_t data[], uint8_t nrData);

#endif /* INC_SERIALIZER_H_ */

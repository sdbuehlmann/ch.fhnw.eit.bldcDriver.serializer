/*
 * serialCom.h
 *
 *  Created on: Jul 19, 2018
 *      Author: simon
 */

#ifndef INC_SERIALIZER_H_
#define INC_SERIALIZER_H_

#include <stdint.h>

//========== functions has to be implemented from user =============================
void eventReceived(uint32_t timestamp, uint8_t symbol);
void msgReceived(uint32_t timestamp, uint8_t symbol, uint8_t msg[], uint8_t lenght);
void unsignedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data);
void signedReceived(uint32_t timestamp, uint8_t symbol, uint32_t data);

uint8_t is_a_event_attribute(uint8_t data);
uint8_t is_a_msg_attribute(uint8_t data);
uint8_t is_a_unsigned_attribute(uint8_t data);
uint8_t is_a_signed_attribute(uint8_t data);

void send(uint8_t data);
//==================================================================================

void send_startFlag();
void send_endFlag();
void send_attribute(uint8_t attr);
void send_byte(uint8_t data);
void send_unsigned(uint32_t number);
void send_signed(int32_t number);
void send_string(uint8_t *pMsg);

uint32_t decode_unsigned(uint8_t data[], uint8_t nrData);
int32_t decode_signed(uint8_t data[], uint8_t nrData);

uint8_t is_a_number(uint8_t data);
uint8_t is_a_ascii_char(uint8_t data);
uint8_t is_a_control_flag(uint8_t data);

#endif /* INC_SERIALIZER_H_ */

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
#define FIRST_ATTRIBUTE_CHAR							5
#define LAST_ATTRIBUTE_CHAR								31

//========== functions has to be implemented from user =============================

void handleDataFromXPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);
void handleDataFromYPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);
void handleDataFromZPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);

void addToStream(uint8_t data);
//==================================================================================

void deserialize(uint8_t data);

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
uint8_t * decode_string(uint8_t data[], uint8_t nrData);

#endif /* INC_SERIALIZER_H_ */

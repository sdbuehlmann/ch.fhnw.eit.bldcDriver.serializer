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
#define END_CONTROL_FLAG								4

#define ATTR_1											5
#define ATTR_2											6
#define ATTR_3											7
#define ATTR_4											8
#define ATTR_5		 									9
#define ATTR_6		 									10
#define ATTR_7		 									11
#define ATTR_8		 									12
#define ATTR_9											13
#define ATTR_10											14
#define ATTR_11 										15
#define ATTR_12											16
#define ATTR_13											17
#define ATTR_14											18
#define ATTR_15											19
#define ATTR_16											20
#define ATTR_17											21
#define ATTR_18											22
#define ATTR_19											23
#define ATTR_20											24
#define ATTR_21											25
#define ATTR_22											26
#define ATTR_23											27
#define ATTR_24											28
#define ATTR_25											29
#define ATTR_26											30
#define ATTR_27											31


//========== functions has to be implemented from user =============================

void handleDataFromXPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);
void handleDataFromYPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);
void handleDataFromZPackage(uint8_t attr, uint32_t timestamp, uint8_t data[], uint8_t nrData);

void addToStream(uint8_t data);

void print(char txt[]);
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

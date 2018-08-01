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

#define ERROR											-1
#define SUCCESSFUL										0

//========== functions has to be implemented from user =============================
void handleXPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData);
void handleYPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData);
void handleZPackageData(uint32_t packageID, uint8_t attr, uint8_t data[], uint8_t nrData);

void handleOutgoingPackage(uint8_t buffer[], uint8_t size);
//==================================================================================
uint8_t bufferIncommingData(uint8_t receivedByte);

void openXPackage(uint32_t packageID);
void openYPackage(uint32_t packageID);
void openZPackage(uint32_t packageID);

int8_t closePackage();

int8_t addEvent(uint8_t attr);
int8_t addUnsigned(uint8_t attr, uint32_t data);
int8_t addSigned(uint8_t attr, int32_t data);
int8_t addMsg(uint8_t attr, uint8_t msg[]);

uint32_t decode_unsigned(uint8_t data[], uint8_t nrData);
int32_t decode_signed(uint8_t data[], uint8_t nrData);
uint8_t * decode_string(uint8_t data[], uint8_t nrData);

#endif /* INC_SERIALIZER_H_ */

/*
 * bldcDriverSerializer_operator.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_OPERATOR_H_
#define INC_BLDCDRIVERSERIALIZER_OPERATOR_H_

#include "serializerConfig.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef OPERATOR_RX
void enableSerialOperationgMode();
void enableLogging();
void enableDriver();
void disableDriver();
void selectPositiveTorque();
void selectNegativeTorque();
void rotadeClockwise();
void rotadeCounterclockwise();
void getObservingInfos();
void getLoggingConfig();

void setPositiveTorqueLevel(uint8_t level);
void setNegativeTorqueLevel(uint8_t level);
void setMaxPhaseCurrent(uint8_t current);

void setTiming(uint8_t timing);
void setRotorPosController_pParam(uint32_t pParam);
void setRotorPosController_iParam(uint32_t iParam);
void setLoggingConfig(uint32_t config);
#endif

#ifdef OPERATOR_TX

// ____TX____
void startOperatorPackage();

int8_t add_enableSerialOperatingMode();
int8_t add_enableLogging();
int8_t add_EnableDriver();
int8_t add_DisableDriver();
int8_t add_SelectPositiveTorque();
int8_t add_SelectNegativeTorque();
int8_t add_rotadeClockwise();
int8_t add_rotadeCounterclockwise();
int8_t add_getObservingInfos();
int8_t add_getLoggingConfig();

int8_t add_SetPositiveTorqueLevel(uint8_t level);
int8_t add_SetNegativeTorqueLevel(uint8_t level);
int8_t add_SetMaxPhaseCurrent(uint8_t level);

int8_t add_SetTiming(uint8_t timing);
int8_t add_SetRotorPosController_pParam(uint32_t pParam);
int8_t add_SetRotorPosController_iParam(uint32_t iParam);
int8_t add_setLoggingConfig(uint32_t config);
#endif


#endif /* INC_BLDCDRIVERSERIALIZER_OPERATOR_H_ */

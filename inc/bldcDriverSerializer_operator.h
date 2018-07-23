/*
 * bldcDriverSerializer_operator.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_OPERATOR_H_
#define INC_BLDCDRIVERSERIALIZER_OPERATOR_H_

#include "bldcDriverSerializer.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef OPERATOR_RX
void enableSerialOperationgMode();
void enableDriver();
void disableDriver();
void selectPositiveTorque();
void selectNegativeTorque();

void setPositiveTorqueLevel(uint8_t level);
void setNegativeTorqueLevel(uint8_t level);
void setMaxPhaseCurrent(uint8_t current);

void setTiming(int8_t timing);
void setRotorPosController_pParam(uint32_t pParam);
void setRotorPosController_iParam(uint32_t iParam);
#endif

#ifdef OPERATOR_TX

// ____TX____
void startOperatorPackage();

void add_EnableSerialOperatingMode();
void add_EnableDriver();
void add_DisableDriver();
void add_SelectPositiveTorque();
void add_SelectNegativeTorque();

void add_SetPositiveTorqueLevel(uint8_t level);
void add_SetNegativeTorqueLevel(uint8_t level);
void add_SetMaxPhaseCurrent(uint8_t level);

void add_SetTiming(uint8_t timing);
void add_SetRotorPosController_pParam(uint32_t pParam);
void add_SetRotorPosController_iParam(uint32_t iParam);
#endif


#endif /* INC_BLDCDRIVERSERIALIZER_OPERATOR_H_ */

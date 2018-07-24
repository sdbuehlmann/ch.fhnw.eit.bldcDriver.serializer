/*
 * bldcDriverCom.h
 *
 *  Created on: Jul 20, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_H_
#define INC_BLDCDRIVERSERIALIZER_H_

#include <stdint.h>

// ----configurate supported functions--------------
//#define LOGGER_RX
//#define LOGGER_TX
//#define OBSERVER_RX
//#define OBSERVER_TX
#define OPERATOR_RX
#define OPERATOR_TX
// -------------------------------------------------

// ----functions has to be implemented from user----
void handleOutgoing(uint8_t outData);
// -------------------------------------------------

void closePackage();
void handleIncomming(uint8_t inData);

#endif /* INC_BLDCDRIVERSERIALIZER_H_ */

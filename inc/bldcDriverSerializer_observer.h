/*
 * bldcDriverSerializer_observer.h
 *
 *  Created on: Jul 23, 2018
 *      Author: simon
 */

#ifndef INC_BLDCDRIVERSERIALIZER_OBSERVER_H_
#define INC_BLDCDRIVERSERIALIZER_OBSERVER_H_

#include "bldcDriverSerializer.h"

// ____RX____ (if supported, functions has to be implemented from user)
#ifdef OBSERVER_RX

#endif

// ____TX____
#ifdef OBSERVER_TX
void startObservingPackage();
#endif



#endif /* INC_BLDCDRIVERSERIALIZER_OBSERVER_H_ */

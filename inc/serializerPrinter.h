/*
 * seralizerPrinter.h
 *
 *  Created on: Jul 27, 2018
 *      Author: simon
 */

#ifndef INC_SERIALIZERPRINTER_H_
#define INC_SERIALIZERPRINTER_H_

#include <stdint.h>

// ----to be implemented from user----
void print(char pTxt[]);
extern uint8_t serializerPrinterIsEnabled;
// -------------------------------------------------

void printControlFlag(uint8_t flag);
void printAttribute(uint8_t flag);
void printBinary(uint8_t data);

#endif /* INC_SERIALIZERPRINTER_H_ */

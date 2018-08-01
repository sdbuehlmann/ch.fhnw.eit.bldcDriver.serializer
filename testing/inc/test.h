/*
 * test.h
 *
 *  Created on: Jul 24, 2018
 *      Author: simon
 */

#ifndef TESTING_TEST_H_
#define TESTING_TEST_H_

#include <stdint.h>

typedef struct {
	uint8_t value;
	uint8_t flag;
} NrAttr_uint8;

typedef struct {
	int8_t value;
	uint8_t flag;
} NrAttr_int8;

typedef struct {
	uint32_t value;
	uint8_t flag;
} NrAttr_uint32;

typedef struct {
	int32_t value;
	uint8_t flag;
} NrAttr_int32;

typedef struct {
	uint8_t flag;
} EventAttr;

typedef struct {
	uint8_t *pValue;
	uint8_t flag;
} StringAttr;

void startTest_serializer();

void startTest_bldcDriverLogger();
void analyzeFlags_bldcDriverLogger();

void startTest_bldcDriverOperator();
void analyzeFlags_bldcDriverOperator();

void startTest_bldcDriverObserver();
void analyzeFlags_bldcDriverObserver();

#endif /* TESTING_TEST_H_ */

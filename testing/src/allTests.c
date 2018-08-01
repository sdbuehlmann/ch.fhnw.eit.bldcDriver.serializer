/*
 * allTests.c
 *
 *  Created on: Aug 1, 2018
 *      Author: simon
 */

#include <stdio.h>

#include "test.h"
#include "serializer.h"
#include "serializerPrinter.h"

uint8_t serializerPrinterIsEnabled = 0; // enable/disable printer

static uint8_t buffer[500];
static uint32_t bufferCnt = 0;

int main(void) {
	startTest_serializer();

	startTest_bldcDriverLogger();
	startTest_bldcDriverObserver();
	startTest_bldcDriverOperator();

	for (uint8_t cnt = 0; cnt < bufferCnt; cnt++) {
		bufferIncommingData(buffer[cnt]);
	}

	analyzeFlags_bldcDriverLogger();
	analyzeFlags_bldcDriverObserver();
	analyzeFlags_bldcDriverOperator();

	printf("***passed all tests successfully***");
}

// --------------- serializer.h ----------------------------------------------------------------------------------------
void handleOutgoingPackage(uint8_t packageBuffer[], uint8_t size) {
	for (uint8_t cnt = 0; cnt < size; cnt++) {
		buffer[bufferCnt] = packageBuffer[cnt];
		bufferCnt++;
	}
}

void print(char pTxt[]) {
	printf(pTxt);
}

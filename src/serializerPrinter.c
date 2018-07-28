/*
 * serializerPrinter.c
 *
 *  Created on: Jul 27, 2018
 *      Author: simon
 */
#include <stdio.h>

#include "serializerPrinter.h"
#include "serializer.h"

void printControlFlag(uint8_t flag) {
	if (serializerPrinterIsEnabled) {
		switch (flag) {
		case START_CONTROL_FLAG_X:
			print("<START_X>  ");
			break;
		case START_CONTROL_FLAG_Y:
			print("<START_Y> ");
			break;
		case START_CONTROL_FLAG_Z:
			print("<START_Z>  ");
			break;
		case END_CONTROL_FLAG:
			print("<END> \n");
			break;
		default:
			// print nothing
			break;
		}
	}
}

void printAttribute(uint8_t flag) {
	if (serializerPrinterIsEnabled) {
		switch (flag) {
		case ATTR_1:
			print("<ATTR_1> ");
			break;
		case ATTR_2:
			print("<ATTR_2> ");
			break;
		case ATTR_3:
			print("<ATTR_3> ");
			break;
		case ATTR_4:
			print("<ATTR_4> ");
			break;
		case ATTR_5:
			print("<ATTR_5> ");
			break;
		case ATTR_6:
			print("<ATTR_6> ");
			break;
		case ATTR_7:
			print("<ATTR_7> ");
			break;
		case ATTR_8:
			print("<ATTR_8> ");
			break;
		case ATTR_9:
			print("<ATTR_9> ");
			break;
		case ATTR_10:
			print("<ATTR_10> ");
			break;
		case ATTR_11:
			print("<ATTR_11> ");
			break;
		case ATTR_12:
			print("<ATTR_12> ");
			break;
		case ATTR_13:
			print("<ATTR_13> ");
			break;
		case ATTR_14:
			print("<ATTR_14> ");
			break;
		case ATTR_15:
			print("<ATTR_15> ");
			break;
		case ATTR_16:
			print("<ATTR_16> ");
			break;
		case ATTR_17:
			print("<ATTR_17> ");
			break;
		case ATTR_18:
			print("<ATTR_18> ");
			break;
		case ATTR_19:
			print("<ATTR_19> ");
			break;
		case ATTR_20:
			print("<ATTR_20> ");
			break;
		case ATTR_21:
			print("<ATTR_21> ");
			break;
		case ATTR_22:
			print("<ATTR_22> ");
			break;
		case ATTR_23:
			print("<ATTR_23> ");
			break;
		case ATTR_24:
			print("<ATTR_24> ");
			break;
		case ATTR_25:
			print("<ATTR_25> ");
			break;
		case ATTR_26:
			print("<ATTR_26> ");
			break;
		case ATTR_27:
			print("<ATTR_27> ");
			break;

		default:
			// print nothing
			break;
		}
	}
}

void printBinary(uint8_t data) {
	if (serializerPrinterIsEnabled) {
		char buffer[10]; // 8 digits plus a whitespace plus a zero (end of string)

		for (uint8_t cnt = 0; cnt < 8; cnt++) {
			if (data & 0b00000001) {
				buffer[cnt] = '1';
			} else {
				buffer[cnt] = '0';
			}
			data = data >> 1;
		}

		buffer[8] = ' ';
		buffer[9] = 0;

		print(buffer);
	}
}

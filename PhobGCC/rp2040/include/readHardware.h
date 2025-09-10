#ifndef READHARDWARE_H
#define READHARDWARE_H

//include this after the pins are defined in the RP2040 board-specific headers

#include "structsAndEnums.h"

#include "hardware/adc.h"

void setPinModes();

void readButtons(const Pins &, Buttons &hardware);

void readADCScale(float &, float );

//implement a 3 unit deadzone
int readLa(const Pins &, const int initial, const float scale);

int readRa(const Pins &, const int initial, const float scale);

/*
//for external MCP3002 adc, 10 bit
int __time_critical_func(readExtAdc)(const WhichStick whichStick, const WhichAxis whichAxis);
*/

//for external MCP3202 adc, 12 bit
int __time_critical_func(readExtAdc)(const WhichStick whichStick, const WhichAxis whichAxis);

int readAx(const Pins &);

int readAy(const Pins &);

int readCx(const Pins &);

int readCy(const Pins &);

uint32_t micros();

uint64_t millis();

#endif //READHARDWARE_H

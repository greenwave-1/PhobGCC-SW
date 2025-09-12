#ifndef READHARDWARE_H
#define READHARDWARE_H

//include this after the pins are defined in the Teensy board-specific headers

#include <ADC.h>
#include <VREF.h>
#include "../common/structsAndEnums.h"

extern ADC *adc;

void setPinModes();

void readButtons(const Pins &pin, Buttons &hardware);
void readADCScale(float &ADCScale, float ADCScaleFactor);

//these are 12 bit but we right shift to get 8 bit
//implement a 3 unit deadzone
int readLa(const Pins &pin, const int initial, const float scale);
int readRa(const Pins &pin, const int initial, const float scale);

//these are native 12-bit
int readAx(const Pins &pin);
int readAy(const Pins &pin);
int readCx(const Pins &pin);
int readCy(const Pins &pin);

#endif //READHARDWARE_H

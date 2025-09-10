#ifndef FILTER_H
#define FILTER_H

#include <cmath>

#include "structsAndEnums.h"

//The median filter can be either length 3, 4, or 5.
#define MEDIANLEN 5
//Edit MEDIANARRAY to be MEDIANLEN long
#define MEDIANARRAY {0,0,0,0,0}
//Comment this define to disable it entirely.
//#define USEMEDIAN

void runMedian(float &val, float valArray[MEDIANLEN], unsigned int &medianIndex);

float velDampFromSnapback(const int snapback);

void recomputeGains(const ControlConfig controls, FilterGains &gains, FilterGains &normGains);

void runKalman(float &xPosFilt, float &yPosFilt, const float xZ,const float yZ, const ControlConfig &controls, const FilterGains &normGains);

//The input setting should range from 0 to 15.
//The output should be 0 for 0.
float calcWaveshapeMult(const int setting);

//This simulates an idealized sort of pode:
// if the stick is moving fast, it responds poorly, while
// if the stick is moving slowly, it follows closely.
//It's not suitable to be the sole filter, but when put after
// the smart snapback filter, it should be able to hold the
// output at the rim longer when released.
void aRunWaveShaping(const float xPos, const float yPos, float &xOut, float &yOut, const ControlConfig &controls, const FilterGains &normGains);

//We need to duplicate this and call each one only once so that we don't reuse the history and screw things up.
void cRunWaveShaping(const float xPos, const float yPos, float &xOut, float &yOut, const ControlConfig &controls, const FilterGains &normGains);

#endif //FILTER_H

#ifndef STICKCAL_H
#define STICKCAL_H

#include <cmath>

#include "curveFitting.h"
#include "structsAndEnums.h"
#include "filter.h"

//TODO: either put these const globals in varables.h or make them #defines
//origin values, useful for writing readable stick positions
const int _intOrigin = 127;
const float _floatOrigin = 127.5;

//////values used for calibration
const int _noOfNotches = 16;
const int _noOfCalibrationPoints = _noOfNotches * 2;
const int _noOfAdjNotches = 12;
const int _fitOrder = 3; //fit order used in the linearization step
const float _maxStickAngle = 0.4886921906;//28 degrees; this is the max angular deflection of the stick.

const float _defaultCalPoints[_noOfCalibrationPoints] =  {
	0.0,0.0,//right
	0.0,0.0,
	0.0,0.0,//up right
	0.0,0.0,
	0.0,0.0,//up
	0.0,0.0,
	0.0,0.0,//up left
	0.0,0.0,
	0.0,0.0,//left
	0.0,0.0,
	0.0,0.0,//down left
	0.0,0.0,
	0.0,0.0,//down
	0.0,0.0,
	0.0,0.0,//down right
	0.0,0.0};

//Defaults
//                                                         right        notch 1      up right     notch 2      up           notch 3      up left      notch 4      left         notch 5      down left    notch 6      down         notch 7      down right   notch 8
//                                                         0            1            2            3            4            5            6            7            8            9            10           11           12           13           14           15
const int _calOrder[_noOfCalibrationPoints] =             {0, 1,        8, 9,       16, 17,       24, 25,      4, 5,        12, 13,      20, 21,      28, 29,      2, 3,        6, 7,        10, 11,      14, 15,      18, 19,      22, 23,      26, 27,      30, 31};
const float _notchAngleDefaults[_noOfNotches] =           {0,           M_PI/8.0,    M_PI*2/8.0,  M_PI*3/8.0,  M_PI*4/8.0,  M_PI*5/8.0,  M_PI*6/8.0,  M_PI*7/8.0,  M_PI*8/8.0,  M_PI*9/8.0,  M_PI*10/8.0, M_PI*11/8.0, M_PI*12/8.0, M_PI*13/8.0, M_PI*14/8.0, M_PI*15/8.0};
const NotchStatus _notchStatusDefaults[_noOfNotches] =    {CARDINAL,    TERT_ACTIVE, SECONDARY,   TERT_ACTIVE, CARDINAL,    TERT_ACTIVE, SECONDARY,   TERT_ACTIVE, CARDINAL,    TERT_ACTIVE, SECONDARY,   TERT_ACTIVE, CARDINAL,    TERT_ACTIVE, SECONDARY,   TERT_ACTIVE};
//                                                         up right     up left      down left    down right   notch 1      notch 2      notch 3      notch 4      notch 5      notch 6      notch 7      notch 8
const int _notchAdjOrder[_noOfAdjNotches] =               {2,           6,           10,          14,          1,           3,           5,           7,           9,           11,          13,          15};

float linearize(const float point, const float coefficients[]);

/*
 * calcStickValues computes the stick x/y coordinates from angle.
 * This requires weird trig because the stick moves spherically.
 */
void calcStickValues(float angle, float* x, float* y);

/*
 * Convert the x/y coordinates (actually angles on a sphere) to an azimuth
 * We first convert to a 3D coordinate and then drop to 2D, then arctan it
 * This does the opposite of calcStickValues, ideally.
 */
void angleOnSphere(const float x, const float y, float& angle);

/*
 * stripCalPoints removes the notches from un-cleaned cal points
 * this is so we can get the original values of the notches after the affine transform.
 * there need to be _noOfCalibrationPoints values in the inputs and outputs.
 */
void stripCalPoints(const float calPointsX[], const float calPointsY[], float strippedPointsX[], float strippedPointsY[]);

/*
 * computeStickAngles
 * write all the stick angles into the notch angles array array
 * inputs need to be length _noOfNotches+1
 * outputs need to be length _noOfNotches
 */
void computeStickAngles(float xInput[], float yInput[], float stickAngles[]);
//sets notches to measured values if absent
void cleanNotches(float notchAngles[], float measuredNotchAngles[], NotchStatus notchStatus[]);

/*******************
	notchRemap
	Remaps the stick position using affine transforms generated from the notch positions
*******************/
void notchRemap(const float xIn, const float yIn, float* xOut, float* yOut, const int regions, const StickParams &stickParams, int currentCalStep, const ControlConfig &controls, const WhichStick whichStick);

/*
 * transformCalPoints
 * remaps the cleaned calibration points from raw measurements to output coordinates
 * This seems redundant but we're feeding it coordinates without non-diagonal notches
 */
void transformCalPoints(const float xInput[], const float yInput[], float xOutput[], float yOutput[], const StickParams &stickParams, const ControlConfig &controls, const WhichStick whichStick);

/*******************
	cleanCalPoints
	take the x and y coordinates and notch angles collected during the calibration procedure,
	and generate the cleaned (non-redundant) x and y stick coordinates and the corresponding x and y notch coordinates
*******************/
void cleanCalPoints(const float calPointsX[], const float calPointsY[], const float notchAngles[], float cleanedPointsX[], float cleanedPointsY[], float notchPointsX[], float notchPointsY[], NotchStatus notchStatus[]);

//The notch adjustment is limited in order to control
//1. displacement of points (max 12 units out of +/- 100, for now)
//2. stretching of coordinates (max +/- 30%)
void legalizeNotch(const int notchIndex, float measuredNotchAngles[], float notchAngles[], NotchStatus notchStatus[]);

void legalizeNotches(const int currentStepIn, float measuredNotchAngles[], float notchAngles[], NotchStatus notchStatus[]);

//adjustNotch is used to adjust the angles of the notch.
//It is run after calibration points are collected.
//It runs a legalization routine to limit subsequent notches
void adjustNotch(const int currentStepIn, const float loopDelta, const WhichStick whichStick, float measuredNotchAngles[], float notchAngles[], NotchStatus notchStatus[], Buttons &btn, Buttons &hardware);

//displayNotch is used in lieu of adjustNotch when doing basic calibration
void displayNotch(const int currentStepIn, const bool calibratingAStick, const float notchAngles[], Buttons &btn);

void insertCalPoints(const WhichStick whichStick, const int currentStepIn, float calPointsX[], float calPointsY[], Pins &pin, float X, float Y);

/*******************
	linearizeCal
	Generate a fit to linearize the stick response.
	Inputs:
		cleaned points X and Y, (must be 17 points for each of these, the first being the center, the others starting at 3 oclock and going around counterclockwise)
	Outputs:
		linearization fit coefficients for X and Y
*******************/
void linearizeCal(const float inX[], const float inY[], float outX[], float outY[], StickParams &stickParams);

//Self-explanatory.
void inverse(const float in[3][3], float (&out)[3][3]);

//Self-explanatory.
void matrixMatrixMult(const float left[3][3], const float right[3][3], float (&output)[3][3]);

void print_mtx(const float matrix[3][3]);


void notchCalibrate(const float xIn[], const float yIn[], const float xOut[], const float yOut[], const int regions, StickParams &stickParams);

#endif //STICKCAL_H

#ifndef PHOBGCC_H
#define PHOBGCC_H

#include <algorithm>
#include <cmath>
using std::min;
using std::max;

//Uncomment to get a glowing LED on Teensy 4.
//#define ENABLE_LED

//Uncomment the appropriate #include line for your hardware by deleting the two slashes at the beginning of the line.
//#include "../teensy/Phob1_0Teensy3_2.h"          // For PhobGCC board 1.0 with Teensy 3.2
//#include "../teensy/Phob1_0Teensy3_2DiodeShort.h"// For PhobGCC board 1.0 with Teensy 3.2 and the diode shorted
//#include "../teensy/Phob1_1Teensy3_2.h"          // For PhobGCC board 1.1 with Teensy 3.2
//#include "../teensy/Phob1_1Teensy3_2DiodeShort.h"// For PhobGCC board 1.1 with Teensy 3.2 and the diode shorted
//#include "../teensy/Phob1_1Teensy4_0.h"          // For PhobGCC board 1.1 with Teensy 4.0
//#include "../teensy/Phob1_1Teensy4_0DiodeShort.h"// For PhobGCC board 1.1 with Teensy 4.0 and the diode shorted
//#include "../teensy/Phob1_2Teensy4_0.h"          // For PhobGCC board 1.2.x with Teensy 4.0
//#include "../rp2040/include/PicoProtoboard.h"    // For a protoboard with a Pico on it, used for developing for the RP2040
//#include "../rp2040/include/Phob2_0.h"           // For PhobGCC Board 2.0 with RP2040

#include "structsAndEnums.h"
#include "variables.h"
#include "filter.h"
#include "stick.h"
#include "../extras/extras.h"

//#define BUILD_RELEASE
#define BUILD_DEV

//This is just an integer.
#define SW_VERSION 30

extern ControlConfig _controls;

extern FilterGains _gains; //these values are for 800 hz, recomputeGains converts them to what is needed for the actual frequency (1000 Hz)

extern FilterGains _normGains;//this gets filled by recomputeGains();

extern Pins _pinList;

int calcRumblePower(const int rumble);

void freezeSticks(const int time, Buttons &btn, Buttons &hardware);

void freezeSticksToggleIndicator(const int time, Buttons &btn, Buttons &hardware, bool toggle);

//This clears all the buttons but doesn't overwrite the sticks or shoulder buttons.
void clearButtons(const int time, Buttons &btn, Buttons &hardware);

void showRumble(const int time, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void changeRumble(const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

//Make it so you don't need to press B.
//This is only good if the sticks are calibrated, so
// the setting auto-resets whenever you hard reset or recalibrate.
void changeAutoInit(Buttons &btn, Buttons &hardware, ControlConfig &controls);

void adjustSnapback(const WhichAxis axis, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains, FilterGains &normGains);

void adjustWaveshaping(const WhichStick whichStick, const WhichAxis axis, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void adjustSmoothing(const WhichAxis axis, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains, FilterGains &normGains);

void showAstickSettings(Buttons &btn, Buttons &hardware, const ControlConfig &controls, FilterGains &gains);

void adjustCstickSmoothing(const WhichAxis axis, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains, FilterGains &normGains);

void adjustCstickOffset(const WhichAxis axis, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void showCstickSettings(Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains);

void adjustCardinalSnapping(const WhichStick whichStick, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void adjustAnalogScaler(const WhichStick whichStick, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void nextTriggerState(WhichTrigger trigger, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void adjustTriggerOffset(const WhichTrigger trigger, const Increase increase, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void showTriggerSettings(Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains);

void changeTournamentToggle(Buttons &btn, Buttons &hardware, ControlConfig &controls);

//apply digital button swaps for ABLRXYZ
void applyRemaps(const ControlConfig &controls, const Buttons &hardware, Buttons &btn);

void remapAdvance(int &step, ControlConfig &controls, Buttons &hardware, Buttons &btn);

void resetRemap(ControlConfig &controls);

void toggleExtra(ExtrasSlot slot, Buttons &btn, Buttons &hardware, ControlConfig &controls);

void configExtra(ExtrasSlot slot, Buttons &btn, Buttons &hardware, ControlConfig &controls);

bool checkAdjustExtra(ExtrasSlot slot, Buttons &btn, bool checkConfig);

void initializeButtons(const Pins &pin, Buttons &btn,int &startUpLa, int &startUpRa);

//Take tempCalPoints and use it to generate new stick cal parameters to be used
void applyCalFromPoints(const WhichStick whichStick, float notchAngles[], const float tempCalPointsX[], const float tempCalPointsY[], NotchStatus notchStatus[], float measuredNotchAngles[], StickParams &stickParams, const ControlConfig &controls);

int readEEPROM(ControlConfig &controls, FilterGains &gains, FilterGains &normGains, StickParams &aStickParams, StickParams &cStickParams, const bool noLock = false);

void resetDefaults(HardReset reset, ControlConfig &controls, FilterGains &gains, FilterGains &normGains, StickParams &aStickParams, StickParams &cStickParams, const bool noLock = false);

void copyButtons(const Buttons &src, Buttons &dest);

void calibrationSkipMeasurement(int &currentCalStep, const WhichStick whichStick, float tempCalPointsX[], float tempCalPointsY[], NotchStatus notchStatus[], float notchAngles[], float measuredNotchAngles[], StickParams &aStickParams, StickParams &cStickParams, const ControlConfig &controls);

void calibrationUndo(int &currentCalStep, const WhichStick whichStick, NotchStatus notchStatus[]);

void calibrationAdvance(ControlConfig &controls, int &currentCalStep, const WhichStick whichStick, float tempCalPointsX[], float tempCalPointsY[], bool &undoCal, float notchAngles[], NotchStatus notchStatus[], float measuredNotchAngles[], StickParams &aStickParams, StickParams &cStickParams);

void processButtons(Pins &pin, Buttons &btn, Buttons &hardware, ControlConfig &controls, FilterGains &gains, FilterGains &normGains, int &currentCalStep, int &currentRemapStep, bool &currentlyRaw, bool &running, float tempCalPointsX[], float tempCalPointsY[], WhichStick &whichStick, NotchStatus notchStatus[], float notchAngles[], float measuredNotchAngles[], StickParams &aStickParams, StickParams &cStickParams);

void readSticks(int readA, int readC, Buttons &btn, Pins &pin, RawStick &raw, const Buttons &hardware, const ControlConfig &controls, const FilterGains &normGains, const StickParams &aStickParams, const StickParams &cStickParams, float &dT, const int currentCalStep, const bool currentlyRaw);

#endif //PHOBGCC_H

#ifndef BOARD_H
#define BOARD_H

//Uncomment to get a glowing LED on Teensy 4.
//#define ENABLE_LED

//Uncomment the appropriate #define line for your hardware by deleting the two slashes at the beginning of the line.
//#define PHOB_1_0_TEENSY_3_2             // For PhobGCC board 1.0 with Teensy 3.2
//#define PHOB_1_0_TEENSY_3_2_DIODE       // For PhobGCC board 1.0 with Teensy 3.2 and the diode shorted
//#define PHOB_1_1_TEENSY_3_2             // For PhobGCC board 1.1 with Teensy 3.2
//#define PHOB_1_1_TEENSY_3_2_DIODE       // For PhobGCC board 1.1 with Teensy 3.2 and the diode shorted
//#define PHOB_1_1_TEENSY_4_0             // For PhobGCC board 1.1 with Teensy 4.0
//#define PHOB_1_1_TEENSY_4_0_DIODE       // For PhobGCC board 1.1 with Teensy 4.0 and the diode shorted
#define PHOB_1_2_TEENSY_4_0             // For PhobGCC board 1.2.x with Teensy 4.0
//#define PHOB_PICO_PROTOBOARD            // For a protoboard with a Pico on it, used for developing for the RP2040
//#define PHOB_2_0_PICO                   // For PhobGCC Board 2.0 with RP2040



//hardware specific code defines
//teensy 3.2
#if defined(PHOB_1_0_TEENSY_3_2) || defined(PHOB_1_0_TEENSY_3_2_DIODE) || defined(PHOB_1_1_TEENSY_3_2) || defined(PHOB_1_1_TEENSY_3_2_DIODE)
#define TEENSY3_2
#endif

//teensy 4.0
#if defined(PHOB_1_1_TEENSY_4_0) || defined(PHOB_1_1_TEENSY_4_0_DIODE) || defined(PHOB_1_2_TEENSY_4_0)
#define TEENSY4_0
#endif

//half dupled
#if defined(PHOB_1_0_TEENSY_3_2_DIODE) || defined(PHOB_1_1_TEENSY_3_2_DIODE) || defined(PHOB_1_1_TEENSY_4_0_DIODE) || defined(PHOB_1_2_TEENSY_4_0)
#define HALFDUPLEX
#endif

//rumble
#if defined(PHOB_1_2_TEENSY_4_0) || defined(PHOB_2_0_PICO) || defined(PHOB_PICO_PROTOBOARD)

//protoboard has rumble and brake pins defined, but not used
#if defined(PHOB_1_2_TEENSY_4_0) || defined(PHOB_2_0_PICO)
#define RUMBLE
#endif

extern const int _pinRumble;
extern const int _pinBrake;
#endif

//use adc scale
//only set for 1.0 phob without diode
#ifdef PHOB_1_0_TEENSY_3_2
#define USEADCSCALE
#endif

//only set for picos
#if defined(PHOB_2_0_PICO) || defined(PHOB_PICO_PROTOBOARD)
#define CLEANADC

//and some pico specific vars
//GPIO SPI for ADCs
extern const int _pinSPIclk;
extern const int _pinSPItx;
extern const int _pinSPIrx;
extern const int _pinAcs;
extern const int _pinCcs;

//a little resistor ladder DAC
extern const int _pinDac0;
extern const int _pinDac1;
extern const int _pinDac2;
extern const int _pinDac3;

//this is only for the pico itself, not necessarily the phob
//two of the built-in ADCs:
extern const int _pinRadc; //ADC number
extern const int _pinLadc; //ADC number

//and four more spare connections
extern const int _pinSpare0;
extern const int _pinSpare1;
extern const int _pinSpare2;

#endif

//vars that are shared across all boards
extern const int _pinLa;
extern const int _pinRa;
extern const int _pinL;
extern const int _pinR;
extern const int _pinAx;
extern const int _pinAy;
extern const int _pinCx;
extern const int _pinCy;
extern const int _pinRX;
extern const int _pinTX;
extern const int _pinDr;
extern const int _pinDu;
extern const int _pinDl;
extern const int _pinDd;
extern const int _pinX;
extern const int _pinY;
extern const int _pinA;
extern const int _pinB;
extern const int _pinZ;
extern const int _pinS;
extern const int _pinLED;

#ifndef PICO_RP2040
#include <ADC.h>

extern const int _pinInt;

void serialSetup();

void ADCSetup(ADC * adc,
              float & ADCScale,
              float & ADCScaleFactor);
#endif //PICO_RP2040

#endif //BOARD_H

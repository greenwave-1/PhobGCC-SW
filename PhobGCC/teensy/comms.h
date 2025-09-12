#ifndef COMMS_H
#define COMMS_H

//This must be included at the end of the Teensy board header file

#include "TeensyTimerTool.h"
#include "../common/structsAndEnums.h"

#include "../common/board.h"

extern TeensyTimerTool::OneShotTimer timer1;

extern const int _originLength;
//extern volatile char _originResponse[];
extern const int _fastBaud;
extern const int _slowBaud;
extern const int _probeLength;
extern const int _pollLength;

#ifdef TEENSY3_2
const int _cmdLengthShort = 5; //number or serial bytes (2 bits per byte) in a short command - 8 bits + stopbit = 5 bytes
const int _cmdLengthLong = 13; //number or serial bytes (2 bits per byte) in a long command - 24 bits + stopbit = 13 bytes

const int _fastDivider = (((F_CPU * 2) + ((_fastBaud) >> 1)) / (_fastBaud));
const int _slowDivider = (((F_CPU * 2) + ((_slowBaud) >> 1)) / (_slowBaud));
const int _fastBDH = (_fastDivider >> 13) & 0x1F;
const int _slowBDH = (_slowDivider >> 13) & 0x1F;
const int _fastBDL = (_fastDivider >> 5) & 0xFF;
const int _slowBDL = (_slowDivider >> 5) & 0xFF;
const int _fastC4 = _fastDivider & 0x1F;
const int _slowC4 = _slowDivider & 0x1F;
extern volatile int _writeQueue;

extern const char _probeResponse[];
extern volatile char _originResponse[];
extern volatile char _commResponse[];

extern volatile char _bitCount;
extern volatile int _commStatus;
const int _commIdle = 0;
const int _commRead = 1;
const int _commPoll = 2;
const int _commWrite = 3;
#endif // TEENSY3_2

#ifdef TEENSY4_0
////Serial settings
extern bool _writing;
extern bool _waiting;
extern int _bitQueue;
extern int _waitQueue;
extern int _writeQueue;
extern uint8_t _cmdByte;
extern char _serialBuffer[128];
extern char _writeBuffer[128];
extern int _errorCount;
extern int _reportCount;

const char _probeResponse[] = {
0,0,0,0, 1,0,0,1,
0,0,0,0, 0,0,0,0,
0,0,0,0, 0,0,1,1};
extern volatile char _commResponse[];
#endif // TEENSY4_0

/*******************
	setCommResponse
	takes the values that have been put into the button struct and translates them in the serial commands ready
	to be sent to the gamecube/wii
*******************/
void setCommResponse(volatile char response[], Buttons &button);


#ifdef TEENSY4_0
#ifdef HALFDUPLEX
void resetSerial();
#endif // HALFDUPLEX
//We were using Serial2.begin() to change baudrate, but that took *waaay* too long.
void setFastBaud();

//commInt() will be called on every rising edge of a pulse that we receive
//we will check if we have the expected amount of serial data yet, if we do we will do something with it, if we don't we will do nothing and wait for the next rising edge to check again
//there are two implementations of this function, depending of if HALFDUPLEX is defined
void commInt();

#endif // TEENSY4_0


#ifdef TEENSY3_2
/*******************
	communicate
	try to communicate with the gamecube/wii
*******************/
void bitCounter();
void setSerialFast();
void resetSerial();
void communicate();
#endif // TEENSY3_2

void commsSetup(Buttons &btn);


#endif // COMMS_H

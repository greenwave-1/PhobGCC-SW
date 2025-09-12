#ifndef SETTINGS_H
#define SETTINGS_H

#include <EEPROM.h>

#include "../common/stick.h"
#include "../common/structsAndEnums.h"

//Reimplement all the functions in this header for each platform.
//Include the appropriate one in each per-board file.

namespace Eeprom {
	//index values to store data into eeprom
	extern const int _bytesPerUint8;
	extern const int _bytesPerFloat;
	extern const int _eepromAPointsX;
	extern const int _eepromAPointsY;
	extern const int _eepromCPointsX;
	extern const int _eepromCPointsY;
	extern const int _eepromxSnapback;
	extern const int _eepromySnapback;
	extern const int _eepromJump;// not used
	extern const int _eepromANotchAngles;
	extern const int _eepromCNotchAngles;
	extern const int _eepromLToggle;
	extern const int _eepromRToggle;
	extern const int _eepromcXOffset;
	extern const int _eepromcYOffset;
	extern const int _eepromxSmoothing;
	extern const int _eepromySmoothing;
	extern const int _eepromLOffset;
	extern const int _eepromROffset;
	extern const int _eepromCxSmoothing;
	extern const int _eepromCySmoothing;
	extern const int _eepromRumble;
	extern const int _eepromAutoInit;
	extern const int _eepromAxWaveshaping;
	extern const int _eepromAyWaveshaping;
	extern const int _eepromCxWaveshaping;
	extern const int _eepromCyWaveshaping;
	extern const int _eepromExtrasUp;
	extern const int _eepromExtrasDown;
	extern const int _eepromExtrasLeft;
	extern const int _eepromExtrasRight;
	extern const int _eepromSchema;
	extern const int _eepromAstickCardinalSnapping;
	extern const int _eepromCstickCardinalSnapping;
	extern const int _eepromAstickAnalogScaler;
	extern const int _eepromCstickAnalogScaler;
	extern const int _eepromTournamentToggle;
	extern const int _eepromARemap;
	extern const int _eepromBRemap;
	extern const int _eepromLRemap;
	extern const int _eepromRRemap;
	extern const int _eepromXRemap;
	extern const int _eepromYRemap;
	extern const int _eepromZRemap;
	//const int _nextSetting = _eepromZRemap+bytesPerFloat;
};

/*
JumpConfig getJumpSetting() {
	JumpConfig output;
	EEPROM.get(Eeprom::_eepromJump, output);
	return output;
};
*/

void getRemapSetting(
		uint8_t &aRemap,
		uint8_t &bRemap,
		uint8_t &lRemap,
		uint8_t &rRemap,
		uint8_t &xRemap,
		uint8_t &yRemap,
		uint8_t &zRemap);
/*
void setJumpSetting(const JumpConfig jump) {
	EEPROM.put(Eeprom::_eepromJump, jump);
};
*/

void setRemapSetting(
		const uint8_t aRemap,
		const uint8_t bRemap,
		const uint8_t lRemap,
		const uint8_t rRemap,
		const uint8_t xRemap,
		const uint8_t yRemap,
		const uint8_t zRemap);

int getLSetting();

void setLSetting(const int L);

int getRSetting();

void setRSetting(const int R);

int getLOffsetSetting();

void setLOffsetSetting(const int L);

int getROffsetSetting();

void setROffsetSetting(const int R);

int getCxOffsetSetting();

void setCxOffsetSetting(const int X);

int getCyOffsetSetting();

void setCyOffsetSetting(const int Y);

int getXSnapbackSetting();

void setXSnapbackSetting(const int X);

int getYSnapbackSetting();

void setYSnapbackSetting(const int Y);

int getXSmoothingSetting();

void setXSmoothingSetting(const int X);

int getYSmoothingSetting();

void setYSmoothingSetting(const int Y);

int getCxSmoothingSetting();

void setCxSmoothingSetting(const int X);

int getCySmoothingSetting();

void setCySmoothingSetting(const int Y);
int getRumbleSetting();

void setRumbleSetting(const int rumble);

int getAutoInitSetting();

void setAutoInitSetting(const int autoInit);

int getWaveshapingSetting(const WhichStick whichStick, const WhichAxis whichAxis);

void setWaveshapingSetting(const int waveshaping, const WhichStick whichStick, const WhichAxis whichAxis);

int getCardinalSnappingSetting(const WhichStick whichStick);

void setCardinalSnappingSetting(const int cardinalSnapping, const WhichStick whichStick);

int getAnalogScalerSetting(const WhichStick whichStick);

void setAnalogScalerSetting(const int analogScaler, const WhichStick whichStick);

int getTournamentToggleSetting();

void setTournamentToggleSetting(const int tournamentToggle);

//pulls 32 points from eeprom
void getFloatPoints(const int eepromAddress, float array[32]);

//writes 32 points to eeprom
void setFloatPoints(const int eepromAddress, const float array[32]);

void getPointsSetting(float points[32], const WhichStick whichStick, const WhichAxis whichAxis);

void setPointsSetting(const float points[32], const WhichStick whichStick, const WhichAxis whichAxis);

//pulls 16 points from eeprom
void getFloatNotches(const int eepromAddress, float array[16]);

//writes 32 points to eeprom
void setFloatNotches(const int eepromAddress, const float array[16]);

//combination getter and setter
void getNotchAnglesSetting(float angles[16], const WhichStick whichStick);

void setNotchAnglesSetting(const float angles[16], const WhichStick whichStick);

//Extras
int getExtrasSettingInt(const ExtrasSlot slot, const int offset);

void setExtrasSettingInt(const ExtrasSlot slot, const int offset, const int value);

float getExtrasSettingFloat(const ExtrasSlot slot, const int offset);

void setExtrasSettingFloat(const ExtrasSlot slot, const int offset, const float value);

int getSchemaSetting();

void setSchemaSetting(const int schema);

#endif //SETTINGS_H

// adapted from ess.h example

#ifndef EXTRAS_GTS_COMMS_H
#define EXTRAS_GTS_COMMS_H

#include "extras.h"
#include "../common/structsAndEnums.h"

namespace gts_comms {
	extern ExtrasSlot extrasGTSConfigSlot;
	
	enum GTSCommsSettings {
		GTS_COMMS_SETTING_ENABLE,
		GTS_COMMS_SETTING_UNUSED1,
		GTS_COMMS_SETTING_UNUSED2,
		GTS_COMMS_SETTING_UNUSED3
	};
	
	enum GTSCommsSettingEnable {
		GTS_COMMS_DISABLED,
		GTS_COMMS_ENABLED
	};
	
	int getSettingsLen();
	
	bool isEnabled(const IntOrFloat config[]);
	
	/*
	uint8_t *PhobSettings() {
		//int len = gts_comms_getSettingsLen();
		
		return 0;
		//return (uint8_t*) _controls;
	}
	 */
	
	bool toggle(IntOrFloat config[]);
}

#endif //EXTRAS_GTS_COMMS_H

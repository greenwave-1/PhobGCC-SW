#include "gts_comms.h"

namespace gts_comms {
	ExtrasSlot extrasGTSConfigSlot = EXTRAS_UNSET;
	
	int getSettingsLen() {
		// phob 2.0 (PICO_RP2040) has more vars in the struct
		return sizeof(ControlConfig);
		//return sizeof(_controls);
	}
	
	bool isEnabled(const IntOrFloat config[]) {
		return (config[GTS_COMMS_SETTING_ENABLE].intValue == GTS_COMMS_ENABLED);
	}
	
	bool toggle(IntOrFloat config[]) {
		int& enabled = config[GTS_COMMS_SETTING_ENABLE].intValue;
		if (enabled != GTS_COMMS_DISABLED){
			enabled = GTS_COMMS_DISABLED;
		} else {
			enabled = GTS_COMMS_ENABLED;
		}
		setExtrasSettingInt(extrasGTSConfigSlot, GTS_COMMS_SETTING_ENABLE, enabled);
		return (enabled == GTS_COMMS_ENABLED);
	}
}
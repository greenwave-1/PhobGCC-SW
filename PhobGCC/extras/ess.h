#ifndef EXTRAS_ESS_H
#define EXTRAS_ESS_H

#include "extras.h"
#include "stick.h"

namespace ess {
	/* This namespace uses GPLv3 Licensed code from Skuzee's ESS Adapter 
	 * code to reverse WiiVC mapping in Ocarina of Time. Please check out      
	 * the source for that here: https://github.com/Skuzee/ESS-Adapter 
	 */

	// ALL COMMENTS REGARDING HOW THIS WORKS HAVE BEEN REMOVED.
	// Please refer to the original code for notes. This code is
	// likely never changing unless we implement a float interpretation.

	extern ExtrasSlot extrasEssConfigSlot;

	enum EssSettings{
		ESS_SETTING_ENABLE,
		ESS_SETTING_UNUSED1,
		ESS_SETTING_UNUSED2,
		ESS_SETTING_UNUSED3
	};

	enum EssSettingEnable{
		ESS_DISABLED,
		ESS_ENABLED
	};
	
	void gc_to_n64(uint8_t coords[2]);
	
	uint16_t triangular_to_linear_index(uint8_t row, uint8_t col, uint8_t size);
	
	void invert_vc(uint8_t coords[2]);
	
	void invert_vc_gc(uint8_t coords[2]);
	
	bool remap(float* Ax, float* Ay, const IntOrFloat config[]);
	
	bool toggle(IntOrFloat config[]);
}

#endif //EXTRAS_ESS_H

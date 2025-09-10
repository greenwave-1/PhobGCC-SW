#include "extras.h"

ExtrasFunctions extrasFunctions[EXTRAS_SIZE] = {NULL};


void extrasConfigAssign(ExtrasSlot slot, ExtrasToggleFn toggleFn, ExtrasConfigFn configFn){
	switch(slot){
		case EXTRAS_UP:
			debug_println("Extra: Setting configuration to Up...");
			break;
		case EXTRAS_DOWN:
			debug_println("Extra: Setting configuration to Down...");
			break;
		case EXTRAS_LEFT:
			debug_println("Extra: Setting configuration to Left...");
			break;
		case EXTRAS_RIGHT:
			debug_println("Extra: Setting configuration to Right...");
			break;
		case EXTRAS_UNSET:
			debug_println("Extra: Configuration slot not set, feature will be inaccessible.");
			return;
		default:
			debug_println("Extra: Invalid configuration slot requested, feature will be inaccessible.");
			return;
	}
	ExtrasFunctions &fns = extrasFunctions[slot];
	if(fns.toggleFn || fns.configFn) {
		debug_println("Extra: Warning! Configuration slot was already in use, previous feature will be inaccessible.");
	}
	fns.toggleFn = toggleFn;
	fns.configFn = configFn;
}

void extrasInit() {
	/*----------------------------------------------------------
	 * Configuration slots for extras, the available options are:
	 *	- EXTRAS_UP
	 *	- EXTRAS_DOWN
	 *	- EXTRAS_LEFT
	 *	- EXTRAS_RIGHT
	 * Make sure to set the slot from EXTRAS_UNSET to one of the
	 * above for the extras below if applicable!
	 */
#ifdef EXTRAS_ESS
	//-----------------------------------------
	ess::extrasEssConfigSlot = EXTRAS_UNSET;
	//-----------------------------------------
	debug_println("Extra: Enabling ESS functionality...");
	extrasConfigAssign(ess::extrasEssConfigSlot, ess::toggle, NULL);
#endif

#ifdef EXTRAS_GTS_COMMS
	//-----------------------------------------
	gts_comms::extrasGTSConfigSlot = EXTRAS_UNSET;
	//-----------------------------------------
	debug_println("Extra: Enabling GTS Comms functionality...");
	extrasConfigAssign(gts_comms::extrasGTSConfigSlot, gts_comms::toggle, NULL);
#endif
}

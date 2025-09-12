#include "../../extras/gts_comms.h"

#ifdef PICO_RP2040
#include "storage/pages/storage.h"
#include "board.h"
#else
#include "../../common/board.h"
#endif

namespace gts_comms {
	ExtrasSlot extrasGTSConfigSlot = EXTRAS_UNSET;
	
	int getSettingsLen() {
		// phob 2.0 (PICO_RP2040) has more vars in the struct
		return sizeof(ControlConfig);
		//return sizeof(_controls);
	}
	
	// generates the response array for a given command argument.
	// we ignore the first byte in response[] since two bits are reserved for error detection
	// we do use the last 4 bits of the first byte for checksum, though.
	// max length of response[] should be 10 bytes, since _commResponse[] for teensy is set to 10
	int interpretCommandArg(uint8_t arg, uint8_t response[]) {
		// used to tell comms code how much of the array is actually the response data
		int returnLen = 1;
		
		switch (arg) {
			// 'handshake', used in gts to detect if this is actually a phob or not
			// we also identify what type of phob is present
			case 0x01:
				returnLen = 8;
				response[1] = 'P';
				response[2] = 'H';
				response[3] = 'O';
				response[4] = 'B';
				response[5] = ':';
				response[6] = ')';
				response[7] = _boardID;
				break;
			// request command, console tells us what it wants, and we prepare it. we don't send yet
			// TODO: actually figure out how this should be implemented
			case 0x02:
				// set some flag so that we can detect when we receive the second argument
				// bool waitingSecondArg = true; or something like that
				returnLen = 1;
				break;
			// request command, console now wants the data specified from 0x01. we now send that prepped data
			// TODO
			case 0x03:
				returnLen = 1;
				break;
			default:
				returnLen = 2;
				response[1] = 0xFF;
				break;
		}
		
		// make sure this is cleared before we do anything
		// this shouldn't matter, but eh
		response[0] = 0x00;
		
		// using last four bits of first byte as a 'checksum' and is ignored,
		// which is why we require "3" bytes or more to checksum
		if (returnLen > 2) {
			int checksum = 0;
			for (int i = 1; i < returnLen; i++) {
				checksum += response[i];
			}
			response[0] = checksum % 16;
		}
		
		return returnLen;
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
#ifndef EXTRAS_H
#define EXTRAS_H

#include "debug.h"
#include "structsAndEnums.h"
#include "storage/pages/storage.h"

/* Plugins and extra features outside the normal scope of
 * the PhobGCC can be found here. Uncomment each #define
 * to include the features they provide in a build then
 * set the configuration slot it uses (if it needs configuration)
 *
 */
//------------------------------------------------------
//#define EXTRAS_ESS
//#define EXTRAS_GTS_COMMS
//------------------------------------------------------

#ifdef EXTRAS_ESS
#include "ess.h"
#endif

#ifdef EXTRAS_GTS_COMMS
#include "gts_comms.h"
#endif

typedef bool(*ExtrasToggleFn)(IntOrFloat config[]);//Used for toggling extras
typedef void(*ExtrasConfigFn)(IntOrFloat config[], Cardinals dpad);//Used for configuring extras with the Dpad

struct ExtrasFunctions{
	ExtrasToggleFn toggleFn;
	ExtrasConfigFn configFn;
};

extern ExtrasFunctions extrasFunctions[EXTRAS_SIZE];

void extrasConfigAssign(ExtrasSlot slot, ExtrasToggleFn toggleFn, ExtrasConfigFn configFn);

void extrasInit();

#endif //EXTRAS_H

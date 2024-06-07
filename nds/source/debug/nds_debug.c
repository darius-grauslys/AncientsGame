#include "debug/debug.h"
#include <platform.h>

void PLATFORM_coredump(void) {
#ifndef VERBOSE
    debug_warning("PLATFORM_coredump not defined on nds, aborting instead.");
    PLATFORM_abort();
#endif
}

void PLATFORM_abort(void) {
    *(uint32_t*)8192 = 100;
}

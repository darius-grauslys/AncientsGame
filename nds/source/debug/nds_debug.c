#include "debug/debug.h"
#include "nds/arm9/console.h"
#include <platform.h>

void PLATFORM_coredump(void) {
#ifndef VERBOSE
    debug_warning("PLATFORM_coredump not defined on nds, aborting instead.");
    PLATFORM_abort();
#endif
}

void PLATFORM_abort(void) {
    // *(uint32_t*)8192 = 100;
}

//TODO: move to nds
void NDS_initialize_debug__main(void) {
#ifndef NDEBUG
    PrintConsole *console =
        consoleGetDefault();
    consoleInit(
            console,
            3,
            BgType_Text4bpp,
            BgSize_T_256x256,
            console->mapBase,
            console->gfxBase,
            true,
            true);
#endif
}
void NDS_initialize_debug__sub(void) {
#ifndef NDEBUG
    PrintConsole *console =
        consoleGetDefault();
    consoleInit(
            console,
            3,
            BgType_Text4bpp,
            BgSize_T_256x256,
            console->mapBase,
            console->gfxBase,
            false,
            true);
#endif
}

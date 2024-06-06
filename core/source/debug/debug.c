#include "nds/arm9/background.h"
#include "nds/arm9/console.h"
#include "platform.h"
#include <debug/debug.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <debug/nds_debug.h>
#include <nds.h>

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

#define VERBOSE
void debug_verbose(const char *msg_fmt, ...) {
#ifdef VERBOSE
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[37;1mverbose:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);
    
    printf("\n");
#endif
}

void debug_info(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[30;1minfo:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);
    
    printf("\n");
#endif
}

void debug_warning(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[33;1mwarning:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);
    
    printf("\n");
#endif
}

void debug_error(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[31;1merror:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);

    printf("\n");

    // create core dump, but keep going.
    PLATFORM_coredump();
#endif
}

void debug_abort(const char *msg_fmt, ...) {
#ifndef NDEBUG
    va_list args_list;
    va_start(args_list, msg_fmt);
    printf("\033[31;1mabort:\033[0m ");
    vprintf(msg_fmt, args_list);
    va_end(args_list);

    printf("\n");

    PLATFORM_abort();
#endif
}

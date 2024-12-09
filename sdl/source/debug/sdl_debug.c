#include <defines.h>
#include <stdlib.h>
#include <unistd.h>

void PLATFORM_coredump(void) {
#ifdef _WIN32
    // TODO: impl win32
#else
    if(!fork()) abort();
#endif
}

void PLATFORM_pre_abort(void) {
}

void PLATFORM_abort(void) {
    abort();
}

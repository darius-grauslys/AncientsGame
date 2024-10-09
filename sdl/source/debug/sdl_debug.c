#include <defines.h>
#include <stdlib.h>
#include <unistd.h>

void PLATFORM_coredump(void) {
    if(!fork()) abort();
}

void PLATFORM_abort(void) {
    abort();
}

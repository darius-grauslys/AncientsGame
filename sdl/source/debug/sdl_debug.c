#include <defines.h>
#include <stdlib.h>
#include <unistd.h>

void PLATFORM_coredump(void) {
    abort();
    // TODO:    replace abort() with below comment
    //          for release.
    // if(!fork()) abort();
}

void PLATFORM_abort(void) {
    abort();
}

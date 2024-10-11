#ifndef CORE_STRING_H
#define CORE_STRING_H

#include "defines_weak.h"

///
/// Same as strncpy, but returns the length of the string.
///
Index__u32 strncpy_returns__strlen(
        void *p_destination,
        const void *p_source,
        Quantity__u32 max_length_of__copy);

#endif

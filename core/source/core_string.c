#include "defines_weak.h"
#include <core_string.h>

Index__u32 strncpy_returns__strlen(
        void *p_destination,
        const void *p_source,
        Quantity__u32 max_length_of__copy) {
    u8 *p_destination__u8 = 
        (u8*)p_destination;
    u8 *p_source__u8 =
        (u8*)p_source;

    Index__u32 index_of__string = 0;
    for (;
            index_of__string < max_length_of__copy;
            index_of__string++) {
        p_destination__u8[index_of__string] =
            p_source__u8[index_of__string];
        if (!p_source__u8[index_of__string])
            break;
    }

    return index_of__string;
}

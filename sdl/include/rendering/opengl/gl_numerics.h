#ifndef GL_NUMERICS_H
#define GL_NUMERICS_H

#include <defines_weak.h>

static inline
float i32F4_to__float(i32F4 x) {
    return (float)(x >> 4)
        + (1.0 / (float)(x & MASK(4)))
        ;
}

#endif

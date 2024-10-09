#ifndef SDL_NUMERICS_H
#define SDL_NUMERICS_H

#include <sdl_defines.h>

static inline
float i32F4_to__float(i32F4 x) {
    return (float)(x >> 4)
        + ((BIT(0) & x)
            ? 0.0625f
            : 0)
        + ((BIT(1) & x)
            ? 0.125f
            : 0)
        + ((BIT(2) & x)
            ? 0.25f
            : 0)
        + ((BIT(3) & x)
            ? 0.5f
            : 0)
        ;
}

float i32F20_to__float(i32F20 x);

#endif

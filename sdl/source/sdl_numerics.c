#include "numerics.h"
#include <sdl_numerics.h>

float i32F20_to__float(i32F20 x) {
    float value = i32F20_to__i32(x);
    float contribution = 0.5f;

    for (int i=0;i<20;i++) {
        if (x & BIT(19-i))
            value += contribution;
        contribution /= 2;
    }

    return value;
}

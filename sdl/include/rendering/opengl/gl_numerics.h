#ifndef GL_NUMERICS_H
#define GL_NUMERICS_H

#include <cglm/types.h>
#include <defines.h>
#include <sdl_numerics.h>

static inline
void vector_3i32F4_to__vec3(
        Vector__3i32F4 vector__3i32F4,
        vec3 vector_xyz) {
    vector_xyz[0] = 
        i32F4_to__float(vector__3i32F4.x__i32F4);
    vector_xyz[1] = 
        i32F4_to__float(vector__3i32F4.y__i32F4);
    vector_xyz[2] = 
        i32F4_to__float(vector__3i32F4.z__i32F4);
}

#endif

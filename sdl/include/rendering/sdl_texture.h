#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include "defines_weak.h"
#include <sdl_defines.h>

void SDL_update_texture_format_and__access(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

#endif
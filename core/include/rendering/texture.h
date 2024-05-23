#ifndef TEXTURE_H
#define TEXTURE_H

#include <defines.h>

static void inline set_texture_flag__hidden(PLATFORM_Texture *texture) {
    *PLATFORM_get_texture_flags_ptr(texture) |= 
        TEXTURE_FLAG__IS_HIDDEN;
}

static bool inline is_texture_flag_set__hidden(PLATFORM_Texture *texture) {
    return *PLATFORM_get_texture_flags_ptr(texture) & TEXTURE_FLAG__IS_HIDDEN;
}

#endif

#ifndef TEXTURE_H
#define TEXTURE_H

#include <defines.h>

void PLATFORM_init_texture(PLATFORM_Texture *texture, Texture_Flags flags);

///
/// This is currently no-op on NDS. Later, if we need to,
/// we can to nitroFS along with this.
///
void PLATFORM_init_texture__with_path(PLATFORM_Texture *texture,
        Texture_Flags flags,
        const char *path);

void PLATFORM_init_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height);

void PLATFORM_update_texture(PLATFORM_Texture *texture);

void PLATFORM_use_texture(PLATFORM_Texture *texture);

void PLATFORM_release_texture(PLATFORM_Texture *texture);

uint32_t *PLATFORM_get_texture_flags_ptr(PLATFORM_Texture *texture);

static void inline set_texture_flag__hidden(PLATFORM_Texture *texture) {
    *PLATFORM_get_texture_flags_ptr(texture) |= 
        TEXTURE_FLAG__IS_HIDDEN;
}

static bool inline is_texture_flag_set__hidden(PLATFORM_Texture *texture) {
    return *PLATFORM_get_texture_flags_ptr(texture) & TEXTURE_FLAG__IS_HIDDEN;
}


#endif

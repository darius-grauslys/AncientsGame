#ifndef SPRITE_H
#define SPRITE_H

#include "defines_weak.h"
#include "platform.h"
#include "rendering/texture.h"
#include <defines.h>

void initialize_sprite_wrapper(
        Sprite_Wrapper *sprite_wrapper,
        Texture_Flags texture_flags_for__sprite);

static inline
bool is_sprite_flags__allocated(Sprite_Flags sprite_flags) {
    return (bool)(sprite_flags
            & SPRITE_FLAG__BIT_IS_ALLOCATED);
}

static inline
void set_sprite_flags_as__allocated(Sprite_Flags *p_sprite_flags) {
    *p_sprite_flags |= SPRITE_FLAG__BIT_IS_ALLOCATED;
}

static inline
void set_sprite_flags_as__deallocated(Sprite_Flags *p_sprite_flags) {
    *p_sprite_flags &= ~SPRITE_FLAG__BIT_IS_ALLOCATED;
}

#endif

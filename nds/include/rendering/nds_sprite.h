#ifndef NDS_SPRITE_H
#define NDS_SPRITE_H

#include "defines_weak.h"
#include <rendering/sprite.h>
#include <nds_defines.h>

static inline
void NDS_initialize_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Flags sprite_flags) {
    p_PLATFORM_sprite->sprite_flags = sprite_flags;
}

void NDS_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item);

void NDS_update__sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

static inline
bool NDS_is_sprite__allocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    return is_sprite_flags__allocated(p_PLATFORM_sprite->sprite_flags);
}

static inline
void NDS_set_sprite_as__allocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    set_sprite_flags_as__allocated(
            &p_PLATFORM_sprite->sprite_flags);
}

static inline
void NDS_set_sprite_as__deallocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    set_sprite_flags_as__deallocated(
            &p_PLATFORM_sprite->sprite_flags);
}

#endif

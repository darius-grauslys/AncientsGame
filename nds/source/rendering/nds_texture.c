#include "defines.h"
#include "defines_weak.h"
#include <rendering/texture.h>
#include <debug/debug.h>
#include <nds.h>
#include <nds_defines.h>

void PLATFORM_allocate_texture(
        PLATFORM_Texture *p_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    p_texture->gfx = 0;
    p_texture->width =
        p_texture->height = 0;

    Texture_Flags texture_flags =
        p_texture_allocation_specification
        ->texture_flags;

    uint8_t flags_width = 
        GET_TEXTURE_FLAG__LENGTH__WIDTH(texture_flags);
    uint8_t flags_height =
        GET_TEXTURE_FLAG__LENGTH__HEIGHT(texture_flags);

    switch (flags_width) {
        default:
            goto _abort;
        case TEXTURE_FLAG__LENGTH_x8:
            p_texture->width = 8;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_texture->height = 8;
                    p_texture->sprite_size = SpriteSize_8x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_texture->height = 16;
                    p_texture->sprite_size = SpriteSize_8x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_texture->height = 32;
                    p_texture->sprite_size = SpriteSize_8x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x16:
            p_texture->width = 16;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_texture->height = 8;
                    p_texture->sprite_size = SpriteSize_16x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_texture->height = 16;
                    p_texture->sprite_size = SpriteSize_16x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_texture->height = 32;
                    p_texture->sprite_size = SpriteSize_16x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x32:
            p_texture->width = 32;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_texture->height = 8;
                    p_texture->sprite_size = SpriteSize_32x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_texture->height = 16;
                    p_texture->sprite_size = SpriteSize_32x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_texture->height = 32;
                    p_texture->sprite_size = SpriteSize_32x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    p_texture->height = 64;
                    p_texture->sprite_size = SpriteSize_32x64;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x64:
            p_texture->width = 64;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_texture->height = 32;
                    p_texture->sprite_size = SpriteSize_64x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    p_texture->height = 64;
                    p_texture->sprite_size = SpriteSize_64x64;
                    break;
            }
            break;
    }

    switch (get_texture_flags__rendering_method(texture_flags)) {
        default:
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN:
            p_texture->oam = &oamMain;
            break;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB:
            p_texture->oam = &oamSub;
            break;
    }

	p_texture->gfx = 
        oamAllocateGfx(
                p_texture->oam, 
                p_texture->sprite_size, 
                SpriteColorFormat_256Color);
    p_texture->oam_index = 
        oamGfxPtrToOffset(
                p_texture->oam, 
                p_texture->gfx);
    oamSet(
        p_texture->oam, 
        p_texture->oam_index, 
        127 - 8, 96 - 8, 
        1, 
        0, 
        p_texture->sprite_size, 
        SpriteColorFormat_256Color, 
        0, // null gfx source to copy
        -1, 
        false, 
        false, 
        false, false, 
        false);

   p_texture->flags |=
        TEXTURE_FLAG__IS_ALLOCATED
        ;
    return;
_abort:
    debug_abort("Invalid sprite size.");
}

void PLATFORM_allocate_texture__with_path(PLATFORM_Texture *texture,
        Texture_Flags flags,
        const char *path) {
    // no-op
    debug_error("allocate_texture__with_path not defined on NDS.");
}

void PLATFORM_allocate_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {
    debug_error("allocate_texture__with_size not supported on NDS.");
}

void PLATFORM_use_texture(PLATFORM_Texture *texture) {
    // no-op
}

void PLATFORM_release_texture_with__p_PLATFORM_sprite(PLATFORM_Sprite *p_PLATFORM_sprite) {
    PLATFORM_release_texture(&p_PLATFORM_sprite->sprite_texture);
}

void PLATFORM_release_texture(PLATFORM_Texture *texture) {
    if (!CHECK_TEXTURE_FLAG__USE_OAM(texture->flags)) {
        //TODO: impl non-oam texture deallocation.
        debug_error("PLATFORM_release_texture, cannot deallocate non-oam atm.");
        return;
    }

    OamState *oam;
    if (CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(texture->flags))
        oam = &oamMain;
    else
        oam = &oamSub;

    oamFreeGfx(oam, texture->gfx);
}

uint32_t *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(PLATFORM_Texture *texture) {
    return &texture->flags;
}

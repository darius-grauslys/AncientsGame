#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/sprite.h"
#include <rendering/texture.h>
#include <debug/debug.h>
#include <nds.h>
#include <nds_defines.h>

void NDS_initialize_texture(
        PLATFORM_Texture *p_PLATFORM_texture,
        OamState *oam,
        uint16_t *gfx,
        uint16_t *gfx__readonly,
        uint32_t oam_index,
        Texture_Flags texture_flags,
        uint8_t dma_channel,
        enum NDS_Texture_Kind the_kind_of__texture) {
    texture_flags &=
        ~TEXTURE_FLAG__IS_ALLOCATED;

    p_PLATFORM_texture->gfx = 0;
    p_PLATFORM_texture->width =
        p_PLATFORM_texture->height = 0;

    p_PLATFORM_texture->oam = oam;
    p_PLATFORM_texture->gfx = gfx;
    p_PLATFORM_texture->gfx__readonly = gfx__readonly;
    p_PLATFORM_texture->oam_index = oam_index;
    p_PLATFORM_texture->the_kind_of__texture = 
        the_kind_of__texture;

    uint8_t flags_width = 
        GET_TEXTURE_FLAG__LENGTH__WIDTH(texture_flags);
    uint8_t flags_height =
        GET_TEXTURE_FLAG__LENGTH__HEIGHT(texture_flags);

    switch (flags_width) {
        default:
            goto abort__texture_size;
        case TEXTURE_FLAG__LENGTH_x8:
            p_PLATFORM_texture->width = 8;
            switch (flags_height) {
                default:
                    goto abort__texture_size;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_PLATFORM_texture->height = 8;
                    p_PLATFORM_texture->sprite_size = SpriteSize_8x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_PLATFORM_texture->height = 16;
                    p_PLATFORM_texture->sprite_size = SpriteSize_8x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_PLATFORM_texture->height = 32;
                    p_PLATFORM_texture->sprite_size = SpriteSize_8x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x16:
            p_PLATFORM_texture->width = 16;
            switch (flags_height) {
                default:
                    goto abort__texture_size;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_PLATFORM_texture->height = 8;
                    p_PLATFORM_texture->sprite_size = SpriteSize_16x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_PLATFORM_texture->height = 16;
                    p_PLATFORM_texture->sprite_size = SpriteSize_16x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_PLATFORM_texture->height = 32;
                    p_PLATFORM_texture->sprite_size = SpriteSize_16x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x32:
            p_PLATFORM_texture->width = 32;
            switch (flags_height) {
                default:
                    goto abort__texture_size;
                case TEXTURE_FLAG__LENGTH_x8:
                    p_PLATFORM_texture->height = 8;
                    p_PLATFORM_texture->sprite_size = SpriteSize_32x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    p_PLATFORM_texture->height = 16;
                    p_PLATFORM_texture->sprite_size = SpriteSize_32x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_PLATFORM_texture->height = 32;
                    p_PLATFORM_texture->sprite_size = SpriteSize_32x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    p_PLATFORM_texture->height = 64;
                    p_PLATFORM_texture->sprite_size = SpriteSize_32x64;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x64:
            p_PLATFORM_texture->width = 64;
            switch (flags_height) {
                default:
                    goto abort__texture_size;
                case TEXTURE_FLAG__LENGTH_x32:
                    p_PLATFORM_texture->height = 32;
                    p_PLATFORM_texture->sprite_size = SpriteSize_64x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    p_PLATFORM_texture->height = 64;
                    p_PLATFORM_texture->sprite_size = SpriteSize_64x64;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x128:
        case TEXTURE_FLAG__LENGTH_x256:
        case TEXTURE_FLAG__LENGTH_x512:
            if (NDS_Texture_Kind__OAM ==
                    the_kind_of__texture)
                goto abort__texture_size__too_large_for_sprite;
            texture_flags |=
                TEXTURE_FLAG__IS_ALLOCATED;
            the_kind_of__texture = NDS_Texture_Kind__Background;
            p_PLATFORM_texture->sprite_size = SpriteSize_8x8;
            switch (flags_width) {
                case TEXTURE_FLAG__LENGTH_x128:
                    p_PLATFORM_texture->width = 128;
                    break;
                case TEXTURE_FLAG__LENGTH_x256:
                    p_PLATFORM_texture->width = 256;
                    break;
                case TEXTURE_FLAG__LENGTH_x512:
                    p_PLATFORM_texture->width = 512;
                    break;
            }
            switch (flags_height) {
                default:
                    goto abort__texture_size;
                case TEXTURE_FLAG__LENGTH_x128:
                    p_PLATFORM_texture->height = 128;
                    break;
                case TEXTURE_FLAG__LENGTH_x256:
                    p_PLATFORM_texture->height = 256;
                    break;
                case TEXTURE_FLAG__LENGTH_x512:
                    p_PLATFORM_texture->height = 512;
                    break;
            }
            break;
    }

    p_PLATFORM_texture->the_kind_of__texture =
        the_kind_of__texture;
    return;
abort__texture_size:
    debug_abort("NDS_initialize_texture, invalid texture size %x",
            texture_flags & TEXTURE_FLAG__SIZE__MASK);
abort__texture_size__too_large_for_sprite:
    debug_abort("NDS_initialize_texture, texture size %x, too large for sprite.",
            texture_flags & TEXTURE_FLAG__SIZE__MASK);
}

void NDS_initialize_texture_as__empty(
        PLATFORM_Texture *p_PLATFORM_texture) {
    NDS_initialize_texture(
            p_PLATFORM_texture, 
            0, 
            0, 
            0,
            0, 
            TEXTURE_FLAG__SIZE_8x8,
            0, 
            NDS_Texture_Kind__None);
}

void PLATFORM_allocate_texture(
        PLATFORM_Texture *p_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {

    NDS_initialize_texture(
            p_texture, 
            0, 
            0, 
            0,
            0, 
            p_texture_allocation_specification
                ->texture_flags, 
            0, 
            NDS_Texture_Kind__OAM);

    p_texture->oam =
        p_texture_allocation_specification
        ->p_PLATFORM_graphics_window->p_oam_state;

    bool is_gfx__readonly =
        is_texture_flags__readonly(
            p_texture_allocation_specification
            ->texture_flags);

    uint16_t *gfx = 
        oamAllocateGfx(
                p_texture->oam, 
                p_texture->sprite_size, 
                SpriteColorFormat_256Color);

    if (is_gfx__readonly) {
        p_texture->gfx__readonly = gfx;
    } else {
        p_texture->gfx = gfx;
    }

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
    oamSetHidden(
            p_texture->oam, 
            p_texture->oam_index, 
            false);
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
    if (!texture->oam) {
        debug_abort("PLATFORM_release_texture, texture not allocated.");
        return;
    }
    oamClearSprite(
            texture->oam, 
            texture->oam_index);
    oamFreeGfx(texture->oam, texture->gfx);
    texture->oam = 0;
    texture->oam_index = -1;
    texture->gfx = 0;
}

uint32_t *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(PLATFORM_Texture *texture) {
    return &texture->flags;
}

#include <rendering/texture.h>
#include <debug/debug.h>
#include <nds.h>

void PLATFORM_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Flags flags) {
    texture->gfx = 0;
    texture->width =
        texture->height = 0;

    uint8_t flags_width = 
        GET_TEXTURE_FLAG__LENGTH__WIDTH(flags);
    uint8_t flags_height =
        GET_TEXTURE_FLAG__LENGTH__HEIGHT(flags);

    switch (flags_width) {
        default:
            goto _abort;
        case TEXTURE_FLAG__LENGTH_x8:
            texture->width = 8;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    texture->height = 8;
                    texture->sprite_size = SpriteSize_8x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    texture->sprite_size = SpriteSize_8x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    texture->sprite_size = SpriteSize_8x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x16:
            texture->width = 16;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    texture->height = 8;
                    texture->sprite_size = SpriteSize_16x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    texture->sprite_size = SpriteSize_16x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    texture->sprite_size = SpriteSize_16x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x32:
            texture->width = 32;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x8:
                    texture->height = 8;
                    texture->sprite_size = SpriteSize_32x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    texture->sprite_size = SpriteSize_32x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    texture->sprite_size = SpriteSize_32x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    texture->height = 64;
                    texture->sprite_size = SpriteSize_32x64;
                    break;
            }
            break;
        case TEXTURE_FLAG__LENGTH_x64:
            texture->width = 64;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    texture->sprite_size = SpriteSize_64x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    texture->height = 64;
                    texture->sprite_size = SpriteSize_64x64;
                    break;
            }
            break;
    }

    if (CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(flags)) {
        texture->oam = &oamMain;
    } else {
        texture->oam = &oamSub;
    }

	texture->gfx = 
        oamAllocateGfx(
                texture->oam, 
                texture->sprite_size, 
                SpriteColorFormat_256Color);
    texture->oam_index = 
        oamGfxPtrToOffset(
                texture->oam, 
                texture->gfx);
    oamSet(
        texture->oam, 
        texture->oam_index, 
        127 - 8, 96 - 8, 
        1, 
        0, 
        texture->sprite_size, 
        SpriteColorFormat_256Color, 
        0, // null gfx source to copy
        -1, 
        false, 
        false, 
        false, false, 
        false);
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

uint32_t *PLATFORM_get_texture_flags_ptr(PLATFORM_Texture *texture) {
    return &texture->flags;
}

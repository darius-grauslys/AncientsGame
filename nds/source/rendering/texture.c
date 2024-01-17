#include <rendering/texture.h>
#include <debug/debug.h>
#include <nds.h>

uint32_t current_oam_index = 0;

void PLATFORM_init_texture(PLATFORM_Texture *texture, Texture_Flags flags) {
    texture->gfx = 0;
    texture->width =
        texture->height = 0;

    uint8_t flags_width = 
        GET_TEXTURE_FLAG__LENGTH__WIDTH(flags);
    uint8_t flags_height =
        GET_TEXTURE_FLAG__LENGTH__HEIGHT(flags);

    SpriteSize sprite_size;

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
                    sprite_size = SpriteSize_8x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_8x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_8x32;
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
                    sprite_size = SpriteSize_16x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_16x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_16x32;
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
                    sprite_size = SpriteSize_32x8;
                    break;
                case TEXTURE_FLAG__LENGTH_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_32x16;
                    break;
                case TEXTURE_FLAG__LENGTH_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_32x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    texture->height = 64;
                    sprite_size = SpriteSize_32x64;
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
                    sprite_size = SpriteSize_64x32;
                    break;
                case TEXTURE_FLAG__LENGTH_x64:
                    texture->height = 64;
                    sprite_size = SpriteSize_64x64;
                    break;
            }
            break;
    }

    if (CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(flags)) {
        texture->oam = &oamMain;
    } else {
        texture->oam = &oamSub;
    }

    debug_warning("oam id setting is not robust.");
    texture->oam_index = current_oam_index;
    current_oam_index++;
	texture->gfx = oamAllocateGfx(texture->oam, sprite_size, SpriteColorFormat_256Color);

    return;
_abort:
    debug_abort("Invalid sprite size.");
}

void PLATFORM_init_texture__with_path(PLATFORM_Texture *texture,
        Texture_Flags flags,
        const char *path) {
    // no-op
    debug_error("init_texture__with_path not defined on NDS.");
}

void PLATFORM_init_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {
    debug_error("init_texture__with_size not supported on NDS.");
}

void PLATFORM_use_texture(PLATFORM_Texture *texture) {
    // no-op
}

void PLATFORM_release_texture(PLATFORM_Texture *texture) {
    if (!CHECK_TEXTURE_FLAG__USE_OAM(texture->flags))
        return;

    OamState *oam;
    if (CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(texture->flags))
        oam = &oamMain;
    else
        oam = &oamSub;

    oamFreeGfx(oam, texture->gfx);
}

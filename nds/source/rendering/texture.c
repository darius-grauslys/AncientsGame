#include <rendering/texture.h>
#include <debug/debug.h>
#include <nds.h>

/*
 *
   SpriteSize_8x8   = (OBJSIZE_8 << 14) | (OBJSHAPE_SQUARE << 12) | (8*8>>5),		//!< 8x8
   SpriteSize_16x16 = (OBJSIZE_16 << 14) | (OBJSHAPE_SQUARE << 12) | (16*16>>5),	//!< 16x16
   SpriteSize_32x32 = (OBJSIZE_32 << 14) | (OBJSHAPE_SQUARE << 12) | (32*32>>5),	//!< 32x32
   SpriteSize_64x64 = (OBJSIZE_64 << 14) | (OBJSHAPE_SQUARE << 12) | (64*64>>5),	//!< 64x64

   SpriteSize_16x8  = (OBJSIZE_8 << 14)  | (OBJSHAPE_WIDE << 12) | (16*8>>5),		//!< 16x8
   SpriteSize_32x8  = (OBJSIZE_16 << 14) | (OBJSHAPE_WIDE << 12) | (32*8>>5),		//!< 32x8
   SpriteSize_32x16 = (OBJSIZE_32 << 14) | (OBJSHAPE_WIDE << 12) | (32*16>>5),		//!< 32x16
   SpriteSize_64x32 = (OBJSIZE_64 << 14) | (OBJSHAPE_WIDE << 12) | (64*32>>5),		//!< 64x32

   SpriteSize_8x16  = (OBJSIZE_8 << 14)  | (OBJSHAPE_TALL << 12) | (8*16>>5),		//!< 8x16
   SpriteSize_8x32  = (OBJSIZE_16 << 14) | (OBJSHAPE_TALL << 12) | (8*32>>5),		//!< 8x32
   SpriteSize_16x32 = (OBJSIZE_32 << 14) | (OBJSHAPE_TALL << 12) | (16*32>>5),		//!< 16x32
   SpriteSize_32x64 = (OBJSIZE_64 << 14) | (OBJSHAPE_TALL << 12) | (32*64>>5)		//!< 32x64
 * */

void PLATFORM_init_texture(PLATFORM_Texture *texture, Texture_Flags flags) {
    texture->gfx = 0;
    texture->width =
        texture->height = 0;

    uint8_t flags_width = 
        GET_TEXTURE_FLAG__SIZE__WIDTH(flags);
    uint8_t flags_height =
        GET_TEXTURE_FLAG__SIZE__HEIGHT(flags);

    SpriteSize sprite_size;

    switch (flags_width) {
        default:
            goto _abort;
        case TEXTURE_FLAG__SIZE_x8:
            texture->width = 8;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__SIZE_x8:
                    texture->height = 8;
                    sprite_size = SpriteSize_8x8;
                    break;
                case TEXTURE_FLAG__SIZE_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_8x16;
                    break;
                case TEXTURE_FLAG__SIZE_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_8x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__SIZE_x16:
            texture->width = 16;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__SIZE_x8:
                    texture->height = 8;
                    sprite_size = SpriteSize_16x8;
                    break;
                case TEXTURE_FLAG__SIZE_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_16x16;
                    break;
                case TEXTURE_FLAG__SIZE_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_16x32;
                    break;
            }
            break;
        case TEXTURE_FLAG__SIZE_x32:
            texture->width = 32;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__SIZE_x8:
                    texture->height = 8;
                    sprite_size = SpriteSize_32x8;
                    break;
                case TEXTURE_FLAG__SIZE_x16:
                    texture->height = 16;
                    sprite_size = SpriteSize_32x16;
                    break;
                case TEXTURE_FLAG__SIZE_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_32x32;
                    break;
                case TEXTURE_FLAG__SIZE_x64:
                    texture->height = 64;
                    sprite_size = SpriteSize_32x64;
                    break;
            }
            break;
        case TEXTURE_FLAG__SIZE_x64:
            texture->width = 64;
            switch (flags_height) {
                default:
                    goto _abort;
                case TEXTURE_FLAG__SIZE_x32:
                    texture->height = 32;
                    sprite_size = SpriteSize_64x32;
                    break;
                case TEXTURE_FLAG__SIZE_x64:
                    texture->height = 64;
                    sprite_size = SpriteSize_64x64;
                    break;
            }
            break;
    }

    OamState *oam;
    if (CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(flags)) {
        oam = &oamMain;
    } else {
        oam = &oamSub;
    }

	texture->gfx = oamAllocateGfx(oam, sprite_size, SpriteColorFormat_256Color);

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

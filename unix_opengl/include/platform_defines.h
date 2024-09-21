#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

#include <stdint.h>
#include <rendering/framebuffer.h>

#define CHUNK_WIDTH__IN_TILES 8
#define CHUNK_DEPTH__IN_TILES 1

#define CHUNK_QUANTITY_OF__TILES \
    (CHUNK_WIDTH__IN_TILES * CHUNK_WIDTH__IN_TILES)

// We use a singular wrapping background.
#define LOCAL_SPACE_RENDER_WIDTH__IN_CHUNKS 0
#define LOCAL_SPACE_LOGICAL_WIDTH__IN_CHUNKS 5

//16bpx, 8 pixels per row (of 8 rows)
#define TILE_WIDTH__IN_BYTES (2 * 8)
#define TILE_WIDTH__IN_PIXELS 8

#define CHUNK_WIDTH__IN_BYTES (\
        TILE_WIDTH__IN_BYTES *\
        CHUNK_WIDTH__IN_TILES)

#define TILE_SHEET_WIDTH__IN_PIXELS 256
#define TILE_SHEET_WIDTH__IN_TILES (\
        TILE_SHEET_WIDTH__IN_PIXELS /\
        TILE_WIDTH__IN_BYTES)

#define TILE_SHEET_WIDTH__IN_BYTES (\
        TILE_WIDTH__IN_BYTES *\
        TILE_SHEET_WIDTH__IN_TILES)

typedef struct RenderTarget_t {
    Framebuffer framebuffer;
    uint32_t x, y;
} RenderTarget;

typedef struct PLATFORM_Sprite_t {

} PLATFORM_Sprite;

typedef struct PLATFORM_Texture_t {
    uint32_t handle;
    uint32_t width, height;
    uint32_t channel_count;
} PLATFORM_Texture;

#define SCENE_IDENTIFIER__QUIT -2
#define SCENE_IDENTIFIER__UNKNOWN -1
#define SCENE_IDENTIFIER__MAIN_MENU 0
#define SCENE_IDENTIFIER__SINGLE_PLAYER_MENU \
    (SCENE_IDENTIFIER__MAIN_MENU + 1)
#define SCENE_IDENTIFIER__MULTIPLAYER_MENU \
    (SCENE_IDENTIFIER__MAIN_MENU + 1)
#define SCENE_IDENTIFIER__SETTINGS_MENU \
    (SCENE_IDENTIFIER__MAIN_MENU + 1)
#define SCENE_IDENTIFIER__GAME \
    (SCENE_IDENTIFIER__MAIN_MENU + 1)
#define SCENE_IDENTIFIER__TEST \
    (SCENE_IDENTIFIER__GAME + 1)

#endif

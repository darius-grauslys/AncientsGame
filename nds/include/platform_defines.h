#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

#include <stdint.h>

/*****************************************************
 *  CHUNKS
 *****************************************************/
#define PLATFORM__CHUNKS

#define GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS 6
#define GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS 5

#define CHUNK_WIDTH__IN_TILES 8
#define CHUNK_DEPTH__IN_TILES 1

#define CHUNK_QUANTITY_OF__TILES \
    (CHUNK_WIDTH__IN_TILES * CHUNK_WIDTH__IN_TILES)

#define CHUNK__WIDTH_BIT_SHIFT 3
#define CHUNK__HEIGHT_BIT_SHIFT 3
#define CHUNK__DEPTH_BIT_SHIFT (CHUNK__WIDTH_BIT_SHIFT \
        + CHUNK__HEIGHT_BIT_SHIFT)

#define CHUNK__WIDTH (1 << CHUNK__WIDTH_BIT_SHIFT)
#define CHUNK__HEIGHT (1 << CHUNK__HEIGHT_BIT_SHIFT)
// depth is 1 until AFTER the adventure update.
#define CHUNK__DEPTH (1)

#define CHUNK__QUANTITY_OF_TILES (CHUNK__WIDTH * \
        CHUNK__HEIGHT * CHUNK__DEPTH)

#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 8
#define CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS 8
#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS \
    (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS \
    * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)

// We use a singular wrapping background.
// #define LOCAL_SPACE_RENDER_WIDTH__IN_CHUNKS 0
// #define LOCAL_SPACE_LOGICAL_WIDTH__IN_CHUNKS 5

//16bpx, 8 pixels per row (of 8 rows)
#define TILE_WIDTH__IN_BYTES (2 * 8)
#define TILE_WIDTH__IN_PIXELS 8

#define CHUNK_WIDTH__IN_BYTES (\
        TILE_WIDTH__IN_BYTES *\
        CHUNK_WIDTH__IN_TILES)

/*****************************************************
 *  ENTITIES
 *****************************************************/

#define PLATFORM__ENTITIES
#define ENTITY_MAXIMUM_QUANTITY_OF 128
#define ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS 8
#define ENTITY_MAXIMUM_QUANTITY_OF__NPCS 48
#define ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES 72

/*****************************************************
 *  TILES
 *****************************************************/

#define TILE_SHEET_WIDTH__IN_PIXELS 256
#define TILE_SHEET_WIDTH__IN_TILES (\
        TILE_SHEET_WIDTH__IN_PIXELS /\
        TILE_WIDTH__IN_BYTES)

#define TILE_SHEET_WIDTH__IN_BYTES (\
        TILE_WIDTH__IN_BYTES *\
        TILE_SHEET_WIDTH__IN_TILES)

/*****************************************************
 *  GFX_CONTEXT
 *****************************************************/

typedef struct NDS_Background_t {
    int background_index;
    uint16_t *gfx_map;
    uint16_t *gfx_tileset;
    // uint16_t *gfx_palette;
    uint32_t background__scroll_x, background__scroll_y;
    uint32_t priority;
    uint8_t map_base, tile_base;
} NDS_Background;

static void inline NDS_init_background(
        NDS_Background *background) {
    background->background_index = -1;
    background->gfx_map = 0;
    background->gfx_tileset = 0;
    background->background__scroll_x =
        background->background__scroll_y = 0;
    background->priority = 0;
    background->tile_base =
        background->map_base = 0;
}

typedef uint8_t Direction;

typedef struct NDS_Gfx_Context__Chunk_Record_t {
    int32_t x, y;
} NDS_Gfx_Context__Chunk_Record;

typedef struct PLATFORM_Gfx_Context_t {
    NDS_Background background_ground;
    NDS_Background background_ground__overlay;
    NDS_Background background_ground__sprite_cover;
    NDS_Background background_ui;
    NDS_Background background_ui__overlay;

    NDS_Gfx_Context__Chunk_Record chunk_records
        [CHUNK_MANAGER__QUANTITY_OF_CHUNKS];
} PLATFORM_Gfx_Context;

/*****************************************************
 *  TEXTURES
 *****************************************************/

typedef struct OamState OamState;

typedef struct PLATFORM_Texture_t {
    OamState *oam;
    uint16_t *gfx;
    uint32_t width, height;
    uint32_t oam_index;
    uint32_t flags;
    uint8_t dma_channel;
} PLATFORM_Texture;

#define TEXTURE_FLAG__USE_OAM__BIT_INDEX 31
#define TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX 30

#define TEXTURE_FLAGS__USE_OAM_MAIN 1
#define TEXTURE_FLAGS__USE_OAM_SUB  0

#define TEXTURE_FLAG__USE_OAM (1 << \
        TEXTURE_FLAG__USE_OAM__BIT_INDEX)
#define TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB (1 << \
        TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX)
#define CHECK_TEXTURE_FLAG__USE_OAM(flags) (flags & TEXTURE_FLAG__USE_OAM)
#define CHECK_TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB(flags) \
    (flags & TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB)

#define USE_TEXTURE_FLAGS__OAM__8x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x8 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x8))

#define USE_TEXTURE_FLAGS__OAM__8x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x8 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x16))

#define USE_TEXTURE_FLAGS__OAM__8x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x8 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x32))

#define USE_TEXTURE_FLAGS__OAM__16x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x16 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x8))

#define USE_TEXTURE_FLAGS__OAM__16x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x16 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x16))

#define USE_TEXTURE_FLAGS__OAM__16x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x16 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x32))

#define USE_TEXTURE_FLAGS__OAM__32x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x32 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x8))

#define USE_TEXTURE_FLAGS__OAM__32x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x32 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x16))

#define USE_TEXTURE_FLAGS__OAM__32x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x32 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x32))

#define USE_TEXTURE_FLAGS__OAM__32x64(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x32 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x64))

#define USE_TEXTURE_FLAGS__OAM__64x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x64 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x32))

#define USE_TEXTURE_FLAGS__OAM__64x64(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__LENGTH_x64 << TEXTURE_FLAG__LENGTH__BIT_COUNT) | \
     (TEXTURE_FLAG__LENGTH_x64))

/*****************************************************
 *  SPRITES
 *****************************************************/

#define SPRITE_PALETTE__PLAYER      0
#define SPRITE_PALETTE__SKELETON    1
#define SPRITE_PALETTE__ZOMBIE      2


typedef struct PLATFORM_Sprite_t {
    PLATFORM_Texture sprite_texture;
    const uint16_t *gfx_sprite_sheet;
} PLATFORM_Sprite;

#endif

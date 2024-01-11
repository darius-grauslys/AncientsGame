#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

#include <stdint.h>

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
    unsigned short *destination;
    uint32_t offset;
    uint32_t target_row_stride;
    uint8_t dma_channel;
} RenderTarget;

typedef struct PLATFORM_Texture_t {
    uint16_t *gfx;
    uint32_t width, height;
    uint32_t oam_index;
    uint32_t flags;
    uint8_t dma_channel;
} PLATFORM_Texture;

typedef struct PLATFORM_Sprite_t {
    PLATFORM_Texture sprite_texture;
    const uint16_t *gfx_sprite_sheet;
    uint8_t frame;
} PLATFORM_Sprite;

#define TEXTURE_FLAG__SIZE__BIT_COUNT 3
#define TEXTURE_FLAG__MASK__SIZE 0b111

#define TEXTURE_FLAG__SIZE_x8   0b000
#define TEXTURE_FLAG__SIZE_x16  0b001
#define TEXTURE_FLAG__SIZE_x32  0b010
#define TEXTURE_FLAG__SIZE_x64  0b011
#define TEXTURE_FLAG__SIZE_x128 0b100
#define TEXTURE_FLAG__SIZE_x256 0b101

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

#define GET_TEXTURE_FLAG__SIZE__WIDTH(flags) \
    ((flags & (TEXTURE_FLAG__MASK__SIZE \
              << TEXTURE_FLAG__SIZE__BIT_COUNT)) \
              >> TEXTURE_FLAG__SIZE__BIT_COUNT)

#define GET_TEXTURE_FLAG__SIZE__HEIGHT(flags) \
    (flags & TEXTURE_FLAG__MASK__SIZE)

#define USE_TEXTURE_FLAGS__OAM__8x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x8 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x8))

#define USE_TEXTURE_FLAGS__OAM__8x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x8 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x16))

#define USE_TEXTURE_FLAGS__OAM__8x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x8 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x32))

#define USE_TEXTURE_FLAGS__OAM__16x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x16 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x8))

#define USE_TEXTURE_FLAGS__OAM__16x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x16 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x16))

#define USE_TEXTURE_FLAGS__OAM__16x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x16 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x32))

#define USE_TEXTURE_FLAGS__OAM__32x8(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x32 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x8))

#define USE_TEXTURE_FLAGS__OAM__32x16(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x32 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x16))

#define USE_TEXTURE_FLAGS__OAM__32x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x32 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x32))

#define USE_TEXTURE_FLAGS__OAM__32x64(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x32 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x64))

#define USE_TEXTURE_FLAGS__OAM__64x32(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x64 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x32))

#define USE_TEXTURE_FLAGS__OAM__64x64(main_or_sub) \
    (TEXTURE_FLAG__USE_OAM | \
     (main_or_sub << \
      TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB__BIT_INDEX) | \
     (TEXTURE_FLAG__SIZE_x64 << TEXTURE_FLAG__SIZE__BIT_COUNT) | \
     (TEXTURE_FLAG__SIZE_x64))

#endif

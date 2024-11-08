#ifndef PLATFORM_DEFAULTS_H
#define PLATFORM_DEFAULTS_H

#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

#ifndef PLATFORM__IO
#define PLATFORM__IO
#define MAX_LENGTH_OF__IO_PATH 128
#endif

#ifndef PLATFORM__CAMERA
#define PLATFORM__CAMERA
#define CAMERA_FULCRUM__WIDTH 256
#define CAMERA_FULCRUM__HEIGHT 196
#endif

#ifndef PLATFORM__CHUNKS
#define PLATFORM__CHUNKS
#define GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS 4
#define GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS 3

//16bpx, 8 pixels per row (of 8 rows)
#define TILE_WIDTH__IN_BYTES (2 * 8)
#define TILE_WIDTH__IN_PIXELS 8

#define CHUNK_WIDTH__IN_TILES 8
#define CHUNK_DEPTH__IN_TILES 1

#define CHUNK_QUANTITY_OF__TILES \
    (CHUNK_WIDTH__IN_TILES * CHUNK_WIDTH__IN_TILES)

#define CHUNK__WIDTH_BIT_SHIFT 3
#define CHUNK__HEIGHT_BIT_SHIFT 3
#define CHUNK__DEPTH_BIT_SHIFT (CHUNK__WIDTH_BIT_SHIFT + CHUNK__HEIGHT_BIT_SHIFT)

#define CHUNK__WIDTH (1 << CHUNK__WIDTH_BIT_SHIFT)
#define CHUNK__HEIGHT (1 << CHUNK__HEIGHT_BIT_SHIFT)
// depth is 1 until AFTER the adventure update.
#define CHUNK__DEPTH (1)

#define CHUNK__QUANTITY_OF_TILES (CHUNK__WIDTH * \
        CHUNK__HEIGHT * CHUNK__DEPTH)

///
/// Note, both  CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
/// and         CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS
///
/// must equal one another. These two only exist to remind
/// the programmer if we are moving along COLS or ROWS.
///
/// That also means YOU should use these appropriately.
///
#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 8
#define CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS 8
#define CHUNK_MANAGER__QUANTITY_OF_CHUNKS \
    (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS \
    * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
#define CHUNK_MANAGER__QUANTITY_OF_IO_QUEUED_CHUNKS \
    CHUNK_MANAGER__QUANTITY_OF_CHUNKS \
    * 2
#endif

#ifndef PLATFORM__ENTITIES
#define PLATFORM__ENTITIES
#define ENTITY_MAXIMUM_QUANTITY_OF 128
#define ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS 8
#define ENTITY_MAXIMUM_QUANTITY_OF__NPCS 48
#define ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES 32
#define ENTITY_MAXIMUM_QUANTITY_OF__PARTICLES 40
#define ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE \
    (ENTITY_MAXIMUM_QUANTITY_OF__NPCS \
    + ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES \
    + ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS)
#endif

#define QUANTITY_OF__INPUTS 14
#ifndef PLATFORM__INPUT
#define INPUT_CODE_NONE 0
#define INPUT_CODE_FORWARD (1+0)
#define INPUT_CODE_LEFT (INPUT_CODE_FORWARD+1)
#define INPUT_CODE_RIGHT (INPUT_CODE_LEFT+1)
#define INPUT_CODE_BACKWARD (INPUT_CODE_RIGHT+1)

#define INPUT_CODE_GAME_SETTINGS (INPUT_CODE_BACKWARD+1)
#define INPUT_CODE_LOCKON (INPUT_CODE_GAME_SETTINGS+1)
#define INPUT_CODE_USE (INPUT_CODE_LOCKON+1)
#define INPUT_CODE_USE_SECONDARY (INPUT_CODE_USE+1)
#define INPUT_CODE_EXAMINE (INPUT_CODE_USE_SECONDARY+1)
#define INPUT_CODE_CONSUME (INPUT_CODE_EXAMINE+1)
#define INPUT_CODE_TURN_RIGHT (INPUT_CODE_CONSUME+1)
#define INPUT_CODE_TURN_LEFT (INPUT_CODE_TURN_RIGHT+1)
#define INPUT_CODE_CLICK (INPUT_CODE_TURN_LEFT+1)

#define INPUT_NONE 0
#define INPUT_FORWARD (1<<0)
#define INPUT_LEFT (INPUT_FORWARD<<1)
#define INPUT_RIGHT (INPUT_LEFT<<1)
#define INPUT_BACKWARD (INPUT_RIGHT<<1)

#define INPUT_GAME_SETTINGS (INPUT_BACKWARD<<1)
#define INPUT_LOCKON (INPUT_GAME_SETTINGS<<1)
#define INPUT_USE (INPUT_LOCKON<<1)
#define INPUT_USE_SECONDARY (INPUT_USE<<1)
#define INPUT_EXAMINE (INPUT_USE_SECONDARY<<1)
#define INPUT_CONSUME (INPUT_EXAMINE<<1)
#define INPUT_TURN_RIGHT (INPUT_CONSUME<<1)
#define INPUT_TURN_LEFT (INPUT_TURN_RIGHT<<1)
#define INPUT_CLICK (INPUT_TURN_LEFT<<1)
#endif

#ifndef PLATFORM__UI
#define PLATFORM__UI
// #define UI_TILE__IS_NOT__SAVING_FLAGS_TO__RAW

#define UI_TILE_MAP__SMALL__MAX_QUANTITY_OF 32
#define UI_TILE_MAP__SMALL__WIDTH 8
#define UI_TILE_MAP__SMALL__HEIGHT 8

#define UI_TILE_MAP__MEDIUM__MAX_QUANTITY_OF 16
#define UI_TILE_MAP__MEDIUM__WIDTH 16
#define UI_TILE_MAP__MEDIUM__HEIGHT 16

#define UI_TILE_MAP__LARGE__MAX_QUANTITY_OF 8
#define UI_TILE_MAP__LARGE__WIDTH 32
#define UI_TILE_MAP__LARGE__HEIGHT 32
#endif

#endif

#endif

#ifndef PLATFORM_DEFINES_H
#define PLATFORM_DEFINES_H

#include "defines_weak.h"

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
 *  INPUT
 *****************************************************/
//
// The following defines are from
// nds arm9 input
//
// typedef enum KEYPAD_BITS {
//   KEY_A      = BIT(0),  //!< Keypad A button.
//   KEY_B      = BIT(1),  //!< Keypad B button.
//   KEY_SELECT = BIT(2),  //!< Keypad SELECT button.
//   KEY_START  = BIT(3),  //!< Keypad START button.
//   KEY_RIGHT  = BIT(4),  //!< Keypad RIGHT button.
//   KEY_LEFT   = BIT(5),  //!< Keypad LEFT button.
//   KEY_UP     = BIT(6),  //!< Keypad UP button.
//   KEY_DOWN   = BIT(7),  //!< Keypad DOWN button.
//   KEY_R      = BIT(8),  //!< Right shoulder button.
//   KEY_L      = BIT(9),  //!< Left shoulder button.
//   KEY_X      = BIT(10), //!< Keypad X button.
//   KEY_Y      = BIT(11), //!< Keypad Y button.
//   KEY_TOUCH  = BIT(12), //!< Touchscreen pendown.
//   KEY_LID    = BIT(13)  //!< Lid state.
// } KEYPAD_BITS;

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

/*****************************************************
 *  TEXTURES
 *****************************************************/

//TODO: if heart/energy_orb HUD breaks, its likely because
//      the tileset got moved around. DON'T PANIC! Just change
//      the values below. TODO, make this not a problem.
//TODO: 6/27/2024, current required offset is 28 for most tiles
#define UI_TILE_SHEET_INDEX__EMPTY_HEART (Index__u16)220-23
#define UI_TILE_SHEET_INDEX__HALF_HEART (Index__u16)221-23
#define UI_TILE_SHEET_INDEX__FULL_HEART (Index__u16)222-23
#define UI_TILE_SHEET_INDEX__HALF_POISON_HEART (Index__u16)223-23
#define UI_TILE_SHEET_INDEX__FULL_POISON_HEART (Index__u16)224-23
#define UI_TILE_SHEET_INDEX__NORMAL_POISON_HEART (Index__u16)225-23
#define UI_TILE_SHEET_INDEX__HALF_IMMORTAL_HEART (Index__u16)226-23
#define UI_TILE_SHEET_INDEX__FULL_IMMORTAL_HEART (Index__u16)227-23
#define UI_TILE_SHEET_INDEX__IMMORTAL_NORMAL_HEART (Index__u16)228-23
#define UI_TILE_SHEET_INDEX__IMMORTAL_POISON_HEART (Index__u16)229-23
#define UI_TILE_SHEET_INDEX__LOCKED_HEART (Index__u16)230-23

#define UI_TILE_SHEET_INDEX__EMPTY_ENERGY_ORB (Index__u16)209-23
#define UI_TILE_SHEET_INDEX__HALF_ENERGY_ORB (Index__u16)210-23
#define UI_TILE_SHEET_INDEX__FULL_ENERGY_ORB (Index__u16)211-23
#define UI_TILE_SHEET_INDEX__HALF_POISON_ENERGY_ORB (Index__u16)212-23
#define UI_TILE_SHEET_INDEX__FULL_POISON_ENERGY_ORB (Index__u16)213-23
#define UI_TILE_SHEET_INDEX__NORMAL_POISON_ENERGY_ORB (Index__u16)214-23
#define UI_TILE_SHEET_INDEX__HALF_DEMONIC_ENERGY_ORB (Index__u16)215-23
#define UI_TILE_SHEET_INDEX__FULL_DEMONIC_ENERGY_ORB (Index__u16)216-23
#define UI_TILE_SHEET_INDEX__DEMONIC_NORMAL_ENERGY_ORB (Index__u16)217-23
#define UI_TILE_SHEET_INDEX__DEMONIC_POISON_ENERGY_ORB (Index__u16)218-23
#define UI_TILE_SHEET_INDEX__LOCKED_ENERGY_ORB (Index__u16)219-23

#define UI_TILE_SHEET_INDEX__EXTREME_FREEZING   (Index__u16)377+98 
#define UI_TILE_SHEET_INDEX__FREEZING           (Index__u16)379+102
#define UI_TILE_SHEET_INDEX__COLD               (Index__u16)385+106
#define UI_TILE_SHEET_INDEX__NEUTRAL            (Index__u16)391+110 +34+18
#define UI_TILE_SHEET_INDEX__HOT                (Index__u16)397+114
#define UI_TILE_SHEET_INDEX__BURNING            (Index__u16)403+118
#define UI_TILE_SHEET_INDEX__EXTREME_BURNING    (Index__u16)405+122
#define UI_TILE_SHEET_INDEX__DIVINE_PROVIDENCE  (Index__u16)407+122
#define UI_TILE_SHEET_INDEX__SOULFULL           (Index__u16)409+122
#define UI_TILE_SHEET_INDEX__FLEETING_SOUL      (Index__u16)411+122
#define UI_TILE_SHEET_INDEX__SOULLESS           (Index__u16)413+122
#define UI_TILE_SHEET_INDEX__LICHLING           (Index__u16)415+122
#define UI_TILE_SHEET_INDEX__LICH               (Index__u16)417+122

//sub 53
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_BLOATED (Index__u16)427
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_BLOATED (Index__u16)429
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_TOP (Index__u16)419
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_TOP (Index__u16)421
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_FULL (Index__u16)435
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_FULL (Index__u16)438
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_TOP_MIDDLE (Index__u16)447
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_TOP_MIDDLE (Index__u16)450
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_SATISFIED (Index__u16)441
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_SATISFIED (Index__u16)444
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_MIDDLE (Index__u16)465
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_MIDDLE (Index__u16)468
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_WELL (Index__u16)453
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_WELL (Index__u16)466
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_INDIFFERENT (Index__u16)459
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_INDIFFERENT (Index__u16)462
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_BOTTOM_MIDDLE \
    (Index__u16)483
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_BOTTOM_MIDDLE \
    (Index__u16)486
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_WANTING (Index__u16)471
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_WANTING (Index__u16)474
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_NEEDING (Index__u16)477
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_NEEDING (Index__u16)480
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_DESPERATE (Index__u16)431
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_DESPERATE (Index__u16)433
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_BOTTOM (Index__u16)423
#define UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_BOTTOM (Index__u16)425

#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_BLOATED (Index__u16)497+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_BLOATED (Index__u16)499+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_TOP (Index__u16)489+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_TOP (Index__u16)491+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_FULL (Index__u16)501+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_FULL (Index__u16)504+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_TOP_MIDDLE (Index__u16)517+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_TOP_MIDDLE (Index__u16)520+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_SATISFIED (Index__u16)511+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_SATISFIED (Index__u16)514+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_MIDDLE (Index__u16)535+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_MIDDLE (Index__u16)538+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_WELL (Index__u16)529+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_WELL (Index__u16)532+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_INDIFFERENT (Index__u16)529+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_INDIFFERENT (Index__u16)532+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_BOTTOM_MIDDLE \
    (Index__u16)553+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_BOTTOM_MIDDLE \
    (Index__u16)556+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_WANTING (Index__u16)535+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_WANTING (Index__u16)538+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_NEEDING (Index__u16)547+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_NEEDING (Index__u16)550+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_DESPERATE (Index__u16)501+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_DESPERATE (Index__u16)503+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_BOTTOM (Index__u16)493+93+82
#define UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_BOTTOM (Index__u16)495+93+82

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

#define MAX_QUANTITY_OF__SPRITES 256

#define SPRITE_PALETTE__PLAYER      0
#define SPRITE_PALETTE__SKELETON    1
#define SPRITE_PALETTE__ZOMBIE      2

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

/*****************************************************
 *  SDL
 *****************************************************/

typedef union SDL_Event SDL_Event;

typedef void (*f_SDL_Event_Handler)(
        Game *p_game,
        SDL_Event *p_event);

#define TEXTURE_FLAG__FORMAT__RGB888 \
    TEXTURE_FLAG__FORMAT__1
#define TEXTURE_FLAG__FORMAT__RGBA8888 \
    TEXTURE_FLAG__FORMAT__2

#endif

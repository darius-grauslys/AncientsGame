#ifndef PLATFORM_H
#define PLATFORM_H

#include <defines_weak.h>

///
/// This file contains all function signatures
/// which are NOT implemented in core.
///
/// Their implementation is platform dependent
/// and will be implemented by a backend such
/// as OpenGL, or nds.
///
/// -- HOW TO MAKE YOUR OWN BACKEND IMPLEMENTATION --
/// Create a header file at the base directory of your
/// include folder named "platform_defines.h"
///
/// Here you will define all your PLATFORM_*** structs.
/// Define the PLATFORM_*** functions whenever you want
/// but try to be organized about it.
///
/// NOTE: there are some PLATFORM specific macros
/// which should be considered. Search for 
/// SECTION_defines. PLATFORM__*** is a series of
/// macros which should be defined in the backend.
///
/// Defaults are provided, but are not always optimal
/// for every platform.

///
/// SECTION_debug
///

void PLATFORM_coredump(void);
void PLATFORM_abort(void);

///
/// SECTION_entity
///
void PLATFORM_render_entity(
        Entity *entity,
        Vector__3i32F4 camera_position__3i32F4,
        Game *game);

///
/// SECTION_game_actions
///

void m_PLATFORM_game_action_handler_for__multiplayer(
        Game *p_this_game,
        Game_Action *p_game_action);

///
/// SECTION_rendering
///
void PLATFORM_initialize_gfx_context(PLATFORM_Gfx_Context *gfx_context);

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__menu(PLATFORM_Gfx_Context *gfx_context);
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__game(PLATFORM_Gfx_Context *gfx_context);

void PLATFORM_allocate_texture(PLATFORM_Texture *texture, Texture_Flags flags);

///
/// This is currently no-op on NDS. Later, if we need to,
/// we can to nitroFS along with this.
///
void PLATFORM_allocate_texture__with_path(PLATFORM_Texture *texture,
        Texture_Flags flags,
        const char *path);

void PLATFORM_allocate_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height);

void PLATFORM_update_texture(PLATFORM_Texture *texture);

void PLATFORM_use_texture(PLATFORM_Texture *texture);

void PLATFORM_release_texture(PLATFORM_Texture *texture);
void PLATFORM_release_texture_with__p_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

uint32_t *PLATFORM_get_texture_flags_ptr(PLATFORM_Texture *texture);

///
/// SECTION_world
///

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk);

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile);

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager);

typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;
void PLATFORM_initialize_sprite(PLATFORM_Sprite *sprite,
        Texture_Flags texture_flags_for__sprite,
        bool perform_update);
void PLATFORM_initialize_sprite_for__entity(Entity *entity);

void PLATFORM_render_sprite(Sprite_Wrapper *sprite);

void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper);

///
/// SECTION_core
///

void PLATFORM_pre_render(Game *game);

void PLATFORM_post_render(Game *game);

/// 
/// SECTION_ui
///

///
/// SECTION_scene
///

void PLATFORM_establish_scenes(Scene_Manager *p_scene_manager);

///
/// SECTION_input
///
void PLATFORM_poll_input(Input *p_input);

/// 
/// SECTION_defines
///
typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture_t;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

#include <platform_defines.h>

#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif

#ifndef PLATFORM__CHUNKS
#define GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS 4
#define GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS 3

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
#endif

#ifndef PLATFORM__ENTITIES
#define ENTITY_MAXIMUM_QUANTITY_OF 128
#define ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS 8
#define ENTITY_MAXIMUM_QUANTITY_OF__NPCS 48
#define ENTITY_MAXIMUM_QUANTITY_OF__PROJECTILES 72
#endif

#define ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE \
    (ENTITY_MAXIMUM_QUANTITY_OF__NPCS \
    + ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS)

#include <stdint.h>
#include <stdbool.h>

#ifndef PLATFORM__INPUT
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

#endif

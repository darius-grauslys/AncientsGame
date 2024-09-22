#include <defines.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

///
/// SECTION_debug
///

void PLATFORM_coredump(void) {
    if (!fork()) { abort(); }
}
void PLATFORM_abort(void) {
    abort();
}

///
/// SECTION_entity
///
void PLATFORM_render_entity(
        Entity *entity,
        Game *game) {}

///
/// SECTION_game_actions
///

void m_PLATFORM_game_action_handler_for__multiplayer(
        Game *p_this_game,
        Game_Action *p_game_action) {}

///
/// SECTION_rendering
///

PLATFORM_Graphics_Window 
*PLATFORM_get_p_graphics_window_with__graphics_window_kind(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Graphics_Window_Kind the_kind_of__graphics_window,
        Identifier__u32 identifier_of__graphics_window) {}

PLATFORM_Gfx_Context *PLATFORM_get_p_gfx_context_from__graphics_window(
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {}

void PLATFORM_put_char_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        unsigned char letter) {}

///
/// Opens the specified UI. Depending on the backend this
/// might close all other UI's.
///
void PLATFORM_open_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open) {}

///
/// Closes the specified UI. Depending on the backend this
/// might cause a UI window to open. For example, on NDS
/// this will close the specified UI Window, and transition
/// to the UI Idle window.
///
void PLATFORM_close_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__close) {}

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void) {}
Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer) {}

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {}

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Allocation_Specification *p_sprite_allocation_specification) {}

void PLATFORM_release_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite) {}

void PLATFORM_release_all__sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {}

void PLATFORM_release_all__sprites_using__this_graphics_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {}

void PLATFORM_render_sprite(Sprite_Wrapper *sprite) {}

void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper) {}

void PLATFORM_update_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {}
void PLATFORM_set_sprite__position(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u16 x, Index__u16 y) {}

Quantity__u32 PLATFORM_get_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {}

Quantity__u32 PLATFORM_get_max_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {}

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__menu(PLATFORM_Gfx_Context *gfx_context) {}
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__game(PLATFORM_Gfx_Context *gfx_context) {}

void PLATFORM_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {}

///
/// This is currently no-op on NDS. Later, if we need to,
/// we can to nitroFS along with this.
///
void PLATFORM_allocate_texture__with_path(PLATFORM_Texture *texture,
        Texture_Allocation_Specification
            *p_texture_allocation_specification,
        const char *path) {}

void PLATFORM_allocate_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {}

void PLATFORM_update_texture(PLATFORM_Texture *texture) {}

void PLATFORM_use_texture(PLATFORM_Texture *texture) {}

void PLATFORM_release_texture(PLATFORM_Texture *texture) {}
void PLATFORM_release_texture_with__p_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {}

Texture_Flags *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
        PLATFORM_Texture *texture) {}

Quantity__u32 PLATFORM_get_max_quantity_of__allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {}

Quantity__u32 PLATFORM_get_quantity_of__available_allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {}

bool PLATFORM_has_support_for__texture_flag__render_method(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {}

///
/// SECTION_world
///

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk) {}

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile) {}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager) {}

///
/// SECTION_core
///

int PLATFORM_main(Game *p_game) {}

void PLATFORM_pre_render(Game *game) {}

void PLATFORM_post_render(Game *game) {}

/// 
/// SECTION_ui
///

///
/// SECTION_scene
///

///
/// SECTION_input
///
void PLATFORM_poll_input(Input *p_input) {}

/// 
/// SECTION_defines
///

#include <platform_defines.h>

#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif

#ifndef PLATFORM__CAMERA
#define CAMERA_FULCRUM__WIDTH 256
#define CAMERA_FULCRUM__HEIGHT 196
#endif

#ifndef PLATFORM__CHUNKS
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


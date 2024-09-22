///
/// !!THIS FILE IS TO BE REMOVED COMPLETELY IN THE FUTURE!!
///

///
/// We are temporarily storing platform specific definitions here.
/// Specifically those which are not yet implemented in the SDL
/// backend.
///

#include "defines_weak.h"
#include <platform.h>

///
/// SECTION_audio
///

void PLATFORM_initialize_audio(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {}

/// 
/// Returns false if fails to allocate audio effect.
///
Audio_Effect *PLATFORM_allocate_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    return 0;
}

void PLATFORM_play_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        Audio_Effect *p_audio_effect) {}

void PLATFORM_poll_audio_effects(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {}

void PLATFORM_play_audio__stream(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Stream_Kind the_kind_of__audio_stream) {}

bool PLATFORM_is_audio__streaming(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context) {
    return false;
}

///
/// SECTION_debug
///

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
        Identifier__u32 identifier_of__graphics_window) {
    return 0;
}

PLATFORM_Gfx_Context *PLATFORM_get_p_gfx_context_from__graphics_window(
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    return 0;
}

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

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void) {
    return UI_Window_Kind__None;
}
Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer) {
    return 0;
}

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return 0;
}

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
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 0;
}

Quantity__u32 PLATFORM_get_max_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 0;
}

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__menu(PLATFORM_Gfx_Context *gfx_context) {}
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__game(PLATFORM_Gfx_Context *gfx_context) {}

void PLATFORM_allocate_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {}

void PLATFORM_update_texture(PLATFORM_Texture *texture) {}

void PLATFORM_release_texture_with__p_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {}

Texture_Flags *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
        PLATFORM_Texture *texture) {}

Quantity__u32 PLATFORM_get_max_quantity_of__allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    return 0;
}

Quantity__u32 PLATFORM_get_quantity_of__available_allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    return 0;
}

bool PLATFORM_has_support_for__texture_flag__render_method(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    return false;
}

///
/// SECTION_world
///

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk) {}

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile) {}

void PLATFORM_update_chunk(
        PLATFORM_Gfx_Context *p_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager) {}

///
/// SECTION_core
///

// int abs(int x) {}
// void srand(unsigned int seed) {}
// int rand(void) {}

/// 
/// SECTION_ui
///

///
/// SECTION_scene
///

///
/// SECTION_serialization
///

void PLATFORM_initialize_file_system_context(
        Game *p_game,
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context) {}

Serialization_Request *PLATFORM_allocate_serialization_request(
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context) {
    return 0;
}

void PLATFORM_release_serialization_request(
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context,
        Serialization_Request *p_serialization_request) {}

enum PLATFORM_Open_File_Error PLATFORM_open_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        const char *p_path,
        const char *p_flags,
        Serialization_Request *p_serialization_request) {
    return PLATFORM_Open_File_Error__Unknown;
}

void PLATFORM_close_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        Serialization_Request *p_serialization_request) {}

enum PLATFORM_Write_File_Error PLATFORM_write_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *source,
        Quantity__u32 length_of__data,
        Quantity__u32 quantity_of__writes,
        void *p_file_handler) {
    return PLATFORM_Write_File_Error__Unknown;
}

enum PLATFORM_Read_File_Error PLATFORM_read_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *destination,
        Quantity__u32 *p_length_of__data_to_read,
        Quantity__u32 quantity_of__reads,
        void *p_file_handler) {
    return PLATFORM_Read_File_Error__Unknown;
}

///
/// Returns -1 on error.
///
Index__u32 PLATFORM_get_position_in__file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        void *p_file_handler) {
    return -1;
}

bool PLATFORM_set_position_in__file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        Index__u32 position_in__file_u32,
        void *p_file_handler) {
    return false;
}

///
/// SECTION_input
///

///
/// SECTION_inventory
///

///
/// SECTION_log
///
bool PLATFORM_update_log__global(Game *p_game) {}
bool PLATFORM_update_log__local(Game *p_game) {}
bool PLATFORM_update_log__system(Game *p_game) {}

bool PLATFORM_clear_log__global(Game *p_game) {}
bool PLATFORM_clear_log__local(Game *p_game) {}
bool PLATFORM_clear_log__system(Game *p_game) {}

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

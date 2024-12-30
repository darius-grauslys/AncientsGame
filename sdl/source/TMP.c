///
/// !!THIS FILE IS TO BE REMOVED COMPLETELY IN THE FUTURE!!
///

///
/// We are temporarily storing platform specific definitions here.
/// Specifically those which are not yet implemented in the SDL
/// backend.
///

#include "defines_weak.h"
#include "game.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_window.h"
#include "sdl_defines.h"
#include "rendering/texture.h"

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
/// SECTION_game_actions
///

void m_PLATFORM_game_action_handler_for__multiplayer(
        Game *p_this_game,
        Game_Action *p_game_action) {}

///
/// SECTION_rendering
///

PLATFORM_Texture *PLATFORM_allocate_texture__TMP(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    return 0;
}

PLATFORM_Texture *PLATFORM_allocate_texture_with__path__TMP(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags,
        const char *c_str__path) {
    return 0;
}

PLATFORM_Graphics_Window 
*PLATFORM_get_p_graphics_window_with__graphics_window_kind(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Graphics_Window_Kind the_kind_of__graphics_window,
        Identifier__u32 identifier_of__graphics_window) {
    return 0;
}

void PLATFORM_put_char_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        unsigned char letter) {}

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return 0;
}

void PLATFORM_release_all__sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {}

void PLATFORM_release_all__sprites_using__this_graphics_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {}

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

void PLATFORM_allocate_texture__with_size(PLATFORM_Texture *texture, 
        Texture_Flags flags,
        uint32_t width, uint32_t height) {}

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

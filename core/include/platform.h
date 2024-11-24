#ifndef PLATFORM_H
#define PLATFORM_H

#include "platform_defines.h"
#ifndef PLATFORM_DEFINES_H
#error Cannot build AncientsGame without a backend implementation.
#endif

#include "platform_defaults.h"

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
/// SECTION_audio
///

void PLATFORM_initialize_audio(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context);

/// 
/// Returns false if fails to allocate audio effect.
///
Audio_Effect *PLATFORM_allocate_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context);

void PLATFORM_play_audio_effect(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        Audio_Effect *p_audio_effect);

void PLATFORM_poll_audio_effects(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context);

void PLATFORM_play_audio__stream(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context,
        enum Audio_Stream_Kind the_kind_of__audio_stream);

bool PLATFORM_is_audio__streaming(
        PLATFORM_Audio_Context *p_PLATFORM_audio_context);

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

PLATFORM_Graphics_Window 
*PLATFORM_get_p_graphics_window_with__graphics_window_kind(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Graphics_Window_Kind the_kind_of__graphics_window,
        Identifier__u32 identifier_of__graphics_window);

PLATFORM_Gfx_Context *PLATFORM_get_p_gfx_context_from__graphics_window(
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window);

void PLATFORM_put_char_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        unsigned char letter);

///
/// Opens the specified UI. Depending on the backend this
/// might close all other UI's.
///
/// p_game_action can be null, this however might cause
/// the ui to fail in opening depending on the ui and
/// it's implementation. It's recommended to keep a COPY
/// of p_game_action in PLATFORM_Graphics_Window.
///
/// TODO: backend impl note
/// If you are implementing a backend, its recommended to
/// store this copy in PLATFORM_Graphics_Window.
///
void PLATFORM_open_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open,
        Game_Action *p_game_action);

///
/// TODO: this will be called on game_action
///
void PLATFORM_refresh_ui(
        Game *p_game,
        UI_Window_Kind the_kind_of__ui_window_to__refresh);

///
/// Closes the specified UI. Depending on the backend this
/// might cause a UI window to open. For example, on NDS
/// this will close the specified UI Window, and transition
/// to the UI Idle window.
///
void PLATFORM_close_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__close);

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void);
Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer);

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Allocation_Specification *p_sprite_allocation_specification);

void PLATFORM_release_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);

void PLATFORM_release_all__sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

void PLATFORM_release_all__sprites_using__this_graphics_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window);

void PLATFORM_render_sprite(Sprite_Wrapper *sprite);

void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper);

void PLATFORM_update_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);
void PLATFORM_set_sprite__position(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u16 x, Index__u16 y);

Quantity__u32 PLATFORM_get_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

Quantity__u32 PLATFORM_get_max_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__menu(PLATFORM_Gfx_Context *gfx_context);
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_initialize_rendering__game(PLATFORM_Gfx_Context *gfx_context);

PLATFORM_Texture *PLATFORM_allocate_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

///
/// This is currently no-op on NDS. Later, if we need to,
/// we can to nitroFS along with this.
///
PLATFORM_Texture *PLATFORM_allocate_texture__with_path(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification,
        const char *path);

void PLATFORM_update_texture(
        PLATFORM_Texture *texture);

void PLATFORM_use_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Texture *texture);

void PLATFORM_release_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Texture *texture);

Texture_Flags *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
        PLATFORM_Texture *texture);

Quantity__u32 PLATFORM_get_max_quantity_of__allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags);

Quantity__u32 PLATFORM_get_quantity_of__available_allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags);

bool PLATFORM_has_support_for__texture_flag__render_method(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags);

///
/// SECTION_world
///

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile);

void PLATFORM_update_chunk(
        PLATFORM_Gfx_Context *p_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager);

///
/// SECTION_core
///

int abs(int x);
void srand(unsigned int seed);
int rand(void);

int PLATFORM_main(Game *p_game);

void PLATFORM_pre_render(Game *game);

void PLATFORM_post_render(Game *game);

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
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context);

void PLATFORM_append_base_directory_to__path(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        char *p_c_str_path,
        Index__u32 *p_index_of__path_end);

enum PLATFORM_Open_File_Error {
    PLATFORM_Open_File_Error__None = 0,
    PLATFORM_Open_File_Error__Invalid_Path = 1,
    PLATFORM_Open_File_Error__File_Not_Found = 2,
    PLATFORM_Open_File_Error__Unknown,
};

enum PLATFORM_Write_File_Error {
    PLATFORM_Write_File_Error__None = 0,
    PLATFORM_Write_File_Error__Max_Size_Reached = 1,
    PLATFORM_Write_File_Error__Unknown
};

enum PLATFORM_Read_File_Error {
    PLATFORM_Read_File_Error__None = 0,
    PLATFORM_Read_File_Error__End_Of_File = 1,
    PLATFORM_Read_File_Error__Unknown
};

Serialization_Request *PLATFORM_allocate_serialization_request(
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context);

void PLATFORM_release_serialization_request(
        PLATFORM_File_System_Context *p_PLATOFRM_file_system_context,
        Serialization_Request *p_serialization_request);

enum PLATFORM_Open_File_Error PLATFORM_open_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        const char *p_path,
        const char *p_flags,
        Serialization_Request *p_serialization_request);

void PLATFORM_close_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        Serialization_Request *p_serialization_request);

enum PLATFORM_Write_File_Error PLATFORM_write_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *source,
        Quantity__u32 length_of__data,
        Quantity__u32 quantity_of__writes,
        void *p_file_handler);

enum PLATFORM_Read_File_Error PLATFORM_read_file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        u8 *destination,
        Quantity__u32 *p_length_of__data_to_read,
        Quantity__u32 quantity_of__reads,
        void *p_file_handler);

///
/// Returns -1 on error.
///
Index__u32 PLATFORM_get_position_in__file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        void *p_file_handler);

bool PLATFORM_set_position_in__file(
        PLATFORM_File_System_Context *p_PLATFORM_file_system_context,
        Index__u32 position_in__file_u32,
        void *p_file_handler);

///
/// SECTION_input
///
void PLATFORM_poll_input(Input *p_input);

///
/// SECTION_inventory
///

///
/// SECTION_log
///
bool PLATFORM_update_log__global(Game *p_game);
bool PLATFORM_update_log__local(Game *p_game);
bool PLATFORM_update_log__system(Game *p_game);

bool PLATFORM_clear_log__global(Game *p_game);
bool PLATFORM_clear_log__local(Game *p_game);
bool PLATFORM_clear_log__system(Game *p_game);

/// 
/// SECTION_defines
///
typedef struct PLATFORM_Gfx_Context_t PLATFORM_Gfx_Context;
typedef struct PLATFORM_Texture_t PLATFORM_Texture_t;
typedef struct PLATFORM_Sprite_t PLATFORM_Sprite;

typedef char IO_path[MAX_LENGTH_OF__IO_PATH];

#endif

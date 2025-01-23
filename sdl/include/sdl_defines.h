#ifndef SDL_DEFINES_H
#define SDL_DEFINES_H

#include "defines_weak.h"
#include <defines.h>
#include <SDL2/SDL_render.h>
#include <platform_defines.h>

#define TO_STRING(x) #x
#define TO_STRING_EXPANDED(x) TO_STRING(x)

#ifndef NDEBUG
#define SDL_ASSERT_HOOK_NULL(\
        callee,\
        p_PLATFORM_gfx_context,\
        f_hook)\
        (!p_PLATFORM_gfx_context\
                ->SDL_gfx_sub_context__wrapper\
                .f_hook)

#define SDL_DEBUG_ABORT_IF__HOOK_NULL(\
        callee,\
        p_PLATFORM_gfx_context,\
        f_hook)\
        if SDL_ASSERT_HOOK_NULL(callee, p_PLATFORM_gfx_context, f_hook) {\
            debug_warning("Did you forget to initialize a SDL graphics backend?");\
            debug_abort("SDL::" TO_STRING_EXPANDED(callee) ", " TO_STRING_EXPANDED(f_hook) " == 0.");\
            return;\
        }
#else
#define SDL_ASSERT_HOOK_NULL(\
        callee,\
        p_PLATFORM_gfx_context,\
        f_hook)

#define SDL_DEBUG_ABORT_IF__HOOK_NULL(\
        callee,\
        p_PLATFORM_gfx_context,\
        f_hook)
#endif


typedef union SDL_Event SDL_Event;

typedef void (*f_SDL_Event_Handler)(
        Game *p_game,
        SDL_Event *p_event);


typedef u32 SDL_Texture_Format__u32;
typedef u32 GL_Texture_Handle__u32;

#define MAX_LENGTH_OF__SDL_TEXTURE_STRING 32
typedef char Texture_String[
    MAX_LENGTH_OF__SDL_TEXTURE_STRING];
typedef const char SDL_Texture_String__Const[
    MAX_LENGTH_OF__SDL_TEXTURE_STRING];

typedef enum SDL_Texture_Access_Kind {
    SDL_Texture_Access_Kind__None,
    SDL_Texture_Access_Kind__Static,
    SDL_Texture_Access_Kind__Streaming,
    SDL_Texture_Access_Kind__Target,
    SDL_Texture_Access_Kind__Unknown,
} SDL_Texture_Access_Kind;

typedef struct PLATFORM_Texture_t {
    Texture_String SDL_texture_string;
    union {
        GL_Texture_Handle__u32 GL_texture_handle;
    };
    Texture_Flags texture_flags;
    SDL_Texture_Format__u32 SDL_texture_format__u32;
    SDL_Texture_Access_Kind SDL_texture_access;
    Quantity__u16 width;
    Quantity__u16 height;
} PLATFORM_Texture;

typedef struct PLATFORM_Graphics_Window_t {
#warning TODO: remove ui_associated game action here.
    Game_Action associated_game_action;
    PLATFORM_Texture *p_SDL_graphics_window__texture;
    void *p_SDL_graphics_window__data;
    UI_Tile_Map__Wrapper SDL_graphics_window__ui_tile_map__wrapper;
    Vector__3i32F4 SDL_position_of__graphics_window;
    Vector__3i32F4 SDL_origin_of__graphics_window;
    bool is_allocated;
} PLATFORM_Graphics_Window;

typedef struct SDL_Gfx_Window_Mananger_t {
    PLATFORM_Graphics_Window SDL_gfx_windows[
        PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF];
} SDL_Gfx_Window_Manager;

typedef void SDL_Gfx_Sub_Context;

typedef union SDL_Event SDL_Event;
typedef void (*f_SDL_Event_Handler)(
        Game *p_game,
        SDL_Event *p_event);

///
/// After SDL handles input, give backend
/// a chance to if needed.
///
typedef void (*f_SDL_Process_Input)(
        Game *p_game,
        Input *p_input);

typedef void (*f_SDL_Initialize_Rendering__Worldspace)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

typedef void (*f_SDL_Allocate_Gfx_Window)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        Texture_Flags texture_flags);
typedef void (*f_SDL_Release_Gfx_Window)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window);

typedef void (*f_SDL_Compose_Gfx_Window)(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world);
typedef void (*f_SDL_Render_Gfx_Window)(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world);

typedef PLATFORM_Texture *(*f_SDL_Allocate_Texture)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags);

typedef PLATFORM_Texture *(*f_SDL_Allocate_Texture__With_Path)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags,
        const char *path);

typedef void (*f_SDL_Use_Texture)(
        PLATFORM_Texture *p_PLATFORM_texture);

typedef void (*f_SDL_Release_Texture)(
        PLATFORM_Texture *p_PLATFORM_texture);

typedef void (*f_SDL_Allocate_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);

typedef void (*f_SDL_Initialize_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);

typedef void (*f_SDL_Render_Sprite)(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        Vector__3i32F4 position_of__sprite__3i32F4);

typedef void (*f_SDL_Release_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);




typedef void (*f_SDL_Render_Entity)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Entity *p_entity);




typedef void (*f_SDL_Render_Chunk)(
        Gfx_Context *p_PLATFORM_gfx_context,
        Graphics_Window *p_PLATFORM_gfx_window,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

typedef void (*f_SDL_Update_Chunk)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

typedef void (*f_SDL_Update_Chunks)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager);




typedef void (*f_SDL_Clear_Screen)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

typedef void (*f_SDL_Allocate_Camera_Data)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

typedef void (*f_SDL_Release_Camera_Data)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

typedef void (*m_SDL_Render_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper);

typedef struct PLATFORM_Sprite_t {
    /// 
    /// This is agnostic to render backend.
    ///
    void *p_SDL_sprite;
    PLATFORM_Texture *p_PLATFORM_texture;
    Quantity__u8 quantity_of__sprite_frame__columns;
    Quantity__u8 quantity_of__sprite_frame__rows;
    float sprite_frame__width;
    float sprite_frame__height;
    bool is_sprite__allocated;
    bool is_sprite_with__anonymous_texture;
} PLATFORM_Sprite;

typedef struct SLD_Texture_Manager_t {
    PLATFORM_Texture SDL_textures[
        MAX_QUANTITY_OF__TEXTURES];
} SDL_Texture_Manager;

typedef struct SDL_Sprite_Manager_t {
    PLATFORM_Sprite SDL_sprites[MAX_QUANTITY_OF__SPRITES];
} SDL_Sprite_Manager;

typedef enum {
    SDL_Gfx_Sub_Context__None,
    SDL_Gfx_Sub_Context__OpenGL_1_2,
    SDL_Gfx_Sub_Context__OpenGL_3_0,
    SDL_Gfx_Sub_Context__Vulcan //TODO: not impl'd
} SDL_Gfx_Sub_Context__Kind;

typedef struct SDL_Gfx_Sub_Context__Wrapper_t {
    SDL_Gfx_Sub_Context__Kind           the_kind_of__sub_context;
    SDL_Sprite_Manager                  SDL_sprite_manager;
    SDL_Texture_Manager                 SDL_texture_manager;
    void                                *p_SDL_gfx_sub_context;

    f_SDL_Process_Input                 f_SDL_process_input;

    f_SDL_Initialize_Rendering__Worldspace
                                        f_SDL_initialize_rendering__worldspace;

    f_SDL_Allocate_Gfx_Window           f_SDL_allocate_gfx_window;
    f_SDL_Release_Gfx_Window            f_SDL_release_gfx_window;
    f_SDL_Compose_Gfx_Window            f_SDL_compose_gfx_window;
    f_SDL_Render_Gfx_Window             f_SDL_render_gfx_window;

    f_SDL_Clear_Screen                  f_SDL_clear_screen;

    f_SDL_Allocate_Camera_Data          f_SDL_allocate_camera_data;
    f_SDL_Release_Camera_Data           f_SDL_release_camera_data;

    f_SDL_Allocate_Texture              f_SDL_allocate_texture;
    f_SDL_Allocate_Texture__With_Path   f_SDL_allocate_texture_with__path;
    f_SDL_Use_Texture                   f_SDL_use_texture;
    f_SDL_Release_Texture               f_SDL_release_texture;

    f_SDL_Allocate_Sprite               f_SDL_allocate_sprite;
    f_SDL_Initialize_Sprite             f_SDL_initialize_sprite;
    f_SDL_Render_Sprite                 f_SDL_render_sprite;
    f_SDL_Release_Sprite                f_SDL_release_sprite;

    f_SDL_Render_Entity                 f_SDL_render_entity;

    f_SDL_Render_Chunk                  f_SDL_render_chunk;
    f_SDL_Update_Chunk                  f_SDL_update_chunk;
    f_SDL_Update_Chunks                 f_SDL_update_chunks;

} SDL_Gfx_Sub_Context__Wrapper;

typedef struct PLATFORM_Gfx_Context_t {
    UI_Tile_Map_Manager SDL_ui_tile_map_manager;

    SDL_Gfx_Window_Manager SDL_gfx_window_manager;

    SDL_Gfx_Sub_Context__Wrapper SDL_gfx_sub_context__wrapper;
    PLATFORM_Graphics_Window SDL_graphics_window__main;

    SDL_Window *p_SDL_window;

    i32 width_of__sdl_window;
    i32 height_of__sdl_window;
} PLATFORM_Gfx_Context;

typedef struct PLATFORM_Audio_Context_t {

} PLATFORM_Audio_Context;

#define MAX_QUANTITY_OF__SERIALIZATION_REQUESTS 256

typedef struct PLATFORM_File_System_Context_t {
    Serialization_Request SDL_serialization_requests[
        MAX_QUANTITY_OF__SERIALIZATION_REQUESTS];
    IO_path path_to__base_directory;
    Quantity__u32 size_of__path_to__base_directory;
} PLATFORM_File_System_Context;

#endif

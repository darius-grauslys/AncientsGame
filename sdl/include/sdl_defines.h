#ifndef SDL_DEFINES_H
#define SDL_DEFINES_H

#include "defines_weak.h"
#include <SDL2/SDL_render.h>
#include <platform_defines.h>

typedef struct PLATFORM_Graphics_Window_t {
} PLATFORM_Graphics_Window;

typedef void SDL_Gfx_Sub_Context;

typedef void (*f_SDL_Allocate_Texture)(
        PLATFORM_Texture *p_PLATFORM_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

typedef void (*f_SDL_Allocate_Texture__With_Path)(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path);

typedef void (*f_SDL_Use_Texture)(
        PLATFORM_Texture *p_PLATFORM_texture);

typedef void (*f_SDL_Release_Texture)(
        PLATFORM_Texture *p_PLATFORM_texture);




typedef void (*f_SDL_Allocate_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);

typedef void (*f_SDL_Release_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite);




typedef void (*f_SDL_Render_Entity)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Entity *p_entity);




typedef void (*f_SDL_Clear_Screen)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

typedef void (*f_SDL_Update_Camera)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

typedef u32 SDL_Texture_Format__u32;
typedef u32 GL_Texture_Handle__u32;

#define MAX_LENGTH_OF__SDL_TEXTURE_STRING 32
typedef char Texture_String[
    MAX_LENGTH_OF__SDL_TEXTURE_STRING];
typedef const char SDL_Texture_String__Const[
    MAX_LENGTH_OF__SDL_TEXTURE_STRING];

typedef struct PLATFORM_Texture_t {
    Texture_String SDL_texture_string;
    union {
        GL_Texture_Handle__u32 GL_texture_handle;
    };
    Texture_Flags texture_flags;
    SDL_Texture_Format__u32 SDL_texture_format__u32;
    SDL_TextureAccess SDL_texture_access;
    Quantity__u16 width;
    Quantity__u16 height;
    bool SDL_is_texture__allocated;
} PLATFORM_Texture;

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
    bool is_sprite__allocated;
    bool is_sprite_with__anonymous_texture;
} PLATFORM_Sprite;

#define MAX_QUANTITY_OF__SDL_TEXTURES 1024

typedef struct SLD_Texture_Manager_t {
    PLATFORM_Texture SDL_textures[
        MAX_QUANTITY_OF__SDL_TEXTURES];
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

    f_SDL_Clear_Screen                  f_SDL_clear_screen;
    f_SDL_Update_Camera                 f_SDL_update_camera;

    f_SDL_Allocate_Texture              f_SDL_allocate_texture;
    f_SDL_Allocate_Texture__With_Path   f_SDL_allocate_texture__with_path;
    f_SDL_Use_Texture                   f_SDL_use_texture;
    f_SDL_Release_Texture               f_SDL_release_texture;

    f_SDL_Allocate_Sprite               f_SDL_allocate_sprite;
    f_SDL_Release_Sprite                f_SDL_release_sprite;

    f_SDL_Render_Entity                 f_SDL_render_entity;

} SDL_Gfx_Sub_Context__Wrapper;

typedef struct PLATFORM_Gfx_Context_t {
    PLATFORM_Graphics_Window graphics_window__main_window;
    SDL_Gfx_Sub_Context__Wrapper SDL_gfx_sub_context__wrapper;
    SDL_Window *p_SDL_window;
} PLATFORM_Gfx_Context;

typedef void (*f_SDL_Initialize_Sprite_Wrapper)(
        Sprite_Wrapper *p_sprite_wrapper);

typedef struct PLATFORM_Audio_Context_t {

} PLATFORM_Audio_Context;

typedef struct PLATFORM_File_System_Context_t {

} PLATFORM_File_System_Context;

#endif

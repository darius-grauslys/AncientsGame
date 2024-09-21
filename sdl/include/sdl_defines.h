#ifndef SDL_DEFINES_H
#define SDL_DEFINES_H

#include "defines_weak.h"
#include "rendering/sdl_gfx_context.h"
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

typedef void (*f_SDL_Clear_Screen)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

typedef struct SDL_Gfx_Sub_Context__Wrapper_t {
    SDL_Gfx_Sub_Context__Kind           the_kind_of__sub_context;
    void                                *p_SDL_gfx_sub_context;

    f_SDL_Clear_Screen                  f_SDL_clear_screen;

    f_SDL_Allocate_Texture              f_SDL_allocate_texture;
    f_SDL_Allocate_Texture__With_Path   f_SDL_allocate_texture__with_path;
    f_SDL_Use_Texture                   f_SDL_use_texture;
    f_SDL_Release_Texture               f_SDL_release_texture;
} SDL_Gfx_Sub_Context__Wrapper;

typedef struct PLATFORM_Gfx_Context_t {
    PLATFORM_Graphics_Window graphics_window__main_window;
    SDL_Gfx_Sub_Context__Wrapper SDL_gfx_sub_context__wrapper;
    SDL_Window *p_SDL_window;
} PLATFORM_Gfx_Context;

typedef u32 SDL_Texture_Format__u32;
typedef u32 GL_Texture_Handle__u32;

typedef struct PLATFORM_Texture_t {
    union {
        GL_Texture_Handle__u32 GL_texture_handle;
    };
    Texture_Flags texture_flags;
    SDL_Texture_Format__u32 SDL_texture_format__u32;
    SDL_TextureAccess SDL_texture_access;
    Quantity__u16 width;
    Quantity__u16 height;
} PLATFORM_Texture;

typedef struct SLD_Texture_Manager_t {
    Quantity__u32 SDL_max_quantity_of__textures;
    PLATFORM_Texture SDL_textures[];
} SDL_Texture_Manager;

typedef void (*m_SDL_Render_Sprite)(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper);

typedef struct PLATFORM_Sprite_t {
    /// 
    /// This is agnostic to render backend.
    ///
    void *p_SDL_sprite;
    m_SDL_Render_Sprite m_SDL_render_sprite;
    Quantity__u8 quantity_of__sprite_frame__columns;
    Quantity__u8 quantity_of__sprite_frame__rows;
} PLATFORM_Sprite;

typedef void (*f_SDL_Initialize_Sprite_Wrapper)(
        Sprite_Wrapper *p_sprite_wrapper);

typedef struct PLATFORM_Audio_Context_t {

} PLATFORM_Audio_Context;

typedef struct PLATFORM_File_System_Context_t {

} PLATFORM_File_System_Context;

#endif

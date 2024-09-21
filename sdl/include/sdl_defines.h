#ifndef SDL_DEFINES_H
#define SDL_DEFINES_H

#include "defines_weak.h"
#include <SDL2/SDL_render.h>
#include <platform_defines.h>

typedef struct PLATFORM_Graphics_Window_t {
    SDL_Renderer *p_SDL_renderer;
} PLATFORM_Graphics_Window;

typedef struct PLATFORM_Gfx_Context_t {
    SDL_Renderer *p_SDL_renderer;
    SDL_Window *p_SDL_window;
    PLATFORM_Graphics_Window graphics_window__main_window;
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

typedef struct PLATFORM_Audio_Context_t {

} PLATFORM_Audio_Context;

typedef struct PLATFORM_File_System_Context_t {

} PLATFORM_File_System_Context;

#endif

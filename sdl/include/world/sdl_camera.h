#ifndef SDL_CAMERA_H
#define SDL_CAMERA_H

#include <sdl_defines.h>

void SDL_allocate_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

void SDL_update_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

void SDL_release_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

#endif

#include "debug/debug.h"
#include "defines_weak.h"
#include "sdl_defines.h"
#include <world/sdl_camera.h>

void SDL_allocate_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    f_SDL_Allocate_Camera_Data f_SDL_allocate_camera_data =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_camera_data
        ;

    SDL_DEBUG_ABORT_IF__HOOK_NULL(
            SDL_allocate_camera_data,
            p_PLATFORM_gfx_context,
            f_SDL_allocate_camera_data);

    f_SDL_allocate_camera_data(
            p_PLATFORM_gfx_context,
            p_camera);
}

void SDL_update_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    f_SDL_Update_Camera f_SDL_update_camera =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_update_camera
        ;

    SDL_DEBUG_ABORT_IF__HOOK_NULL(
            SDL_update_camera,
            p_PLATFORM_gfx_context,
            f_SDL_update_camera);

    f_SDL_update_camera(
            p_PLATFORM_gfx_context,
            p_camera);
}

void SDL_release_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    f_SDL_Release_Camera_Data f_SDL_release_camera_data =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_release_camera_data
        ;

    SDL_DEBUG_ABORT_IF__HOOK_NULL(
            SDL_release_camera_data, 
            p_PLATFORM_gfx_context, 
            f_SDL_release_camera_data);

    f_SDL_release_camera_data(
            p_PLATFORM_gfx_context,
            p_camera);
}

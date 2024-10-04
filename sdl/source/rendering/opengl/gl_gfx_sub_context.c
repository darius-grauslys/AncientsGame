#include "debug/opengl/gl_debug.h"
#include "defines_weak.h"
#include "game.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_sprite_manager.h"
#include "rendering/sdl_gfx_context.h"
#include "world/opengl/gl_camera.h"
#include "world/opengl/gl_camera_data_manager.h"
#include <SDL2/SDL_video.h>
#include <rendering/opengl/gl_gfx_sub_context.h>
#include <rendering/opengl/gl_shader_manager.h>
#include <rendering/opengl/gl_sprite_manager.h>
#include <sdl_defines.h>
#include <sdl_event.h>

void GL_initialize_gfx_sub_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context) {

    p_GL_gfx_sub_context->GL_context = 
        SDL_GL_CreateContext(
                p_PLATFORM_gfx_context
                ->p_SDL_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        debug_error("SDL::PLATFORM_main failed to load GL functions.");
        return;
    }
    
    GL_debug_init();

    GL_initialize_shader_manager(
            GL_get_p_shader_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));
    GL_initialize_sprite_manager(
            GL_get_p_sprite_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));
    GL_initialize_camera_data_manager(
            GL_get_p_camera_data_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));

    SDL_register_window_event(
            SDL_WINDOWEVENT_RESIZED,
            f_SDL_event_handler__GL_resize);

    Camera *p_GL_camera__default =
        &p_GL_gfx_sub_context
        ->GL_camera__default;
    
    GL_allocate_camera_data(
            p_PLATFORM_gfx_context, 
            p_GL_camera__default);

    GL_initialize_camera(
            p_PLATFORM_gfx_context, 
            p_GL_camera__default);

    SDL_set_active_camera(
            p_PLATFORM_gfx_context, 
            p_GL_camera__default);

    glClearColor(0,0,0,1);
}

void GL_dispose_gfx_sub_context(
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context) {
    GL_dispose_shader_manager(
            &p_GL_gfx_sub_context->GL_shader_manager);
    GL_dispose_sprite_manager(
            &p_GL_gfx_sub_context->GL_sprite_manager);
    SDL_GL_DeleteContext(
            &p_GL_gfx_sub_context
            ->GL_context);
}

void GL_clear_screen(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    glClear(GL_COLOR_BUFFER_BIT);
}

GL_Gfx_Sub_Context *GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return (GL_Gfx_Sub_Context*)p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context
        ;
}

void f_SDL_event_handler__GL_resize(
        Game *p_game,
        SDL_Event *p_event) {
    f_SDL_event_handler__resize(
            p_game,
            p_event);
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    i32 width  = p_PLATFORM_gfx_context->width_of__sdl_window;
    i32 height = p_PLATFORM_gfx_context->height_of__sdl_window;

    i32 width__fixed = width / 64;
    i32 height__fixed = width__fixed / 4 * 3;

    width__fixed *= 32;
    height__fixed *= 32;

    glViewport(
            (width - width__fixed) / 2, (height - height__fixed) / 2,
            width__fixed,
            height__fixed);

    p_PLATFORM_gfx_context->width_of__sdl_viewport =
        width__fixed;
    p_PLATFORM_gfx_context->height_of__sdl_viewport =
        height__fixed;

    GL_fit_projection_of__camera_to__window(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_gfx_context
                ->p_active_camera);
}

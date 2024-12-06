#include "debug/opengl/gl_debug.h"
#include "defines_weak.h"
#include "game.h"
#include <world/camera.h>
#include "rendering/opengl/gl_chunk_texture_manager.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer_manager.h"
#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_sprite_manager.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/opengl/glad/glad.h"
#include "rendering/sdl_gfx_context.h"
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
        debug_error("SDL::PLATFORM_main failed to load GL functions. Version: %d.%d", GLVersion.major, GLVersion.minor);
        return;
    }
    
    GL_debug_init();

    GL_initialize_shader_manager(
            GL_get_p_shader_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));
    GL_initialize_sprite_manager(
            GL_get_p_sprite_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));
    GL_initialize_viewport_stack(
            GL_get_p_viewport_stack_from__gfx_sub_context(
                p_GL_gfx_sub_context),
            0,
            0,
            p_PLATFORM_gfx_context->width_of__sdl_window,
            p_PLATFORM_gfx_context->height_of__sdl_window);
    GL_initialize_framebuffer_manager(
            GL_get_p_framebuffer_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context));

    SDL_register_window_event(
            SDL_WINDOWEVENT_RESIZED,
            f_SDL_event_handler__GL_resize);

    Camera *p_GL_camera__default =
        &p_GL_gfx_sub_context
        ->GL_camera__default;

    initialize_camera(
            p_GL_camera__default, 
            VECTOR__3i32F4__0_0_0, 
            0, 
            16,
            12, 
            -BIT(18), 
            i32_to__i32F20(100));

    SDL_set_active_camera(
            p_PLATFORM_gfx_context, 
            p_GL_camera__default);

    initialize_vertex_object_as__unit_square(
            &p_GL_gfx_sub_context
            ->GL_vertex_object__unit_square);

    glClearColor(0,0,0,1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    i32 minima = (width > height)
        ? height
        : width
        ;

    i32 width__fixed = minima / 32;
    i32 height__fixed = width__fixed;

    width__fixed *= 32;
    height__fixed *= 32;

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    debug_info("RESIZE: %d, %d",
            width__fixed,
            height__fixed);

    p_GL_viewport_stack->p_GL_viewport__base->x =
        (width - width__fixed) / 2;
    p_GL_viewport_stack->p_GL_viewport__base->y =
        (height - height__fixed) / 2;
    p_GL_viewport_stack->p_GL_viewport__base->width =
        width__fixed;
    p_GL_viewport_stack->p_GL_viewport__base->height =
        height__fixed;

    if (GL_is_viewport_stack__only_the_base(
                p_GL_viewport_stack)) {
        GL_refresh_viewport_on_top_of__viewport_stack(
                p_GL_viewport_stack);
    }
}

void GL_initialize_rendering__worldspace(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    GL_Gfx_Sub_Context *p_GL_gfx_sub_context =
        GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager =
        GL_get_p_chunk_texture_manager_from__gfx_sub_context(
                p_GL_gfx_sub_context);

    GL_initialize_chunk_texture_manager(
            p_PLATFORM_gfx_context, 
            p_GL_chunk_texture_manager);
}

#include "debug/opengl/gl_debug.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_sprite_manager.h"
#include <SDL2/SDL_video.h>
#include <rendering/opengl/gl_gfx_sub_context.h>
#include <rendering/opengl/gl_shader_manager.h>
#include <rendering/opengl/gl_sprite_manager.h>
#include <sdl_defines.h>

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
            &p_GL_gfx_sub_context->GL_shader_manager);
    GL_initialize_sprite_manager(
            &p_GL_gfx_sub_context->GL_sprite_manager);

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

void GL_update_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    GL_Gfx_Sub_Context *p_GL_gfx_sub_context =
        (GL_Gfx_Sub_Context*)
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context
        ;

    GL_Shader_2D *p_GL_shader__sprite =
        p_GL_gfx_sub_context
        ->GL_shader_manager
        .p_GL_shader__sprite
        ;

    // TODO: impl
    // GL_Shader_2D *p_GL_shader__world =
    //     p_GL_gfx_sub_context
    //     ->GL_shader_manager
    //     .p_GL_shader__world
    //     ;

    set_shader_mat4_view__position(
            p_GL_shader__sprite, 
            i32F4_to__float(
                p_camera
                ->position.x__i32F4), 
            i32F4_to__float(
                p_camera
                ->position.y__i32F4), 
            i32F4_to__float(
                p_camera
                ->position.z__i32F4)
            );
}

GL_Gfx_Sub_Context *GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return (GL_Gfx_Sub_Context*)p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context
        ;
}

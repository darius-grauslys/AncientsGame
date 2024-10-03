#include "defines_weak.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_manager.h"
#include "rendering/opengl/gl_shader_sprite.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/opengl/glad/glad.h"
#include <rendering/opengl/gl_sprite.h>
#include <rendering/opengl/gl_gfx_sub_context.h>
#include <sdl_defines.h>

void f_GL_initialize_sprite_wrapper(
        Sprite_Wrapper *p_sprite_wrapper) {
    //TODO: impl
    debug_abort("SDL::GL::f_GL_initialize_sprite_wrapper impl");
}

void GL_initialize_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    GL_Gfx_Sub_Context *p_GL_gfx_sub_context =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .p_SDL_gfx_sub_context
        ;
    GL_Sprite *p_GL_sprite =
        (GL_Sprite*)p_PLATFORM_sprite
        ->p_SDL_sprite
        ;
    GL_Shader_2D *p_GL_shader =
        GL_get_shader_from__shader_manager(
                &p_GL_gfx_sub_context
                ->GL_shader_manager, 
                shader_string__sprite);

    if (!p_GL_shader) {
        debug_error("SDL::GL_initialize_sprite failed to find sprite shader.");        
        PLATFORM_release_sprite(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_sprite);
        return;
    }

    GL_initialize_sprite_with__this_shader(
            p_GL_sprite, 
            p_GL_shader);
}

void GL_initialize_sprite_with__this_shader(
        GL_Sprite *p_GL_sprite,
        GL_Shader_2D *p_GL_shader) {
    p_GL_sprite
        ->p_GL_shader = p_GL_shader;
    initialize_vertex_object_as__unit_square(
            &p_GL_sprite->GL_vertex_object);

    p_GL_sprite->location_of__sprite_frame_row_col
        = glGetUniformLocation(p_GL_sprite->p_GL_shader->handle, 
                "spriteframe_row_col");
    p_GL_sprite->location_of__sprite_frame_width_height
        = glGetUniformLocation(p_GL_sprite->p_GL_shader->handle, 
                "spriteframe_width_height");
}

void GL_release_sprite_vertext_object(
        GL_Sprite *p_GL_sprite) {
    release_vertex_object(
            &p_GL_sprite->GL_vertex_object);
}

GL_Sprite *GL_get_p_sprite_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return (GL_Sprite*)
        p_PLATFORM_sprite
        ->p_SDL_sprite
        ;
}

GL_Sprite *GL_get_p_sprite_from__sprite_wrapper(
        Sprite_Wrapper *p_sprite_wrapper) {
    return (GL_Sprite*)
        p_sprite_wrapper
        ->p_sprite
        ->p_SDL_sprite
        ;
}

void GL_render_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper,
        Vector__3i32F4 position__3i32F4) {

    GL_Gfx_Sub_Context *p_GL_gfx_sub_context =
        GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);
    PLATFORM_Sprite *p_PLATFORM_sprite =
        p_sprite_wrapper
        ->p_sprite
        ;
    GL_Sprite *p_GL_sprite =
        (GL_Sprite*)
        p_PLATFORM_sprite->p_SDL_sprite
        ;
    GL_Shader_2D *p_GL_shader__sprite =
        p_GL_sprite->p_GL_shader;

    set_shader_mat4_model__position(
            p_GL_shader__sprite, 
            i32F4_to__float(
                position__3i32F4.x__i32F4),
            i32F4_to__float(
                position__3i32F4.y__i32F4),
            i32F4_to__float(
                position__3i32F4.z__i32F4)
            );

    use_shader_2d(p_GL_shader__sprite);
    use_vertex_object(&p_GL_sprite->GL_vertex_object);
    PLATFORM_use_texture(
            p_PLATFORM_gfx_context,
            p_PLATFORM_sprite
            ->p_PLATFORM_texture);
    glUniform2f(
            p_GL_sprite->location_of__sprite_frame_row_col,
            p_sprite_wrapper->frame__current
            % p_PLATFORM_sprite->quantity_of__sprite_frame__columns, 
            (u8)(p_PLATFORM_sprite->quantity_of__sprite_frame__rows-1)
            - (u8)((p_sprite_wrapper->frame__current
                / p_PLATFORM_sprite->quantity_of__sprite_frame__columns)
            ) % p_PLATFORM_sprite->quantity_of__sprite_frame__rows
            );
    glUniform2f(
            p_GL_sprite->location_of__sprite_frame_width_height,
            p_PLATFORM_sprite->sprite_frame__width, 
            p_PLATFORM_sprite->sprite_frame__height);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

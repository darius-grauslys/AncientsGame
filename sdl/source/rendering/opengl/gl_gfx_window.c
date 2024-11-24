#include "rendering/opengl/gl_gfx_window.h"
#include "game.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer.h"
#include "rendering/opengl/gl_framebuffer_manager.h"
#include "rendering/opengl/gl_shader_manager.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/glad/glad.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/texture.h"

void GL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    PLATFORM_allocate_texture(
            &p_PLATFORM_graphics_window
            ->SDL_graphics_window__texture,
            p_texture_allocation_specification);

    if (!is_texture_flags__allocated(
                p_PLATFORM_graphics_window
                ->SDL_graphics_window__texture
                .texture_flags)) {
        debug_error("GL_allocate_gfx_window, failed to allocate texture.");
        return;
    }

    GL_Framebuffer *p_GL_framebuffer =
        GL_allocate_framebuffer_with__framebuffer_manager(
                p_PLATFORM_gfx_context, 
                GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context));

    if (!p_GL_framebuffer) {
        PLATFORM_release_texture(
                p_PLATFORM_gfx_context, 
                &p_PLATFORM_graphics_window
                ->SDL_graphics_window__texture);
        debug_error("GL_allocate_gfx_window, failed to allocate framebuffer");
        return;
    }

    p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__data =
        p_GL_framebuffer
        ;

    SDL_set_gfx_window_as__allocated(
            p_PLATFORM_graphics_window);
}

void GL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    GL_Shader_2D *p_GL_shader =
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    get_p_PLATFORM_gfx_context_from__game(
                        p_game)), 
                shader_string__passthrough);

    if (!p_GL_shader) {
        debug_error("GL_render_gfx_window, p_GL_shader == 0.");
        return;
    }

    GL_Framebuffer *p_GL_framebuffer =
        (GL_Framebuffer*)
        p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__data
        ;

    if (!p_GL_framebuffer) {
        return;
    }

    // TODO: make proper
    GL_bind_texture_to__framebuffer(
            p_GL_framebuffer, 
            &p_PLATFORM_graphics_window
            ->SDL_graphics_window__texture);
    // TODO: use UI texture atlas
    // PLATFORM_use_texture(
    //         p_PLATFORM_gfx_context, 
    //         p_GL_chunk_texture_manager
    //         ->p_PLATFORM_texture_of__tilesheet_ground);
    GL_render_with__shader__passthrough(
            p_GL_shader, 
            0, //int x__uv, 
            0, //int y__uv, 
            0, //float width_of__uv, 
            0, //float height_of__uv, 
            0, //bool is_flipped_on__x, 
            0  //bool is_flipped_on__y
            );
}

void GL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    PLATFORM_release_texture(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_graphics_window
            ->SDL_graphics_window__texture);

    GL_Framebuffer *p_GL_framebuffer =
        (GL_Framebuffer*)p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__data
        ;

    if (!p_GL_framebuffer) {
        return;
    }

    p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__data = 0;

    GL_release_framebuffer_from__framebuffer_manager(
            p_PLATFORM_gfx_context, 
            GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context), 
            p_GL_framebuffer);

    SDL_set_gfx_window_as__deallocated(
            p_PLATFORM_graphics_window);
}

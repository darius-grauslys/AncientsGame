#include "rendering/opengl/gl_gfx_window.h"
#include "defines.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer.h"
#include "rendering/opengl/gl_framebuffer_manager.h"
#include "rendering/opengl/gl_gfx_sub_context.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_manager.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/opengl/glad/glad.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/sdl_texture_manager.h"
#include "rendering/sdl_texture_strings.h"
#include "rendering/texture.h"
#include "rendering/sdl_texture.h"
#include "ui/ui_manager.h"
#include "vectors.h"

void GL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__texture =
            PLATFORM_allocate_texture(
                    p_PLATFORM_gfx_context,
                    p_texture_allocation_specification);

    if (!SDL_is_texture__allocated(
                p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture)) {
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
                p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture);
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

void GL_compose_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    GL_Shader_2D *p_GL_shader__passthrough=
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                shader_string__passthrough);

    if (!p_GL_shader__passthrough) {
        debug_warning("Did you forget to attach a chunk shader?");
        debug_error("SDL::GL::GL_update_chunk, p_GL_chunk_texture_manager has p_GL_shader__chunk == 0.");
        return;
    }

    UI_Tile_Map__Wrapper ui_tile_map__wrapper =
        p_PLATFORM_graphics_window
        ->SDL_graphics_window__ui_tile_map__wrapper;

    GL_Framebuffer *p_GL_framebuffer =
        (GL_Framebuffer*)p_PLATFORM_graphics_window
        ->p_SDL_graphics_window__data;

    if (!p_GL_framebuffer) {
        debug_error("GL_composite_gfx_window_from__ui_tiles, missing framebuffer.");
        return;
    }

    GL_Framebuffer_Manager *p_GL_framebuffer_manager =
        GL_get_p_framebuffer_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    PLATFORM_Texture *p_PLATFORM_texture__ui_tilesheet =
        SDL_get_texture_from__texture_manager(
                SDL_get_p_texture_manager_from__gfx_context(
                    p_PLATFORM_gfx_context), 
                SDL_texture_string__tilesheet_ui);

    float clear_color[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, clear_color);

    glClearColor(1.0, 0.0, 1.0, 0.0);
    GL_push_framebuffer_onto__framebuffer_manager(
            p_GL_framebuffer_manager,
            p_GL_framebuffer);
    GL_bind_texture_to__framebuffer(
            p_GL_framebuffer, 
            p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(
            clear_color[0],
            clear_color[1],
            clear_color[2],
            clear_color[3]);

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    GL_Vertex_Object *p_GL_vertex_object =
        &GL_get_p_gfx_sub_context_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context)
        ->GL_vertex_object__unit_square;

    GL_push_viewport(
            GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context), 
            0, 
            0,
            p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture
            ->width,
            p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture
            ->height);

    render_all_ui_elements_in__ui_manager(
            SDL_get_p_ui_manager_from__PLATFORM_gfx_window(
                p_PLATFORM_graphics_window), 
            p_PLATFORM_graphics_window,
            p_game);

    GL_pop_viewport(
            GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context));

    use_shader_2d(
            p_GL_shader__passthrough);

    float width__f = 
        (float)p_PLATFORM_texture__ui_tilesheet
        ->width;
    float height__f = 
        (float)p_PLATFORM_texture__ui_tilesheet
        ->height;

    float width_of__uv  = 1.0 / (width__f / 8);
    float height_of__uv = 1.0 / (height__f / 8);

    use_vertex_object(p_GL_vertex_object);

    PLATFORM_use_texture(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_texture__ui_tilesheet);

    for (Index__u8 index_of__y_tile = 0;
            index_of__y_tile 
            < ui_tile_map__wrapper.height_of__ui_tile_map;
            index_of__y_tile++) {
        for (Index__u8 index_of__x_tile = 0;
                index_of__x_tile 
                < ui_tile_map__wrapper.width_of__ui_tile_map;
                index_of__x_tile++) {
            UI_Tile_Raw ui_tile_raw =
                ui_tile_map__wrapper
                .p_ui_tile_data[
                index_of__x_tile
                    + (ui_tile_map__wrapper.width_of__ui_tile_map 
                            - 1 - index_of__y_tile) 
                    * ui_tile_map__wrapper.width_of__ui_tile_map];
            if (!ui_tile_raw)
                continue;
            ui_tile_raw--;

            GL_push_viewport(
                    p_GL_viewport_stack, 
                    index_of__x_tile * TILE_WIDTH__IN_PIXELS, 
                    index_of__y_tile * TILE_WIDTH__IN_PIXELS, 
                    TILE_WIDTH__IN_PIXELS, 
                    TILE_WIDTH__IN_PIXELS);

            GL_render_with__shader__passthrough_using__index_sampling(
                    p_GL_shader__passthrough, 
                    ui_tile_raw % 32, 
                    (int)(ui_tile_raw / 32), 
                    width_of__uv, 
                    height_of__uv,
                    false,
                    false);

            GL_pop_viewport(p_GL_viewport_stack);
        }
    }

    GL_pop_framebuffer_off_of__framebuffer_manager(
            p_GL_framebuffer_manager);
}

void GL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    // TODO: make and use shader_string__ui along with it's shader.
    GL_Shader_2D *p_GL_shader__passthrough =
        GL_get_shader_from__shader_manager(
                GL_get_p_shader_manager_from__PLATFORM_gfx_context(
                    get_p_PLATFORM_gfx_context_from__game(
                        p_game)), 
                shader_string__passthrough);

    if (!p_GL_shader__passthrough) {
        debug_error("GL_render_gfx_window, p_GL_shader == 0.");
        return;
    }

    use_shader_2d(p_GL_shader__passthrough);
    PLATFORM_use_texture(
            p_PLATFORM_gfx_context,
            p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture);

    float width_of__uv = 1.0f;
    float height_of__uv = 1.0f;

    float x = 0, y = 0;

    if (!GL_is_viewport_stack__only_the_base(
                GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context))) {
        GL_Viewport *p_GL_viewport =
            GL_peek_viewport_stack(
                    GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                        p_PLATFORM_gfx_context));

        if (p_GL_viewport->width
                < p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture
                ->width) {
            width_of__uv =
                (float)p_GL_viewport
                ->width 
                / (float)p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture
                ->width
                ;
        }

        if (p_GL_viewport->height
                < p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture
                ->height) {
            height_of__uv =
                (float)p_GL_viewport
                ->height 
                / (float)p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture
                ->height
                ;
        }

        x = p_GL_viewport->x;
        y = 
            p_PLATFORM_graphics_window
                ->p_SDL_graphics_window__texture
                ->height
            - p_GL_viewport->y
            - p_GL_viewport->height
            ;

        x /= (float)p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture
            ->width
            ;
        y /= (float)p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture
            ->height
            ;

        // TODO:    this makes the most sense right now
        //          as the above manipulations although deemed
        //          necessary (from lack of planning... rushing...)
        //          are not usable for our purposes in UI.
        x = 0;
        y = 0;
    }

    GL_render_with__shader__passthrough_using__coordinate_sampling(
            p_GL_shader__passthrough, 
            x,
            y, 
            width_of__uv, 
            height_of__uv,
            false,
            false);
}

void GL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    PLATFORM_release_texture(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_graphics_window
            ->p_SDL_graphics_window__texture);

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

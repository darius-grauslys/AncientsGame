#include "ui/sdl_ui__background.h"
#include "game.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "ui/ui_element.h"
#include "vectors.h"

void SDL_initialize_ui_element_as__background(
        UI_Element *p_ui_background,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    initialize_ui_element(
            p_ui_background, 
            0, 
            0, 
            0, 
            UI_Element_Kind__Background, 
            get_ui_element__flags(
                p_ui_background), 
            width__u8, 
            height__u8, 
            position__3i32);

    SDL_set_position_of__gfx_window(
            p_PLATFORM_gfx_window, 
            vector_3i32_to__vector_3i32F4(
                position__3i32));

    set_ui_element__p_data(
            p_ui_background, 
            p_PLATFORM_gfx_window);

    set_ui_element__render_handler(
            p_ui_background, 
            m_SDL_render__ui__background);
}

///
/// This disposes the attached p_PLATFORM_gfx_window
///
void m_SDL_dispose__ui__background(
        UI_Element *p_ui_element,
        Game *p_game) {
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
        (PLATFORM_Graphics_Window*)
        p_ui_element
        ->p_ui_data
        ;

    SDL_release_gfx_window(
            get_p_PLATFORM_gfx_context_from__game(
                p_game), 
            p_PLATFORM_gfx_window);
}

void m_SDL_render__ui__background(
        UI_Element *p_ui_element,
        PLATFORM_Graphics_Window *_p_PLATFORM_gfx_window,
        Game *p_game) {
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window_from__data =
        (PLATFORM_Graphics_Window*)
        p_ui_element
        ->p_ui_data
        ;

    int x =
        get_x_i32_from__p_ui_element(
                p_ui_element);
    int y =
        get_y_i32_from__p_ui_element(
                p_ui_element);

    int width =
        get_width_from__p_ui_element(
                p_ui_element);
    int height =
        get_height_from__p_ui_element(
                p_ui_element);

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
            get_p_PLATFORM_gfx_context_from__game(
                p_game));

    GL_push_viewport(
            p_GL_viewport_stack,
            x, 
            y, 
            width, 
            height);

    SDL_render_gfx_window(
            p_game, 
            p_PLATFORM_gfx_window_from__data);

    GL_pop_viewport(
            p_GL_viewport_stack);
}

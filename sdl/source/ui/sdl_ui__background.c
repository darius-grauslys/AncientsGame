#include "ui/sdl_ui__background.h"
#include "game.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "ui/ui_element.h"
#include "vectors.h"

void SDL_initialize_ui_element_as__background(
        UI_Element *p_ui_background,
        Quantity__u16 width__u16,
        Quantity__u16 height__u16,
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
            width__u16, 
            height__u16, 
            position__3i32);

   p_PLATFORM_gfx_window 
        ->SDL_origin_of__graphics_window =
        vector_3i32_to__vector_3i32F4(position__3i32);

    SDL_set_position_of__gfx_window(
            p_PLATFORM_gfx_window, 
            vector_3i32_to__vector_3i32F4(
                position__3i32));

    set_ui_element__p_data(
            p_ui_background, 
            p_PLATFORM_gfx_window);

    set_ui_element__dispose_handler(
            p_ui_background, 
            m_SDL_dispose__ui__background);

    //
    // This is done so a HUGE background overlayed
    // ontop of interactive UIs does not stop
    // the overlayed UIs from interacting with the
    // cursor.
    //
    set_ui_element_as__non_interactive(
            p_ui_background);
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
            p_game,
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

    Vector__3i32 position_of__background__3i32 =
        PLATFORM_get_gfx_window__position(
                p_PLATFORM_gfx_window_from__data);

    int x =
        position_of__background__3i32.x__i32;
    int y =
        position_of__background__3i32.y__i32;

    set_position_3i32_of__ui_element(
            p_ui_element,
            position_of__background__3i32);

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
}

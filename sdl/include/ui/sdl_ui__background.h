#ifndef SDL_UI__BACKGROUND_H
#define SDL_UI__BACKGROUND_H

///
/// TODO:   Eventually this should be a CORE ui element
///         where the p_data is a pointer to PLATFORM_Gfx_Window.
///

#include "defines.h"

///
/// NOTE: Takes ownership of p_PLATFORM_gfx_window
/// TODO: make naming convention for parameter names which take ptr ownership.
///
void SDL_initialize_ui_element_as__background(
        UI_Element *p_ui_background,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

///
/// This disposes the attached p_PLATFORM_gfx_window
///
void m_SDL_dispose__ui__background(
        UI_Element *p_ui_element,
        Game *p_game);

void m_SDL_render__ui__background(
        UI_Element *p_ui_element,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Game *p_game);

#endif

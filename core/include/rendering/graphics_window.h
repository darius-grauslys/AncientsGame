#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include "defines_weak.h"
#include <defines.h>

void initialize_graphics_window(
        Graphics_Window *p_graphics_window);

void initialize_graphics_window_as__allocated(
        Graphics_Window *p_graphics_window,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Graphics_Window_Kind the_kind_of__graphics_window);

static inline
bool is_graphics_window__allocated(
        Graphics_Window *p_graphics_window) {
    return (bool)p_graphics_window->p_PLATFORM_gfx_window;
}

static inline
Vector__3i32 get_origin_3i32_of__graphics_window(
        Graphics_Window *p_graphics_window) {
    return p_graphics_window->origin_of__gfx_window;
}

static inline
Vector__3i32 get_position_3i32_of__graphics_window(
        Graphics_Window *p_graphics_window) {
    return p_graphics_window->position_of__gfx_window;
}

static inline
Vector__3i32 get_position_maximum_3i32_of__graphics_window(
        Graphics_Window *p_graphics_window) {
    return p_graphics_window->position_of__gfx_window__maximum;
}

static inline
Vector__3i32 get_position_minimum_3i32_of__graphics_window(
        Graphics_Window *p_graphics_window) {
    return p_graphics_window->position_of__gfx_window__minimum;
}

static inline
Graphics_Window *get_p_child_of__graphics_window(
        Graphics_Window *p_graphics_window) {
    return p_graphics_window->p_child__graphics_window;
}

static inline
bool is_graphics_window_possessing__a_child(
        Graphics_Window *p_graphics_window) {
    return (bool)get_p_child_of__graphics_window(
            p_graphics_window);
}

static inline
bool is_graphics_window_a__child_of__this_graphics_window(
        Graphics_Window *p_graphics_window__child,
        Graphics_Window *p_graphics_window__parent) {
    return p_graphics_window__parent
        ->p_child__graphics_window =
        p_graphics_window__child;
}

static inline
bool is_graphics_window_of__this_kind(
        Graphics_Window *p_graphics_window,
        Graphics_Window_Kind the_kind_of__graphics_window) {
    return p_graphics_window->the_kind_of__window
        == the_kind_of__graphics_window;
}

#endif

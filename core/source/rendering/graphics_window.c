#include "rendering/graphics_window.h"
#include "defines.h"
#include "defines_weak.h"
#include "vectors.h"

void initialize_graphics_window(
        Graphics_Window *p_graphics_window) {
    p_graphics_window->p_PLATFORM_gfx_window = 0;
    p_graphics_window->p_child__graphics_window = 0;
    p_graphics_window->origin_of__gfx_window =
        VECTOR__3i32__OUT_OF_BOUNDS;
    p_graphics_window->position_of__gfx_window =
        VECTOR__3i32__OUT_OF_BOUNDS;
    p_graphics_window->position_of__gfx_window__maximum =
        VECTOR__3i32__OUT_OF_BOUNDS;
    p_graphics_window->position_of__gfx_window__minimum =
        VECTOR__3i32__OUT_OF_BOUNDS;
    p_graphics_window->priority_of__window =
        INDEX__UNKNOWN__u8;
    p_graphics_window->the_kind_of__window =
        Graphics_Window_Kind__None;
}

void initialize_graphics_window_as__allocated(
        Graphics_Window *p_graphics_window,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Graphics_Window_Kind the_kind_of__graphics_window) {
    p_graphics_window->p_PLATFORM_gfx_window = 
        p_PLATFORM_gfx_window;
    p_graphics_window->p_child__graphics_window = 0;
    p_graphics_window->origin_of__gfx_window =
        VECTOR__3i32__0_0_0;
    p_graphics_window->position_of__gfx_window =
        VECTOR__3i32__0_0_0;
    p_graphics_window->position_of__gfx_window__maximum =
        VECTOR__3i32__0_0_0;
    p_graphics_window->position_of__gfx_window__minimum =
        VECTOR__3i32__0_0_0;
    p_graphics_window->priority_of__window =
        0;
    p_graphics_window->the_kind_of__window =
        the_kind_of__graphics_window;
}


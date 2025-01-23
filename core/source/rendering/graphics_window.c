#include "rendering/graphics_window.h"
#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_tile_map.h"
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
    p_graphics_window->graphics_window__flags =
        GRAPHICS_WINDOW__FLAGS__NONE;
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
    p_graphics_window->graphics_window__flags =
        GRAPHICS_WINDOW__FLAGS__NONE;
}

void update_graphics_window__ui_tiles(
        Graphics_Window *p_gfx_window,
        const UI_Tile_Raw *p_ui_tiles,
        Quantity__u32 size_of__p_ui_tiles) {
    if (!is_ui_tile_map__wrapper__valid(
                p_gfx_window->ui_tile_map__wrapper)) {
        debug_error("update_graphics_window__ui_tiles, p_gfx_window lacks ui_tile_map data.");
        return;
    }
    memcpy(
            p_gfx_window
                ->ui_tile_map__wrapper
                .p_ui_tile_data,
            p_ui_tiles,
            size_of__p_ui_tiles);
    set_graphics_window_as__in_need_of__composition(p_gfx_window);
}

void set_graphics_window__ui_tile_map(
        Graphics_Window *p_gfx_window,
        UI_Tile_Map__Wrapper ui_tile_map_wrapper) {
    if (is_ui_tile_map__wrapper__valid(
                p_gfx_window->ui_tile_map__wrapper)) {
        debug_warning("set_graphics_window__ui_tile_map, ui_tile_map already assigned.");
    }

    p_gfx_window->ui_tile_map__wrapper =
        ui_tile_map_wrapper;
}

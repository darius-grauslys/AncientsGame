#ifndef UI_TILE_MAP_H
#define UI_TILE_MAP_H

#include "defines.h"
#include "defines_weak.h"
#include "platform_defaults.h"
#include "platform_defines.h"

UI_Tile_Map__Wrapper get_ui_tile_map__wrapper(
        UI_Tile_Raw *p_ui_tile_data,
        Quantity__u32 width_of__tile_map,
        Quantity__u32 height_of__tile_map) {
    return (UI_Tile_Map__Wrapper) {
        p_ui_tile_data,
        width_of__tile_map,
        height_of__tile_map
    };
}

UI_Tile_Map__Wrapper ui_tile_map__small_to__ui_tile_map_wrapper(
        UI_Tile_Map__Small *p_ui_tile_map__small) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__small->ui_tile_data__small, 
            UI_TILE_MAP__SMALL__WIDTH, 
            UI_TILE_MAP__SMALL__HEIGHT);
}

UI_Tile_Map__Wrapper ui_tile_map__medium_to__ui_tile_map_wrapper(
        UI_Tile_Map__Medium *p_ui_tile_map__medium) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__medium->ui_tile_data__medium, 
            UI_TILE_MAP__MEDIUM__WIDTH, 
            UI_TILE_MAP__MEDIUM__HEIGHT);
}

UI_Tile_Map__Wrapper ui_tile_map__large_to__ui_tile_map_wrapper(
        UI_Tile_Map__Large *p_ui_tile_map__large) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__large->ui_tile_data__large, 
            UI_TILE_MAP__LARGE__WIDTH, 
            UI_TILE_MAP__LARGE__HEIGHT);
}

static inline
Quantity__u32 get_width_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper *p_ui_tile_map__wraper) {
    return p_ui_tile_map__wraper
        ->width_of__ui_tile_map;
}

static inline
Quantity__u32 get_height_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper *p_ui_tile_map__wraper) {
    return p_ui_tile_map__wraper
        ->height_of__ui_tile_map;
}

void generate_ui_span_in__ui_tile_map(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper,
        const UI_Tile_Span *p_ui_tile_span,
        Quantity__u32 width_of__ui_tile_span,
        Quantity__u32 height_of__ui_tile_span,
        Index__u32 index_x__u32,
        Index__u32 index_y__u32);

#endif

#ifndef UI_TILE_MAP_H
#define UI_TILE_MAP_H

#include "defines.h"
#include "defines_weak.h"
#include "platform_defaults.h"
#include "platform_defines.h"

void initialize_ui_tile_map__small_as__deallocated(
        UI_Tile_Map__Small *p_ui_tile_map__small);

void initialize_ui_tile_map__medium_as__deallocated(
        UI_Tile_Map__Medium *p_ui_tile_map__medium);

void initialize_ui_tile_map__large_as__deallocated(
        UI_Tile_Map__Large *p_ui_tile_map__large);

void initialize_ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper *p_ui_tile_map__wrapper,
        UI_Tile_Raw *p_ui_tile_data,
        Quantity__u32 width_of__tile_map,
        Quantity__u32 height_of__tile_map,
        UI_Tile_Map_Size catagory_size_of__ui_tile_map);

void generate_ui_span_in__ui_tile_map(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper,
        const UI_Tile_Span *p_ui_tile_span,
        Quantity__u32 width_of__ui_tile_span,
        Quantity__u32 height_of__ui_tile_span,
        Index__u32 index_x__u32,
        Index__u32 index_y__u32);

///
/// Makes sure that the set size does not exceed allocation limits.
///
void set_ui_tile_map__wrapper__utilized_size(
        UI_Tile_Map__Wrapper *p_ui_tile_map__wrapper,
        Quantity__u32 width__u32,
        Quantity__u32 height__u32);

static inline
bool is_ui_tile_map_flags__allocated(
        UI_Tile_Map__Flags ui_tile_map__flags) {
    return ui_tile_map__flags
        & UI_TILE_MAP__FLAG__IS_ALLOCATED
        ;
}

static inline
void set_ui_tile_map_flags_as__allocated(
        UI_Tile_Map__Flags *p_ui_tile_map__flags) {
    *p_ui_tile_map__flags |=
        UI_TILE_MAP__FLAG__IS_ALLOCATED
        ;
}

static inline
void set_ui_tile_map_flags_as__deallocated(
        UI_Tile_Map__Flags *p_ui_tile_map__flags) {
    *p_ui_tile_map__flags &=
        ~UI_TILE_MAP__FLAG__IS_ALLOCATED
        ;
}

static inline
bool is_ui_tile_map__wrapper_with__data(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return ui_tile_map__wrapper
        .p_ui_tile_data;
}

static inline
bool is_ui_tile_map__wrapper_with__valid_size_catagory(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return ui_tile_map__wrapper
        .catagory_size_of__ui_tile_map
        > UI_Tile_Map_Size__None
        && ui_tile_map__wrapper
        .catagory_size_of__ui_tile_map
        < UI_Tile_Map_Size__Unknown
        ;
}

static inline
bool is_ui_tile_map__wrapper_with__valid_size(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return ui_tile_map__wrapper
        .width_of__ui_tile_map > 0
        && ui_tile_map__wrapper
        .height_of__ui_tile_map > 0
        && is_ui_tile_map__wrapper_with__valid_size_catagory(
                ui_tile_map__wrapper);
        ;
}

static inline
bool is_ui_tile_map__wrapper__valid(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return 
        is_ui_tile_map_flags__allocated(
                *ui_tile_map__wrapper
                .p_ui_tile_map__flags)
        && is_ui_tile_map__wrapper_with__data(
                ui_tile_map__wrapper)
        && is_ui_tile_map__wrapper_with__valid_size(
                ui_tile_map__wrapper)
        ;
}

static inline
UI_Tile_Map__Wrapper get_ui_tile_map__wrapper(
        UI_Tile_Raw *p_ui_tile_data,
        UI_Tile_Map__Flags *p_ui_tile_map__flags,
        Quantity__u32 width_of__tile_map,
        Quantity__u32 height_of__tile_map,
        UI_Tile_Map_Size catagory_size_of__ui_tile_map) {
    return (UI_Tile_Map__Wrapper) {
        p_ui_tile_data,
        p_ui_tile_map__flags,
        width_of__tile_map,
        height_of__tile_map,
        catagory_size_of__ui_tile_map
    };
}

static inline
UI_Tile_Map__Wrapper ui_tile_map__small_to__ui_tile_map_wrapper(
        UI_Tile_Map__Small *p_ui_tile_map__small) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__small->ui_tile_data__small, 
            &p_ui_tile_map__small->ui_tile_map__flags,
            UI_TILE_MAP__SMALL__WIDTH, 
            UI_TILE_MAP__SMALL__HEIGHT,
            UI_Tile_Map_Size__Small);
}

static inline
UI_Tile_Map__Wrapper ui_tile_map__medium_to__ui_tile_map_wrapper(
        UI_Tile_Map__Medium *p_ui_tile_map__medium) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__medium->ui_tile_data__medium, 
            &p_ui_tile_map__medium->ui_tile_map__flags,
            UI_TILE_MAP__MEDIUM__WIDTH, 
            UI_TILE_MAP__MEDIUM__HEIGHT,
            UI_Tile_Map_Size__Medium);
}

static inline
UI_Tile_Map__Wrapper ui_tile_map__large_to__ui_tile_map_wrapper(
        UI_Tile_Map__Large *p_ui_tile_map__large) {
    return get_ui_tile_map__wrapper(
            p_ui_tile_map__large->ui_tile_data__large, 
            &p_ui_tile_map__large->ui_tile_map__flags,
            UI_TILE_MAP__LARGE__WIDTH, 
            UI_TILE_MAP__LARGE__HEIGHT,
            UI_Tile_Map_Size__Large);
}

static inline
UI_Tile_Map__Flags *get_p_ui_tile_map_flags_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return ui_tile_map__wrapper
        .p_ui_tile_map__flags;
}

static inline
UI_Tile_Map_Size get_catagory_size_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    return ui_tile_map__wrapper
        .catagory_size_of__ui_tile_map;
}

static inline
Quantity__u32 get_width_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper ui_tile_map__wraper) {
    return ui_tile_map__wraper
        .width_of__ui_tile_map;
}

static inline
Quantity__u32 get_height_of__ui_tile_map__wrapper(
        UI_Tile_Map__Wrapper ui_tile_map__wraper) {
    return ui_tile_map__wraper
        .height_of__ui_tile_map;
}

#endif

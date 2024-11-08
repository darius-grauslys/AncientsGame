#ifndef UI_TILE_H
#define UI_TILE_H

#include "defines.h"

void initialize_ui_tile_as__empty(UI_Tile *p_ui_tile);

void initialize_ui_tile(
        UI_Tile *p_ui_tile,
        UI_Tile_Kind the_kind_of__ui_tile,
        UI_Tile_Flags ui_tile_flags);

static inline
UI_Tile_Raw get_ui_tile_raw_from__ui_tile(
        const UI_Tile *p_ui_tile) {
    return 
        (p_ui_tile->the_kind_of__ui_tile & MASK(10))
#ifndef UI_TILE__IS_NOT__SAVING_FLAGS_TO__RAW
        | ((p_ui_tile->ui_tile_flags & MASK(6)) << 10)
#endif
        ;
}

static inline
void set_ui_tile_to__ui_tile_raw(
        UI_Tile *p_ui_tile,
        UI_Tile_Raw *p_ui_tile_raw) {
    *p_ui_tile_raw =
        get_ui_tile_raw_from__ui_tile(
                p_ui_tile);
}

static inline
void set_ui_tile_as__flipped_horizontally(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags |=
        UI_TILE_FLAG__FLIPPED_HORIZONTAL
        ;
}

static inline
void set_ui_tile_as__flipped_vertically(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags |=
        UI_TILE_FLAG__FLIPPED_VERTICAL
        ;
}

static inline
void set_ui_tile_as__unflipped_horizontally(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags &=
        ~UI_TILE_FLAG__FLIPPED_HORIZONTAL
        ;
}

static inline
void set_ui_tile_as__unflipped_vertically(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags &=
        ~UI_TILE_FLAG__FLIPPED_VERTICAL
        ;
}

static inline
void set_ui_tile_as__scaling_horizontally(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags |=
        UI_TILE_FLAG__SCALE_HORIZONTAL
        ;
}

static inline
void set_ui_tile_as__scaling_vertically(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags |=
        UI_TILE_FLAG__SCALE_VERTICAL
        ;
}

static inline
void set_ui_tile_as__not_scaling_horizontally(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags &=
        ~UI_TILE_FLAG__SCALE_HORIZONTAL
        ;
}

static inline
void set_ui_tile_as__not_scaling_vertically(
        UI_Tile *p_ui_tile) {
    p_ui_tile->ui_tile_flags &=
        ~UI_TILE_FLAG__SCALE_VERTICAL
        ;
}

#endif

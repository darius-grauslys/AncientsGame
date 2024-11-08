#ifndef UI_TILE_SPAN_H
#define UI_TILE_SPAN_H

#include "defines.h"
#include "defines_weak.h"

void initialize_ui_tile_span_as__empty(
        UI_Tile_Span *p_ui_tile_span);

void initialize_ui_tile_span(
        UI_Tile_Span *p_ui_tile_span,
        UI_Tile ui_tile__corners[4],
        UI_Tile ui_tile__edges[4],
        UI_Tile ui_tile__fill);

const UI_Tile *get_ui_tile_of__ui_tile_span(
        const UI_Tile_Span *p_ui_tile_span,
        Quantity__u32 width_of__ui_tile_span__u32,
        Quantity__u32 height_of__ui_tile_span__u32,
        Index__u32 index_x_of__ui_tile_span__u32,
        Index__u32 index_y_of__ui_tile_span__u32);

#endif

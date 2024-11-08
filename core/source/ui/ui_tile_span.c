#include "ui/ui_tile_span.h"
#include "ui/ui_tile.h"
#include "defines.h"

void initialize_ui_tile_span_as__empty(
        UI_Tile_Span *p_ui_tile_span) {
    for (Index__u32 index_of__corner = 0;
            index_of__corner <
            UI_TILE_SPAN__QUANTITY_OF__CORNERS;
            index_of__corner++) {
        initialize_ui_tile_as__empty(
                &p_ui_tile_span->ui_tile__corners[
                index_of__corner]);
    }
    for (Index__u32 index_of__edge = 0;
            index_of__edge <
            UI_TILE_SPAN__QUANTITY_OF__EDGES;
            index_of__edge++) {
        initialize_ui_tile_as__empty(
                &p_ui_tile_span->ui_tile__edges[
                index_of__edge]);
    }
    initialize_ui_tile_as__empty(
            &p_ui_tile_span->ui_tile__fill);
}

void initialize_ui_tile_span(
        UI_Tile_Span *p_ui_tile_span,
        UI_Tile ui_tile__corners[4],
        UI_Tile ui_tile__edges[4],
        UI_Tile ui_tile__fill) {
    for (Index__u32 index_of__corner = 0;
            index_of__corner <
            UI_TILE_SPAN__QUANTITY_OF__CORNERS;
            index_of__corner++) {
        p_ui_tile_span->ui_tile__corners[
            index_of__corner] =
                ui_tile__corners[index_of__corner];
    }
    for (Index__u32 index_of__edge = 0;
            index_of__edge <
            UI_TILE_SPAN__QUANTITY_OF__EDGES;
            index_of__edge++) {
        p_ui_tile_span->ui_tile__edges[
            index_of__edge] =
                ui_tile__edges[index_of__edge];
    }
    p_ui_tile_span->ui_tile__fill =
        ui_tile__fill;
}

const UI_Tile *get_ui_tile_of__ui_tile_span(
        const UI_Tile_Span *p_ui_tile_span,
        Quantity__u32 width_of__ui_tile_span__u32,
        Quantity__u32 height_of__ui_tile_span__u32,
        Index__u32 index_x_of__ui_tile_span__u32,
        Index__u32 index_y_of__ui_tile_span__u32) {
    bool is_on_left_edge =
        index_x_of__ui_tile_span__u32 == 0
        ;
    bool is_on_right_edge =
        index_x_of__ui_tile_span__u32 ==
        width_of__ui_tile_span__u32
        - 1
        ;

    bool is_on_top_edge =
        index_y_of__ui_tile_span__u32 == 0
        ;

    bool is_on_bottom_edge =
        index_x_of__ui_tile_span__u32 ==
        height_of__ui_tile_span__u32
        - 1
        ;

    if (is_on_top_edge) {
        if (is_on_left_edge)
            return &p_ui_tile_span->ui_tile__corner__top_left;
        if (is_on_right_edge)
            return &p_ui_tile_span->ui_tile__corner__top_right;
        return &p_ui_tile_span->ui_tile__edge__top;
    }
    if (is_on_bottom_edge) {
        if (is_on_left_edge)
            return &p_ui_tile_span->ui_tile__corner__bottom_left;
        if (is_on_right_edge)
            return &p_ui_tile_span->ui_tile__corner__bottom_right;
        return &p_ui_tile_span->ui_tile__edge__bottom;
    }
    if (is_on_left_edge) {
        return &p_ui_tile_span->ui_tile__edge__left;
    }
    if (is_on_right_edge) {
        return &p_ui_tile_span->ui_tile__edge__right;
    }
    return &p_ui_tile_span->ui_tile__fill;
}

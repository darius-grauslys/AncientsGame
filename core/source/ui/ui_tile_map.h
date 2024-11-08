#include "ui/ui_tile.h"
#include "ui/ui_tile_map.h"
#include "ui/ui_tile_span.h"

void generate_ui_span_in__ui_tile_map(
        UI_Tile_Map__Wrapper ui_tile_map__wrapper,
        const UI_Tile_Span *p_ui_tile_span,
        Quantity__u32 width_of__ui_tile_span__u32,
        Quantity__u32 height_of__ui_tile_span__u32,
        Index__u32 index_x__u32,
        Index__u32 index_y__u32) {
    for (Index__u32 index_y_of__ui_tile_span__u32 = 0;
            index_y_of__ui_tile_span__u32 
            < height_of__ui_tile_span__u32;
            index_y_of__ui_tile_span__u32++) {
        u32 y = 
            index_y__u32
            + index_y_of__ui_tile_span__u32
            ;
        if (y >= get_height_of__ui_tile_map__wrapper(
                    &ui_tile_map__wrapper)) {
            break;
        }
        for (Index__u32 index_x_of__ui_tile_span__u32 = 0;
                index_x_of__ui_tile_span__u32
                < width_of__ui_tile_span__u32;
                index_x_of__ui_tile_span__u32++) {
            u32 x = 
                index_x__u32
                + index_x_of__ui_tile_span__u32
                ;
            if (x >= get_width_of__ui_tile_map__wrapper(
                        &ui_tile_map__wrapper)) {
                break;
            }

            UI_Tile_Raw ui_tile_raw = 
                get_ui_tile_raw_from__ui_tile(
                        get_ui_tile_of__ui_tile_span(
                            p_ui_tile_span, 
                            width_of__ui_tile_span__u32, 
                            height_of__ui_tile_span__u32, 
                            index_x_of__ui_tile_span__u32, 
                            index_y_of__ui_tile_span__u32));

            ui_tile_map__wrapper.p_ui_tile_data[
                x + y
                    * get_width_of__ui_tile_map__wrapper(
                            &ui_tile_map__wrapper)] =
                    ui_tile_raw;
        }
    }
}

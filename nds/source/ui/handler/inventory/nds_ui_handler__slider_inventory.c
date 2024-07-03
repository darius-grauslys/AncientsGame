#include "defines_weak.h"
#include "nds_defines.h"
#include "ui/ui_element.h"
#include <ui/handlers/inventory/nds_ui_handler__slider_inventory.h>
#include <ui/ui_slider.h>

void m_NDS_ui_slider__dragged_handler__inventory(
        UI_Element *p_this_slider,
        Game *p_game) {
    m_ui_slider__dragged_handler__default(
            p_this_slider, 
            p_game);

    NDS_Background *p_NDS_background =
        (NDS_Background*)p_this_slider->p_ui_data;

    Vector__3i32 starting_position =
        p_NDS_background->starting_position__3i32;
    Vector__3i32 spanning_scroll_lengths =
        p_NDS_background->spanning_scroll_lengths__3i32;

    bool is_snapped_x_or_y__axis =
        is_ui_element__snapped_x_or_y_axis(p_this_slider);

    i32 *p_modified_position =
        (is_snapped_x_or_y__axis)
        ? &starting_position.y__i32
        : &starting_position.x__i32
        ;

    *p_modified_position +=
        get_offset_from__ui_slider_percentage(
                p_this_slider, 
                (is_snapped_x_or_y__axis)
                ? spanning_scroll_lengths.y__i32
                : spanning_scroll_lengths.x__i32);

    bgSetScroll(
            p_NDS_background->background_index_from__hardware,
            starting_position.x__i32,
            starting_position.y__i32);
}

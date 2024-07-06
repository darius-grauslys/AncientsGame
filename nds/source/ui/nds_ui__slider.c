#include "defines_weak.h"
#include "nds/arm9/background.h"
#include "platform.h"
#include "ui/ui_element.h"
#include <ui/ui_slider.h>
#include <ui/nds_ui__slider.h>
#include <game.h>
#include <nds_defines.h>

void m_NDS_ui_slider__dragged_handler_for__backgrounds(
        UI_Element *p_this_draggable,
        Game *p_game) {
    m_ui_slider__dragged_handler__default(
            p_this_draggable, 
            p_game);

    NDS_Background *p_NDS_background =
        (NDS_Background *)p_this_draggable->p_ui_data;

    bool is_snapped_x_or_y_axis =
        is_ui_element__snapped_x_or_y_axis(p_this_draggable);

    Vector__3i32 position_for__bgSetScroll =
        p_NDS_background
        ->starting_position__3i32;

    i32 *p_starting_distance =
        (is_snapped_x_or_y_axis)
        ? &position_for__bgSetScroll
            .y__i32
        : &position_for__bgSetScroll
            .x__i32
        ;

    i32 spanning_length =
        (is_snapped_x_or_y_axis)
        ? p_NDS_background
            ->spanning_scroll_lengths__3i32.y__i32
        : p_NDS_background
            ->spanning_scroll_lengths__3i32.x__i32
        ;

    *p_starting_distance +=
        get_offset_from__ui_slider_percentage(
                p_this_draggable, 
                spanning_length)
        ;

    bgSetScroll(
            p_NDS_background
            ->background_index_from__hardware, 
            position_for__bgSetScroll.x__i32, 
            position_for__bgSetScroll.y__i32);
    debug_info("x: %d, y: %d",
            position_for__bgSetScroll.x__i32, 
            position_for__bgSetScroll.y__i32);
}

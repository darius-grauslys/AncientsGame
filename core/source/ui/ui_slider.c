#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "numerics.h"
#include "platform.h"
#include "ui/ui_element.h"
#include "vectors.h"
#include <ui/ui_slider.h>

void initialize_ui_element_as__slider(
        UI_Element *p_ui_slider,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Dragged m_ui_dragged_handler,
        bool is_snapped_x_or_y__axis) {
    initialize_ui_element(
            p_ui_slider, 
            p_ui_slider->p_parent,
            p_ui_slider->p_child,
            p_ui_slider->p_next,
            UI_Element_Kind__Slider, 
            p_ui_slider->ui_flags, 
            width__u8, 
            height__u8, 
            position__3i32);
    set_ui_element__dragged_handler(
            p_ui_slider, 
            m_ui_dragged_handler);
    set_ui_element__render_handler(
            p_ui_slider, 
            m_ui_slider__render_handler__default);

    if (is_snapped_x_or_y__axis) {
        set_ui_element_as__snapped_x_axis(p_ui_slider);
    } else {
        set_ui_element_as__snapped_y_axis(p_ui_slider);
    }
}

void m_ui_slider__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game) {
    Input *p_input =
        get_p_input_from__game(p_game);
    bool is_snapped_x_or_y__axis =
        is_ui_element__snapped_x_or_y_axis(p_this_draggable);

    i32 cursor_position =
        (is_snapped_x_or_y__axis)
        ? clamp__i32(p_input->cursor__3i32.y__i32
            - get_y_i32_from__p_ui_element(p_this_draggable)
            + (get_height_from__p_ui_element(p_this_draggable) >> 1),
            0,
            get_height_from__p_ui_element(p_this_draggable))
        : clamp__i32(p_input->cursor__3i32.x__i32
            - get_x_i32_from__p_ui_element(p_this_draggable)
            + (get_width_from__p_ui_element(p_this_draggable) >> 1),
            0,
            get_width_from__p_ui_element(p_this_draggable));
        ;

    p_this_draggable
        ->slider__distance__u32 = 
        cursor_position;
}

void m_ui_slider__render_handler__default(
        UI_Element *p_this_draggable,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Game *p_game) {
    bool is_snapped_x_or_y__axis =
        is_ui_element__snapped_x_or_y_axis(p_this_draggable);

    Vector__3i32 sprite_position =
        get_position_3i32_from__p_ui_element(p_this_draggable);

    i32 cursor_position =
        p_this_draggable
            ->slider__distance__u32;

    if (is_snapped_x_or_y__axis) {
        sprite_position.y__i32 =
            cursor_position
            - get_y_i32_from__p_ui_element(p_this_draggable)
            - (get_height_from__p_ui_element(p_this_draggable) >> 1)
            ;
    } else {
        sprite_position.x__i32 =
            cursor_position
            - get_x_i32_from__p_ui_element(p_this_draggable)
            - (get_width_from__p_ui_element(p_this_draggable) >> 1)
            ;
    }

    PLATFORM_render_sprite(
            p_PLATFORM_gfx_window,
            &p_this_draggable
            ->ui_sprite_wrapper, 
            vector_3i32_to__vector_3i32F4(
                sprite_position));
}

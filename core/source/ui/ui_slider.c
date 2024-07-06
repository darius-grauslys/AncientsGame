#include "defines.h"
#include "defines_weak.h"
#include "game.h"
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
            UI_Element_Kind__Slider, 
            p_ui_slider->ui_flags, 
            width__u8, 
            height__u8, 
            position__3i32);
    set_ui_element__dragged_handler(
            p_ui_slider, 
            m_ui_dragged_handler);
    set_ui_element__dispose_handler(
            p_ui_slider, 
            m_ui_slider__dispose_handler__default);

    p_ui_slider->p_PLATFORM_sprite_for__slider = 0;

    if (is_snapped_x_or_y__axis) {
        set_ui_element_as__snapped_x_axis(p_ui_slider);
    } else {
        set_ui_element_as__snapped_y_axis(p_ui_slider);
    }
}

void m_ui_slider__dispose_handler__default(
        UI_Element *p_this_slider,
        Game *p_game) {
    if (p_this_slider->p_PLATFORM_sprite_for__slider) {
        PLATFORM_release_sprite(
                get_p_PLATFORM_gfx_context_from__game(p_game), 
                p_this_slider->p_PLATFORM_sprite_for__slider);
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
        ? p_input->cursor__3i32.y__i32
        : p_input->cursor__3i32.x__i32
        ;

    Hitbox_AABB *p_hitbox =
        &p_this_draggable
        ->ui_bounding_box__aabb;

    Vector__3i32 sprite_position =
        vector_3i32F4_to__vector_3i32(
                p_hitbox->position__3i32F4);

    i32 *center = 
        (is_snapped_x_or_y__axis)
        ? &sprite_position
            .y__i32
        : &sprite_position
            .x__i32
        ;

    i32 offset =
        (is_snapped_x_or_y__axis)
        ? p_hitbox
            ->height__quantity_u32 >> 1
        : p_hitbox
            ->width__quantity_u32 >> 1
        ;

    *center = cursor_position;

    clamp_p_vector_3i32_to__ui_element(
            p_this_draggable, 
            &sprite_position);

    p_this_draggable
        ->slider__distance__u32 = 
        *center 
        + offset;

    PLATFORM_set_sprite__position(
            p_this_draggable
            ->p_PLATFORM_sprite_for__draggable, 
            sprite_position.x__i32 - 8, 
            sprite_position.y__i32 - 8);
}

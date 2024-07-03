#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include "defines_weak.h"
#include "ui/ui_element.h"
#include "vectors.h"
#include <defines.h>

void initialize_ui_element_as__slider(
        UI_Element *p_ui_slider,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Dragged m_ui_dragged_handler,
        bool is_snapped_x_or_y__axis);

void m_ui_slider__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game);

static inline
void set_ui_slider__PLATFORM_sprite(
        UI_Element *p_ui_slider,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
#ifndef NDEBUG
    if (!is_ui_element_of__this_kind(
                p_ui_slider,
                UI_Element_Kind__Slider)) {
        debug_error("set_ui_slider__PLATFORM_sprite, p_ui_slider is not of UI_Element_Kind__Slider.");
        return;
    }
#endif
    p_ui_slider->p_PLATFORM_sprite_for__slider =
        p_PLATFORM_sprite;
}

static inline
i32F8 get_percentage_i32F8_from__ui_slider(
        UI_Element *p_ui_slider) {
#ifndef NDEBUG
    if (!is_ui_element_of__this_kind(
                p_ui_slider,
                UI_Element_Kind__Slider)) {
        debug_error("get_ui_slider_percentage__i32F8, p_ui_slider is not of UI_Element_Kind__Slider.");
        return 0;
    }
#endif
    return i32_to__i32F8(
            p_ui_slider->slider__distance__u32)
        / (is_ui_element__snapped_x_or_y_axis(p_ui_slider)
        ? p_ui_slider->ui_bounding_box__aabb.height__quantity_u32
        : p_ui_slider->ui_bounding_box__aabb.width__quantity_u32);
}

///
/// Returns a percentage of the range given
/// the state of the slider.
///
static inline
i32 get_offset_from__ui_slider_percentage(
        UI_Element *p_ui_slider,
        i32 range) {
#ifndef NDEBUG
    if (!is_ui_element_of__this_kind(
                p_ui_slider,
                UI_Element_Kind__Slider)) {
        debug_error("get_offset_from__ui_slider_percentage, p_ui_slider is not of UI_Element_Kind__Slider.");
        return 0;
    }
#endif
    return i32F8_to__i32(
            get_percentage_i32F8_from__ui_slider(p_ui_slider)
            * range);
}

static inline
void set_ui_slider_at__this_distance_u32(
        UI_Element *p_ui_slider,
        u32 slider__distance__u32) {
#ifndef NDEBUG
    if (!is_ui_element_of__this_kind(
                p_ui_slider,
                UI_Element_Kind__Slider)) {
        debug_error("set_ui_slider_at__this_distance_u32, p_ui_slider is not of UI_Element_Kind__Slider.");
        return;
    }
#endif
    p_ui_slider->slider__distance__u32 =
        slider__distance__u32;
}

#endif

#include "defines_weak.h"
#include "platform.h"
#include "ui/ui_element.h"
#include <ui/ui_slider.h>
#include <ui/nds_ui__slider.h>
#include <game.h>

void m_NDS_ui_dragged_handler_for__slider(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    PLATFORM_Sprite *p_PLATFORM_sprite =
        (PLATFORM_Sprite*)p_this_ui_element->p_ui_data;
    Vector__3i32 position =
        get_p_input_from__game(p_game)->cursor__3i32;
    if (is_ui_element__snapped_x_or_y_axis(p_this_ui_element)) {
        position.x__i32 = 
            get_x_i32_from__p_ui_element(p_this_ui_element)
            - (p_this_ui_element
                    ->ui_bounding_box__aabb
                    .width__quantity_u32 >> 1)
            ;
    } else {
        position.y__i32 = 
            get_y_i32_from__p_ui_element(p_this_ui_element)
            - (p_this_ui_element
                    ->ui_bounding_box__aabb
                    .height__quantity_u32 >> 1)
            ;
    }
    clamp_p_vector_3i32_to__ui_element(
            p_this_ui_element, 
            &position);

    PLATFORM_set_sprite__position(
            p_PLATFORM_sprite, 
            position.x__i32, 
            position.y__i32);
}

void NDS_initialize_ui_element_as__nds_slider(
        UI_Element *p_ui_element,
        Vector__3i32 position,
        Quantity__u32 width,
        Quantity__u32 height,
        bool is_snapped_x_or_y__axis,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    initialize_ui_element_as__slider(
            p_ui_element,
            width,
            height,
            position,
            m_NDS_ui_dragged_handler_for__slider,
            is_snapped_x_or_y__axis);
    p_ui_element->p_ui_data =
        p_PLATFORM_sprite;
    PLATFORM_set_sprite__position(
            p_PLATFORM_sprite, 
            position.x__i32
            - (p_ui_element->ui_bounding_box__aabb.width__quantity_u32 >> 1), 
            position.y__i32
            - (p_ui_element->ui_bounding_box__aabb.height__quantity_u32 >> 1)
            );
}

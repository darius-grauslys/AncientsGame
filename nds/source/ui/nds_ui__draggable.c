#include <platform_defines.h>
#include "ui/ui_element.h"
#include "vectors.h"
#include <ui/nds_ui__draggable.h>

void NDS_initialize_ui_element_as__nds_draggable(
        UI_Element *p_ui_element,
        PLATFORM_Sprite *p_sprite) {
    p_ui_element->p_ui_data = p_sprite;
    set_ui_element__dragged_handler(
            p_ui_element, 
            m_NDS_ui_dragged__handler);
}

void m_NDS_ui_dragged__handler(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    PLATFORM_Sprite *p_sprite = 
        (p_this_ui_element->p_ui_data);

    Vector__3i32 position =
        vector_3i32F4_to__vector_3i32(
                p_this_ui_element
                ->ui_bounding_box__aabb
                .position__3i32F4);
    PLATFORM_set_sprite__position(
            p_sprite, 
            position.x__i32, position.y__i32);
}

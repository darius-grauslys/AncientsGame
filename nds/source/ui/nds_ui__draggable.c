#include <platform_defines.h>
#include "defines.h"
#include "ui/nds_ui.h"
#include "ui/ui_draggable.h"
#include "ui/ui_element.h"
#include "vectors.h"
#include <ui/nds_ui__draggable.h>

void NDS_initialize_ui_element_as__nds_draggable(
        UI_Element *p_ui_element,
        Vector__3i32 position__3i32,
        PLATFORM_Sprite *p_sprite) {
    initialize_ui_element(
            p_ui_element, 
            UI_Element_Kind__Draggable, 
            p_ui_element->ui_flags,
            0, 
            0,
            position__3i32);
    p_ui_element->p_ui_data = p_sprite;
    set_ui_element__dragged_handler(
            p_ui_element, 
            m_NDS_ui_dragged__handler);
    NDS_set_ui_element_size_using__sprite_size(
            p_ui_element, 
            p_sprite->sprite_texture.sprite_size);
    Vector__3i32 position =
        vector_3i32F4_to__vector_3i32(
                p_ui_element
                ->ui_bounding_box__aabb
                .position__3i32F4);
    PLATFORM_set_sprite__position(
            p_sprite, 
            position.x__i32
            - (p_ui_element->ui_bounding_box__aabb.width__quantity_u32 >> 1), 
            position.y__i32
            - (p_ui_element->ui_bounding_box__aabb.height__quantity_u32 >> 1)
            );
}

void m_NDS_ui_dragged__handler(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    m_ui_draggable__dragged_handler__default(
            p_this_ui_element, p_game);
    PLATFORM_Sprite *p_sprite = 
        (p_this_ui_element->p_ui_data);

    Vector__3i32 position =
        vector_3i32F4_to__vector_3i32(
                p_this_ui_element
                ->ui_bounding_box__aabb
                .position__3i32F4);
    PLATFORM_set_sprite__position(
            p_sprite, 
            position.x__i32
            - (p_this_ui_element->ui_bounding_box__aabb.width__quantity_u32 >> 1), 
            position.y__i32
            - (p_this_ui_element->ui_bounding_box__aabb.height__quantity_u32 >> 1)
            );
}

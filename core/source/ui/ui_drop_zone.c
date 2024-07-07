#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include <ui/ui_drop_zone.h>

void initialize_ui_element_as__drop_zone(
        UI_Element *p_ui_drop_zone,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Receive_Drop m_ui_receive_drop_handler) {
    initialize_ui_element(
            p_ui_drop_zone, 
            p_ui_drop_zone->p_parent,
            p_ui_drop_zone->p_child,
            p_ui_drop_zone->p_next,
            UI_Element_Kind__Button, 
            p_ui_drop_zone->ui_flags,
            width__u8, 
            height__u8,
            position__3i32);
    set_ui_element__receive_drop_handler(
            p_ui_drop_zone, 
            m_ui_receive_drop_handler);
}

void m_ui_drop_zone__receive_drop_handler__default(
        UI_Element *p_this_draggable,
        UI_Element *p_ui_element__dropped,
        Game *p_game) {
    if (p_ui_element__dropped->p_parent) {
        set_ui_element_as__the_parent_of__this_ui_element(
                get_p_ui_manager_from__game(p_game), 
                p_ui_element__dropped->p_parent, 
                p_this_draggable->p_child);
        set_ui_element__position(
                p_this_draggable->p_child, 
                vector_3i32F4_to__vector_3i32(
                    p_ui_element__dropped
                    ->p_parent
                    ->ui_bounding_box__aabb
                    .position__3i32F4));
    }

    set_ui_element_as__the_parent_of__this_ui_element(
            get_p_ui_manager_from__game(p_game), 
            p_this_draggable, 
            p_ui_element__dropped);
}

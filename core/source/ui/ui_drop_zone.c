#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include <ui/ui_drop_zone.h>

void initialize_ui_element_as__drop_zone(
        UI_Element *p_ui_drop_zone,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Recieve_Drop m_ui_recieve_drop_handler) {
    initialize_ui_element(
            p_ui_drop_zone, 
            UI_Element_Kind__Button, 
            p_ui_drop_zone->ui_flags,
            width__u8, 
            height__u8,
            position__3i32);
    set_ui_element__receive_drop_handler(
            p_ui_drop_zone, 
            m_ui_drop_zone__recieve_drop_handler__default);
}

void m_ui_drop_zone__recieve_drop_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game) {

}

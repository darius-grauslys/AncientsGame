#ifndef UI_DROP_ZONE
#define UI_DROP_ZONE

#include <defines.h>

void initialize_ui_element_as__drop_zone(
        UI_Element *p_ui_button,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Receive_Drop m_ui_receive_drop_handler);

void m_ui_drop_zone__receive_drop_handler__default(
        UI_Manager *p_ui_manager,
        UI_Element *p_this_draggable,
        UI_Element *p_ui_element__dropped,
        Game *p_game);

#endif

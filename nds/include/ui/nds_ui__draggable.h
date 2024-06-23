#ifndef NDS_UI__DRAGGABLE_H
#define NDS_UI__DRAGGABLE_H

#include "defines_weak.h"

void NDS_initialize_ui_element_as__nds_draggable(
        UI_Element *p_ui_element,
        Vector__3i32 position__3i32,
        PLATFORM_Sprite *p_sprite);

void m_NDS_ui_dragged__handler(
        UI_Element *p_this_ui_element,
        Game *p_game);

#endif

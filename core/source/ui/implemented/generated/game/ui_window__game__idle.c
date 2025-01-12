#include <ui/implemented/generated/game/ui_window__game__idle.h>
#include <ui/implemented/generated/game/ui_window__game__hud.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_draggable.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./core/assets/ui/xml/ instead of modifying this file.

bool allocate_ui_for__ui_window__game__idle(Gfx_Context *p_gfx_context, Graphics_Window *p_gfx_window, UI_Manager *p_ui_manager){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
allocate_ui_for__ui_window__game__hud(p_gfx_context, p_gfx_window, p_ui_manager);
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_slider, 16, 80, get_vector__3i32(228 + 0, 132 + 0, 0), m_ui_button__clicked_handler__default, false, false);
    UI_Element *p_button__chat = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button__chat, 32, 16, get_vector__3i32(220 + 0, 186 + 0, 0), m_ui_button__clicked_handler__default, false, false);
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 4);
    for (Index__u32 index_of__iteration__1=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__1++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 16, 12, get_vector__3i32(28 + 0* index_of__iteration__1, 96 + 24* index_of__iteration__1, 0), m_ui_button__clicked_handler__default, false, false);
    }
return true;
;
}

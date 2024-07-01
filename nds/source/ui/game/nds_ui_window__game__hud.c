#include <ui/game/nds_ui_window__game__hud.h>
#include <ui/handlers/hud/nds_ui_handler__hud_button.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__hud(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__2++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_NDS_ui_button__clicked_handler__hud);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, true);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 56, 16, get_vector__3i32(56 + 72* index_of__itteration__2, 52 + 0* index_of__itteration__2, 0));
    }

}

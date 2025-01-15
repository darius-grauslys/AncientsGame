#include <ui/implemented/generated/game/ui_window__game__equip.h>
#include <ui/implemented/generated/game/ui_window__game__hud.h>
#include <ui/ui_context.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_draggable.h>
#include <ui/ui_slider.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
#include <ui/ui_drop_zone__inventory_slot.h>
#include <ui/ui_drop_zone__equipment_slot.h>
// THIS CODE IS AUTO GENERATED. Go to ./core/assets/ui/xml/ instead of modifying this file.

bool allocate_ui_for__ui_window__game__equip(Gfx_Context *p_gfx_context, Graphics_Window *p_gfx_window, UI_Manager *p_ui_manager){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
allocate_ui_for__ui_window__game__hud(p_gfx_context, p_gfx_window, p_ui_manager);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 0));
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(p_slider, 16, 80, get_vector__3i32(196 + 0, 132 + 0, 0), get_vector__3i32(0 + 0, 176 + 0, 0 + 0), m_ui_slider__dragged_handler__gfx_window__default, true);

allocate_sprite_for__ui_slider(
    p_gfx_context,
    p_gfx_window,
    p_slider);
    Graphics_Window *p_gfx_window__inv_column =
    open_ui(
    p_gfx_context,
    p_ui_manager,
    0,
    UI_Window_Kind__Inventory_Column);
    p_slider->p_ui_data = 
    p_gfx_window__inv_column;

    UI_Element *p_button_filter__usable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__usable, 16, 16, get_vector__3i32(228 + 0, 104 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_filter__wearable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__wearable, 16, 16, get_vector__3i32(228 + 0, 132 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_filter__consumable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__consumable, 16, 16, get_vector__3i32(228 + 0, 160 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(32 + 28* index_of__iteration__3, 100 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__equipment_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7));
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(32 + 28* index_of__iteration__3, 132 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__equipment_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,9);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(32 + 28* index_of__iteration__3, 164 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__equipment_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,11);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 103 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 131 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,16);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 159 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,19);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 187 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,22);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 215 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,25);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 243 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,28);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 271 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,31);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 299 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,34);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 327 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,37);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

set_ui_element_as__the_parent_of__this_ui_element(
    p_ui_manager,
    p_slider,
    get_p_ui_element_by__index_from__ui_manager(
    p_ui_manager,
    UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));

Graphics_Window *p_gfx_window__equipment =
    open_ui(
    p_gfx_context,
    p_ui_manager,
    0,
    UI_Window_Kind__Equipment);

return true;
;
}

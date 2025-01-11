#include <ui/implemented/generated/game/ui_window__game__trade.h>
#include <ui/implemented/generated/game/ui_window__game__hud.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_draggable.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_slider.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
#include <ui/ui_drop_zone__inventory_slot.h>
// THIS CODE IS AUTO GENERATED. Go to ./core/assets/ui/xml/ instead of modifying this file.

UI_Element *allocate_ui_for__ui_window__game__trade(Game *p_game, PLATFORM_Graphics_Window *p_PLATFORM_gfx_window, UI_Manager *p_ui_manager){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
SDL_allocate_ui_for__sdl_ui_window__game__hud(p_game, p_PLATFORM_gfx_window, p_ui_manager);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 1));
    UI_Element *p_filter_button__usables = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_filter_button__usables, 16, 12, get_vector__3i32(60 + 0, 176 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_filter_button__wearables = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_filter_button__wearables, 16, 12, get_vector__3i32(84 + 0, 176 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_filter_button__consumables = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_filter_button__consumables, 16, 12, get_vector__3i32(108 + 0, 176 + 0, 0), m_ui_button__clicked_handler__default, false, false);


    UI_Element *p_slider_left = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(p_slider_left, 16, 80, get_vector__3i32(28 + 0, 132 + 0, 0), get_vector__3i32(0 + 0, 176 + 0, 0 + 0), m_ui_slider__dragged_handler__gfx_window__default, true);

allocate_sprite_for__ui_slider(
    p_game,
    p_PLATFORM_gfx_window,
    p_slider_left);
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__bg_left =
    SDL_allocate_background_as__PLATFORM_Gfx_Window(
    p_game,
    p_PLATFORM_gfx_window,
    SDL_Background_Kind__Inventory_Column,
    get_vector__3i32(0,0,0));
    p_slider_left->p_ui_data = 
    p_PLATFORM_gfx_window__bg_left;

    UI_Element *p_slider_right = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(p_slider_right, 16, 80, get_vector__3i32(228 + 0, 132 + 0, 0), get_vector__3i32(0 + 0, 176 + 0, 0 + 0), m_ui_slider__dragged_handler__gfx_window__default, true);

allocate_sprite_for__ui_slider(
    p_game,
    p_PLATFORM_gfx_window,
    p_slider_right);
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__bg_right =
    SDL_allocate_background_as__PLATFORM_Gfx_Window(
    p_game,
    p_PLATFORM_gfx_window,
    SDL_Background_Kind__Inventory_Column,
    get_vector__3i32(0,0,0));
    p_slider_right->p_ui_data = 
    p_PLATFORM_gfx_window__bg_right;

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 15 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 15 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 43 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 43 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,14);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 71 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 71 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,20);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 99 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 99 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,26);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 127 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 127 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,32);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 155 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 155 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,38);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 183 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 183 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,44);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 211 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 211 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,50);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(58 + 24* index_of__iteration__3, 239 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__iteration__3, 239 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,56);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 15 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 15 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 43 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 43 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,68);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 71 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 71 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,74);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 99 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 99 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,80);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 127 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 127 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,86);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 155 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 155 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,92);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 183 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 183 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,98);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 211 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 211 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,104);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(150 + 24* index_of__iteration__3, 239 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
                p_ui_iterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_iterator);
        initialize_ui_element_as__draggable(p_ui_iterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__iteration__3, 239 + 0* index_of__iteration__3, 0), m_ui_draggable__dragged_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,110);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

set_ui_element_as__the_parent_of__this_ui_element(
    p_ui_manager,
    p_slider_left,
    get_p_ui_element_by__index_from__ui_manager(
    p_ui_manager,
    UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__LEFT_8));
    set_ui_element_as__the_parent_of__this_ui_element(
    p_ui_manager,
    p_slider_right, 
    get_p_ui_element_by__index_from__ui_manager(
    p_ui_manager,
    UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__RIGHT_62));

    UI_Element *p_bg_left = allocate_ui_element_from__ui_manager(p_ui_manager);
    SDL_initialize_ui_element_as__background(p_bg_left, 256, 256, get_vector__3i32(41 + 0, 86 + 0, 0), p_PLATFORM_gfx_window__bg_left);

    UI_Element *p_bg_right = allocate_ui_element_from__ui_manager(p_ui_manager);
    SDL_initialize_ui_element_as__background(p_bg_right, 256, 256, get_vector__3i32(134 + 0, 86 + 0, 0), p_PLATFORM_gfx_window__bg_right);

}

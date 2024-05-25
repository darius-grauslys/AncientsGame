#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "input/input.h"
#include <ui/ui_element.h>
#include <ui/ui_manager.h>

void init_ui_manager(
        UI_Manager *p_ui_manager) {
    p_ui_manager->p_ui_element__focused = 0;
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element *p_ui_element =
            &p_ui_manager->ui_elements[ui_index];
        init_ui_element(
                p_ui_element, 
                UI_Element_Kind__None, 
                1, 
                1);
        p_ui_element->ui_identifier = ui_index;
        p_ui_manager->ui_element_ptrs[ui_index] = 0;
    }
}

static bool inline is_not_at_end_of__ui_element_array(
        UI_Manager *p_ui_manager,
        Quantity__u8 ui_index) {
    return 
        ui_index < UI_ELEMENT_MAXIMUM_QUANTITY_OF
        && p_ui_manager->ui_element_ptrs[ui_index]
        && is_ui_element__allocated(p_ui_manager->ui_element_ptrs[ui_index]);
}

static bool inline does_ui_manager_have__focused_ui_element(
        UI_Manager *p_ui_manager) {
    return (bool)(p_ui_manager->p_ui_element__focused);
}

static void inline drop_ui_element_focus_for__ui_manager(
        UI_Manager *p_ui_manager) {
    p_ui_manager
        ->p_ui_element__focused = 0;
}

UI_Element *get_highest_priority_ui_element_thats__under_the_cursor(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    for (Quantity__u8 ui_index=0;
            is_not_at_end_of__ui_element_array(p_ui_manager, ui_index);
            ui_index++) {
        UI_Element *p_ui_element =
            p_ui_manager->ui_element_ptrs[ui_index];
        if (!is_ui_element__enabled(p_ui_element)) {
            continue;
        }

        if (is_vector_inside__hitbox(
                    p_input->cursor__i32f4, 
                    &p_ui_element->ui_bounding_box__aabb)) {
            return p_ui_element;
        }
    }
    return 0;
}

void poll_ui_manager_for__focused_ui_element_with__cursor_holding(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_input);
    if (!does_ui_element_have__held_handler(p_ui_element__focused))
        return;
    p_ui_manager->p_ui_element__focused =
        p_ui_element__focused;
    set_ui_element_as__being_held(
            p_ui_element__focused);
}

void poll_ui_manager_for__focused_ui_element_with__cursor_dragging(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_input);
    if (!does_ui_element_have__dragged_handler(p_ui_element__focused))
        return;
    p_ui_manager->p_ui_element__focused =
        p_ui_element__focused;
    set_ui_element_as__being_dragged(
            p_ui_element__focused);
}

void poll_ui_manager__update_for__drag(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    if (!does_ui_manager_have__focused_ui_element(p_ui_manager)) {
        poll_ui_manager_for__focused_ui_element_with__cursor_dragging(
                p_ui_manager, 
                p_input);
        // Still don't have focus? quit early.
        if (!does_ui_manager_have__focused_ui_element(p_ui_manager))
            return;
    }
    if (!does_ui_element_have__dragged_handler(
                p_ui_manager->p_ui_element__focused))
        return;
    if (is_ui_element__being_held(
                p_ui_manager->p_ui_element__focused)) {
        set_ui_element_as__dropped(p_ui_manager->p_ui_element__focused);
        set_ui_element_as__being_dragged(p_ui_manager->p_ui_element__focused);
    }
    p_ui_manager
        ->p_ui_element__focused
        ->m_ui_dragged_handler(
                p_ui_manager
                ->p_ui_element__focused,
                p_input);
}

void poll_ui_manager__update_for__held(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    if (!does_ui_manager_have__focused_ui_element(p_ui_manager)) {
        poll_ui_manager_for__focused_ui_element_with__cursor_holding(
                p_ui_manager, 
                p_input);
        // Still don't have focus? quit early.
        if (!does_ui_manager_have__focused_ui_element(p_ui_manager))
            return;
    }
    if (is_ui_element__being_dragged(
                p_ui_manager->p_ui_element__focused)) {
        poll_ui_manager__update_for__drag(
                p_ui_manager,
                p_input);
        return;
    }
    if (!does_ui_element_have__held_handler(
                p_ui_manager->p_ui_element__focused))
        return;
    p_ui_manager
        ->p_ui_element__focused
        ->m_ui_held_handler(
                p_ui_manager
                ->p_ui_element__focused,
                p_input);
}

void poll_ui_manager__update_for__drop(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    if (!p_ui_manager->p_ui_element__focused
            || !does_ui_element_have__dropped_handler(
                p_ui_manager->p_ui_element__focused))
        return;
    set_ui_element_as__dropped(
            p_ui_manager->p_ui_element__focused);
    if (!does_ui_element_have__dropped_handler(
                p_ui_manager->p_ui_element__focused))
        return;
    p_ui_manager
        ->p_ui_element__focused
        ->m_ui_dropped_handler(
                p_ui_manager
                ->p_ui_element__focused,
                p_input);
    drop_ui_element_focus_for__ui_manager(p_ui_manager);
}

void poll_ui_manager__update_for__clicked(
        UI_Manager *p_ui_manager,
        Input *p_input) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_input);
    if (!does_ui_element_have__clicked_handler(p_ui_element__focused))
        return;
    p_ui_element__focused->m_ui_clicked_handler(
            p_ui_element__focused,
            p_input);
}

void poll_ui_manager__update(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    Input *p_input = &p_game->input;

    bool has_ui_element__focus =
        does_ui_manager_have__focused_ui_element(p_ui_manager);

    if (is_input__click_released(p_input)) {
        if (!has_ui_element__focus) {
            poll_ui_manager__update_for__clicked(
                    p_ui_manager, 
                    p_input);
            return;
        }
        poll_ui_manager__update_for__drop(
                p_ui_manager,
                p_input);
        return;
    }

    if (!has_ui_element__focus)
        return;
    if (is_input__click_held(p_input)) {
        poll_ui_manager__update_for__held(
                p_ui_manager, 
                p_input);
        return;
    }
    if (is_input__click_dragged(p_input)) {
        poll_ui_manager__update_for__drag(
                p_ui_manager, 
                p_input);
        return;
    }
}

UI_Element **get_next__available_slot_in__ui_element_ptrs(
        UI_Manager *p_ui_manager) {
    for (Quantity__u8 ui_ptr_index=0;
            ui_ptr_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_ptr_index++) {
        UI_Element **p_ui_element_ptr =
            &p_ui_manager->ui_element_ptrs[ui_ptr_index];
        if (!(*p_ui_element_ptr))
            return p_ui_element_ptr;
    }
    debug_abort("Next ui_element_ptrs slot unavailable.");
    return 0;
}

UI_Element *get_new__ui_element(
        UI_Manager *p_ui_manager,
        enum UI_Element_Kind kind_of_ui_element,
        Quantity__u8 width,
        Quantity__u8 height) {
    UI_Element **p_ui_element_ptr =
        get_next__available_slot_in__ui_element_ptrs(
                p_ui_manager);
    if (!p_ui_element_ptr) {
        goto failure;
    }

    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element *p_ui_element =
            &p_ui_manager->ui_elements[ui_index];
        if (!is_ui_element__allocated(p_ui_element)) {
            *p_ui_element_ptr =
                p_ui_element;
            p_ui_manager->quantity_of__ui_elements__quantity_u8++;
            init_ui_element(
                    p_ui_element, 
                    kind_of_ui_element, 
                    width, 
                    height);
            p_ui_element->ui_identifier = ui_index;
            return p_ui_element;
        }
    }
failure:
    debug_abort("Cannot allocate new UI_Element.");
    return 0;
}

void release__ui_element(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element) {
    if (p_ui_manager->quantity_of__ui_elements__quantity_u8 == 0) {
#ifndef NDEBUG
        debug_error("Tried to release UI_Element %p while ui_manager is empty.",
                p_ui_element);
        debug_warning("Did you not call get_new__ui_element for this ui_element?");
#endif
        return;
    }
    if (p_ui_element->m_ui_dispose_handler) {
        p_ui_element->m_ui_dispose_handler(
                p_ui_manager,
                p_ui_element);
    }
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element **p_ui_element_ptr =
            &p_ui_manager->ui_element_ptrs[ui_index];
        if (*p_ui_element_ptr != p_ui_element)
            continue;
        // swap with last ui_element_ptr
        for (Quantity__u8 ui_sub_index=ui_index+1;
                ui_sub_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
                ui_sub_index++) {
            UI_Element **p_ui_element_ptr__for_swap =
                &p_ui_manager->ui_element_ptrs[ui_sub_index];
            if (!*p_ui_element_ptr__for_swap) {
                *p_ui_element_ptr =
                    *p_ui_element_ptr__for_swap;
                *p_ui_element_ptr__for_swap = 0;
                break;
            }
        }
        break;
    }
    p_ui_manager->quantity_of__ui_elements__quantity_u8--;
}

void raise_priority_of_this__ui_element__with_respect_to_other__ui_element(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__this,
        UI_Element *p_ui_element__other) {
    UI_Element **p_ui_element_ptr__this = 0;
    UI_Element **p_ui_element_ptr__other = 0;
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element **p_ui_element_ptr =
            &p_ui_manager->ui_element_ptrs[ui_index];
        if (*p_ui_element_ptr == p_ui_element__this) {
            // Check if p_ui_element_this already has higher priority.
            if (!p_ui_element_ptr__other)
                return;
            p_ui_element_ptr__this =
                p_ui_element_ptr;
            continue;
        }
        if (*p_ui_element_ptr == p_ui_element__other) {
            if (!p_ui_element_ptr__this) {
                *p_ui_element_ptr__other =
                    p_ui_element__this;
                *p_ui_element_ptr__this =
                    p_ui_element__other;
                return;
            }
            p_ui_element_ptr__other =
                p_ui_element_ptr;
        }
    }
}

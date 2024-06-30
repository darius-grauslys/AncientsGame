#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "input/input.h"
#include <ui/ui_element.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <game.h>

void initialize_ui_manager(
        UI_Manager *p_ui_manager) {
    p_ui_manager->p_ui_element__focused = 0;
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element *p_ui_element =
            &p_ui_manager->ui_elements[ui_index];
        initialize_ui_element(
                p_ui_element, 
                UI_Element_Kind__None, 
                UI_FLAGS__NONE,
                1, 
                1,
                get_vector__3i32(0,0,0));
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
        Game *p_game) {
    Vector__3i32 cursor_position =
        (is_input__click_released(&p_game->input))
        ? p_game->input.cursor__old__3i32
        : p_game->input.cursor__3i32;
        ;
    for (Quantity__u8 ui_index=0;
            is_not_at_end_of__ui_element_array(p_ui_manager, ui_index);
            ui_index++) {
        UI_Element *p_ui_element =
            p_ui_manager->ui_element_ptrs[ui_index];
        if (!is_ui_element__enabled(p_ui_element)) {
            continue;
        }

        //TODO: look into why using cursor old.
        if (is_vector_3i32_inside__hitbox(
                    cursor_position,
                    &p_ui_element->ui_bounding_box__aabb)) {
            return p_ui_element;
        }
    }
    return 0;
}

void poll_ui_manager_for__focused_ui_element_with__cursor_holding(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_game);
    if (!does_ui_element_have__held_handler(p_ui_element__focused))
        return;
    p_ui_manager->p_ui_element__focused =
        p_ui_element__focused;
    set_ui_element_as__being_held(
            p_ui_element__focused);
}

void poll_ui_manager_for__focused_ui_element_with__cursor_dragging(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_game);
    if (!does_ui_element_have__dragged_handler(p_ui_element__focused))
        return;
    p_ui_manager->p_ui_element__focused =
        p_ui_element__focused;
    set_ui_element_as__being_dragged(
            p_ui_element__focused);
}

void poll_ui_manager__update_for__drag(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    if (!does_ui_manager_have__focused_ui_element(p_ui_manager)) {
        poll_ui_manager_for__focused_ui_element_with__cursor_dragging(
                p_ui_manager, 
                p_game);
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
                p_game);
}

void poll_ui_manager__update_for__held(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    if (!does_ui_manager_have__focused_ui_element(p_ui_manager)) {
        poll_ui_manager_for__focused_ui_element_with__cursor_holding(
                p_ui_manager, 
                p_game);
        // Still don't have focus? quit early.
        if (!does_ui_manager_have__focused_ui_element(p_ui_manager))
            return;
    }
    if (is_ui_element__being_dragged(
                p_ui_manager->p_ui_element__focused)) {
        poll_ui_manager__update_for__drag(
                p_ui_manager,
                p_game);
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
                p_game);
}

void poll_ui_manager__update_for__drop(
        UI_Manager *p_ui_manager,
        Game *p_game) {
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
        ->m_ui_recieve_drop_handler(
                p_ui_manager
                ->p_ui_element__focused,
                p_game);
    drop_ui_element_focus_for__ui_manager(p_ui_manager);
}

void poll_ui_manager__update_for__clicked(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    UI_Element *p_ui_element__focused =
        get_highest_priority_ui_element_thats__under_the_cursor(
                p_ui_manager, 
                p_game);
    if (!p_ui_element__focused) {
        return;
    }
    if (!does_ui_element_have__clicked_handler(p_ui_element__focused))
        return;
    p_ui_element__focused->m_ui_clicked_handler(
            p_ui_element__focused,
            p_game);
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
                    p_game);
            return;
        }
        poll_ui_manager__update_for__drop(
                p_ui_manager,
                p_game);
        drop_ui_element_focus_for__ui_manager(p_ui_manager);
        return;
    }

    if (is_input__click_held(p_input)) {
        poll_ui_manager__update_for__held(
                p_ui_manager, 
                p_game);
        return;
    }
    if (is_input__click_dragged(p_input)) {
        poll_ui_manager__update_for__drag(
                p_ui_manager, 
                p_game);
        return;
    }
}

UI_Element **get_next__available_slot_in__ui_element_ptrs(
        UI_Manager *p_ui_manager) {
    Quantity__u8 ui_ptr_index = 0;
    for (;ui_ptr_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_ptr_index++) {
        UI_Element **p_ui_element_ptr =
            &p_ui_manager->ui_element_ptrs[ui_ptr_index];
        if (!(*p_ui_element_ptr))
            return p_ui_element_ptr;
    }
    debug_abort("Next ui_element_ptrs slot unavailable. ui_ptr_index = %d.", 
            ui_ptr_index);
    return 0;
}

UI_Element *allocate_ui_element_from__ui_manager(
        UI_Manager *p_ui_manager) {
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
            initialize_ui_element(
                    p_ui_element, 
                    UI_Element_Kind__None,
                    UI_FLAGS__NONE,
                    1,
                    1,
                    get_vector__3i32(0,0,0));
            p_ui_element->ui_identifier = ui_index;
            set_ui_element_as__allocated(p_ui_element);
            set_ui_element_as__enabled(p_ui_element);
            return p_ui_element;
        }
    }
failure:
    debug_abort("Cannot allocate new UI_Element.");
    return 0;
}

void allocate_many_ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager,
        UI_Element **p_ptr_buffer,
        Quantity__u8 quantity_of__ui_elements_in__ptr_buffer
        ) {
    if (quantity_of__ui_elements_in__ptr_buffer
            > UI_ELEMENT_MAXIMUM_QUANTITY_OF) {
        return;
    }
    for (Quantity__u8 buffer_index=0;
            buffer_index<quantity_of__ui_elements_in__ptr_buffer;
            buffer_index++) {
        p_ptr_buffer[buffer_index] =
            allocate_ui_element_from__ui_manager(p_ui_manager);
    }
}

UI_Element *allocate_many_ui_elements_from__ui_manager_in__succession(
        UI_Manager *p_ui_manager,
        Quantity__u8 quantity_of__ui_elements_to__allocate
        ) {
    if (quantity_of__ui_elements_to__allocate == 0)
        return 0;
    UI_Element *p_head = allocate_ui_element_from__ui_manager(
            p_ui_manager);
    UI_Element *p_current = p_head;

    for (Quantity__u8 quantity_of__ui_elements__allocated = 1;
            quantity_of__ui_elements__allocated < 
                quantity_of__ui_elements_to__allocate;
            quantity_of__ui_elements__allocated++) {
        p_current->p_next =
            allocate_ui_element_from__ui_manager(p_ui_manager);
        p_current = p_current->p_next;
    }
    return p_head;
}

UI_Element *allocate_many_ui_elements_from__ui_manager_as__recursive_children(
        UI_Manager *p_ui_manager,
        Quantity__u8 quantity_of__ui_elements_to__allocate
        ) {
    if (quantity_of__ui_elements_to__allocate == 0)
        return 0;
    UI_Element *p_parent = allocate_ui_element_from__ui_manager(
            p_ui_manager);
    UI_Element *p_current = p_parent;

    for (Quantity__u8 quantity_of__ui_elements__allocated = 1;
            quantity_of__ui_elements__allocated < 
                quantity_of__ui_elements_to__allocate;
            quantity_of__ui_elements__allocated++) {
        p_current->p_child =
            allocate_ui_element_from__ui_manager(p_ui_manager);
        p_current = p_current->p_child;
    }
    return p_parent;
}

void release__ui_element_from__ui_manager(
        UI_Element *p_ui_element,
        Game *p_game) {
    UI_Manager *p_ui_manager =
        get_p_ui_manager_from__game(p_game);
    if (p_ui_manager->quantity_of__ui_elements__quantity_u8 == 0) {
#ifndef NDEBUG
        debug_error("Tried to release UI_Element %p while ui_manager is empty.",
                p_ui_element);
        debug_warning("Did you not call get_new__ui_element for this ui_element?");
#endif
        return;
    }
    if (p_ui_element->m_ui_dispose_handler
            && is_ui_element__allocated(p_ui_element)) {
        // the second clause of the if statement
        // is in the case of a p_next->m_ui_dispose_handler
        // invocation chain.
        p_ui_element->m_ui_dispose_handler(
                p_ui_element,
                p_game);
    }
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element **p_ui_element_ptr =
            &p_ui_manager->ui_element_ptrs[ui_index];
        UI_Element **p_ui_element_ptr__for_swap =
            &p_ui_manager->ui_element_ptrs[ui_index];
        if (*p_ui_element_ptr != p_ui_element)
            continue;
        // swap with last ui_element_ptr
        for (Quantity__u8 ui_sub_index=ui_index;
                ui_sub_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
                ui_sub_index++) {
            p_ui_element_ptr__for_swap =
                &p_ui_manager->ui_element_ptrs[ui_sub_index];
            if (!*p_ui_element_ptr__for_swap) {
                break;
            }
        }
        *p_ui_element_ptr =
            *p_ui_element_ptr__for_swap;
        *p_ui_element_ptr__for_swap = 0;
        break;
    }
    p_ui_manager->quantity_of__ui_elements__quantity_u8--;
}

void release_all__ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager,
        Game *p_game) {
    for (Quantity__u8 ui_index=0;
            ui_index<UI_ELEMENT_MAXIMUM_QUANTITY_OF;
            ui_index++) {
        UI_Element **p_ui_element_ptr = 
            &p_ui_manager->ui_element_ptrs[ui_index];
        if (!p_ui_element_ptr) {
            return;
        }

        if (does_ui_element_have__dispose_handler(*p_ui_element_ptr)) {
            (*p_ui_element_ptr)->m_ui_dispose_handler(
                    *p_ui_element_ptr,
                    p_game);
        }
        
        set_ui_element_as__deallocated(*p_ui_element_ptr);
        *p_ui_element_ptr = 0;
    }
    p_ui_manager
        ->quantity_of__ui_elements__quantity_u8 = 0;
}

void swap_priority_of__ui_elenents_within__ui_manager(
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

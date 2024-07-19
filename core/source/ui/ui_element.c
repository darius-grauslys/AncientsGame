#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_button.h"
#include "ui/ui_draggable.h"
#include "ui/ui_slider.h"
#include <ui/ui_element.h>
#include <vectors.h>
#include <game.h>

void initialize_ui_element(
        UI_Element *p_ui_element,
        UI_Element *p_ui_element__parent,
        UI_Element *p_ui_element__child,
        UI_Element *p_ui_element__next,
        enum UI_Element_Kind kind_of_ui_element,
        UI_Flags__u8 ui_flags,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32) {
    p_ui_element->p_ui_data = 0;
    p_ui_element->p_parent = p_ui_element__parent;
    p_ui_element->p_child = p_ui_element__child;
    p_ui_element->p_next = p_ui_element__next;
    p_ui_element->ui_identifier = 
        IDENTIFIER__UNKNOWN__u16;
    p_ui_element->the_kind_of_ui_element__this_is =
        kind_of_ui_element;
    p_ui_element->ui_flags = ui_flags;
    initialize_hitbox(
            &p_ui_element->ui_bounding_box__aabb, 
            width__u8, 
            height__u8, 
            vector_3i32_to__vector_3i32F4(position__3i32));
    p_ui_element->m_ui_clicked_handler = 0;
    p_ui_element->m_ui_dragged_handler = 0;
    p_ui_element->m_ui_receive_drop_handler = 0;
    p_ui_element->m_ui_held_handler = 0;
    p_ui_element->m_ui_dispose_handler = 
        m_ui_element__dispose_handler__default;
    p_ui_element->p_PLATFORM_sprite = 0;
}

void m_ui_element__dispose_handler__default(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    set_ui_element_as__deallocated(p_this_ui_element);
    if (does_ui_element_have__child(p_this_ui_element)) {
        UI_Element *p_child =
            get_child_of__ui_element(p_this_ui_element);
        if (does_ui_element_have__dispose_handler(p_child)) {
            p_child->m_ui_dispose_handler(
                    p_child,
                    p_game);
        }
    }
    if (p_this_ui_element->p_PLATFORM_sprite) {
        PLATFORM_release_sprite(
                get_p_PLATFORM_gfx_context_from__game(p_game), 
                p_this_ui_element->p_PLATFORM_sprite); 
    }
    p_this_ui_element->p_PLATFORM_sprite = 0;
    p_this_ui_element->p_parent = 0;
    p_this_ui_element->p_child = 0;
    p_this_ui_element->p_next = 0;
}

void m_ui_element__dispose_handler__default_collection(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    m_ui_element__dispose_handler__default(
            p_this_ui_element, 
            p_game);
    UI_Element *p_next =
        get_next__ui_element(p_this_ui_element);
    if (!p_next) return;

    do {
        UI_Element *p_disposing_element = p_next;
        p_next = get_next__ui_element(p_next);
        if (does_ui_element_have__dispose_handler(p_disposing_element)) {
            p_disposing_element->m_ui_dispose_handler(
                    p_disposing_element, 
                    p_game);
        }
    } while (p_next);
}

void set_positions_of__ui_elements_in__succession(
        UI_Element *p_ui_element__succession_collection,
        Vector__3i32 starting_position__3i32,
        i32 x__stride,
        Quantity__u32 quantity_of__elements_per_row,
        i32 y__stride) {
    Index__u32 index_of__current_ui_element = 0;
    Vector__3i32 current_position__3i32 = 
        starting_position__3i32;
    do {
        set_position_3i32_of__ui_element(
                p_ui_element__succession_collection, 
                current_position__3i32);
        if (++index_of__current_ui_element
                == quantity_of__elements_per_row) {
            index_of__current_ui_element = 0;
            current_position__3i32.y__i32 += y__stride;
            current_position__3i32.x__i32 =
                starting_position__3i32.x__i32;
        } else {
            current_position__3i32.x__i32 += x__stride;
        }
    } while (
            iterate_to_next__ui_element(
                &p_ui_element__succession_collection));
}

void set_position_3i32_of__ui_element(
        UI_Element *p_ui_element,
        Vector__3i32 position__3i32) {
    Vector__3i32 vector_of__child_relative_to__parent =
        VECTOR__3i32__0_0_0;
    if (does_ui_element_have__child(p_ui_element)) {
        vector_of__child_relative_to__parent =
            subtract_vectors__3i32(
                position__3i32, 
                vector_3i32F4_to__vector_3i32(
                    p_ui_element
                    ->ui_bounding_box__aabb
                    .position__3i32F4));
    }
    p_ui_element->ui_bounding_box__aabb
        .position__3i32F4 = 
            vector_3i32_to__vector_3i32F4(position__3i32);
    if (p_ui_element->p_PLATFORM_sprite)
        PLATFORM_set_sprite__position(
                p_ui_element->p_PLATFORM_sprite, 
                get_x_i32_from__p_ui_element(p_ui_element), 
                get_y_i32_from__p_ui_element(p_ui_element));
    if (does_ui_element_have__child(p_ui_element)) {
        set_position_3i32_of__ui_element(
                p_ui_element->p_child,
                add_vectors__3i32(
                    vector_of__child_relative_to__parent, 
                    get_position_3i32_from__p_ui_element(p_ui_element)));
    }
}

void set_ui_element__PLATFORM_sprite(
        UI_Element *p_ui_element,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
#ifndef NDEBUG
    if(!p_PLATFORM_sprite) {
        debug_error("set_ui_element__PLATFORM_sprite, p_PLATFORM_sprite is null.");
        debug_warning("Do not dispose sprites this way. Use release_ui_element__PLATFORM_sprite instead.");
        return;
    }
#endif
    p_ui_element->p_PLATFORM_sprite =
        p_PLATFORM_sprite;
    PLATFORM_set_sprite__position(
            p_PLATFORM_sprite, 
            get_x_i32_from__p_ui_element(p_ui_element), 
            get_y_i32_from__p_ui_element(p_ui_element));
}

void release_ui_element__PLATFORM_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        UI_Element *p_ui_element) {
    if (!p_ui_element->p_PLATFORM_sprite) {
#ifndef NDEBUG
        debug_error("release_ui_element__PLATFORM_sprite, p_PLATFORM_sprite is null.");
#endif
        return;
    }

    PLATFORM_release_sprite(
            p_PLATFORM_gfx_context,
            p_ui_element->p_PLATFORM_sprite);

    p_ui_element->p_PLATFORM_sprite = 0;
}

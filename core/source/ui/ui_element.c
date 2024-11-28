#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "platform_defaults.h"
#include "ui/ui_button.h"
#include "ui/ui_draggable.h"
#include "ui/ui_slider.h"
#include "ui/ui_tile_map.h"
#include <ui/ui_element.h>
#include <vectors.h>
#include <game.h>
#include <wctype.h>

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
    p_ui_element->m_ui_render_handler = 0;
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
    set_ui_element_as__using_sprite(
            p_ui_element);
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

void set_ui_tile_span_of__ui_element(
        UI_Element *p_ui_element,
        UI_Tile_Span *p_ui_tile_span) {
    set_ui_element_as__using_ui_tile_span(
            p_ui_element);
    p_ui_element->ui_tile_span =
        *p_ui_tile_span;
}

const UI_Tile_Span *get_ui_tile_span_of__ui_element(
        UI_Element *p_ui_element,
        Quantity__u32 *p_width_in__tiles,
        Quantity__u32 *p_height_in__tiles,
        Index__u32 *p_index_x__u32, 
        Index__u32 *p_index_y__u32) {
    if (is_ui_element__using_sprite(
            p_ui_element)) {
        *p_width_in__tiles = 0;
        *p_height_in__tiles = 0;
        *p_index_x__u32 = 0;
        *p_index_y__u32 = 0;
        return 0;
    }

    *p_width_in__tiles = 
        p_ui_element
        ->ui_bounding_box__aabb
        .width__quantity_u32
        / UI_TILE__WIDTH_IN__PIXELS;
    *p_height_in__tiles =
        p_ui_element
        ->ui_bounding_box__aabb
        .height__quantity_u32
        / UI_TILE__HEIGHT_IN__PIXELS;

    *p_index_x__u32 = 
        (p_ui_element
        ->ui_bounding_box__aabb
        .position__3i32F4
        .x__i32F4
        / UI_TILE__WIDTH_IN__PIXELS)
        - (*p_width_in__tiles >> 1);
    *p_index_y__u32 =
        (p_ui_element
        ->ui_bounding_box__aabb
        .position__3i32F4
        .y__i32F4
        / UI_TILE__HEIGHT_IN__PIXELS)
        - (*p_height_in__tiles >> 1);

    return &p_ui_element->ui_tile_span;
}

void m_ui_render__element__tile_span(
        UI_Element *p_ui_element,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Game *p_game) {
    Quantity__u32 width_of__ui_tile_span; 
    Quantity__u32 height_of__ui_tile_span;
    Index__u32 index_x__u32; 
    Index__u32 index_y__u32;
    const UI_Tile_Span *p_const_ui_tile_span =
        get_ui_tile_span_of__ui_element(
                p_ui_element,
                &width_of__ui_tile_span,
                &height_of__ui_tile_span,
                &index_x__u32,
                &index_y__u32);

    generate_ui_span_in__ui_tile_map(
            PLATFORM_get_tile_map__wrapper_from__gfx_window(
                p_PLATFORM_gfx_window), 
            p_const_ui_tile_span, 
            width_of__ui_tile_span, 
            height_of__ui_tile_span, 
            index_x__u32, 
            index_y__u32);
}

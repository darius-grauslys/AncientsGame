#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "collisions/hitbox_aabb.h"
#include "defines_weak.h"
#include "numerics.h"
#include "vectors.h"
#include <defines.h>

static Signed_Index__i32 inline get_x_i32_from__p_ui_element(
        UI_Element *p_ui_element) {
    return get_x_i32_from__hitbox(&p_ui_element->ui_bounding_box__aabb);
}
static Signed_Index__i32 inline get_y_i32_from__p_ui_element(
        UI_Element *p_ui_element) {
    return get_y_i32_from__hitbox(&p_ui_element->ui_bounding_box__aabb);
}
static Signed_Index__i32 inline get_z_i32_from__p_ui_element(
        UI_Element *p_ui_element) {
    return get_z_i32_from__hitbox(&p_ui_element->ui_bounding_box__aabb);
}

static inline
Quantity__u32 get_width_from__p_ui_element(
        UI_Element *p_ui_element) {
    return p_ui_element->ui_bounding_box__aabb.width__quantity_u32;
} 

static inline
Quantity__u32 get_height_from__p_ui_element(
        UI_Element *p_ui_element) {
    return p_ui_element->ui_bounding_box__aabb.height__quantity_u32;
}

///
/// Logically associate a contiguous collection of
/// UI_Element via p_next pointers. Forming a one-way
/// linked list.
///
static inline
void link_ui_element_to__this_ui_element(
        UI_Element *p_predecessor,
        UI_Element *p_successor) {
    if (p_predecessor == p_successor)
        p_predecessor->p_next = 0;
    p_predecessor->p_next =
        p_successor;
}

///
/// Establish a form of ownership via p_parent.
///
static inline
void set_ui_element_as__the_parent_of__this_ui_element(
        UI_Element *p_parent,
        UI_Element *p_child) {
    if (p_parent == p_child)
        p_parent->p_parent = 0;
    p_child->p_parent =
        p_parent;
}

static inline
UI_Element *get_next__ui_element(
        UI_Element *p_ui_element) {
    return p_ui_element->p_next;
}

static inline
UI_Element *get_parent_of__ui_element(
        UI_Element *p_ui_element) {
    return p_ui_element->p_parent;
}

static inline
UI_Element *get_child_of__ui_element(
        UI_Element *p_ui_element) {
    return p_ui_element->p_child;
}

static inline
UI_Element *itterate_to_next__ui_element(
        UI_Element **p_ui_element_ptr) {
    if (!(*p_ui_element_ptr)->p_next)
        return 0;
    *p_ui_element_ptr =
        (*p_ui_element_ptr)->p_next;
    return *p_ui_element_ptr;
}

static inline 
UI_Element *itterate_to_parent_of__ui_element(
        UI_Element **p_ui_element_ptr) {
    if (!(*p_ui_element_ptr)->p_parent)
        return 0;
    *p_ui_element_ptr =
        (*p_ui_element_ptr)->p_parent;
    return *p_ui_element_ptr;
}

static inline 
UI_Element *itterate_to_child_of__ui_element(
        UI_Element **p_ui_element_ptr) {
    if (!(*p_ui_element_ptr)->p_child)
        return 0;
    *p_ui_element_ptr =
        (*p_ui_element_ptr)->p_child;
    return *p_ui_element_ptr;
}

void initialize_ui_element(
        UI_Element *p_ui_element,
        enum UI_Element_Kind kind_of_ui_element,
        UI_Flags__u8 ui_flags,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32);

void m_ui_element__dispose_handler__default(
        UI_Element *p_this_ui_element,
        Game *p_game);

static bool inline is_ui_element__allocated(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_ALLOCATED);
}

static bool inline is_ui_element__enabled(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_ENABLED);
}

static bool inline is_ui_element__in_needing_update(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_NEEDING_UPDATE);
}

static bool inline is_ui_element__being_held(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_BEING_HELD);
}

static bool inline is_ui_element__being_dragged(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_BEING_DRAGGED);
}

static bool inline is_ui_element__snapped_x_or_y_axis(UI_Element *p_ui_element) {
    return (bool)(p_ui_element->ui_flags & UI_FLAGS__BIT_IS_SNAPPED_X_OR_Y_AXIS);
}

static bool inline is_ui_element__focused(
        UI_Element *p_ui_element) {
    return is_ui_element__being_held(p_ui_element)
        || is_ui_element__being_dragged(p_ui_element);
}

static bool inline does_ui_element_have__parent(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->p_parent;
}

static bool inline does_ui_element_have__child(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->p_child;
}

static bool inline does_ui_element_have__next(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->p_next;
}

//TODO: move to private header
static void inline set_ui_element_as__allocated(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags |=
        UI_FLAGS__BIT_IS_ALLOCATED;
}

//TODO: move to private header
static void inline set_ui_element_as__deallocated(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags &=
        ~UI_FLAGS__BIT_IS_ALLOCATED;
}

static void inline set_ui_element_as__being_dragged(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags |=
        UI_FLAGS__BIT_IS_BEING_DRAGGED;
}

static void inline set_ui_element_as__being_held(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags |=
        UI_FLAGS__BIT_IS_BEING_HELD;
}

static void inline set_ui_element_as__dropped(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags &=
        ~UI_FLAGS__BIT_IS_BEING_HELD
        & ~UI_FLAGS__BIT_IS_BEING_DRAGGED;
}

static void inline set_ui_element_as__snapped_x_axis(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags |=
        UI_FLAGS__BIT_IS_SNAPPED_X_OR_Y_AXIS;
}

static void inline set_ui_element_as__snapped_y_axis(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags &=
        ~UI_FLAGS__BIT_IS_SNAPPED_X_OR_Y_AXIS;
}

static void inline set_ui_element_as__enabled(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags |=
        UI_FLAGS__BIT_IS_ENABLED;
}

static void inline set_ui_element_as__disabled(
        UI_Element *p_ui_element) {
    p_ui_element->ui_flags &=
        ~UI_FLAGS__BIT_IS_ENABLED;
}

static void inline set_ui_element__clicked_handler(
        UI_Element *p_ui_element,
        m_UI_Clicked m_ui_clicked_handler) {
    p_ui_element->m_ui_clicked_handler =
        m_ui_clicked_handler;
}

static void inline set_ui_element__dragged_handler(
        UI_Element *p_ui_element,
        m_UI_Dragged m_ui_dragged_handler) {
    p_ui_element->m_ui_dragged_handler =
        m_ui_dragged_handler;
}

static void inline set_ui_element__dropped_handler(
        UI_Element *p_ui_element,
        m_UI_Dragged m_ui_dropped_handler) {
    p_ui_element->m_ui_dropped_handler =
        m_ui_dropped_handler;
}

static void inline set_ui_element__held_handler(
        UI_Element *p_ui_element,
        m_UI_Dragged m_ui_held_handler) {
    p_ui_element->m_ui_held_handler =
        m_ui_held_handler;
}

static bool inline does_ui_element_have__dispose_handler(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->m_ui_dispose_handler;
}

static bool inline does_ui_element_have__clicked_handler(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->m_ui_clicked_handler;
}

static bool inline does_ui_element_have__dragged_handler(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->m_ui_dragged_handler;
}

static bool inline does_ui_element_have__dropped_handler(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->m_ui_dropped_handler;
}

static bool inline does_ui_element_have__held_handler(
        UI_Element *p_ui_element) {
    return (bool)p_ui_element->m_ui_held_handler;
}

static inline
void clamp_p_vector_3i32_to__ui_element(
        UI_Element *p_ui_element,
        Vector__3i32 *p_position__3i32) {
    clamp_p_vector_3i32_to__hitbox(
            &p_ui_element->ui_bounding_box__aabb, 
            p_position__3i32);
}

#endif

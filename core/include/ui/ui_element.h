#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "collisions/hitbox_aabb.h"
#include "defines_weak.h"
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

void initialize_ui_element(
        UI_Element *p_ui_element,
        enum UI_Element_Kind kind_of_ui_element,
        UI_Flags__u8 ui_flags,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32);

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

static bool inline is_ui_element__focused(
        UI_Element *p_ui_element) {
    return is_ui_element__being_held(p_ui_element)
        || is_ui_element__being_dragged(p_ui_element);
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

#endif

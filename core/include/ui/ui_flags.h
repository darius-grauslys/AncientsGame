#ifndef UI_FLAGS_H
#define UI_FLAGS_H

#include <defines.h>

static bool inline is_ui_flags__allocated(UI_Flags__u8 ui_flags__u8) {
    return (bool)(ui_flags__u8 & UI_FLAGS__BIT_IS_ALLOCATED);
}

static bool inline is_ui_flags__enabled(UI_Flags__u8 ui_flags__u8) {
    return (bool)(ui_flags__u8 & UI_FLAGS__BIT_IS_ENABLED);
}

static bool inline is_ui_flags__needing_update(UI_Flags__u8 ui_flags__u8) {
    return (bool)(ui_flags__u8 & UI_FLAGS__BIT_IS_NEEDING_UPDATE);
}

static bool inline is_ui_flags__being_held(UI_Flags__u8 ui_flags__u8) {
    return (bool)(ui_flags__u8 & UI_FLAGS__BIT_IS_BEING_HELD);
}

static bool inline is_ui_flags__being_dragged(UI_Flags__u8 ui_flags__u8) {
    return (bool)(ui_flags__u8 & UI_FLAGS__BIT_IS_BEING_DRAGGED);
}

static bool inline is_ui_flags__focused(
        UI_Flags__u8 ui_flags__u8) {
    return is_ui_flags__being_held(ui_flags__u8)
        || is_ui_flags__being_dragged(ui_flags__u8);
}

static void inline set_p_ui_flags__u8_as__allocated(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 |=
        UI_FLAGS__BIT_IS_ALLOCATED;
}

//TODO: move to private header
static void inline set_p_ui_flags__u8_as__deallocated(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 &=
        ~UI_FLAGS__BIT_IS_ALLOCATED;
}

static void inline set_p_ui_flags__u8_as__being_dragged(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 |=
        UI_FLAGS__BIT_IS_BEING_DRAGGED;
}

static void inline set_p_ui_flags__u8_as__being_held(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 |=
        UI_FLAGS__BIT_IS_BEING_HELD;
}

static void inline set_p_ui_flags__u8_as__dropped(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 &=
        ~UI_FLAGS__BIT_IS_BEING_HELD
        & ~UI_FLAGS__BIT_IS_BEING_DRAGGED;
}

static void inline set_p_ui_flags__u8_as__enabled(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 |=
        UI_FLAGS__BIT_IS_ENABLED;
}

static void inline set_p_ui_flags__u8_as__disabled(
        UI_Flags__u8 *p_ui_flags__u8) {
    *p_ui_flags__u8 &=
        ~UI_FLAGS__BIT_IS_ENABLED;
}

#endif

#ifndef INPUT_H
#define INPUT_H

#include <vectors.h>
#include <defines.h>

static void inline clear_input(Input *p_input) {
    p_input->input_flags__held = INPUT_NONE;
    p_input->input_flags__pressed = INPUT_NONE;
    p_input->input_flags__released = INPUT_NONE;
    p_input->cursor__old__i32f4 =
        p_input->cursor__i32f4;
    initialize_3i32F4_vector(&p_input->cursor__i32f4);
}

static bool inline is_input__forward_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_FORWARD;
}
static bool inline is_input__left_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_LEFT;
}
static bool inline is_input__right_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_RIGHT;
}
static bool inline is_input__backward_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_BACKWARD;
}
static bool inline is_input__game_settings_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_GAME_SETTINGS;
}
static bool inline is_input__lockon_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_LOCKON;
}
static bool inline is_input__use_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_USE;
}
static bool inline is_input__use_secondary_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_USE_SECONDARY;
}
static bool inline is_input__examine_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_EXAMINE;
}
static bool inline is_input__consume_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_CONSUME;
}
static bool inline is_input__none_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_NONE;
}
static bool inline is_input__click_released(Input *p_input) {
    return p_input->input_flags__released & INPUT_CLICK;
}



static bool inline is_input__forward_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_FORWARD;
}
static bool inline is_input__left_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_LEFT;
}
static bool inline is_input__right_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_RIGHT;
}
static bool inline is_input__backward_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_BACKWARD;
}
static bool inline is_input__game_settings_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_GAME_SETTINGS;
}
static bool inline is_input__lockon_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_LOCKON;
}
static bool inline is_input__use_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_USE;
}
static bool inline is_input__use_secondary_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_USE_SECONDARY;
}
static bool inline is_input__examine_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_EXAMINE;
}
static bool inline is_input__consume_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_CONSUME;
}
static bool inline is_input__none_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_NONE;
}
static bool inline is_input__click_pressed(Input *p_input) {
    return p_input->input_flags__pressed & INPUT_CLICK;
}



static bool inline is_input__forward_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_FORWARD;
}
static bool inline is_input__left_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_LEFT;
}
static bool inline is_input__right_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_RIGHT;
}
static bool inline is_input__backward_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_BACKWARD;
}
static bool inline is_input__game_settings_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_GAME_SETTINGS;
}
static bool inline is_input__lockon_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_LOCKON;
}
static bool inline is_input__use_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_USE;
}
static bool inline is_input__use_secondary_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_USE_SECONDARY;
}
static bool inline is_input__examine_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_EXAMINE;
}
static bool inline is_input__none_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_NONE;
}
static bool inline is_input__consume_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_CONSUME;
}
static bool inline is_input__click_held(Input *p_input) {
    return p_input->input_flags__held & INPUT_CLICK
        && is_3i32F4_vectors__equal(
                p_input->cursor__i32f4,
                p_input->cursor__old__i32f4)
                ;
}

static bool inline is_input__click_dragged(Input *p_input) {
    return p_input->input_flags__held & INPUT_CLICK
        && !is_3i32F4_vectors__equal(
                p_input->cursor__i32f4,
                p_input->cursor__old__i32f4)
                ;
}

#endif

#ifndef INPUT_H
#define INPUT_H

#include <defines.h>

static void inline clear_input(Game *game) {
    game->input.input_flags = INPUT_NONE;
}

static bool inline is_input__forward(Game *game) {
    return game->input.input_flags & INPUT_FORWARD;
}
static bool inline is_input__left(Game *game) {
    return game->input.input_flags & INPUT_LEFT;
}
static bool inline is_input__right(Game *game) {
    return game->input.input_flags & INPUT_RIGHT;
}
static bool inline is_input__backwards(Game *game) {
    return game->input.input_flags & INPUT_BACKWARDS;
}

static bool inline is_input__game_settings(Game *game) {
    return game->input.input_flags & INPUT_GAME_SETTINGS;
}
static bool inline is_input__lockon(Game *game) {
    return game->input.input_flags & INPUT_LOCKON;
}
static bool inline is_input__use(Game *game) {
    return game->input.input_flags & INPUT_USE;
}
static bool inline is_input__use_secondary(Game *game) {
    return game->input.input_flags & INPUT_USE_SECONDARY;
}
static bool inline is_input__examine(Game *game) {
    return game->input.input_flags & INPUT_EXAMINE;
}

static bool inline is_input__none(Game *game) {
    return game->input.input_flags & INPUT_NONE;
}

#endif

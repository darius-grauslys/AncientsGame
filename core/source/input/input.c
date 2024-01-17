#include <input/input.h>

void clear_input(Game *game) {
    game->input.input_flags = INPUT_NONE;
}

bool is_input__forward(Game *game) {
    return game->input.input_flags & INPUT_FORWARD;
}
bool is_input__left(Game *game) {
    return game->input.input_flags & INPUT_LEFT;
}
bool is_input__right(Game *game) {
    return game->input.input_flags & INPUT_RIGHT;
}
bool is_input__backwards(Game *game) {
    return game->input.input_flags & INPUT_BACKWARDS;
}

bool is_input__game_settings(Game *game) {
    return game->input.input_flags & INPUT_GAME_SETTINGS;
}
bool is_input__inventory(Game *game) {
    return game->input.input_flags & INPUT_INVENTORY;
}
bool is_input__use(Game *game) {
    return game->input.input_flags & INPUT_USE;
}

bool is_input__none(Game *game) {
    return game->input.input_flags & INPUT_NONE;
}

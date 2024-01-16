#include <input/input.h>

void clear_input(Input *input) {
    input->input_flags = INPUT_NONE;
}

bool is_input__forward(Input *input) {
    return input->input_flags & INPUT_FORWARD;
}
bool is_input__left(Input *input) {
    return input->input_flags & INPUT_LEFT;
}
bool is_input__right(Input *input) {
    return input->input_flags & INPUT_RIGHT;
}
bool is_input__backwards(Input *input) {
    return input->input_flags & INPUT_BACKWARDS;
}

bool is_input__game_settings(Input *input) {
    return input->input_flags & INPUT_GAME_SETTINGS;
}
bool is_input__inventory(Input *input) {
    return input->input_flags & INPUT_INVENTORY;
}
bool is_input__use(Input *input) {
    return input->input_flags & INPUT_USE;
}

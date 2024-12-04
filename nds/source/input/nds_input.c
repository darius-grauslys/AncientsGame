#include "defines.h"
#include <nds.h>
#include <input/input.h>

void PLATFORM_poll_input(
        Game *p_game,
        Input *p_input) {
    scanKeys();
    int keys_held = keysHeld();
    int keys_pressed = keysDown();
    int keys_released = keysUp();

    touchPosition stylist;
    touchRead(&stylist);

    clear_input(p_input);

    p_input->input_flags__held = keys_held;
    p_input->input_flags__pressed = keys_pressed;
    p_input->input_flags__released = keys_released;

    p_input->cursor__3i32
        .x__i32 = stylist.px;
    p_input->cursor__3i32
        .y__i32 = stylist.py;
}

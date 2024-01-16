#include <nds.h>
#include <input/input.h>

void PLATFORM_poll_input(Input *input) {
    scanKeys();
    int keys = keysHeld();

    clear_input(input);

    if (keys & KEY_A) {
        input->input_flags |=
            INPUT_USE;
    }
    if (keys & KEY_X) {
        input->input_flags |=
            INPUT_INVENTORY;
    }
    if (keys & KEY_START) {
        input->input_flags |=
            INPUT_GAME_SETTINGS;
    }

    if (keys & KEY_UP) {
        input->input_flags |=
            INPUT_FORWARD;
    }
    if (keys & KEY_LEFT) {
        input->input_flags |=
            INPUT_LEFT;
    }
    if (keys & KEY_RIGHT) {
        input->input_flags |=
            INPUT_RIGHT;
    }
    if (keys & KEY_DOWN) {
        input->input_flags |=
            INPUT_DOWN;
    }
}

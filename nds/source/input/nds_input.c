#include <nds.h>
#include <input/input.h>

void PLATFORM_poll_input(Game *game) {
    scanKeys();
    int keys = keysHeld();

    clear_input(game);

    if (keys & KEY_A) {
        game->input.input_flags |=
            INPUT_USE;
    }
    if (keys & KEY_X) {
        game->input.input_flags |=
            INPUT_INVENTORY;
    }
    if (keys & KEY_START) {
        game->input.input_flags |=
            INPUT_GAME_SETTINGS;
    }

    if (keys & KEY_UP) {
        game->input.input_flags |=
            INPUT_FORWARD;
    }
    if (keys & KEY_LEFT) {
        game->input.input_flags |=
            INPUT_LEFT;
    }
    if (keys & KEY_RIGHT) {
        game->input.input_flags |=
            INPUT_RIGHT;
    }
    if (keys & KEY_DOWN) {
        game->input.input_flags |=
            INPUT_BACKWARDS;
    }
}

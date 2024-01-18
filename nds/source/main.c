
#include <nds.h>
#include <defines.h>

#include <input/input.h>

#include <game.h>

Game game;

int main(void) {
    init_game(&game);

	while(1) {
        //swiWaitForVBlank();
        manage_game(&game);
        if (is_input__game_settings(&game)) break;
	}

    return 0;
}

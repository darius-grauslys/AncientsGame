#include "game_action/game_actions__singleplayer.h"
#include <defines.h>
#include <game.h>

Game game;

int main(void) {
    init_game(&game, m_game_action_handler_for__singleplayer);
    return run_game(&game);
}

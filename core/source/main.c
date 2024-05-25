#include <defines.h>
#include <game.h>

Game game;

int main(void) {
    init_game(&game);
    return run_game(&game);
}

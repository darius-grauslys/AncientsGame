#ifndef INPUT_H
#define INPUT_H

#include <defines.h>

void PLATFORM_poll_input(Game *game);

void clear_input(Game *game);

bool is_input__forward(Game *game);
bool is_input__left(Game *game);
bool is_input__right(Game *game);
bool is_input__backwards(Game *game);

bool is_input__game_settings(Game *game);
bool is_input__inventory(Game *game);
bool is_input__use(Game *game);

bool is_input__none(Game *game);

#endif

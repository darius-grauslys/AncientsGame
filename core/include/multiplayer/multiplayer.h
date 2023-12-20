#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <defines.h>

bool is_in_multiplayer_game(Game* game);
bool is_host(Game* game);
USER_ID get_user_id(Game* game);

#endif

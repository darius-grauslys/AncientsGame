#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>

void init_game(Game *game);

void manage_game(Game *game);

void PLATFORM_pre_render(Game *game);
void PLATFORM_post_render(Game *game);

void manage_game__pre_render(Game *game);
void manage_game__post_render(Game *game);
void manage_entities(Game *game);
void release_entity(Game *game, Entity *entity);

#endif

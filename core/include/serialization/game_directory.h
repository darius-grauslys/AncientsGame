#ifndef GAME_DIRECTORY_H
#define GAME_DIRECTORY_H

#include <defines.h>

///
/// This holds things such as settings, server data
/// and world save names.
///
Index__u32 stat_game_data_file(
        Game *p_game,
        char *buffer);

///
/// Only call this from the main menu.
///
void save_game(
        Game *p_game);

#endif

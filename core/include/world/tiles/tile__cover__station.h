#ifndef TILE__COVER__STATION_H
#define TILE__COVER__STATION_H

#include <defines.h>

void f_tile_interact_handler__table(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity);

void register_tile_handlers_for__table(
        Tile_Logic_Manager *p_tile_logic_managers);

#endif

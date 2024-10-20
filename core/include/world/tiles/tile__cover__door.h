#ifndef TILE__COVER__DOOR_H
#define TILE__COVER__DOOR_H

#include "defines.h"
#include <world/tile.h>

void set_tile_cover_as__door(
        Tile *p_tile,
        Tile_Kind the_kind_of__door,
        bool is_horizontal_or__vertical,
        bool is_closed_or__opened);

void f_tile_interact_handler__door(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity);

void register_tile_handlers_for__door(
        Tile_Logic_Manager *p_tile_logic_managers);

#endif

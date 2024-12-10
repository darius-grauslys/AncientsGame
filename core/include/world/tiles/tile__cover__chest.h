#ifndef TILE__COVER__CHEST_H
#define TILE__COVER__CHEST_H

#include <world/tile.h>

///
/// Does not check if p_tile actually
/// resides at tile_vector__3i32.
///
bool set_tile_cover_as__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32);

void f_tile_interact_handler__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity);

bool f_tile_handler__destroy__chest(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32);

void register_tile_handlers_for__chest(
        Tile_Logic_Manager *p_tile_logic_managers);

#endif

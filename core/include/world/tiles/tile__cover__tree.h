#ifndef TILE__COVER__TREE_H
#define TILE__COVER__TREE_H

#include <world/tile.h>

void set_tile_cover_as__tree(
        Tile *p_tile,
        u8 variation);

void register_tile_handlers_for__trees(
        Tile_Logic_Manager *p_tile_logic_manager);

#endif

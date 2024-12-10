#ifndef TILE__COVER__ORE_H
#define TILE__COVER__ORE_H

#include <world/tile.h>

///
/// The Tile_Kind must correspond to an ore.
///
/// p_tile__right, the tile immediately right of p_tile.
/// variation, should usually be a random value.
/// is_large, if true, p_tile__right cannot be null.
///
void set_tile_cover_as__ore(
        Tile *p_tile,
        Tile *p_tile__right,
        enum Item_Kind the_kind_of__ore,
        u8 variation,
        bool is_large);

void register_tile_handlers_for__ore(
        Tile_Logic_Manager *p_tile_logic_manager);

#endif

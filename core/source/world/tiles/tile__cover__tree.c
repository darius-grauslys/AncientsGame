#include "defines_weak.h"
#include "world/tile.h"
#include <world/tiles/tile__cover__tree.h>

void set_tile_cover_as__tree(
        Tile *p_tile,
        u8 variation) {
    variation %= 3;
    switch(variation) {
        default:
        case 0:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Stump;
            break;
        case 1:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Tree__Oak;
            break;
        case 2:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Tree__Pine;
            break;
    }

    set_tile__is_unpassable(p_tile, true);
}
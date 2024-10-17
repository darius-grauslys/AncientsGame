#ifndef TILE__COVER__CACTUS_H
#define TILE__COVER__CACTUS_H

#include <world/tile.h>

///
/// Growth indicates how far along
/// the crop has grown.
///
void set_tile_cover_as__cactus(
        Tile *p_tile,
        enum Item_Kind the_kind_of__crop,
        bool is_small_or__large);

#endif

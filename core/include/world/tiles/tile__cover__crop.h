#ifndef TILE__COVER__CROP_H
#define TILE__COVER__CROP_H

#include <world/tile.h>

///
/// Growth indicates how far along
/// the crop has grown.
///
void set_tile_cover_as__crop(
        Tile *p_tile,
        enum Item_Kind the_kind_of__crop,
        u8 growth);

#endif

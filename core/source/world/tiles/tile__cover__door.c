#include "defines_weak.h"
#include <world/tiles/tile__cover__door.h>

void set_tile_cover_as__door(
        Tile *p_tile,
        Tile_Kind the_kind_of__door,
        bool is_horizontal_or__vertical) {
    switch (the_kind_of__door) {
        default:
            debug_error("set_tile_cover_as__door, illegal value for, the_kind_of__door: %d", the_kind_of__door);
            break;
        case Tile_Kind__Diamond:
            break;
        case Tile_Kind__Amethyst:
            break;
        case Tile_Kind__Stone:
            break;
        case Tile_Kind__Stone_Brick:
            break;
        case Tile_Kind__Oak_Wood:
            break;
        case Tile_Kind__Gold:
            break;
        case Tile_Kind__Iron:
            break;
        case Tile_Kind__Sandstone:
            break;
        case Tile_Kind__Sand:
            break;
        case Tile_Kind__Dirt:
            break;
    }
}

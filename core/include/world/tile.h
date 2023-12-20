#ifndef TILE_H
#define TILE_H

#include <defines.h>

typedef struct Tile_t {
    enum Tile_Kind          the_kind_of_tile__this_tile_is;
    enum Tile_Cover_Kind    the_kind_of_tile_cover__this_tile_has;
    bool is_passable;
    bool is_sight_blocking;
} Tile;

#endif

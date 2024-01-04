#include <world/tile.h>
#include <stdbool.h>

void init_tile(Tile *tile, enum Tile_Kind kind_of_tile) {
    tile->the_kind_of_tile__this_tile_is =
        kind_of_tile;
    tile->the_kind_of_tile_cover__this_tile_has =
        Tile_Cover_Kind__None;
    switch (kind_of_tile) {
        default:
        case Tile_Kind__Void:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Grass:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Dirt:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Sand:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Oak_Wood:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Stone:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Stone_Brick:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Iron:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Gold:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Diamond:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Amethyst:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
        case Tile_Kind__Sandstone:
            tile->is_passable = true;
            tile->is_sight_blocking = false;
            break;
    }
}

#include <world/tile.h>
#include <stdbool.h>

void init_tile(Tile *tile, enum Tile_Kind kind_of_tile,
        uint8_t flags) {
    tile->flags = flags;
    tile->the_kind_of_tile__this_tile_is =
        kind_of_tile;
    tile->the_kind_of_tile_cover__this_tile_has =
        Tile_Cover_Kind__None;
}

uint32_t get_tile_sheet_index(Tile *tile) {
    switch (tile->the_kind_of_tile__this_tile_is) {
        default:
            return 0;
        case Tile_Kind__Oak_Wood:
            return TILE_SHEET_INDEX__WOOD;
        case Tile_Kind__Stone_Brick:
            return TILE_SHEET_INDEX__STONE_BRICK;
        case Tile_Kind__Gold:
            return TILE_SHEET_INDEX__GOLD;
        case Tile_Kind__Iron:
            return TILE_SHEET_INDEX__IRON;
        case Tile_Kind__Diamond:
            return TILE_SHEET_INDEX__DIAMOND;
        case Tile_Kind__Amethyst:
            return TILE_SHEET_INDEX__AMEYTHYST;
        case Tile_Kind__Sandstone:
            return TILE_SHEET_INDEX__SANDSTONE;
        case Tile_Kind__Stone:
            return TILE_SHEET_INDEX__STONE;
        case Tile_Kind__Dirt:
            return TILE_SHEET_INDEX__DIRT;
        case Tile_Kind__Sand:
            return TILE_SHEET_INDEX__SAND;
        case Tile_Kind__Grass:
            return TILE_SHEET_INDEX__GRASS;
        //TODO: leaves and snow
        // case Tile_Kind__Snow:
        //     return TILE_SHEET_INDEX__DIRT;
    }
}

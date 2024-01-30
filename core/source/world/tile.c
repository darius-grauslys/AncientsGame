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

void init_tile_structure(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Structure_Kind kind_of_tile_structure) {
    init_tile(tile, kind_of_tile, TILE_FLAGS__NONE);
    set_tile__is_passable(
            tile, 
            is_tile_structure_kind__passable(
                kind_of_tile_structure)
            );
    set_tile__sight_blocking(
            tile, 
            is_tile_structure_kind__sight_blocking(
                kind_of_tile_structure)
            );
    //TODO: finish this
}

uint32_t get_tile_texture_sheet_index(Tile *tile) {
    switch (tile->the_kind_of_tile__this_tile_is) {
        default:
            return (uint32_t)tile->the_kind_of_tile__this_tile_is;
        case Tile_Kind__Oak_Wood:
        case Tile_Kind__Stone_Brick:
        case Tile_Kind__Gold:
        case Tile_Kind__Iron:
        case Tile_Kind__Diamond:
        case Tile_Kind__Amethyst:
        case Tile_Kind__Sandstone:
        case Tile_Kind__Stone:
        case Tile_Kind__Dirt:
        case Tile_Kind__Sand:
        case Tile_Kind__Grass:
            goto tile_structure;
        //TODO: leaves and snow
        // case Tile_Kind__Snow:
        //     return TILE_SHEET_INDEX__DIRT;
        case Tile_Kind__Water:
            return TILE_SHEET_INDEX__WATER;
    }
tile_structure:
    uint32_t index = 0;
    switch (tile->the_kind_of_tile__this_tile_is) {
        default:
        case Tile_Kind__Oak_Wood:
            index = TILE_SHEET_INDEX__WOOD;
			break;
        case Tile_Kind__Stone_Brick:
            index = TILE_SHEET_INDEX__STONE_BRICK;
			break;
        case Tile_Kind__Gold:
            index = TILE_SHEET_INDEX__GOLD;
			break;
        case Tile_Kind__Iron:
            index = TILE_SHEET_INDEX__IRON;
			break;
        case Tile_Kind__Diamond:
            index = TILE_SHEET_INDEX__DIAMOND;
			break;
        case Tile_Kind__Amethyst:
            index = TILE_SHEET_INDEX__AMEYTHYST;
			break;
        case Tile_Kind__Sandstone:
            index = TILE_SHEET_INDEX__SANDSTONE;
			break;
        case Tile_Kind__Stone:
            index = TILE_SHEET_INDEX__STONE;
			break;
        case Tile_Kind__Dirt:
            index = TILE_SHEET_INDEX__DIRT;
			break;
        case Tile_Kind__Sand:
            index = TILE_SHEET_INDEX__SAND;
			break;
        case Tile_Kind__Grass:
            index = TILE_SHEET_INDEX__GRASS;
			break;
    }
    switch (tile->the_kind_of_tile_structure__this_tile_is) {
        default:
        case Tile_Structure_Kind__Floor:
            return index;
        case Tile_Structure_Kind__Stair_Ascending:
            return 0;
    }
}


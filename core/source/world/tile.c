#include <world/tile.h>
#include <stdbool.h>

void init_tile(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Cover_Kind kind_of_tile_cover,
        uint8_t flags) {
    tile->flags = flags;
    tile->the_kind_of_tile__this_tile_is =
        kind_of_tile;
    tile->the_kind_of_tile_cover__this_tile_has =
        kind_of_tile_cover;
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
    if (is_tile__stairs(tile)) {
        int32_t offset = 0;
        
        // TODO: magic numbers, but its not that bad.
        // they will only be used here, but who knows
        // what the future might require?
        switch(get_tile__stair_direction(tile)) {
            case TILE_STAIR_DIRECTION_EAST:
            case TILE_STAIR_DIRECTION_WEST:
                offset = TILE_SHEET_ELEMENT_WIDTH;
                break;
            case TILE_STAIR_DIRECTION_NORTH:
            case TILE_STAIR_DIRECTION_SOUTH:
                offset = TILE_SHEET_ELEMENT_WIDTH * 2;
                break;
            case TILE_STAIR_DIRECTION_NORTH_EAST:
            case TILE_STAIR_DIRECTION_NORTH_WEST:
            case TILE_STAIR_DIRECTION_SOUTH_EAST:
            case TILE_STAIR_DIRECTION_SOUTH_WEST:
                if (is_tile__inverted_stairs(tile)) {
                    offset = TILE_SHEET_ELEMENT_WIDTH * 4;
                } else {
                    offset = TILE_SHEET_ELEMENT_WIDTH * 3;
                }
                break;
        }
        if (is_tile__up_or_down_stairs(tile)) {
            offset += TILE_SHEET_ELEMENT_WIDTH * 4;
        }

        return index + offset;
    }
    return index;
}

uint32_t get_tile_cover_texture_sheet_index(Tile *tile) {
    switch(tile->the_kind_of_tile_cover__this_tile_has) {
        default:
        case Tile_Cover_Kind__Wall__Dirt:
            return TILE_COVER_SHEET_INDEX__WALL__DIRT;
        case Tile_Cover_Kind__Wall__Sand:
            return TILE_COVER_SHEET_INDEX__WALL__SAND;
        case Tile_Cover_Kind__Wall__Oak_Wood:
            return TILE_COVER_SHEET_INDEX__WALL__WOOD;
        case Tile_Cover_Kind__Wall__Stone:
            return TILE_COVER_SHEET_INDEX__WALL__STONE;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            return TILE_COVER_SHEET_INDEX__WALL__STONE_BRICK;
        case Tile_Cover_Kind__Wall__Iron:
            return TILE_COVER_SHEET_INDEX__WALL__IRON;
        case Tile_Cover_Kind__Wall__Gold:
            return TILE_COVER_SHEET_INDEX__WALL__GOLD;
        case Tile_Cover_Kind__Wall__Diamond:
            return TILE_COVER_SHEET_INDEX__WALL__DIAMOND;
        case Tile_Cover_Kind__Wall__Amethyst:
            return TILE_COVER_SHEET_INDEX__WALL__AMEYTHYST;
        case Tile_Cover_Kind__Wall__Sandstone:
            return TILE_COVER_SHEET_INDEX__WALL__SANDSTONE;
        case Tile_Cover_Kind__Plant:
            return TILE_COVER_SHEET_INDEX__PLANT;
        case Tile_Cover_Kind__Flower_Red:
            return TILE_COVER_SHEET_INDEX__FLOWER_RED;
        case Tile_Cover_Kind__Flower_Blue:
            return TILE_COVER_SHEET_INDEX__FLOWER_BLUE;
        case Tile_Cover_Kind__Flower_Yellow:
            return TILE_COVER_SHEET_INDEX__FLOWER_YELLOW;
        case Tile_Cover_Kind__Cactus:
            return TILE_COVER_SHEET_INDEX__CACTUS;
        case Tile_Cover_Kind__Oak_Trunk:
        case Tile_Cover_Kind__Oak_Root:
        case Tile_Cover_Kind__Oak_Branch:
        case Tile_Cover_Kind__Oak_Leaves:
        case Tile_Cover_Kind__Leaf_Clutter:
            return 0;
    }
}

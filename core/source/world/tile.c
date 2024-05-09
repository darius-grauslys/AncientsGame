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
        // This is based on how we layout the tile sheet.
        // If we're descending, then we don't need an
        // offset.
        // If we are ascending, we need to offset such that
        // we pass the rows which include the descending
        // tiles. This also included the inverted descending
        // tile variants (example: North-East normal, North-East inverted.)
        int32_t offset = 0;
        //     (is_tile__up_or_down_stairs(tile))
        //     ? TILE_SHEET_ELEMENT_WIDTH
        //         * (TILE_STAIR_DIRECTION_COUNT
        //         + TILE_STAIR_DIRECTION_COUNT / 2)
        //     : 0
        //     ;
        if (is_tile__inverted_stairs(tile)) {
            // offset +=
            //     TILE_SHEET_ELEMENT_WIDTH
            //     * TILE_STAIR_DIRECTION_COUNT
            //     ;
            // offset +=
            //     (tile->flags
            //      & TILE_FLAGS__MASK_STAIR_VALUE) / 2
            //     * TILE_SHEET_ELEMENT_WIDTH
            //     ;
        } else {
            offset += 128;
            // offset +=
            //     ((tile->flags
            //      & TILE_FLAGS__MASK_STAIR_VALUE) + 1)
            //     * TILE_SHEET_ELEMENT_WIDTH
            //     ;
        }

        return index + offset;
    }
    return index;
}


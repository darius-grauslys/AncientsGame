#include <world/tile.h>
#include <defines.h>
#include <world/chunk_manager.h>

static Tile inline *get_tile_from__chunk_node_for__tile_render(
        Chunk_Manager__Chunk_Map_Node *chunk_node,
        int32_t x__local,
        int32_t y__local,
        Tile_Render_Result *render_result) {
    Tile *tile =
        get_tile_from__chunk_node(
                chunk_node,
                x__local,
                y__local);

    Tile *north, *east, *south, *west;

    //TODO: this is a pretty glaring problem
    //with how the chunk_nodes are connected
    north =
        (y__local == 0)
        ? get_tile_from__chunk_node(
                chunk_node->south__chunk_map_node,
                x__local, CHUNK_WIDTH__IN_TILES - 1)
        : get_tile_from__chunk_node(
                chunk_node,
                x__local, y__local - 1)
        ;
    south =
        (y__local == CHUNK_WIDTH__IN_TILES - 1)
        ? get_tile_from__chunk_node(
                chunk_node->north__chunk_map_node,
                x__local, 0)
        : get_tile_from__chunk_node(
                chunk_node,
                x__local, y__local + 1)
        ;
    west =
        (x__local == 0)
        ? get_tile_from__chunk_node(
                chunk_node->west__chunk_map_node,
                CHUNK_WIDTH__IN_TILES - 1, y__local)
        : get_tile_from__chunk_node(
                chunk_node,
                x__local - 1, y__local)
        ;
    east =
        (x__local == CHUNK_WIDTH__IN_TILES - 1)
        ? get_tile_from__chunk_node(
                chunk_node->east__chunk_map_node,
                0, y__local)
        : get_tile_from__chunk_node(
                chunk_node,
                x__local + 1, y__local)
        ;

    Tile_Wall_Adjacency_Code__u16 wall_adjacency = 0;
    if (is_tile_cover__a_wall(north->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__NORTH;
    }
    if (is_tile_cover__a_wall(east->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__EAST;
    }
    if (is_tile_cover__a_wall(south->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__SOUTH;
    }
    if (is_tile_cover__a_wall(west->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__WEST;
    }

    render_result->wall_adjacency = wall_adjacency;

    return tile;
}

static void inline get_tile_texture_sheet_index(
        Tile *tile,
        Tile_Render_Result *result) {
    switch (tile->the_kind_of_tile__this_tile_is) {
        default:
            result->tile_index__ground =
                (uint32_t)tile->the_kind_of_tile__this_tile_is;
            return;
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
            result->tile_index__ground = TILE_SHEET_INDEX__WATER;
            return;
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
    //TODO: look into why we have to add 1.
    index += 1;
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

        index += offset;
    }
    result->tile_index__ground = index;
}

static void inline get_tile_cover_texture_sheet_index(
        Tile *tile,
        Tile_Render_Result *result) {
    switch(tile->the_kind_of_tile_cover__this_tile_has) {
        case Tile_Cover_Kind__Wall__Dirt:
            result->tile_index__cover =
                TILE_SHEET_INDEX__DIRT;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            result->tile_index__cover =
                TILE_SHEET_INDEX__SAND;
            goto wall;
        case Tile_Cover_Kind__Wall__Oak_Wood:
            result->tile_index__cover =
                TILE_SHEET_INDEX__WOOD;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            result->tile_index__cover =
                TILE_SHEET_INDEX__STONE;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            result->tile_index__cover =
                TILE_SHEET_INDEX__STONE_BRICK;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            result->tile_index__cover =
                TILE_SHEET_INDEX__IRON;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            result->tile_index__cover =
                TILE_SHEET_INDEX__GOLD;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            result->tile_index__cover =
                TILE_SHEET_INDEX__DIAMOND;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            result->tile_index__cover =
                TILE_SHEET_INDEX__AMEYTHYST;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            result->tile_index__cover =
                TILE_SHEET_INDEX__SANDSTONE;
wall:
            result->tile_index__cover +=
                TILE_COVER_SHEET_INDEX__WALL
                + get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
                        result->wall_adjacency);
            break;
        case Tile_Cover_Kind__Plant:
            result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__PLANT;
			break;
        case Tile_Cover_Kind__Flower_Red:
            result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_RED;
			break;
        case Tile_Cover_Kind__Flower_Blue:
            result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_BLUE;
			break;
        case Tile_Cover_Kind__Flower_Yellow:
            result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_YELLOW;
			break;
        case Tile_Cover_Kind__Cactus:
            result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__CACTUS;
			break;
        case Tile_Cover_Kind__Oak_Trunk:
        case Tile_Cover_Kind__Oak_Root:
        case Tile_Cover_Kind__Oak_Branch:
        case Tile_Cover_Kind__Oak_Leaves:
        case Tile_Cover_Kind__Leaf_Clutter:
        default:
            result->tile_index__cover = 0;
			break;
    }
}

static void inline get_tile_sprite_cover_texture_sheet_index(
        Tile *tile,
        Tile_Render_Result *render_result) {
    switch(tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            render_result->tile_index__sprite_cover = 0;
            break;
        case Tile_Cover_Kind__Wall__Dirt:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__DIRT;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__SAND;
            goto wall;
        case Tile_Cover_Kind__Wall__Oak_Wood:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__WOOD;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__STONE;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__STONE_BRICK;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__IRON;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__GOLD;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__DIAMOND;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__AMEYTHYST;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__SANDSTONE;
wall:
            render_result->tile_index__sprite_cover +=
                TILE_COVER_SHEET_INDEX__WALL
                + get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
                    render_result->wall_adjacency);
            break;
    }
}

Tile_Render_Result get_tile_render_result(
        Chunk_Manager__Chunk_Map_Node *chunk_node,
        int32_t x__local,
        int32_t y__local) {
    Tile_Render_Result result;

    Tile *tile = 
        get_tile_from__chunk_node_for__tile_render(
            chunk_node,
            x__local,
            y__local,
            &result);

    get_tile_texture_sheet_index(
            tile, 
            &result);

    get_tile_cover_texture_sheet_index(
            tile, 
            &result);

    get_tile_sprite_cover_texture_sheet_index(
            tile, 
            &result);

    result.tile_index__cover &= ((1 << 10)-1);
    result.tile_index__ground &= ((1 << 10)-1);
    result.tile_index__sprite_cover &= ((1 << 10)-1);

    if (does_tile__have_a_wall(tile)) {
        result.tile_index__cover |= 
            does_wall_adjacency_require__vflip(
                    result.wall_adjacency)
            << 10;
        result.tile_index__sprite_cover |= 
            does_wall_adjacency_require__vflip(
                    result.wall_adjacency)
            << 10;
    }

    if (is_tile__stairs(tile)) {
        result.tile_index__ground |= 
            does_tile__stair_direction__require_hflip(tile)
            << 11;
        result.tile_index__ground |= 
            does_tile__stair_direction__require_vflip(tile)
            << 10;
    }

    return result;
}

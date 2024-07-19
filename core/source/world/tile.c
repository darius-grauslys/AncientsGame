#include "defines_weak.h"
#include <world/tile.h>
#include <defines.h>
#include <world/chunk_manager.h>
#include <vectors.h>

static Tile inline *get_p_tile_from__chunk_node_for__tile_render(
        Chunk_Manager__Chunk_Map_Node *p_chunk_node,
        Local_Tile_Vector__3u8 local_tile_vector__3u8,
        Tile_Render_Result *p_render_result) {
    Index__u8 x__local = local_tile_vector__3u8.x__u8;
    Index__u8 y__local = local_tile_vector__3u8.y__u8;
    Tile *p_tile =
        get_p_tile_from__chunk_node(
                p_chunk_node,
                local_tile_vector__3u8);

    Tile *p_north, *p_east, *p_south, *p_west;

    //TODO: this is a pretty glaring problem
    //with how the chunk_nodes are connected
    p_north =
        (y__local == 0)
        ? get_p_tile_from__chunk_node_using__u8(
                p_chunk_node->p_north__chunk_map_node,
                x__local, 
                CHUNK_WIDTH__IN_TILES - 1)
        : get_p_tile_from__chunk_node_using__u8(
                p_chunk_node,
                x__local, 
                y__local - 1)
        ;
    p_south =
        (y__local == CHUNK_WIDTH__IN_TILES - 1)
        ? get_p_tile_from__chunk_node_using__u8(
                p_chunk_node->p_south__chunk_map_node,
                x__local, 
                0)
        : get_p_tile_from__chunk_node_using__u8(
                p_chunk_node,
                x__local, 
                y__local + 1)
        ;
    p_west =
        (x__local == 0)
        ? get_p_tile_from__chunk_node_using__u8(
                p_chunk_node->p_west__chunk_map_node,
                CHUNK_WIDTH__IN_TILES - 1, y__local)
        : get_p_tile_from__chunk_node_using__u8(
                p_chunk_node,
                x__local - 1, 
                y__local)
        ;
    p_east =
        (x__local == CHUNK_WIDTH__IN_TILES - 1)
        ? get_p_tile_from__chunk_node_using__u8(
                p_chunk_node->p_east__chunk_map_node,
                0, 
                y__local)
        : get_p_tile_from__chunk_node_using__u8(
                p_chunk_node,
                x__local + 1, 
                y__local)
        ;

    Tile_Wall_Adjacency_Code__u16 wall_adjacency = 0;
    if (is_tile_cover__a_wall(p_north->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__NORTH;
    }
    if (is_tile_cover__a_wall(p_east->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__EAST;
    }
    if (is_tile_cover__a_wall(p_south->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__SOUTH;
    }
    if (is_tile_cover__a_wall(p_west->the_kind_of_tile_cover__this_tile_has)) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__WEST;
    }

    p_render_result->wall_adjacency = wall_adjacency;

    return p_tile;
}

static inline 
void get_tile_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    switch (p_tile->the_kind_of_tile__this_tile_is) {
        default:
            p_render_result->tile_index__ground =
                (uint32_t)p_tile->the_kind_of_tile__this_tile_is;
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
            p_render_result->tile_index__ground = TILE_SHEET_INDEX__WATER;
            return;
    }
tile_structure:
    uint32_t index = 0;
    switch (p_tile->the_kind_of_tile__this_tile_is) {
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
    p_render_result->tile_index__ground = index;
}

static inline 
void get_tile_cover_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    switch(p_tile->the_kind_of_tile_cover__this_tile_has) {
        case Tile_Cover_Kind__Wall__Dirt:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__DIRT;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__SAND;
            goto wall;
        case Tile_Cover_Kind__Wall__Oak_Wood:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__WOOD;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__STONE;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__STONE_BRICK;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__IRON;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__GOLD;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__DIAMOND;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__AMEYTHYST;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            p_render_result->tile_index__cover =
                TILE_SHEET_INDEX__SANDSTONE;
wall:
            p_render_result->tile_index__cover +=
                TILE_COVER_SHEET_INDEX__WALL
                + get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
                        p_render_result->wall_adjacency);
            break;
        case Tile_Cover_Kind__Plant:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__PLANT;
			break;
        case Tile_Cover_Kind__Flower_Red:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_RED;
			break;
        case Tile_Cover_Kind__Flower_Blue:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_BLUE;
			break;
        case Tile_Cover_Kind__Flower_Yellow:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__FLOWER_YELLOW;
			break;
        case Tile_Cover_Kind__Cactus:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__CACTUS;
			break;
        case Tile_Cover_Kind__Chest_Single:
            p_render_result->tile_index__cover =
				TILE_COVER_SHEET_INDEX__CHEST_SINGLE;
			break;
        default:
            p_render_result->tile_index__cover = 0;
			break;
    }
}

static void inline get_tile_sprite_cover_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    switch(p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            p_render_result->tile_index__sprite_cover = 0;
            break;
        case Tile_Cover_Kind__Wall__Dirt:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__DIRT;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__SAND;
            goto wall;
        case Tile_Cover_Kind__Wall__Oak_Wood:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__WOOD;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__STONE;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__STONE_BRICK;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__IRON;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__GOLD;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__DIAMOND;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__AMEYTHYST;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            p_render_result->tile_index__sprite_cover =
                TILE_SHEET_INDEX__SANDSTONE;
wall:
            p_render_result->tile_index__sprite_cover +=
                TILE_COVER_SHEET_INDEX__WALL
                + get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
                    p_render_result->wall_adjacency);
            break;
    }
}

// TODO: prim wrap
// TODO: move this to nds
Tile_Render_Result get_tile_render_result(
        Chunk_Manager__Chunk_Map_Node *p_chunk_node,
        Local_Tile_Vector__3u8 local_tile_vector__3u8) {
    Tile_Render_Result render_result;

    Tile *p_tile = 
        get_p_tile_from__chunk_node_for__tile_render(
            p_chunk_node,
            local_tile_vector__3u8,
            &render_result);

    get_tile_texture_sheet_index(
            p_tile, 
            &render_result);

    get_tile_cover_texture_sheet_index(
            p_tile, 
            &render_result);

    get_tile_sprite_cover_texture_sheet_index(
            p_tile, 
            &render_result);

    render_result.tile_index__cover &= ((1 << 10)-1);
    render_result.tile_index__ground &= ((1 << 10)-1);
    render_result.tile_index__sprite_cover &= ((1 << 10)-1);

    if (does_tile__have_a_wall(p_tile)) {
        render_result.tile_index__cover |= 
            does_wall_adjacency_require__vflip(
                    render_result.wall_adjacency)
            << 10;
        render_result.tile_index__sprite_cover |= 
            does_wall_adjacency_require__vflip(
                    render_result.wall_adjacency)
            << 10;
    }

    return render_result;
}

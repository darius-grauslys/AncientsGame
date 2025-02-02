#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "world/chunk.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
#include "world/world.h"
#include <world/tile.h>
#include <defines.h>
#include <world/chunk_manager.h>
#include <vectors.h>

void initialize_tile(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Cover_Kind kind_of_tile_cover,
        Tile_Flags__u8 flags) {
    tile->tile_flags = flags;
    tile->the_kind_of_tile__this_tile_is =
        kind_of_tile;
    tile->the_kind_of_tile_cover__this_tile_has =
        kind_of_tile_cover;
}

Index__u16 get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (4
        * (1 + (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__COVER_MASK))
        - 1)
        ;
}

bool is_tile_kind__illegal(
        Tile_Kind the_kind_of__tile) {
    return
        the_kind_of__tile < Tile_Kind__None
        || the_kind_of__tile >= Tile_Kind__Unknown
        ;
}

bool is_tile_cover_kind__illegal(
        Tile_Cover_Kind the_kind_of__tile_cover_kind) {
    return
        the_kind_of__tile_cover_kind < Tile_Cover_Kind__None
        || the_kind_of__tile_cover_kind >= Tile_Cover_Kind__Unknown
        ;
}

static inline 
Tile *get_p_tile_from__chunk_node_for__tile_render(
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
    ;
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
    p_render_result->tile_index__cover = 0;
    switch(p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            p_render_result->tile_index__cover = 
                p_tile->the_kind_of_tile_cover__this_tile_has;
			break;
        case Tile_Cover_Kind__Door__Vertical__Open__Dirt:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Dirt:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__DIRT;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sand:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sand:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__SAND;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Wood:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Wood:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__WOOD;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__STONE;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone_Brick:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__STONE_BRICK;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Iron:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Iron:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__IRON;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Gold:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Gold:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__GOLD;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Diamond:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Diamond:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__DIAMOND;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Amethyst:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Amethyst:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__AMEYTHYST;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sandstone:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sandstone:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__SANDSTONE;
vertical__door:
            p_render_result->tile_index__cover +=
                TILE_COVER_SHEET_INDEX__DOOR
                + 128;
            break;
        case Tile_Cover_Kind__Door__Horizontal__Open__Dirt:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Dirt:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__DIRT;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sand:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sand:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__SAND;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Wood:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Wood:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__WOOD;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__STONE;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone_Brick:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__STONE_BRICK;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Iron:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Iron:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__IRON;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Gold:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Gold:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__GOLD;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Diamond:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Diamond:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__DIAMOND;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Amethyst:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Amethyst:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__AMEYTHYST;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sandstone:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sandstone:
            p_render_result->tile_index__cover +=
                TILE_SHEET_INDEX__SANDSTONE;
horizontal__door:
            p_render_result->tile_index__cover +=
                TILE_COVER_SHEET_INDEX__DOOR
                + 32;
            break;
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
        case Tile_Cover_Kind__Crop_Corn_A:
        case Tile_Cover_Kind__Crop_Onion_A:
        case Tile_Cover_Kind__Crop_Tomato_A:
        case Tile_Cover_Kind__Crop_Pumpkin_A:
        case Tile_Cover_Kind__Crop_Watermelon_A:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__A;
            break;
        case Tile_Cover_Kind__Crop_Corn_B:
        case Tile_Cover_Kind__Crop_Onion_B:
        case Tile_Cover_Kind__Crop_Tomato_B:
        case Tile_Cover_Kind__Crop_Pumpkin_B:
        case Tile_Cover_Kind__Crop_Watermelon_B:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__B;
            break;
        case Tile_Cover_Kind__Crop_Corn_C:
        case Tile_Cover_Kind__Crop_Onion_C:
        case Tile_Cover_Kind__Crop_Tomato_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__C;
            break;
        case Tile_Cover_Kind__Crop_Pumpkin_C:
        case Tile_Cover_Kind__Crop_Watermelon_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__D;
            break;
        case Tile_Cover_Kind__Crop_Wheat_A:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__E;
            break;
        case Tile_Cover_Kind__Crop_Wheat_B:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__F;
            break;
        case Tile_Cover_Kind__Crop_Wheat_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__G;
            break;
        case Tile_Cover_Kind__Tree__Oak:
        case Tile_Cover_Kind__Tree__Pine:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Tree__Trunk;
            break;
    }
}

static void inline get_tile_sprite_cover_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    p_render_result->tile_index__sprite_cover = 0;
    switch(p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            break;
        case Tile_Cover_Kind__Table__Bottom__Left:
        case Tile_Cover_Kind__Table__Bottom__Middle:
        case Tile_Cover_Kind__Table__Bottom__Right:
            p_render_result->tile_index__sprite_cover =
                get_tile_cover_kind_from__tile(p_tile)
                -32;
            break;
        case Tile_Cover_Kind__Door__Vertical__Open__Dirt:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Dirt:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__DIRT;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sand:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sand:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__SAND;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Wood:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Wood:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__WOOD;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__STONE;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone_Brick:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__STONE_BRICK;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Iron:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Iron:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__IRON;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Gold:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Gold:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__GOLD;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Diamond:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Diamond:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__DIAMOND;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Amethyst:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Amethyst:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__AMEYTHYST;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sandstone:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sandstone:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__SANDSTONE;
vertical__door:
            p_render_result->tile_index__sprite_cover +=
                TILE_COVER_SHEET_INDEX__DOOR
                + 128;
            break;
        case Tile_Cover_Kind__Door__Horizontal__Open__Dirt:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Dirt:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__DIRT;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sand:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sand:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__SAND;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Wood:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Wood:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__WOOD;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__STONE;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone_Brick:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__STONE_BRICK;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Iron:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Iron:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__IRON;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Gold:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Gold:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__GOLD;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Diamond:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Diamond:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__DIAMOND;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Amethyst:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Amethyst:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__AMEYTHYST;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sandstone:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sandstone:
            p_render_result->tile_index__sprite_cover +=
                TILE_SHEET_INDEX__SANDSTONE;
horizontal__door:
            p_render_result->tile_index__sprite_cover +=
                TILE_COVER_SHEET_INDEX__DOOR;
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
            // TODO: magic numbers below here.
        case Tile_Cover_Kind__Cactus__Tall__Top:
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Right:
            p_render_result->tile_index__sprite_cover =
                p_tile->the_kind_of_tile_cover__this_tile_has
                - 32;
            break;
        case Tile_Cover_Kind__Tree__Oak:
            p_render_result->tile_index__sprite_cover =
                Tile_Cover_Kind__Stump
                + 1
                - 32
                ;
            p_render_result->tile_index__sprite_cover__extra =
                Tile_Cover_Kind__Stump
                + 1
                - 64
                ;
            break;
        case Tile_Cover_Kind__Tree__Pine:
            p_render_result->tile_index__sprite_cover =
                Tile_Cover_Kind__Stump
                + 2
                - 32
                ;
            p_render_result->tile_index__sprite_cover__extra =
                Tile_Cover_Kind__Stump
                + 2
                - 64
                ;
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

    render_result.tile_index__sprite_cover__extra = 
        Tile_Cover_Kind__None;
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

bool poll_tile_for__interaction(
        Game *p_game,
        Entity *p_entity,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Tile_Logic_Manager *p_tile_logic_manager =
        get_p_tile_logic_manager_from__world(
                get_p_world_from__game(p_game));

    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_cover_kind_from__tile(p_tile));

    if (p_tile_logic_record
            && is_tile_logic_record_possessing__interact(
                p_tile_logic_record)) {
        invoke_tile_logic_record__interact(
                p_tile_logic_record,
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
                
        return true;
    }

    p_tile_logic_record =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_kind_from__tile(p_tile));

    if (p_tile_logic_record
            && is_tile_logic_record_possessing__interact(
                p_tile_logic_record)) {
        invoke_tile_logic_record__interact(
                p_tile_logic_record,
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
                
        return true;
    }

    return false;
}

bool poll_tile_for__touch(
        Game *p_game,
        Entity *p_entity,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Tile_Logic_Manager *p_tile_logic_manager =
        get_p_tile_logic_manager_from__world(
                get_p_world_from__game(p_game));

    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_cover_kind_from__tile(p_tile));

    if (p_tile_logic_record
            && is_tile_logic_record_possessing__touch(
                p_tile_logic_record)) {
        invoke_tile_logic_record__touch(
                p_tile_logic_record,
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
                
        return true;
    }

    p_tile_logic_record =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                p_tile_logic_manager, 
                get_tile_kind_from__tile(p_tile));

    if (p_tile_logic_record
            && is_tile_logic_record_possessing__touch(
                p_tile_logic_record)) {
        invoke_tile_logic_record__touch(
                p_tile_logic_record,
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
                
        return true;
    }

    return false;
}

bool attempt_tile_placement_for__this_tile_logic_record(
        Tile_Logic_Record *p_tile_logic_record,
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    bool is_placement__successful = true;
    if (p_tile_logic_record
            && is_tile_logic_record_possessing__place(
                p_tile_logic_record)) {
        is_placement__successful = invoke_tile_logic_record__place(
                p_tile_logic_record, 
                p_game, 
                p_tile, 
                the_kind_of__tile,
                the_kind_of__tile_cover,
                tile_vector__3i32);
    } else if (the_kind_of__tile
            != Tile_Kind__None) {
        set_tile_kind_of__tile(
                p_tile, 
                the_kind_of__tile);
    } else if (the_kind_of__tile_cover
            != Tile_Cover_Kind__None) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__tile_cover);
    } else {
        return false;
    }

    return is_placement__successful;
}

bool attempt_tile_placement__ground(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                get_p_tile_logic_manager_from__world(
                    get_p_world_from__game(p_game)), 
                the_kind_of__tile);

    if (!is_tile_of__this_kind(
                p_tile,
                Tile_Kind__None)) {
        return false;
    }

    bool is_placement__successful =
        attempt_tile_placement_for__this_tile_logic_record(
            p_tile_logic_record, 
            p_game, 
            p_tile, 
            the_kind_of__tile, 
            Tile_Cover_Kind__None, 
            tile_vector__3i32);

    if (is_placement__successful) {
        set_tile__is_unpassable( // TODO: passability rules
                p_tile, 
                false);
    }

    return is_placement__successful;
}

bool attempt_tile_placement__cover(
        Game *p_game,
        Tile *p_tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile_Logic_Record *p_tile_logic_record =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                get_p_tile_logic_manager_from__world(
                    get_p_world_from__game(p_game)), 
                the_kind_of__tile_cover);

    return attempt_tile_placement_for__this_tile_logic_record(
            p_tile_logic_record, 
            p_game, 
            p_tile, 
            Tile_Kind__None, 
            the_kind_of__tile_cover, 
            tile_vector__3i32);
}

bool attempt_tile_placement(
        Game *p_game,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    if (!p_tile)
        return false;

    bool is_placing__ground_or_cover =
        the_kind_of__tile != Tile_Kind__None;

    Tile_Logic_Record *p_tile_logic_record = 0;
    if (is_placing__ground_or_cover) {
        p_tile_logic_record =
            get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                    get_p_tile_logic_manager_from__world(
                        get_p_world_from__game(p_game)), 
                    the_kind_of__tile);
    } else {
        p_tile_logic_record =
            get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                    get_p_tile_logic_manager_from__world(
                        get_p_world_from__game(p_game)), 
                    the_kind_of__tile_cover);
    }

    if (!p_tile_logic_record)
        return false;

    bool result_of__placement = false;
    if (is_tile_logic_record_possessing__place(
                p_tile_logic_record)) {
        result_of__placement = 
            invoke_tile_logic_record__place(
                p_tile_logic_record, 
                p_game, 
                p_tile, 
                the_kind_of__tile, 
                the_kind_of__tile_cover, 
                tile_vector__3i32);        
    } else {
        if (is_placing__ground_or_cover) {
            if (is_tile_of__this_kind(
                        p_tile, 
                        Tile_Kind__None)) {
                set_tile_kind_of__tile(
                        p_tile, 
                        the_kind_of__tile);
                result_of__placement = true;
            }
        } else {
            if (is_tile_with__this_kind_of__tile_cover(
                        p_tile, 
                        Tile_Cover_Kind__None)) {
                set_tile_cover_kind_of__tile(
                        p_tile, 
                        the_kind_of__tile_cover);
                result_of__placement = true;
            }
        }
    }

    if (result_of__placement) {
        determine_tile_flags(
                get_p_tile_logic_manager_from__world(
                    get_p_world_from__game(p_game)), 
                p_tile);
    }

    return result_of__placement;
}

bool remove_tile__cover(
        Game *p_game,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Tile_Logic_Record *p_logic_record =
        get_p_tile_logic_record_for__cover_kind_from__tile_logic_manager(
                get_p_tile_logic_manager_from__world(
                    get_p_world_from__game(p_game)), 
                get_tile_cover_kind_from__tile(p_tile));

    if (!p_logic_record
            || !is_tile_logic_record_possessing__destroy(
                p_logic_record)) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                Tile_Cover_Kind__None);
    } else {
        if (!invoke_tile_logic_record__destroy(
                p_logic_record, 
                p_game, 
                p_tile, 
                get_tile_kind_from__tile(p_tile), 
                get_tile_cover_kind_from__tile(p_tile), 
                tile_vector__3i32)) {
            return false;
        }
    }

    determine_tile_flags(
            get_p_tile_logic_manager_from__world(
                get_p_world_from__game(p_game)), 
            p_tile);

    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);
    return true;
}

bool remove_tile__ground(
        Game *p_game,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Tile_Logic_Record *p_logic_record =
        get_p_tile_logic_record_for__ground_kind_from__tile_logic_manager(
                get_p_tile_logic_manager_from__world(
                    get_p_world_from__game(p_game)), 
                get_tile_kind_from__tile(p_tile));

    if (!p_logic_record
            || !is_tile_logic_record_possessing__destroy(
                p_logic_record)) {
        set_tile_kind_of__tile(
                p_tile, 
                Tile_Kind__None);
    } else {
        if (!invoke_tile_logic_record__destroy(
                p_logic_record, 
                p_game, 
                p_tile, 
                get_tile_kind_from__tile(p_tile), 
                get_tile_cover_kind_from__tile(p_tile), 
                tile_vector__3i32)) {
            return false;
        }
    }

    determine_tile_flags(
            get_p_tile_logic_manager_from__world(
                get_p_world_from__game(p_game)), 
            p_tile);

    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);
    return true;
}

#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

static void inline init_tile(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Cover_Kind kind_of_tile_cover,
        Tile_Flags__u8 flags) {
    tile->tile_flags = flags;
    tile->the_kind_of_tile__this_tile_is =
        kind_of_tile;
    tile->the_kind_of_tile_cover__this_tile_has =
        kind_of_tile_cover;
}

static void inline set_tile__stair_direction(
        Tile *tile,
        Direction__u8 direction) {
    tile->tile_flags &= ~TILE_FLAGS__MASK_STAIR_VALUE;
    tile->tile_flags |=
        direction & TILE_FLAGS__MASK_STAIR_VALUE
        ;
}

static uint32_t inline get_tile__stair_direction(
        Tile *tile) {
    return tile->tile_flags & TILE_FLAGS__MASK_STAIR_VALUE;
}

static bool inline does_tile__stair_direction__require_hflip(
        Tile *tile) {
    switch(get_tile__stair_direction(tile)) {
        case TILE_STAIR_DIRECTION_SOUTH:
        case TILE_STAIR_DIRECTION_NORTH_EAST:
        case TILE_STAIR_DIRECTION_NORTH_WEST:
            return true;
        default:
            return false;
    }
}

static bool inline does_tile__stair_direction__require_vflip(
        Tile *tile) {
    switch(get_tile__stair_direction(tile)) {
        case TILE_STAIR_DIRECTION_WEST:
        case TILE_STAIR_DIRECTION_NORTH_WEST:
        case TILE_STAIR_DIRECTION_SOUTH_WEST:
            return true;
        default:
            return false;
    }
}

static bool inline is_tile_cover__a_wall(
        enum Tile_Cover_Kind kind_of_tile_cover) {
    return kind_of_tile_cover & TILE_COVER__BIT_IS_WALL;
}

static Index_u16 inline get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (4
        * (1 + (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__COVER_MASK))
        - 1)
        ;
}

static Index_u16 inline
get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__SPRITE_COVER_MASK);
}

static bool inline does_wall_adjacency_require__vflip(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return
        (bool)(wall_adjacency
                & TILE_RENDER__WALL_ADJACENCY__BIT_VFLIP);
}

static bool inline does_tile__have_a_wall(
        Tile *tile) {
    return is_tile_cover__a_wall(tile->the_kind_of_tile_cover__this_tile_has);
}

static enum Tile_Cover_Kind inline get_tile_cover_wall_for__tile_kind(
        enum Tile_Kind kind_of_tile) {
    return (enum Tile_Cover_Kind)(
            kind_of_tile
            | TILE_COVER__BIT_IS_WALL);
}

static bool inline is_tile__unpassable(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_UNPASSABLE);
}
static void inline set_tile__is_unpassable(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_UNPASSABLE;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_UNPASSABLE);
}
static bool inline is_tile__stairs(Tile *tile) {
    return (bool)((tile->tile_flags & TILE_FLAGS__BIT_IS_STAIR));
}
static void inline set_tile__is_stairs(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_STAIR;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_STAIR);
}
static bool inline is_tile__sight_blocking(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_SIGHT_BLOCKING); 
}
static void inline set_tile__sight_blocking(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_SIGHT_BLOCKING;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING);
}
static bool inline is_tile__inverted_stairs(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_INVERTED_STAIR);
}
static void inline set_tile__inverted_stairs(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_INVERTED_STAIR;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR);
}
static bool inline is_tile__up_or_down_stairs(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_STAIR_UP_OR_DOWN);
}
static void inline set_tile__up_or_down_stairs(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_STAIR_UP_OR_DOWN;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN);
}

// TODO: make this PLATFORM_render_tile
// TODO: make Tile_Render_Result into PLATFORM_Tile_Render_Result
Tile_Render_Result get_tile_render_result(
        Chunk_Manager__Chunk_Map_Node *chunk_node,
        Signed_Index__i32 x__local__signed_index_i32,
        Signed_Index__i32 y__local__signed_index_i32);

#endif

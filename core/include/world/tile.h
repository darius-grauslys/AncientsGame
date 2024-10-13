#ifndef TILE_H
#define TILE_H

#include "defines_weak.h"
#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

void initialize_tile(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Cover_Kind kind_of_tile_cover,
        Tile_Flags__u8 flags);

Index__u16 get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency);

bool is_tile_kind__illegal(
        Tile_Kind the_kind_of__tile);

bool is_tile_cover_kind__illegal(
        Tile_Cover_Kind the_kind_of__tile_cover_kind);

static inline Index__u16 
get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__SPRITE_COVER_MASK);
}

static inline 
bool does_wall_adjacency_require__vflip(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return
        (bool)(wall_adjacency
                & TILE_RENDER__WALL_ADJACENCY__BIT_VFLIP);
}

static inline 
bool is_tile_cover__a_wall(
        enum Tile_Cover_Kind kind_of_tile_cover) {
    return kind_of_tile_cover & TILE_COVER__BIT_IS_WALL;
}


static inline 
bool does_tile__have_a_wall(
        Tile *tile) {
    return is_tile_cover__a_wall(tile->the_kind_of_tile_cover__this_tile_has);
}

static inline 
enum Tile_Cover_Kind get_tile_cover_wall_for__tile_kind(
        enum Tile_Kind kind_of_tile) {
    return (enum Tile_Cover_Kind)(
            kind_of_tile
            | TILE_COVER__BIT_IS_WALL);
}

static inline 
bool is_tile__unpassable(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_UNPASSABLE);
}

static inline 
void set_tile__is_unpassable(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_UNPASSABLE;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_UNPASSABLE);
}

static inline 
bool is_tile__sight_blocking(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_SIGHT_BLOCKING); 
}

static inline 
void set_tile__sight_blocking(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_SIGHT_BLOCKING;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING);
}

static inline 
bool is_tile__container(Tile *tile) {
    return (bool)(tile->tile_flags & TILE_FLAGS__BIT_IS_CONTAINER); 
}

static inline 
void set_tile__container(Tile *tile, bool value) {
    tile->tile_flags &= ~TILE_FLAGS__BIT_IS_CONTAINER;
    tile->tile_flags |= (value << TILE_FLAGS__BIT_SHIFT_IS_CONTAINER);
}

static inline
void clear_tile_cover(
        Tile *p_tile) {
    p_tile->the_kind_of_tile_cover__this_tile_has =
        Tile_Cover_Kind__None;
    set_tile__is_unpassable(p_tile, false);
}

// TODO: make this PLATFORM_render_tile
// TODO: make Tile_Render_Result into PLATFORM_Tile_Render_Result
Tile_Render_Result get_tile_render_result(
        Chunk_Manager__Chunk_Map_Node *chunk_node,
        Local_Tile_Vector__3u8 local_tile_vector__3u8);

#endif

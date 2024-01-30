#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

void init_tile(Tile *tile, enum Tile_Kind kind_of_tile,
        uint8_t flags);

void init_tile_structure(Tile *tile, 
        enum Tile_Kind kind_of_tile,
        enum Tile_Structure_Kind kind_of_tile_structure);

static bool inline is_tile__passable(Tile *tile) {
    return (bool)(tile->flags & TILE_FLAGS__BIT_IS_PASSABLE);
}
static void inline set_tile__is_passable(Tile *tile, bool value) {
    tile->flags &= (-1) ^ (value << TILE_FLAGS__BIT_SHIFT_IS_PASSABLE);
}
static bool inline is_tile__stairs(Tile *tile) {
    return (bool)(tile->flags & TILE_FLAGS__BIT_IS_STAIR);
}
static void inline set_tile__is_stairs(Tile *tile, bool value) {
    tile->flags &= (-1) ^ (value << TILE_FLAGS__BIT_SHIFT_IS_STAIR);
}
static bool inline is_tile__sight_blocking(Tile *tile) {
    return (bool)(tile->flags & TILE_FLAGS__BIT_IS_SIGHT_BLOCKING); 
}
static void inline set_tile__sight_blocking(Tile *tile, bool value) {
    tile->flags &= (-1) ^ (value << TILE_FLAGS__BIT_SHIFT_IS_SIGHT_BLOCKING);
}
static bool inline is_tile__inverted_stairs(Tile *tile) {
    return (bool)(tile->flags & TILE_FLAGS__BIT_INVERTED_STAIR);
}
static void inline set_tile__inverted_stairs(Tile *tile, bool value) {
    tile->flags &= (-1) ^ (value << TILE_FLAGS__BIT_SHIFT_INVERTED_STAIR);
}
static bool inline is_tile__up_or_down_stairs(Tile *tile) {
    return (bool)(tile->flags & TILE_FLAGS__BIT_IS_STAIR_UP_OR_DOWN);
}
static void inline set_tile__up_or_down_stairs(Tile *tile, bool value) {
    tile->flags &= (-1) ^ (value << TILE_FLAGS__BIT_SHIFT_IS_STAIR_UP_OR_DOWN);
}

static bool inline is_tile_structure_kind__passable(
        enum Tile_Structure_Kind kind_of_tile_structure) {
    switch (kind_of_tile_structure) {
        default:
            return true;
        case Tile_Structure_Kind__Wall:
        case Tile_Structure_Kind__Window:
            return false;
    }
}

static bool inline is_tile_structure_kind__sight_blocking(
        enum Tile_Structure_Kind kind_of_tile_structure) {
    return kind_of_tile_structure == Tile_Structure_Kind__Wall;
}

static bool inline is_tile_kind__ascending(
        enum Tile_Structure_Kind kind_of_tile_structure) {
    return kind_of_tile_structure == Tile_Structure_Kind__Stair_Ascending;
}

static bool inline is_tile_kind__descending(
        enum Tile_Structure_Kind kind_of_tile_structure) {
    return kind_of_tile_structure == Tile_Structure_Kind__Stair_Descending;
}

uint32_t get_tile_texture_sheet_index(Tile *tile);

#endif

#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

typedef struct Tile_t {
    enum Tile_Kind          the_kind_of_tile__this_tile_is;
    enum Tile_Cover_Kind    the_kind_of_tile_cover__this_tile_has;
    uint8_t flags;
    // bits 1 2 3, stair direction (values 0-7)
    // bit 4, is the stair inverted
    // bit 5, is the stair going up or down
    // bit 6, is this a stair
    // bit 7, is sight blocking
    // bit 8, is passable
} Tile;

void init_tile(Tile *tile, enum Tile_Kind kind_of_tile,
        uint8_t flags);

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

uint32_t get_tile_sheet_index(Tile *tile);

#endif

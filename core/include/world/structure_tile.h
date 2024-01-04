#ifndef STRUCTURE_TILE_H
#define STRUCTURE_TILE_H

///
/// A Structure Tile is a helper struct
/// definition which describes tiles that have:
/// - walls
/// - stairs
/// - windows
///
/// It explains if this tile might missing
/// some of these features or not.
///
typedef struct Structure_Tile_t {
    bool has_walls;
    bool has_stairs;
    bool has_windows;
} Structure_Tile;

#endif

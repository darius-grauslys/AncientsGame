#include <world/generators/generator_test_world.h>
#include <world/world_parameters.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <defines.h>

void chunk_generator__test_world_f(
        World_Parameters *world_params,
        Chunk *chunk) {
    enum Tile_Kind kind_of_tile =
        ((chunk->y % 2 == 0)
         && (chunk->x % 2 == 1))
        || ((chunk->y % 2 == 1)
         && (chunk->x % 2 == 0))
         ? Tile_Kind__Oak_Wood
         : Tile_Kind__Gold
         ;

    for (uint32_t y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (uint32_t x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            init_tile(&chunk->tiles[
                    x + y * CHUNK_WIDTH__IN_TILES],
                    kind_of_tile,
                    Tile_Cover_Kind__None,
                    TILE_FLAGS__NONE);
        }
    }
}

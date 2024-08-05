#include <world/generators/generator_test_world.h>
#include <world/world_parameters.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <defines.h>

void f_chunk_generator__test_world(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    Chunk *p_chunk =
        p_chunk_map_node
        ->p_chunk__here;
    Signed_Index__i32 x = 
        p_chunk_map_node
        ->position_of__chunk_3i32.x__i32;
    Signed_Index__i32 y = 
        p_chunk_map_node
        ->position_of__chunk_3i32.y__i32;
    if (x < 0)
        x *= -1;
    if (y < 0)
        y *= -1;

    enum Tile_Kind kind_of_tile =
        ((y % 2 == 0)
         && (x % 2 == 1))
        || ((y % 2 == 1)
         && (x % 2 == 0))
         ? Tile_Kind__Stone
         : Tile_Kind__Grass
         ;

    for (uint32_t y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (uint32_t x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            initialize_tile(&p_chunk->tiles[
                    x + y * CHUNK_WIDTH__IN_TILES],
                    kind_of_tile,
                    Tile_Cover_Kind__None,
                    TILE_FLAGS__NONE);
        }
    }
}

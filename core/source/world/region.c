#include "world/region.h"
#include "defines.h"
#include "vectors.h"

bool is_tile_position_within__region(
        Tile_Vector__3i32 tile_position__3i32,
        Region_Vector__3i32 region_position__3i32) {
    return
        tile_position__3i32.x__i32
        >> REGION__WIDTH__BIT_SHIFT
        == region_position__3i32.x__i32
        && tile_position__3i32.y__i32
        >> REGION__WIDTH__BIT_SHIFT
        == region_position__3i32.y__i32
        ;
}

bool is_structure_within__region(
        Structure *p_structure,
        Region_Vector__3i32 region_position__3i32) {
    debug_abort("is_structure_within__region, not impl");
    return false;
}

Region_Vector__3i32 get_region_that__this_chunk_map_node_is_in(
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    return get_vector__3i32(
            p_chunk_map_node->position_of__chunk_3i32.x__i32 
            >> REGION__WIDTH__BIT_SHIFT, 
            p_chunk_map_node->position_of__chunk_3i32.y__i32 
            >> REGION__HEIGHT__BIT_SHIFT, 
            0);
}

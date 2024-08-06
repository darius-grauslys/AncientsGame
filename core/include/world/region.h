#ifndef REGION
#define REGION

#include "defines_weak.h"
#include <defines.h>

bool is_tile_position_within__region(
        Tile_Vector__3i32 tile_position__3i32,
        Region_Vector__3i32 region_position__3i32);

bool is_structure_within__region(
        Structure *p_structure,
        Region_Vector__3i32 region_position__3i32);

Region_Vector__3i32 get_region_that__this_chunk_map_node_is_in(
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

#endif

#ifndef WORLD_PARAMETERS_H
#define WORLD_PARAMETERS_H

#include <defines.h>

void initialize_world_parameters(
        World_Parameters *world_params,
        f_Chunk_Generator f_chunk_generator,
        Psuedo_Random_Seed__u32 seed__initial);

Psuedo_Random__i32 get_pseudo_random_i32__from_world_parameters(
        World_Parameters *world_params);

Psuedo_Random__i32 
get_repeatable_pseudo_random_i32_with__xy_from__world_parameters(
        World_Parameters *world_params,
        Signed_Index__i32 x, 
        Signed_Index__i32 y);

#endif

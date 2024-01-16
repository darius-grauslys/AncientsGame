#ifndef WORLD_PARAMETERS_H
#define WORLD_PARAMETERS_H

#include <defines.h>

void init_world_parameters(
        World_Parameters *world_params,
        Chunk_Generator_f chunk_generator_f,
        uint32_t seed__initial);

int32_t get_random__from_world_parameters(
        World_Parameters *world_params);

int32_t get_repeatable_random__xy__from_world_parameters(
        World_Parameters *world_params,
        int32_t x, int32_t y);

#endif

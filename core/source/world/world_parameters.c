#include <world/world_parameters.h>

void initialize_world_parameters(
        World_Parameters *world_parameters,
        f_Chunk_Generator f_chunk_generator) {
    world_parameters->f_chunk_generator =
        f_chunk_generator;
}

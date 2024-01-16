#include <world/world_parameters.h>

void init_world_parameters(
        World_Parameters *world_params,
        Chunk_Generator_f chunk_generator_f,
        uint32_t seed__initial) {
    world_params->seed__initial =
        world_params->seed__current_random =
        seed__initial;

    world_params->chunk_generator_f =
        chunk_generator_f;
}

int32_t get_random__from_world_parameters(
        World_Parameters *world_params) {
    srand(world_params->seed__current_random);
    world_params->seed__current_random =
        rand();
    return world_params->seed__current_random;
}

int32_t get_repeatable_random__xy__from_world_parameters(
        World_Parameters *world_params,
        int32_t x, int32_t y) {
    int32_t random__result;
    srand(x + world_params->seed__initial);
    random__result =
        rand();
    srand(random__result + y + world_params->seed__initial);
    random__result +=
        rand();
    return random__result;
}

#include <world/world_parameters.h>

void initialize_world_parameters(
        World_Parameters *world_parameters,
        f_Chunk_Generator f_chunk_generator,
        Psuedo_Random_Seed__u32 seed__initial) {
    world_parameters->seed__initial =
        world_parameters->seed__current_random =
        seed__initial;

    world_parameters->f_chunk_generator =
        f_chunk_generator;
}

Psuedo_Random__i32 get_pseudo_random_i32__from_world_parameters(
        World_Parameters *world_parameters) {
    srand(world_parameters->seed__current_random);
    world_parameters->seed__current_random =
        rand();
    return world_parameters->seed__current_random;
}

Psuedo_Random__i32 
get_repeatable_pseudo_random_i32_with__xy_from__world_parameters(
        World_Parameters *world_parameters,
        Signed_Index__i32 x, 
        Signed_Index__i32 y) {
    Psuedo_Random__i32 random__result;
    srand(x + world_parameters->seed__initial);
    random__result =
        rand();
    srand(random__result + y + world_parameters->seed__initial);
    random__result +=
        rand();
    return random__result;
}

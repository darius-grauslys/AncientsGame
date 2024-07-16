#include <random.h>

void initialize_repeatable_psuedo_random(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        Psuedo_Random_Seed__u32 seed__initial) {
    p_repeatable_psuedo_random->seed__initial =
        p_repeatable_psuedo_random->seed__current_random =
        seed__initial;
}

Psuedo_Random__i32 get_pseudo_random_i32__intrusively(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random) {
    srand(p_repeatable_psuedo_random->seed__current_random);
    p_repeatable_psuedo_random->seed__current_random =
        rand();
    return p_repeatable_psuedo_random->seed__current_random;
}

Psuedo_Random__i32 get_pseudo_random_i32_with__xy__intrusively(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        Signed_Index__i32 x, 
        Signed_Index__i32 y) {
    Psuedo_Random__i32 random__result;
    srand(x 
            + p_repeatable_psuedo_random
                ->seed__initial);
    random__result =
        rand();
    srand(random__result 
            + y 
            + p_repeatable_psuedo_random
                ->seed__initial);
    random__result +=
        rand();
    return random__result;
}

Psuedo_Random__i32 get_pseudo_random_i32__non_intrusively_with__seed(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 seed) {
    srand(seed);
    Psuedo_Random__i32 random = rand();
    srand(p_repeatable_psuedo_random->seed__current_random);
    return random;
}

Direction__u8 get_psuedo_random__direction_u8__non_intrusively_with__seed(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 seed) {
    srand(seed);
    Direction__u8 direction = rand() & DIRECTION__ANY;
    srand(p_repeatable_psuedo_random->seed__current_random);
    return direction;
}

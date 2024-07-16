#ifndef RANDOM_H
#define RANDOM_H

#include "defines.h"

void initialize_repeatable_psuedo_random(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        Psuedo_Random_Seed__u32 seed__initial);

Psuedo_Random__i32 get_pseudo_random_i32__intrusively(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random);

Psuedo_Random__i32 get_pseudo_random_i32_with__xy__intrusively(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        Signed_Index__i32 x, 
        Signed_Index__i32 y);

Psuedo_Random__i32 get_pseudo_random_i32__non_intrusively_with__seed(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 seed);

Direction__u8 get_psuedo_random__direction_u8__non_intrusively_with__seed(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 seed);

#endif

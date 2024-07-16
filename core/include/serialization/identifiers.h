#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include "defines_weak.h"
#include "game.h"
#include <defines.h>

static inline
Identifier__u32 get_random__uuid_u32(Game *p_game) {
    // Would be pretty problematic if we didn't
    // XOR this wouldn't it? LOL
    //
    // Pretty unlikely to collide, but...
    return get_pseudo_random_i32_from__game(p_game) 
        ^ IDENTIFIER__UNKNOWN__u32;
}

static inline
Identifier__u32 merge_identifiers_u32(
        Identifier__u32 identifier__left_half,
        Quantity__u8 bits__left,
        Identifier__u32 identifier__right_half) {
    return
        (identifier__left_half << (32 - bits__left))
        | (identifier__right_half & MASK(33 - bits__left))
        ;
}

static inline
bool is_identifier_u32__invalid(
        Identifier__u32 identifier__u32) {
    return IDENTIFIER__UNKNOWN__u32 == identifier__u32;
}

#endif

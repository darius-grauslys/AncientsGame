#ifndef HEARTS_DAMAGING_SPECIFIER_H
#define HEARTS_DAMAGING_SPECIFIER_H

#include <defines.h>

static inline
bool is_hearts_damaging_specifier__chaos(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_CHAOS
        ;
}

static inline
bool is_hearts_damaging_specifier__order(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_ORDER
        ;
}

static inline
bool is_hearts_damaging_specifier__bludgeoning(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_BLUDGEONING
        ;
}
static inline
bool is_hearts_damaging_specifier__cursing(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_CURSING
        ;
}
static inline
bool is_hearts_damaging_specifier__piercing(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_PIERCING
        ;
}
static inline
bool is_hearts_damaging_specifier__slashing(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_SLASHING
        ;
}

static inline
bool is_hearts_damaging_specifier__poisonous(
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    return p_hearts_damaging_specifier
        ->hearts_damaging__flags & HEARTS_DAMAGING_FLAG__IS_POISONING
        ;
}

#endif

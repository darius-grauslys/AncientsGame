#ifndef HEARTS_H
#define HEARTS_H

#include "defines_weak.h"
#include <defines.h>

static bool inline is_hearts_damaging_flags__poisoning(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_POISONING);
}
static bool inline is_hearts_damaging_flags__order(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_ORDER);
}
static bool inline is_hearts_damaging_flags__chaos(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_CHAOS);
}
static bool inline is_hearts_damaging_flags__cursing(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_CURSING);
}
static bool inline is_hearts_damaging_flags__bludgeoning(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_BLUDGEONING);
}
static bool inline is_hearts_damaging_flags__slashing(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_SLASHING);
}
static bool inline is_hearts_damaging_flags__piercing(
        Hearts_Damaging_Flags hearts_damaging__flags) {
    return (bool)(hearts_damaging__flags 
            & HEARTS_DAMAGING_FLAG__IS_PIERCING);
}

static bool inline is_hearts_healing_flags__antidote(
        Hearts_Healing_Flags hearts_healing__flags) {
    return (bool)(hearts_healing__flags
            & HEARTS_HEALING_FLAG__IS_ANTIDOTE);
}
static bool inline is_hearts_healing_flags__immortalizing(
        Hearts_Healing_Flags hearts_healing__flags) {
    return (bool)(hearts_healing__flags
            & HEARTS_HEALING_FLAG__IS_IMMORTALIZING);
}

static bool inline is_energy_damaging_flags__poisoning(
        Energy_Damaging_Flags energy_damaging__flags) {
    return (bool)(energy_damaging__flags
            & ENERGY_DAMAGING_FLAG__IS_POISONING);
}
static bool inline is_energy_damaging_flags__order(
        Energy_Damaging_Flags energy_damaging__flags) {
    return (bool)(energy_damaging__flags
            & ENERGY_DAMAGING_FLAG__IS_ORDER);
}
static bool inline is_energy_damaging_flags__chaos(
        Energy_Damaging_Flags energy_damaging__flags) {
    return (bool)(energy_damaging__flags
            & ENERGY_DAMAGING_FLAG__IS_CHAOS);
}

static bool inline is_energy_healing_flags__antidote(
        Energy_Healing_Flags energy_healing__flags) {
    return (bool)(energy_healing__flags
            & ENERGY_HEALING_FLAG__IS_ANTIDOTE);
}
static bool inline is_energy_healing_flags__demonizing(
        Energy_Healing_Flags energy_healing__flags) {
    return (bool)(energy_healing__flags
            & ENERGY_HEALING_FLAG__IS_DEMONIZING);
}

static bool inline is_resource_symbol__usable(
        Resource_Symbol__u8 resource_symbol) {
    return resource_symbol != RESOURCE_SYMBOL__EMPTY
        && resource_symbol != RESOURCE_SYMBOL__LOCKED
        ;
}

static bool inline is_hearts_damaging_specifier__magical(
        Hearts_Damaging_Specifier hearts_damaging_specifier) {
    return 
        is_hearts_damaging_flags__chaos(
                hearts_damaging_specifier.hearts_damaging__flags)
        || is_hearts_damaging_flags__order(
                hearts_damaging_specifier.hearts_damaging__flags)
        || is_hearts_damaging_flags__cursing(
                hearts_damaging_specifier.hearts_damaging__flags);
}

static bool inline is_energy_damaging_specifier__magical(
        Energy_Damaging_Specifier energy_damaging_specifier) {
    return 
        is_energy_damaging_flags__chaos(
                energy_damaging_specifier.energy_damaging__flags)
        || is_energy_damaging_flags__order(
                energy_damaging_specifier.energy_damaging__flags)
        ;
}

void apply_hearts_damaging_specifier_to__entity(
        Entity *p_entity,
        Hearts_Damaging_Specifier hearts_damaging_specifier);

void apply_hearts_healing_specifier_to__entity(
        Entity *p_entity,
        Hearts_Healing_Specifier hearts_healing_specifier);

void apply_energy_damaging_specifier_to__entity(
        Entity *p_entity,
        Energy_Damaging_Specifier energy_damaging_specifier);

void apply_energy_healing_specifier_to__entity(
        Entity *p_entity,
        Energy_Healing_Specifier energy_healing_specifier);

#endif
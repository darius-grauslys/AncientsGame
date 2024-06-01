#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include <entity/reserves.h>
#include <entity/humanoid.h>

static Resource_Symbol__u8 inline *get_ptr_to__first_resource_symbol(
        Resource_Reserve *p_resource_reserve) {
    return &p_resource_reserve->resource_symbols[0];
}

static Resource_Symbol__u8 inline *get_ptr_to__last_resource_symbol(
        Resource_Reserve *p_resource_reserve) {
#ifndef NDEBUG
    if (p_resource_reserve->max_quantity_of__resource_symbols
            > ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF) {
        debug_error("get_ptr_to__last_resource_symbol, max_quantity_of__resource_symbols exceeds ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF.");
        return &p_resource_reserve->resource_symbols
            [ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF-1];
    }
    if (p_resource_reserve->max_quantity_of__resource_symbols
            == 0) {
        debug_error("get_ptr_to__last_resource_symbol, max_quantity_of__resource_symbols is zero.");
        return get_ptr_to__first_resource_symbol(p_resource_reserve);
    }
#endif
    return &p_resource_reserve->resource_symbols
        [p_resource_reserve->max_quantity_of__resource_symbols - 1];
}

Resource_Symbol__u8 *get_last_usable_resource(
        Resource_Symbol__u8 *p_first_symbol,
        Resource_Symbol__u8 *p_last_symbol) {
    if (p_last_symbol < p_first_symbol) {
        debug_error("get_last_usable_resource, p_last_symbol < p_first_symbol");
        return 0;
    }
    if (!p_first_symbol || !p_last_symbol) {
        debug_error("get_last_usable_resource, p_first_symbol:%p p_last_symbol:%p",
                p_first_symbol,
                p_last_symbol);
        return 0;
    }
    do {
        Resource_Symbol__u8 symbol =
            *p_last_symbol;
        if (symbol != RESOURCE_SYMBOL__EMPTY
                && symbol != RESOURCE_SYMBOL__LOCKED)
            return p_last_symbol;
    } while (p_first_symbol <= --p_last_symbol);
    return 0;
}

Heart__u8 *get_first_incomplete_heart(
        Heart__u8 *p_first_heart,
        Heart__u8 *p_last_heart) {
    if (p_first_heart > p_last_heart) {
        debug_error("get_first_incomplete_heart, p_first_heart > p_last_heart");
        return p_first_heart;
    }
    if (!p_first_heart || !p_last_heart) {
        debug_error("get_first_incomplete_heart, p_first_heart:%p, p_last_heart:%p",
                p_first_heart,
                p_last_heart);
        return 0;
    }
    Heart__u8 *p_current_heart =
        p_first_heart;
    if (!p_current_heart)
        p_current_heart = p_first_heart;

    do {
        switch (*p_current_heart) {
            default:
                return p_current_heart;
            case Heart_Kind__Full_Immortal:
            case Heart_Kind__Full_Normal:
            case Heart_Kind__Immortal_Normal:
                continue;
        }
    } while (++p_current_heart <= p_last_heart);
    return p_last_heart;
}

Heart__u8 *get_last_healthy_heart(
        Heart__u8 *p_first_heart,
        Heart__u8 *p_last_heart) {
    if (p_first_heart > p_last_heart) {
        debug_error("get_last_healthy_heart, p_first_heart > p_last_heart");
        return p_first_heart;
    }
    if (!p_first_heart || !p_last_heart) {
        debug_error("get_last_healthy_heart, p_first_heart:%p, p_last_heart:%p",
                p_first_heart,
                p_last_heart);
        return 0;
    }
    Heart__u8 *p_current_heart =
        get_last_usable_resource(
                p_first_heart, 
                p_last_heart);
    if (!p_current_heart)
        return 0;

    do {
        switch (*p_current_heart) {
            default:
                continue;
            case Heart_Kind__Full_Immortal:
            case Heart_Kind__Half_Immortal:
            case Heart_Kind__Normal_Poison:
            case Heart_Kind__Full_Normal:
            case Heart_Kind__Half_Normal:
                return p_current_heart;
        }
    } while (--p_current_heart > p_first_heart);
    return p_current_heart;
}

Heart__u8 *get_first_poisoned__heart(
        Heart__u8 *p_first_heart,
        Heart__u8 *p_last_heart) {
    if (p_first_heart > p_last_heart) {
        debug_error("get_first_poisoned__heart, p_first_heart > p_last_heart");
        return p_first_heart;
    }
    if (!p_first_heart || !p_last_heart) {
        debug_error("get_first_poisoned__heart, p_first_heart:%p, p_last_heart:%p",
                p_first_heart,
                p_last_heart);
        return 0;
    }
    Heart__u8 *p_current_heart =
        p_first_heart;

    do {
        switch (*p_current_heart) {
            default:
                continue;
            case Heart_Kind__Half_Poison:
            case Heart_Kind__Full_Poison:
            case Heart_Kind__Normal_Poison:
            case Heart_Kind__Immortal_Poison:
                return p_current_heart;
        }
    } while (++p_current_heart <= p_last_heart);
    return 0;
}

void poison_heart(Heart__u8 *p_heart) {
    switch (*p_heart) {
        default:
            return;
        case Heart_Kind__Full_Normal:
            *p_heart = Heart_Kind__Normal_Poison;
            return;
        case Heart_Kind__Normal_Poison:
            *p_heart = Heart_Kind__Full_Poison;
            return;
        case Heart_Kind__Half_Normal:
            *p_heart = Heart_Kind__Half_Poison;
            return;
        case Heart_Kind__Immortal_Normal:
            *p_heart = Heart_Kind__Immortal_Poison;
            return;
    }
}

void poison_heart_with__rollover(
        Heart__u8 **p_heart_ptr,
        Heart__u8 *p_first_heart) {
    if (!p_heart_ptr && !*p_heart_ptr)
        return;
    poison_heart(*p_heart_ptr);
    if (p_first_heart < *p_heart_ptr) {
        (*p_heart_ptr)--;
    }
}

void apply_hearts_damaging_specifier_to__entity(
        Entity *p_entity,
        Hearts_Damaging_Specifier hearts_damaging_specifier) {
    Resource_Reserve *p_hearts =
        &p_entity->hearts;
    Heart__u8 *p_first_heart =
        get_ptr_to__first_resource_symbol(p_hearts);
    Heart__u8 *p_last_heart =
        get_ptr_to__last_resource_symbol(p_hearts);
    Heart__u8 *p_current_heart =
        get_last_usable_resource(
                p_first_heart, 
                p_last_heart);
    if (!p_current_heart)
        return;
    Heart__u8 *p_last_healthy_heart =
        get_last_healthy_heart(
                p_first_heart,
                p_last_heart);

    Quantity__u16 quantity_of__damage =
        hearts_damaging_specifier.quantity_of__damage;
    if (is_hearts_damaging_flags__poisoning(
                hearts_damaging_specifier.hearts_damaging__flags)) {
        p_current_heart = p_last_healthy_heart;
        while (
            p_current_heart >= p_first_heart
            && quantity_of__damage-- > 0
            && quantity_of__damage 
            < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2) {
            switch(*p_current_heart) {
                case Heart_Kind__Full_Immortal:
                case Heart_Kind__Half_Immortal:
                case Heart_Kind__Immortal_Poison:
                    return;
                case Heart_Kind__Full_Poison:
                case Heart_Kind__Half_Poison:
                    p_current_heart--;
                    break;
                default:
                    poison_heart(p_current_heart);
                    break;
            }
        }
        return;
    }

    bool is_damage__chaos =
        is_hearts_damaging_flags__chaos(
                    hearts_damaging_specifier
                    .hearts_damaging__flags);
    Quantity__u16 immortal_damaging_tax = 1;
    while (quantity_of__damage-- > 0
            && quantity_of__damage 
            < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2) {
        Resource_Symbol__u8 heart =
            *p_current_heart;
        if (!is_resource_symbol__usable(heart)) {
            p_current_heart--;
            if (p_current_heart < p_first_heart)
                return;
            heart = *p_current_heart;
        }

        switch(heart) {
            default:
#ifndef NDEBUG
                debug_warning("Uncaught switch case apply_hearts_damaging_specifier_to__entity.");
#endif
                continue;
            case Heart_Kind__Half_Poison:
                poison_heart_with__rollover(
                        &p_last_healthy_heart, 
                        p_first_heart);
            case Heart_Kind__Half_Normal:
                *p_current_heart = Heart_Kind__Empty;
                break;
            case Heart_Kind__Full_Normal:
                *p_current_heart = Heart_Kind__Half_Normal;
                break;
            case Heart_Kind__Full_Poison:
            case Heart_Kind__Normal_Poison:
                poison_heart_with__rollover(
                        &p_last_healthy_heart, 
                        p_first_heart);
                *p_current_heart = Heart_Kind__Half_Poison;
                break;
            case Heart_Kind__Full_Immortal:
            case Heart_Kind__Half_Immortal:
                if (!is_hearts_damaging_specifier__magical(
                            hearts_damaging_specifier))
                    return;
                if (!is_damage__chaos 
                        && immortal_damaging_tax > quantity_of__damage)
                    return;
                switch (heart) {
                    case Heart_Kind__Full_Immortal:
                        *p_current_heart = Heart_Kind__Half_Immortal;
                        break;
                    case Heart_Kind__Half_Immortal:
                        *p_current_heart = Heart_Kind__Empty;
                        break;
                }
                quantity_of__damage -= immortal_damaging_tax - 1;
                immortal_damaging_tax =
                    (is_damage__chaos)
                    ? immortal_damaging_tax + 1
                    : immortal_damaging_tax * 3
                    ;
                break;
            case Heart_Kind__Immortal_Poison:
                // The hearts prior to this SHOULD be immortal.
                // TODO: put a debug catch for this.
            case Heart_Kind__Immortal_Normal:
                *p_current_heart = Heart_Kind__Half_Immortal;
                break;
        }
    }
}

void cure_poison_from__hearts(
        Heart__u8 *p_current_heart,
        Heart__u8 *p_last_heart,
        Quantity__u16 quantity_of__purifying) {
    do {
        switch (*p_current_heart) {
            default:
                continue;
            case Heart_Kind__Full_Poison:
                *p_current_heart = Heart_Kind__Normal_Poison;
                break;
            case Heart_Kind__Normal_Poison:
                *p_current_heart = Heart_Kind__Full_Normal;
                break;
            case Heart_Kind__Immortal_Poison:
                *p_current_heart = Heart_Kind__Immortal_Normal;
                break;
            case Heart_Kind__Half_Poison:
                *p_current_heart = Heart_Kind__Half_Normal;
                break;
        }
    } while (++p_current_heart <= p_last_heart
            && --quantity_of__purifying != 0
            && quantity_of__purifying < 
            ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2);
}

void immortalize_hearts(
        Heart__u8 *p_first_heart,
        Heart__u8 *p_last_heart,
        Quantity__u16 quantity_of__immortalization) {
    Heart__u8 *p_current_heart = p_first_heart;
    do {
        switch (*p_current_heart) {
            case Heart_Kind__Full_Immortal:
                continue;
            case Heart_Kind__Locked:
                break;
            default:
                if (quantity_of__immortalization == 1) {
                    switch (*p_current_heart) {
                        case Heart_Kind__Empty:
                        case Heart_Kind__Half_Poison:
                        case Heart_Kind__Half_Normal:
                            *p_current_heart = Heart_Kind__Half_Immortal;
                            break;
                        case Heart_Kind__Normal_Poison:
                        case Heart_Kind__Full_Poison:
                            *p_current_heart = Heart_Kind__Immortal_Poison;
                            break;
                        case Heart_Kind__Immortal_Normal:
                        case Heart_Kind__Immortal_Poison:
                        case Heart_Kind__Half_Immortal:
                            *p_current_heart = Heart_Kind__Full_Immortal;
                            break;
                        case Heart_Kind__Full_Normal:
                            *p_current_heart = Heart_Kind__Immortal_Normal;
                            break;
                    }
                    return;
                }
                *p_current_heart = Heart_Kind__Full_Immortal;
                quantity_of__immortalization -= 2;
                break;
        }
    } while (++p_current_heart <= p_last_heart
            && quantity_of__immortalization > 0);
}

void apply_hearts_healing_specifier_to__entity(
        Entity *p_entity,
        Hearts_Healing_Specifier hearts_healing_specifier) {
    Resource_Reserve *p_hearts =
        &p_entity->hearts;
    Heart__u8 *p_first_heart =
        get_ptr_to__first_resource_symbol(p_hearts);
    Heart__u8 *p_last_heart =
        get_ptr_to__last_resource_symbol(p_hearts);

    if (is_hearts_healing_flags__immortalizing(
                hearts_healing_specifier.hearts_healing__flags)) {
        immortalize_hearts(
                p_first_heart, 
                p_last_heart,
                hearts_healing_specifier.quantity_of__healing);
        return;
    }

    Heart__u8 *p_current_heart =
        get_first_poisoned__heart(
                p_first_heart, 
                p_last_heart);

    bool is_healing__antidote =
        is_hearts_healing_flags__antidote(
                hearts_healing_specifier.hearts_healing__flags);
    if (is_healing__antidote) {
        if (!p_current_heart)
            return;
        cure_poison_from__hearts(
                p_current_heart, 
                p_last_heart,
                hearts_healing_specifier.quantity_of__healing);
        return;
    }

    p_current_heart =
        get_first_incomplete_heart(
                p_first_heart,
                p_last_heart);
    if (!p_current_heart)
        p_current_heart = p_first_heart;
    Quantity__u16 quantity_of__healing =
        hearts_healing_specifier.quantity_of__healing;

    do {
        switch (*p_current_heart) {
            default:
                break;
            case Heart_Kind__Half_Immortal:
            case Heart_Kind__Immortal_Poison:
                *p_current_heart = Heart_Kind__Immortal_Normal;
                break;
            case Heart_Kind__Half_Normal:
            case Heart_Kind__Normal_Poison:
                *p_current_heart = Heart_Kind__Full_Normal;
                break;
            case Heart_Kind__Empty:
            case Heart_Kind__Half_Poison:
                *p_current_heart = Heart_Kind__Half_Normal;
                continue;
            case Heart_Kind__Full_Poison:
                *p_current_heart = Heart_Kind__Normal_Poison;
                continue;
        }
        p_current_heart++;
    } while (p_current_heart <= p_last_heart
            && --quantity_of__healing > 0
            && quantity_of__healing < 
            ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2);
}

Quantity__u16 get_quantity_u16_of__health_of__entity(
        Entity *p_entity,
        bool should_only_count__quality_hearts) {
    Resource_Reserve *p_hearts =
        &p_entity->hearts;
    Heart__u8 *p_first_heart =
        get_ptr_to__first_resource_symbol(p_hearts);
    Heart__u8 *p_last_heart =
        get_ptr_to__last_resource_symbol(p_hearts);
    Heart__u8 *p_last_usable_heart =
        (should_only_count__quality_hearts)
        ? get_last_healthy_heart(
                p_first_heart, p_last_heart)
        : get_last_usable_resource(
                p_first_heart, 
                p_last_heart);
        ;
    if (!p_last_usable_heart)
        p_last_usable_heart =
            p_first_heart;

    Quantity__u16 quantity_of__health =
        p_last_usable_heart - p_first_heart;

    quantity_of__health *= 2;

    switch (*p_last_usable_heart) {
        default:
            break;
        case Heart_Kind__Half_Immortal:
        case Heart_Kind__Half_Poison:
        case Heart_Kind__Half_Normal:
            quantity_of__health++;
            break;
        case Heart_Kind__Full_Immortal:
        case Heart_Kind__Immortal_Poison:
        case Heart_Kind__Normal_Poison:
        case Heart_Kind__Immortal_Normal:
        case Heart_Kind__Full_Poison:
        case Heart_Kind__Full_Normal:
            quantity_of__health+=2;
            break;
    }

    return quantity_of__health;
}

void set_hearts_of__entity(
        Entity *p_entity,
        Resource_Reserve *hearts) {
    if (hearts->max_quantity_of__resource_symbols
            > ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF) {
        debug_error("set_hearts_of__entity, hearts->max_quantity_of__resource_symbols:%d > ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF.",
                hearts->max_quantity_of__resource_symbols);
        return;
    }
    p_entity->hearts.max_quantity_of__resource_overflow =
        hearts->max_quantity_of__resource_overflow;
    for (Quantity__u8 heart_index=0;
            heart_index<hearts->max_quantity_of__resource_symbols;
            heart_index++) {
        p_entity->hearts.resource_symbols[heart_index] =
            hearts->resource_symbols[heart_index];
    }
}

Energy_Orb__u8 *get_first_incomplete_energy_orb(
        Energy_Orb__u8 *p_first_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb) {
    if (p_first_energy_orb > p_last_energy_orb) {
        debug_error("get_first_incomplete_energy_orb, p_first_energy_orb > p_last_energy_orb");
        return p_first_energy_orb;
    }
    if (!p_first_energy_orb || !p_last_energy_orb) {
        debug_error("get_first_incomplete_energy_orb, p_first_energy_orb:%p, p_last_energy_orb:%p",
                p_first_energy_orb,
                p_last_energy_orb);
        return 0;
    }
    Energy_Orb__u8 *p_current_energy_orb =
        p_first_energy_orb;
    if (!p_current_energy_orb)
        p_current_energy_orb = p_first_energy_orb;

    do {
        switch (*p_current_energy_orb) {
            default:
                return p_current_energy_orb;
            case Energy_Orb_Kind__Full_Demonic:
            case Energy_Orb_Kind__Full_Normal:
            case Energy_Orb_Kind__Demonic_Normal:
                continue;
        }
    } while (++p_current_energy_orb <= p_last_energy_orb);
    return p_last_energy_orb;
}

Energy_Orb__u8 *get_last_healthy_energy_orb(
        Energy_Orb__u8 *p_first_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb) {
    if (p_first_energy_orb > p_last_energy_orb) {
        debug_error("get_last_healthy_energy_orb, p_first_energy_orb > p_last_energy_orb");
        return p_first_energy_orb;
    }
    if (!p_first_energy_orb || !p_last_energy_orb) {
        debug_error("get_last_healthy_energy_orb, p_first_energy_orb:%p, p_last_energy_orb:%p",
                p_first_energy_orb,
                p_last_energy_orb);
        return 0;
    }
    Energy_Orb__u8 *p_current_energy_orb =
        get_last_usable_resource(
                p_first_energy_orb, 
                p_last_energy_orb);
    if (!p_current_energy_orb)
        return 0;

    do {
        switch (*p_current_energy_orb) {
            default:
                continue;
            case Energy_Orb_Kind__Full_Demonic:
            case Energy_Orb_Kind__Half_Demonic:
            case Energy_Orb_Kind__Normal_Poison:
            case Energy_Orb_Kind__Full_Normal:
            case Energy_Orb_Kind__Half_Normal:
                return p_current_energy_orb;
        }
    } while (--p_current_energy_orb > p_first_energy_orb);
    return p_current_energy_orb;
}

Energy_Orb__u8 *get_first_poisoned__energy_orb(
        Energy_Orb__u8 *p_first_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb) {
    if (p_first_energy_orb > p_last_energy_orb) {
        debug_error("get_first_poisoned__energy_orb, p_first_energy_orb > p_last_energy_orb");
        return p_first_energy_orb;
    }
    if (!p_first_energy_orb || !p_last_energy_orb) {
        debug_error("get_first_poisoned__energy_orb, p_first_energy_orb:%p, p_last_energy_orb:%p",
                p_first_energy_orb,
                p_last_energy_orb);
        return 0;
    }
    Energy_Orb__u8 *p_current_energy_orb =
        p_first_energy_orb;

    do {
        switch (*p_current_energy_orb) {
            default:
                continue;
            case Energy_Orb_Kind__Half_Poison:
            case Energy_Orb_Kind__Full_Poison:
            case Energy_Orb_Kind__Normal_Poison:
            case Energy_Orb_Kind__Demonic_Poison:
                return p_current_energy_orb;
        }
    } while (++p_current_energy_orb <= p_last_energy_orb);
    return 0;
}

void poison_energy_orb(Energy_Orb__u8 *p_energy_orb) {
    switch (*p_energy_orb) {
        default:
            return;
        case Energy_Orb_Kind__Full_Normal:
            *p_energy_orb = Energy_Orb_Kind__Normal_Poison;
            return;
        case Energy_Orb_Kind__Normal_Poison:
            *p_energy_orb = Energy_Orb_Kind__Full_Poison;
            return;
        case Energy_Orb_Kind__Half_Normal:
            *p_energy_orb = Energy_Orb_Kind__Half_Poison;
            return;
        case Energy_Orb_Kind__Demonic_Normal:
            *p_energy_orb = Energy_Orb_Kind__Demonic_Poison;
            return;
    }
}

void poison_energy_orb_with__rollover(
        Energy_Orb__u8 **p_energy_orb_ptr,
        Energy_Orb__u8 *p_first_energy_orb) {
    if (!p_energy_orb_ptr && !*p_energy_orb_ptr)
        return;
    poison_energy_orb(*p_energy_orb_ptr);
    if (p_first_energy_orb < *p_energy_orb_ptr) {
        (*p_energy_orb_ptr)--;
    }
}

void apply_energy_damaging_specifier_to__entity(
        Entity *p_entity,
        Energy_Damaging_Specifier energy_damaging_specifier) {
    Resource_Reserve *p_energy_orbs =
        &p_entity->energy_orbs;
    Energy_Orb__u8 *p_first_energy_orb =
        get_ptr_to__first_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_last_energy_orb =
        get_ptr_to__last_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_current_energy_orb =
        get_last_usable_resource(
                p_first_energy_orb, 
                p_last_energy_orb);
    if (!p_current_energy_orb)
        return;
    Energy_Orb__u8 *p_last_healthy_energy_orb =
        get_last_healthy_energy_orb(
                p_first_energy_orb,
                p_last_energy_orb);

    Quantity__u16 quantity_of__damage =
        energy_damaging_specifier.quantity_of__damage;
    if (is_energy_damaging_flags__poisoning(
                energy_damaging_specifier.energy_damaging__flags)) {
        p_current_energy_orb = p_last_healthy_energy_orb;
        while (
            p_current_energy_orb >= p_first_energy_orb
            && quantity_of__damage-- > 0
            && quantity_of__damage 
            < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2) {
            switch(*p_current_energy_orb) {
                case Energy_Orb_Kind__Full_Demonic:
                case Energy_Orb_Kind__Half_Demonic:
                case Energy_Orb_Kind__Demonic_Poison:
                    return;
                case Energy_Orb_Kind__Full_Poison:
                case Energy_Orb_Kind__Half_Poison:
                    p_current_energy_orb--;
                    break;
                default:
                    poison_energy_orb(p_current_energy_orb);
                    break;
            }
        }
        return;
    }

    bool is_damage__order =
        is_energy_damaging_flags__order(
                    energy_damaging_specifier
                    .energy_damaging__flags);
    Quantity__u16 immortal_damaging_tax = 1;
    while (quantity_of__damage-- > 0
            && quantity_of__damage 
            < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2) {
        Resource_Symbol__u8 energy_orb =
            *p_current_energy_orb;
        if (!is_resource_symbol__usable(energy_orb)) {
            p_current_energy_orb--;
            if (p_current_energy_orb < p_first_energy_orb)
                return;
            energy_orb = *p_current_energy_orb;
        }

        switch(energy_orb) {
            default:
#ifndef NDEBUG
                debug_warning("Uncaught switch case apply_energy_damaging_specifier_to__entity.");
#endif
                continue;
            case Energy_Orb_Kind__Half_Poison:
                poison_energy_orb_with__rollover(
                        &p_last_healthy_energy_orb, 
                        p_first_energy_orb);
            case Energy_Orb_Kind__Half_Normal:
                *p_current_energy_orb = Energy_Orb_Kind__Empty;
                break;
            case Energy_Orb_Kind__Full_Normal:
                *p_current_energy_orb = Energy_Orb_Kind__Half_Normal;
                break;
            case Energy_Orb_Kind__Full_Poison:
            case Energy_Orb_Kind__Normal_Poison:
                poison_energy_orb_with__rollover(
                        &p_last_healthy_energy_orb, 
                        p_first_energy_orb);
                *p_current_energy_orb = Energy_Orb_Kind__Half_Poison;
                break;
            case Energy_Orb_Kind__Full_Demonic:
            case Energy_Orb_Kind__Half_Demonic:
                if (!is_energy_damaging_specifier__magical(
                            energy_damaging_specifier))
                    return;
                if (!is_damage__order 
                        && immortal_damaging_tax > quantity_of__damage)
                    return;
                switch (energy_orb) {
                    case Energy_Orb_Kind__Full_Demonic:
                        *p_current_energy_orb = Energy_Orb_Kind__Half_Demonic;
                        break;
                    case Energy_Orb_Kind__Half_Demonic:
                        *p_current_energy_orb = Energy_Orb_Kind__Empty;
                        break;
                }
                quantity_of__damage -= immortal_damaging_tax - 1;
                immortal_damaging_tax =
                    (is_damage__order)
                    ? immortal_damaging_tax + 1
                    : immortal_damaging_tax * 3
                    ;
                break;
            case Energy_Orb_Kind__Demonic_Poison:
                // The energy_orbs prior to this SHOULD be immortal.
                // TODO: put a debug catch for this.
            case Energy_Orb_Kind__Demonic_Normal:
                *p_current_energy_orb = Energy_Orb_Kind__Half_Demonic;
                break;
        }
    }
}

void cure_poison_from__energy_orbs(
        Energy_Orb__u8 *p_current_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb,
        Quantity__u16 quantity_of__purifying) {
    do {
        switch (*p_current_energy_orb) {
            default:
                continue;
            case Energy_Orb_Kind__Full_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Normal_Poison;
                break;
            case Energy_Orb_Kind__Normal_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Full_Normal;
                break;
            case Energy_Orb_Kind__Demonic_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Demonic_Normal;
                break;
            case Energy_Orb_Kind__Half_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Half_Normal;
                break;
        }
    } while (++p_current_energy_orb <= p_last_energy_orb
            && --quantity_of__purifying != 0
            && quantity_of__purifying < 
            ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2);
}

void immortalize_energy_orbs(
        Energy_Orb__u8 *p_first_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb,
        Quantity__u16 quantity_of__immortalization) {
    Energy_Orb__u8 *p_current_energy_orb = p_first_energy_orb;
    do {
        switch (*p_current_energy_orb) {
            case Energy_Orb_Kind__Full_Demonic:
                continue;
            case Energy_Orb_Kind__Locked:
                break;
            default:
                if (quantity_of__immortalization == 1) {
                    switch (*p_current_energy_orb) {
                        case Energy_Orb_Kind__Empty:
                        case Energy_Orb_Kind__Half_Poison:
                        case Energy_Orb_Kind__Half_Normal:
                            *p_current_energy_orb = Energy_Orb_Kind__Half_Demonic;
                            break;
                        case Energy_Orb_Kind__Normal_Poison:
                        case Energy_Orb_Kind__Full_Poison:
                            *p_current_energy_orb = Energy_Orb_Kind__Demonic_Poison;
                            break;
                        case Energy_Orb_Kind__Demonic_Normal:
                        case Energy_Orb_Kind__Demonic_Poison:
                        case Energy_Orb_Kind__Half_Demonic:
                            *p_current_energy_orb = Energy_Orb_Kind__Full_Demonic;
                            break;
                        case Energy_Orb_Kind__Full_Normal:
                            *p_current_energy_orb = Energy_Orb_Kind__Demonic_Normal;
                            break;
                    }
                    return;
                }
                *p_current_energy_orb = Energy_Orb_Kind__Full_Demonic;
                quantity_of__immortalization -= 2;
                break;
        }
    } while (++p_current_energy_orb <= p_last_energy_orb
            && quantity_of__immortalization > 0);
}

void apply_energy_healing_specifier_to__entity(
        Entity *p_entity,
        Energy_Healing_Specifier energy_healing_specifier) {
    Resource_Reserve *p_energy_orbs =
        &p_entity->energy_orbs;
    Energy_Orb__u8 *p_first_energy_orb =
        get_ptr_to__first_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_last_energy_orb =
        get_ptr_to__last_resource_symbol(p_energy_orbs);

    if (is_energy_healing_flags__demonizing(
                energy_healing_specifier.energy_healing__flags)) {
        immortalize_energy_orbs(
                p_first_energy_orb, 
                p_last_energy_orb,
                energy_healing_specifier.quantity_of__healing);
        return;
    }

    Energy_Orb__u8 *p_current_energy_orb =
        get_first_poisoned__energy_orb(
                p_first_energy_orb, 
                p_last_energy_orb);

    bool is_healing__antidote =
        is_energy_healing_flags__antidote(
                energy_healing_specifier.energy_healing__flags);
    if (is_healing__antidote) {
        if (!p_current_energy_orb)
            return;
        cure_poison_from__energy_orbs(
                p_current_energy_orb, 
                p_last_energy_orb,
                energy_healing_specifier.quantity_of__healing);
        return;
    }

    p_current_energy_orb =
        get_first_incomplete_energy_orb(
                p_first_energy_orb,
                p_last_energy_orb);
    if (!p_current_energy_orb)
        p_current_energy_orb = p_first_energy_orb;
    Quantity__u16 quantity_of__healing =
        energy_healing_specifier.quantity_of__healing;

    do {
        switch (*p_current_energy_orb) {
            default:
                break;
            case Energy_Orb_Kind__Half_Demonic:
            case Energy_Orb_Kind__Demonic_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Demonic_Normal;
                break;
            case Energy_Orb_Kind__Half_Normal:
            case Energy_Orb_Kind__Normal_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Full_Normal;
                break;
            case Energy_Orb_Kind__Empty:
            case Energy_Orb_Kind__Half_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Half_Normal;
                continue;
            case Energy_Orb_Kind__Full_Poison:
                *p_current_energy_orb = Energy_Orb_Kind__Normal_Poison;
                continue;
        }
        p_current_energy_orb++;
    } while (p_current_energy_orb <= p_last_energy_orb
            && --quantity_of__healing > 0
            && quantity_of__healing < 
            ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF * 2);
}

void set_energy_orbs_of__entity(
        Entity *p_entity,
        Resource_Reserve *energy_orbs) {
    if (energy_orbs->max_quantity_of__resource_symbols
            > ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF) {
        debug_error("set_energy_orbs_of__entity, energy_orbs->max_quantity_of__resource_symbols:%d > ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF.",
                energy_orbs->max_quantity_of__resource_symbols);
        return;
    }
    p_entity->energy_orbs.max_quantity_of__resource_overflow =
        energy_orbs->max_quantity_of__resource_overflow;
    for (Quantity__u8 heart_index=0;
            heart_index<energy_orbs->max_quantity_of__resource_symbols;
            heart_index++) {
        p_entity->energy_orbs.resource_symbols[heart_index] =
            energy_orbs->resource_symbols[heart_index];
    }
}

Quantity__u16 get_quantity_u16_of__energy_of__entity(
        Entity *p_entity,
        bool should_only_count__quality_energy_orbs) {
    Resource_Reserve *p_energy_orbs =
        &p_entity->energy_orbs;
    Energy_Orb__u8 *p_first_energy_orb =
        get_ptr_to__first_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_last_energy_orb =
        get_ptr_to__last_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_last_usable_energy_orb =
        get_last_usable_resource(
                p_first_energy_orb, 
                p_last_energy_orb);

    Quantity__u16 quantity_of__energy =
        p_last_usable_energy_orb - p_first_energy_orb;

    quantity_of__energy *= 2;

    switch (*p_last_usable_energy_orb) {
        default:
            break;
        case Energy_Orb_Kind__Half_Demonic:
        case Energy_Orb_Kind__Half_Poison:
        case Energy_Orb_Kind__Half_Normal:
            quantity_of__energy++;
            break;
        case Energy_Orb_Kind__Full_Demonic:
        case Energy_Orb_Kind__Demonic_Poison:
        case Energy_Orb_Kind__Normal_Poison:
        case Energy_Orb_Kind__Demonic_Normal:
        case Energy_Orb_Kind__Full_Poison:
        case Energy_Orb_Kind__Full_Normal:
            quantity_of__energy+=2;
            break;
    }

    return quantity_of__energy;
}

void increase_homeostasis_of__entity(
        Entity *p_entity,
        Quantity__u8 quantity_of__homeostasis_increase) {
    p_entity->kind_of_homeostasis__update =
        Homeostasis_Update_Kind__Increasing;
    if (quantity_of__homeostasis_increase 
            > HOMEOSTASIS_MAX_QUANTITY_OF
            - p_entity->humanoid__homeostasis__i8) {
        p_entity->humanoid__homeostasis__i8 =
            HOMEOSTASIS_MAX_QUANTITY_OF;
        return;
    }
    p_entity->humanoid__homeostasis__i8 += 
        quantity_of__homeostasis_increase;
}

void decrease_homeostasis_of__entity(
        Entity *p_entity,
        Quantity__u8 quantity_of__homeostasis_decrease) {
    p_entity->kind_of_homeostasis__update =
        Homeostasis_Update_Kind__Decreasing;
    if (quantity_of__homeostasis_decrease 
            > p_entity->humanoid__homeostasis__i8
            - HOMEOSTASIS_MIN_QUANTITY_OF) {
        p_entity->humanoid__homeostasis__i8 =
            HOMEOSTASIS_MIN_QUANTITY_OF;
        return;
    }
    p_entity->humanoid__homeostasis__i8 -= 
        quantity_of__homeostasis_decrease;
}

enum Homeostasis_State get_state_of__homeostasis_of__entity(
        Entity *p_entity) {
    enum Homeostasis_State state_of__homeostasis =
        Homeostasis_State__Unknown;
    Signed_Quantity__i8 homeostasis =
        p_entity->humanoid__homeostasis__i8;
    if (is_humanoid__undead(p_entity)) {
        if (homeostasis < HOMEOSTASIS__SOULFUL)
            return Homeostasis_State__Soulfull;
        if (homeostasis < HOMEOSTASIS__FLEETING_SOUL)
            return Homeostasis_State__Fleeting_Soul;
        if (homeostasis < HOMEOSTASIS__SOULLESS)
            return Homeostasis_State__Soulless;
        if (homeostasis < HOMEOSTASIS__LICHLING)
            return Homeostasis_State__Lichling;
        return Homeostasis_State__Lich;
    }

    if (does_humanoid_have__divine_providence(
                p_entity)) {
        return Homeostasis_State__Divine_Providence;
    }
    if (homeostasis < HOMEOSTASIS__EXTREME_FREEZING)
        return Homeostasis_State__Extreme_Freezing;
    if (homeostasis < HOMEOSTASIS__FREEZING)
        return Homeostasis_State__Freezing;
    if (homeostasis < HOMEOSTASIS__COLD)
        return Homeostasis_State__Cold;
    if (homeostasis > HOMEOSTASIS__COLD
            && homeostasis < HOMEOSTASIS__HOT)
        return Homeostasis_State__Neutral;
    if (homeostasis > HOMEOSTASIS__EXTREME_BURNING)
        return Homeostasis_State__Extreme_Burning;
    if (homeostasis > HOMEOSTASIS__BURNING)
        return Homeostasis_State__Burning;
    if (homeostasis > HOMEOSTASIS__HOT)
        return Homeostasis_State__Hot;

    return state_of__homeostasis;
}

void increase_sustenance_of__entity(
        Entity *p_entity,
        enum Sustenance_Kind kind_of_sustenance,
        Quantity__u8 quantity_of__sustenance_increase) {
    Sustenance__u8 *p_sustenance;
    switch (kind_of_sustenance) {
        default:
            debug_error("increase_sustenance_of__entity, Invalid sustenance %d", kind_of_sustenance);
            return;
        case Sustenance_Kind__Hunger:
        // case Sustenance_Kind__Sanity:
            p_sustenance =
                &p_entity->humanoid__primary_sustenance__u8;
            break;
        case Sustenance_Kind__Thirst:
        // case Sustenance_Kind__Blood:
            p_sustenance =
                &p_entity->humanoid__secondary_sustenance__u8;
            break;
    }

    Quantity__u8 quantity_of__sustenance =
        *p_sustenance;

    if (SUSTENANCE_MAX_QUANTITY_OF - quantity_of__sustenance
            < quantity_of__sustenance_increase) {
        *p_sustenance = SUSTENANCE_MAX_QUANTITY_OF;
    } else {
        *p_sustenance += quantity_of__sustenance_increase;
    }
}

void decrease_sustenance_of__entity(
        Entity *p_entity,
        enum Sustenance_Kind kind_of_sustenance,
        Quantity__u8 quantity_of__sustenance_decrease) {
    Sustenance__u8 *p_sustenance;
    switch (kind_of_sustenance) {
        default:
            debug_error("decrease_sustenance_of__entity, Invalid sustenance %d", kind_of_sustenance);
            return;
        case Sustenance_Kind__Hunger:
        // case Sustenance_Kind__Sanity:
            p_sustenance =
                &p_entity->humanoid__primary_sustenance__u8;
            break;
        case Sustenance_Kind__Thirst:
        // case Sustenance_Kind__Blood:
            p_sustenance =
                &p_entity->humanoid__secondary_sustenance__u8;
            break;
    }

    Quantity__u8 quantity_of__sustenance =
        *p_sustenance;

    if (quantity_of__sustenance + SUSTENANCE_MIN_QUANTITY_OF
            < quantity_of__sustenance_decrease) {
        *p_sustenance = SUSTENANCE_MIN_QUANTITY_OF;
    } else {
        *p_sustenance -= quantity_of__sustenance_decrease;
    }
}

Sustenance__u8 get_quantity_of__sustenance_of__entity(
        Entity *p_entity,
        enum Sustenance_Kind kind_of_sustenance) {
    switch (kind_of_sustenance) {
        default:
            debug_error("get_quantity_of__sustenance_of__entity, Invalid sustenance %d", kind_of_sustenance);
            return 0;
        case Sustenance_Kind__Hunger:
        // case Sustenance_Kind__Sanity:
            return p_entity->humanoid__primary_sustenance__u8;
        case Sustenance_Kind__Thirst:
        // case Sustenance_Kind__Blood:
            return p_entity->humanoid__secondary_sustenance__u8;
    }
}

enum Sustenance_State get_state_of__sustenance_of__entity(
        Entity *p_entity,
        enum Sustenance_Kind kind_of_sustenance) {
    Sustenance__u8 sustenance =
        (kind_of_sustenance == Sustenance_Kind__Primary)
        ? p_entity->humanoid__primary_sustenance__u8
        : p_entity->humanoid__secondary_sustenance__u8
        ;

    if (sustenance > SUSTENANCE__BLOATED)
        return Sustenance_State__Bloated;
    if (sustenance > SUSTENANCE__FULL)
        return Sustenance_State__Full;
    if (sustenance > SUSTENANCE__SATISFIED)
        return Sustenance_State__Satisifed;
    if (sustenance > SUSTENANCE__WELL)
        return Sustenance_State__Well;
    if (sustenance > SUSTENANCE__INDIFFERENT)
        return Sustenance_State__Indifferent;
    if (sustenance > SUSTENANCE__WANTING)
        return Sustenance_State__Wanting;
    if (sustenance > SUSTENANCE__NEEDING)
        return Sustenance_State__Needing;
    if (sustenance > SUSTENANCE__DESPERATE)
        return Sustenance_State__Desperate;
    return Sustenance_State__Dying;
}

#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include <entity/reserves.h>

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
#ifndef NDEBUG
    if (p_last_symbol < p_first_symbol) {
        debug_error("get_last_usable_resource, p_last_symbol < p_first_symbol");
        return 0;
    }
#endif
    do {
        Resource_Symbol__u8 symbol =
            *p_last_symbol;
        if (symbol != RESOURCE_SYMBOL__EMPTY
                && symbol != RESOURCE_SYMBOL__LOCKED)
            return p_last_symbol;
    } while (p_first_symbol <= p_last_symbol--);
    return 0;
}

Heart__u8 *get_first_incomplete_heart(
        Resource_Reserve *p_hearts) {
    Heart__u8 *p_first_heart =
        get_ptr_to__first_resource_symbol(p_hearts);
    Heart__u8 *p_last_heart =
        get_ptr_to__last_resource_symbol(p_hearts);
    Heart__u8 *p_current_heart =
        get_last_usable_resource(
                p_first_heart, 
                p_last_heart);
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
        Resource_Reserve *p_hearts) {
    Heart__u8 *p_first_heart =
        get_ptr_to__first_resource_symbol(p_hearts);
    Heart__u8 *p_last_heart =
        get_ptr_to__last_resource_symbol(p_hearts);
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
    }
}

void poison_heart_with__rollover(
        Heart__u8 **p_heart_ptr,
        Heart__u8 *p_first_heart) {
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
    Heart__u8 *p_last_healthy_heart =
        get_last_healthy_heart(p_hearts);

    Quantity__u16 quantity_of__damage =
        hearts_damaging_specifier.quantity_of__damage;
    while (quantity_of__damage-- < 0) {
        Resource_Symbol__u8 heart =
            *p_current_heart;
        if (!is_resource_symbol__usable(heart)) {
            p_current_heart--;
            if (p_current_heart < p_first_heart)
                return;
            heart = *p_current_heart;
        }

        Quantity__u16 immortal_damaging_tax = 1;
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
                switch (heart) {
                    case Heart_Kind__Full_Immortal:
                        *p_current_heart = Heart_Kind__Half_Immortal;
                        break;
                    case Heart_Kind__Half_Immortal:
                        *p_current_heart = Heart_Kind__Empty;
                        break;
                }
                if (immortal_damaging_tax > quantity_of__damage)
                    return;
                quantity_of__damage -= immortal_damaging_tax;
                immortal_damaging_tax *= 3;
                break;
            case Heart_Kind__Immortal_Poison:
                // The remaining hearts SHOULD be immortal.
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
            && quantity_of__purifying < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF);
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
                            *p_current_heart = Heart_Kind__Immortal_Poison;
                            break;
                        case Heart_Kind__Immortal_Normal:
                        case Heart_Kind__Half_Immortal:
                            *p_current_heart = Heart_Kind__Full_Immortal;
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
        get_last_usable_resource(
                p_first_heart, 
                p_last_heart);

    bool is_healing__antidote =
        is_hearts_healing_flags__antidote(
                hearts_healing_specifier.hearts_healing__flags);
    if (is_healing__antidote && p_current_heart) {
        cure_poison_from__hearts(
                p_current_heart, 
                p_last_heart,
                hearts_healing_specifier.quantity_of__healing);
        return;
    }

    p_current_heart =
        get_first_incomplete_heart(p_hearts);
    if (!p_current_heart)
        p_current_heart = p_first_heart;
    Quantity__u16 quantity_of__healing =
        hearts_healing_specifier.quantity_of__healing;

    do {
        switch (*p_current_heart) {
            default:
                break;
            case Heart_Kind__Half_Immortal:
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
            && quantity_of__healing < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF);
}

Energy_Orb__u8 *get_last_healthy_energy_orb(
        Resource_Reserve *p_energy_orbs) {
    Energy_Orb__u8 *p_first_energy_orb =
        get_ptr_to__first_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_last_energy_orb =
        get_ptr_to__last_resource_symbol(p_energy_orbs);
    Energy_Orb__u8 *p_current_energy_orb =
        get_last_usable_resource(
                p_first_energy_orb, 
                p_last_energy_orb);

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

void poison_energy_orb(Heart__u8 *p_energy_orb) {
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
    }
}

void poison_energy_orb_with__rollover(
        Energy_Orb__u8 **p_energy_orb_ptr,
        Energy_Orb__u8 *p_first_energy_orb) {
    poison_energy_orb(*p_energy_orb_ptr);
    if (p_first_energy_orb < *p_energy_orb_ptr) {
        (*p_energy_orb_ptr)--;
    }
}

void apply_energy_orbs_damaging_specifier_to__entity(
        Entity *p_entity,
        Energy_Damaging_Specifier energy_orbs_damaging_specifier) {
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
    Energy_Orb__u8 *p_last_healthy_energy_orb =
        get_last_healthy_energy_orb(p_energy_orbs);

    Quantity__u16 quantity_of__damage =
        energy_orbs_damaging_specifier.quantity_of__damage;
    while (quantity_of__damage-- < 0) {
        Resource_Symbol__u8 energy_orb =
            *p_current_energy_orb;
        if (!is_resource_symbol__usable(energy_orb)) {
            p_current_energy_orb--;
            if (p_current_energy_orb < p_first_energy_orb)
                return;
            energy_orb = *p_current_energy_orb;
        }

        Quantity__u16 demonic_damaging_tax = 1;
        switch(energy_orb) {
            default:
#ifndef NDEBUG
                debug_warning("Uncaught switch case apply_energy_orbs_damaging_specifier_to__entity.");
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
                            energy_orbs_damaging_specifier))
                    return;
                switch (energy_orb) {
                    case Energy_Orb_Kind__Full_Demonic:
                        *p_current_energy_orb = Energy_Orb_Kind__Half_Demonic;
                        break;
                    case Energy_Orb_Kind__Half_Demonic:
                        *p_current_energy_orb = Energy_Orb_Kind__Empty;
                        break;
                }
                if (demonic_damaging_tax > quantity_of__damage)
                    return;
                quantity_of__damage -= demonic_damaging_tax;
                demonic_damaging_tax *= 3;
                break;
            case Energy_Orb_Kind__Demonic_Poison:
                // The remaining energy_orbs SHOULD be immortal.
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
            && quantity_of__purifying < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF);
}

void demonize_energy_orbs(
        Energy_Orb__u8 *p_first_energy_orb,
        Energy_Orb__u8 *p_last_energy_orb,
        Quantity__u16 quantity_of__demonization) {
    Energy_Orb__u8 *p_current_energy_orb = p_first_energy_orb;
    do {
        switch (*p_current_energy_orb) {
            case Energy_Orb_Kind__Full_Demonic:
                continue;
            case Energy_Orb_Kind__Locked:
                break;
            default:
                if (quantity_of__demonization == 1) {
                    switch (*p_current_energy_orb) {
                        case Energy_Orb_Kind__Empty:
                        case Energy_Orb_Kind__Half_Poison:
                        case Energy_Orb_Kind__Half_Normal:
                            *p_current_energy_orb = Energy_Orb_Kind__Half_Demonic;
                            break;
                        case Energy_Orb_Kind__Normal_Poison:
                            *p_current_energy_orb = Energy_Orb_Kind__Demonic_Poison;
                            break;
                        case Energy_Orb_Kind__Demonic_Normal:
                        case Energy_Orb_Kind__Half_Demonic:
                            *p_current_energy_orb = Energy_Orb_Kind__Full_Demonic;
                            break;
                    }
                    return;
                }
                *p_current_energy_orb = Energy_Orb_Kind__Full_Demonic;
                quantity_of__demonization -= 2;
                break;
        }
    } while (++p_current_energy_orb <= p_last_energy_orb
            && quantity_of__demonization > 0);
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
        demonize_energy_orbs(
                p_first_energy_orb, 
                p_last_energy_orb,
                energy_healing_specifier.quantity_of__healing);
        return;
    }

    Energy_Orb__u8 *p_current_energy_orb =
        get_last_usable_resource(
                p_first_energy_orb, 
                p_last_energy_orb);

    bool is_healing__antidote =
        is_energy_healing_flags__antidote(
                energy_healing_specifier.energy_healing__flags);
    if (is_healing__antidote) {
        cure_poison_from__energy_orbs(
                p_current_energy_orb, 
                p_last_energy_orb,
                energy_healing_specifier.quantity_of__healing);
        return;
    }

    Energy_Orb__u8 *p_last_healthy_energy_orb =
        get_last_healthy_energy_orb(p_energy_orbs);
    Quantity__u16 quantity_of__healing =
        energy_healing_specifier.quantity_of__healing;

    do {
        switch (*p_last_healthy_energy_orb) {
            default:
                break;
            case Energy_Orb_Kind__Half_Demonic:
                *p_last_healthy_energy_orb = Energy_Orb_Kind__Demonic_Normal;
                break;
            case Energy_Orb_Kind__Half_Normal:
            case Energy_Orb_Kind__Normal_Poison:
                *p_last_healthy_energy_orb = Energy_Orb_Kind__Full_Normal;
                break;
            case Energy_Orb_Kind__Empty:
            case Energy_Orb_Kind__Half_Poison:
                *p_last_healthy_energy_orb = Energy_Orb_Kind__Half_Normal;
                continue;
            case Energy_Orb_Kind__Full_Poison:
                *p_last_healthy_energy_orb = Energy_Orb_Kind__Normal_Poison;
                continue;
        }
        p_last_healthy_energy_orb++;
    } while (p_last_healthy_energy_orb <= p_last_energy_orb
            && --quantity_of__healing > 0
            && quantity_of__healing < ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF);
}

#include "defines.h"
#include "defines_weak.h"
#include "entity/reserves.h"
#include "game_action/game_action.h"
#include "timer.h"
#include "world/world.h"
#include <entity/handlers/body/body_handler__living.h>

enum Health_State get_health_state_of__humanoid(
        Entity *p_humanoid) {
    Quantity__u16 quantity_of__quality_health =
        get_quantity_u16_of__health_of__entity(p_humanoid,
                true);

    if (quantity_of__quality_health == 0)
        return Health_State__Dead;

    if (quantity_of__quality_health < 6)
        return Health_State__Dying;

    if (quantity_of__quality_health < 10)
        return Health_State__Injured;

    if (quantity_of__quality_health < 18)
        return Health_State__Hurt;

    return Health_State__Normal;
}

enum Energy_State get_energy_state_of__humanoid(
        Entity *p_humanoid) {
    Quantity__u16 quantity_of__quality_energy =
        get_quantity_u16_of__energy_of__entity(
                p_humanoid,
                false);

    if (quantity_of__quality_energy == 0)
        return Energy_State__Exerted;

    if (quantity_of__quality_energy < 6)
        return Energy_State__Exhausted;

    if (quantity_of__quality_energy < 12)
        return Energy_State__Tired;

    return Energy_State__Normal;
}

Quantity__u16 get_energy_regeneration_tick_rate(
        enum Homeostasis_State state_of__homeostasis,
        enum Health_State state_of__health,
        enum Sustenance_State state_of__primary_sustenance,
        enum Sustenance_State state_of__worst_sustenance) {
    Quantity__u16 tick_rate = 256;
    switch (state_of__homeostasis) {
        case Homeostasis_State__Extreme_Freezing:
            tick_rate *= 2;
            break;
        case Homeostasis_State__Extreme_Burning:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Homeostasis_State__Burning:
        case Homeostasis_State__Freezing:
            break;
        case Homeostasis_State__Hot:
        case Homeostasis_State__Cold:
            tick_rate /= 8;
            tick_rate *= 5;
            break;
        default:
            tick_rate /= 4;
    }

    switch (state_of__health) {
        case Health_State__Dying:
            tick_rate *= 2;
            break;
        case Health_State__Injured:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Health_State__Hurt:
            tick_rate /= 8;
            tick_rate *= 5;
            break;
        default:
            tick_rate /= 4;
            break;
    }

    switch (state_of__worst_sustenance) {
        case Sustenance_State__Dying:
            tick_rate *= 2;
            break;
        case Sustenance_State__Desperate:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Sustenance_State__Needing:
            tick_rate *= 4;
            tick_rate /= 3;
            break;
        case Sustenance_State__Wanting:
            tick_rate *= 5;
            tick_rate /= 4;
            break;
        case Sustenance_State__Bloated:
            if (state_of__primary_sustenance
                    == Sustenance_State__Bloated) {
                tick_rate *= 3;
                break;
            }
        default:
        case Sustenance_State__Indifferent:
            break;
        case Sustenance_State__Well:
            tick_rate *= 4;
            tick_rate /= 5;
            break;
        case Sustenance_State__Satisifed:
            tick_rate *= 3;
            tick_rate /= 4;
            break;
        case Sustenance_State__Full:
            tick_rate *= 2;
            tick_rate /= 3;
            break;
    }

    return tick_rate;
}

Quantity__u16 get_health_regeneration_tick_rate(
        enum Homeostasis_State state_of__homeostasis,
        enum Energy_State state_of__energy,
        enum Sustenance_State state_of__primary_sustenance,
        enum Sustenance_State state_of__worst_sustenance) {
    Quantity__u16 tick_rate = 768;
    switch (state_of__homeostasis) {
        case Homeostasis_State__Extreme_Freezing:
            tick_rate *= 2;
            break;
        case Homeostasis_State__Extreme_Burning:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Homeostasis_State__Burning:
        case Homeostasis_State__Freezing:
            break;
        case Homeostasis_State__Hot:
        case Homeostasis_State__Cold:
            tick_rate /= 8;
            tick_rate *= 5;
            break;
        default:
            tick_rate /= 4;
    }

    switch (state_of__energy) {
        case Energy_State__Exerted:
            tick_rate *= 2;
            break;
        case Energy_State__Exhausted:
            tick_rate *= 8;
            tick_rate /= 5;
            break;
        case Energy_State__Tired:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        default:
            tick_rate /= 4;
            break;
    }

    if (state_of__primary_sustenance
            == Sustenance_State__Bloated) {
        tick_rate /= 2;
    }

    switch (state_of__worst_sustenance) {
        case Sustenance_State__Dying:
            tick_rate *= 2;
            break;
        case Sustenance_State__Desperate:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Sustenance_State__Needing:
            tick_rate *= 4;
            tick_rate /= 3;
            break;
        case Sustenance_State__Wanting:
            tick_rate *= 5;
            tick_rate /= 4;
            break;
        default:
        case Sustenance_State__Indifferent:
            break;
        case Sustenance_State__Well:
            tick_rate *= 4;
            tick_rate /= 5;
            break;
        case Sustenance_State__Satisifed:
            tick_rate *= 3;
            tick_rate /= 4;
            break;
        case Sustenance_State__Full:
            tick_rate *= 2;
            tick_rate /= 3;
            break;
        case Sustenance_State__Bloated:
            if (state_of__primary_sustenance
                    != Sustenance_State__Bloated) {
                tick_rate *= 3;
                tick_rate /= 5;
            }
            break;
    }

    return tick_rate;
}

Quantity__u16 get_primary_sustenance_tick_rate_for__humanoid(
        enum Homeostasis_State state_of__homeostasis,
        enum Health_State state_of__health,
        enum Energy_State state_of__energy) {
    Quantity__u16 tick_rate = 2048;
    switch (state_of__homeostasis) {
        case Homeostasis_State__Extreme_Freezing:
            tick_rate /= 3;
            break;
        case Homeostasis_State__Extreme_Burning:
            tick_rate *= 3;
            break;
        case Homeostasis_State__Freezing:
            tick_rate /= 2;
            break;
        case Homeostasis_State__Burning:
            tick_rate *= 2;
            break;
        case Homeostasis_State__Hot:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Homeostasis_State__Cold:
            tick_rate /= 3;
            tick_rate *= 2;
            break;
        default:
            break;
    }

    return tick_rate;
}

Quantity__u16 get_secondary_sustenance_tick_rate_for__humanoid(
        enum Homeostasis_State state_of__homeostasis,
        enum Health_State state_of__health,
        enum Energy_State state_of__energy) {
    Quantity__u16 tick_rate = 1024;
    switch (state_of__homeostasis) {
        case Homeostasis_State__Extreme_Freezing:
            tick_rate *= 3;
            break;
        case Homeostasis_State__Extreme_Burning:
            tick_rate /= 3;
            break;
        case Homeostasis_State__Freezing:
            tick_rate *= 2;
            break;
        case Homeostasis_State__Burning:
            tick_rate /= 2;
            break;
        case Homeostasis_State__Hot:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        case Homeostasis_State__Cold:
            tick_rate *= 3;
            tick_rate /= 2;
            break;
        default:
            break;
    }

    return tick_rate;
}

void m_entity_body_handler__living(
        Entity *p_this_humanoid,
        Game *p_game) {
    enum Health_State state_of__health =
        get_health_state_of__humanoid(p_this_humanoid);

    loop_timer_u16(
            &p_this_humanoid->humanoid__homeostasis__timer_u16);

    if (p_this_humanoid->hearts.resource_symbols[0]
            == Heart_Kind__Empty) {
        //TODO: play death animation
        release_entity_from__world(
                p_game, 
                p_this_humanoid);
        return;
    }

    enum Energy_State state_of__energy =
        get_energy_state_of__humanoid(p_this_humanoid);

    enum Homeostasis_State state_of__homeostasis =
        get_state_of__homeostasis_of__entity(p_this_humanoid);

    enum Sustenance_State state_of__primary_sustenance =
        get_state_of__sustenance_of__entity(
                p_this_humanoid, 
                Sustenance_Kind__Hunger);

    enum Sustenance_State state_of__secondary_sustenance =
        get_state_of__sustenance_of__entity(
                p_this_humanoid, 
                Sustenance_Kind__Thirst);

    enum Sustenance_State state_of__worst_sustenance =
        get_worst_of__two_sustenance_states(
                state_of__primary_sustenance, 
                state_of__secondary_sustenance);

    Quantity__u16 tick_rate__health =
        get_health_regeneration_tick_rate(
                state_of__homeostasis, 
                state_of__energy, 
                state_of__primary_sustenance,
                state_of__worst_sustenance);

    Quantity__u16 tick_rate__energy =
        get_energy_regeneration_tick_rate(
                state_of__homeostasis, 
                state_of__health, 
                state_of__primary_sustenance,
                state_of__worst_sustenance);

    Quantity__u16 tick_rate__primary_sustenance =
        get_primary_sustenance_tick_rate_for__humanoid(
                state_of__homeostasis, 
                state_of__health, 
                state_of__energy);

    Quantity__u16 tick_rate__secondary_sustenance =
        get_secondary_sustenance_tick_rate_for__humanoid(
                state_of__homeostasis, 
                state_of__health, 
                state_of__energy);

    Quantity__u16 elapsed =
         get_time_elapsed_from__timer_u16(
                 &p_this_humanoid->humanoid__homeostasis__timer_u16);

    if (elapsed % tick_rate__health == 0) {
        Hearts_Healing_Specifier healing;
        healing.hearts_healing__flags = 0;
        healing.quantity_of__healing = 1;

        invoke_action__apply_heart_healing_to__entity(
                p_game,
                p_this_humanoid, 
                p_this_humanoid, 
                &healing);
    }

    if (elapsed % tick_rate__energy == 0) {
        Energy_Healing_Specifier healing;
        healing.energy_healing__flags = 0;
        healing.quantity_of__healing = 1;

        invoke_action__apply_energy_healing_to__entity(
                p_game,
                p_this_humanoid, 
                p_this_humanoid, 
                &healing);
    }

    if (elapsed % tick_rate__primary_sustenance == 0) {
        invoke_action__decrease_sustenance_of__entity(
                p_game, 
                p_this_humanoid, 
                p_this_humanoid, 
                Sustenance_Kind__Hunger, 
                1);
    }
    if (elapsed % tick_rate__secondary_sustenance == 0) {
        invoke_action__decrease_sustenance_of__entity(
                p_game, 
                p_this_humanoid, 
                p_this_humanoid, 
                Sustenance_Kind__Thirst, 
                1);
    }

    //TODO: magic number
    if (state_of__primary_sustenance 
            == Sustenance_State__Dying
            || state_of__secondary_sustenance
            == Sustenance_State__Dying) {
        if (elapsed % 128 == 0) {
            Hearts_Damaging_Specifier damage;
            damage.hearts_damaging__flags = 0;
            damage.quantity_of__damage = 1;

            invoke_action__apply_heart_damage_to__entity(
                    p_game,
                    p_this_humanoid, 
                    p_this_humanoid, 
                    &damage);
        }
    }
}

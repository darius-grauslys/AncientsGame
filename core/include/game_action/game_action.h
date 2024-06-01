#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include <defines.h>

static bool inline is_game_action_using__id_or_ptr(
        Game_Action_Flags game_action_flags) {
    return (bool)(game_action_flags 
            & GAME_ACTION_FLAGS__BIT_IS_ID_OR_PTR);
}

static void inline invoke_game_action(
        Game *p_game,
        Game_Action *p_game_action) {
#ifndef NDEBUG
    if (!p_game->m_game_action_handler) {
        debug_abort("p_game->m_game_action_handler == 0.");
        debug_warning("Did you forget to init_game(...)?");
        return;
    }
#endif
    p_game->m_game_action_handler(p_game, p_game_action);
}

///
/// Sends a Game_Action which applies velocity.
///
void invoke_action__apply_velocity_to__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector);

///
/// Sends a Game_Action which sets velocity.
///
void invoke_action__set_velocity_of__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector);

void invoke_action__apply_heart_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier *p_hearts_healing_specifier);

void invoke_action__apply_energy_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier *p_energy_healing_specifier);

void invoke_action__apply_heart_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier);

void invoke_action__apply_energy_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier *p_energy_damaging_specifier);

void invoke_action__increase_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance);

void invoke_action__decrease_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance);

void invoke_action__increase_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis);

void invoke_action__decrease_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis);

#endif

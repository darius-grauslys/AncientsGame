#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include "defines_weak.h"
#include "game.h"
#include <defines.h>

void initialize_p_game_action(
        Game_Action *p_game_action);

void invoke_game_action(
        Game *p_game,
        Game_Action *p_game_action);

enum Game_Action_Kind get_the_kind_of__game_action(
        Game_Action *p_game_action);

void initialize_game_action_as__allocate_entity(
        Game_Action *p_game_action,
        enum Entity_Kind the_kind_of__entity,
        Vector__3i32F4 position__3i32F4);

void initialize_game_action_as__set_flags_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Entity_Flags__u8 entity_flags);

///
/// Sends a Game_Action which applies velocity.
///
void initialize_game_action_as__apply_velocity_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector);

///
/// Sends a Game_Action which sets velocity.
///
void initialize_game_action_as__set_velocity_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector);

void initialize_game_action_as__apply_heart_healing_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier *p_hearts_healing_specifier);

void initialize_game_action_as__apply_energy_healing_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier *p_energy_healing_specifier);

void initialize_game_action_as__apply_heart_damage_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier);

void initialize_game_action_as__apply_energy_damage_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier *p_energy_damaging_specifier);

void initialize_game_action_as__increase_sustenance_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance);

void initialize_game_action_as__decrease_sustenance_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance);

void initialize_game_action_as__increase_homeostasis_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis);

void initialize_game_action_as__decrease_homeostasis_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis);

void invoke_action__allocate_entity(
        Game *p_game,
        enum Entity_Kind the_kind_of__entity,
        Vector__3i32F4 position__3i32F4);

void invoke_action__set_flags_of__entity(
        Game *p_game,
        Entity *p_entity,
        Entity_Flags__u8 entity_flags);

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

#include "defines.h"
#include "defines_weak.h"
#include <game_action/game_action.h>

///
/// Sends a Game_Action which applies velocity.
///
void invoke_action__apply_velocity_to__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    Game_Action game_action;

    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Hitbox__Apply_Velocity;
    game_action.p_entity_target = p_entity;
    game_action.velocity_vector__apply = velocity_vector;

    invoke_game_action(
            p_game, 
            &game_action);
}

///
/// Sends a Game_Action which sets velocity.
///
void invoke_action__set_velocity_of__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    Game_Action game_action;

    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Hitbox__Set_Velocity;
    game_action.p_entity_target = p_entity;
    game_action.velocity_vector__set = velocity_vector;

    invoke_game_action(
            p_game, 
            &game_action);
}

void invoke_action__apply_heart_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier *p_hearts_healing_specifier) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Health__Apply_Healing;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.hearts_healing_specifier = *p_hearts_healing_specifier;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__apply_energy_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier *p_energy_healing_specifier) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Energy__Apply_Healing;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.energy_healing_specifier = *p_energy_healing_specifier;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__apply_heart_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Health__Apply_Damage;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.hearts_damaging_specifier = *p_hearts_damaging_specifier;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__apply_energy_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier *p_energy_damaging_specifier) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Energy__Apply_Damage;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.energy_damage_specifier = *p_energy_damaging_specifier;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__increase_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Sustenance__Increase;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.kind_of_sustenance = kind_of_sustenance;
    game_action.change_in__sustenance = change_in__sustenance;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__decrease_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Sustenance__Decrease;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.kind_of_sustenance = kind_of_sustenance;
    game_action.change_in__sustenance = change_in__sustenance;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__increase_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Homeostasis__Increase;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.change_in__homeostasis = change_in__homeostasis;

    invoke_game_action(p_game, &game_action);
}

void invoke_action__decrease_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    Game_Action game_action;
    game_action.the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Homeostasis__Decrease;
    game_action.p_entity_source = p_entity_source;
    game_action.p_entity_target = p_entity_target;
    game_action.change_in__homeostasis = change_in__homeostasis;

    invoke_game_action(p_game, &game_action);
}

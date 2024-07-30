#include "defines.h"
#include "defines_weak.h"
#include <game_action/game_action.h>
#include <serialization/serialized_field.h>

void initialize_game_action_as__allocate_entity(
        Game_Action *p_game_action,
        enum Entity_Kind the_kind_of__entity,
        Vector__3i32F4 position__3i32F4) {
    initialize_p_game_action(p_game_action);

    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Allocate;
    p_game_action->allocate__kind_of__entity = 
        the_kind_of__entity;
    p_game_action->allocate__position =
        position__3i32F4;
}

void initialize_game_action_as__set_flags_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Entity_Flags__u8 entity_flags) {
    initialize_p_game_action(p_game_action);

    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Flags__Set;
    p_game_action->entity_flags =
        entity_flags;
}

///
/// Sends a Game_Action which applies velocity.
///
void initialize_game_action_as__apply_velocity_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    initialize_p_game_action(p_game_action);

    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Hitbox__Apply_Velocity;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity);
    p_game_action->velocity_vector__apply = velocity_vector;
}

///
/// Sends a Game_Action which sets velocity.
///
void initialize_game_action_as__set_velocity_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    initialize_p_game_action(p_game_action);

    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Hitbox__Set_Velocity;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity);
    p_game_action->velocity_vector__set = velocity_vector;
}

void initialize_game_action_as__apply_heart_healing_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier *p_hearts_healing_specifier) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Health__Apply_Healing;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->hearts_healing_specifier = *p_hearts_healing_specifier;

}

void initialize_game_action_as__apply_energy_healing_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier *p_energy_healing_specifier) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Energy__Apply_Healing;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->energy_healing_specifier = *p_energy_healing_specifier;

}

void initialize_game_action_as__apply_heart_damage_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Health__Apply_Damage;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->hearts_damaging_specifier = *p_hearts_damaging_specifier;

}

void initialize_game_action_as__apply_energy_damage_to__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier *p_energy_damaging_specifier) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Energy__Apply_Damage;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->energy_damage_specifier = *p_energy_damaging_specifier;

}

void initialize_game_action_as__increase_sustenance_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Sustenance__Increase;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->kind_of_sustenance = kind_of_sustenance;
    p_game_action->change_in__sustenance = change_in__sustenance;

}

void initialize_game_action_as__decrease_sustenance_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Sustenance__Decrease;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->kind_of_sustenance = kind_of_sustenance;
    p_game_action->change_in__sustenance = change_in__sustenance;
}

void initialize_game_action_as__increase_homeostasis_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Homeostasis__Increase;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->change_in__homeostasis = change_in__homeostasis;
}

void initialize_game_action_as__decrease_homeostasis_of__entity(
        Game_Action *p_game_action,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    initialize_p_game_action(p_game_action);
    p_game_action->the_kind_of_game_action__this_action_is =
        Game_Action_Kind__Entity__Homeostasis__Decrease;
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__source,
            p_entity_source);
    point_serialized_field_to__this_serialized_struct(
            &p_game_action->s_entity__target,
            p_entity_target);
    p_game_action->change_in__homeostasis = change_in__homeostasis;
}

void invoke_action__allocate_entity(
        Game *p_game,
        enum Entity_Kind the_kind_of__entity,
        Vector__3i32F4 position__3i32F4) {
    Game_Action game_action;
    initialize_game_action_as__allocate_entity(
            &game_action, 
            the_kind_of__entity, 
            position__3i32F4);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__set_flags_of__entity(
        Game *p_game,
        Entity *p_entity,
        Entity_Flags__u8 entity_flags) {
    Game_Action game_action;
    initialize_game_action_as__set_flags_of__entity(
            &game_action, 
            p_entity, 
            entity_flags);
    invoke_game_action(
            p_game, &game_action);
}

///
/// Sends a Game_Action which applies velocity.
///
void invoke_action__apply_velocity_to__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    Game_Action game_action;
    initialize_game_action_as__apply_velocity_to__entity(
            &game_action, 
            p_entity, 
            velocity_vector);
    invoke_game_action(
            p_game, &game_action);
}

///
/// Sends a Game_Action which sets velocity.
///
void invoke_action__set_velocity_of__entity(
        Game *p_game,
        Entity *p_entity,
        Vector__3i32F4 velocity_vector) {
    Game_Action game_action;
    initialize_game_action_as__set_velocity_of__entity(
            &game_action, 
            p_entity, 
            velocity_vector);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__apply_heart_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Healing_Specifier *p_hearts_healing_specifier) {
    Game_Action game_action;
    initialize_game_action_as__apply_heart_healing_to__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            p_hearts_healing_specifier);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__apply_energy_healing_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Healing_Specifier *p_energy_healing_specifier) {
    Game_Action game_action;
    initialize_game_action_as__apply_energy_healing_to__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            p_energy_healing_specifier);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__apply_heart_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Hearts_Damaging_Specifier *p_hearts_damaging_specifier) {
    Game_Action game_action;
    initialize_game_action_as__apply_heart_damage_to__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            p_hearts_damaging_specifier);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__apply_energy_damage_to__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Energy_Damaging_Specifier *p_energy_damaging_specifier) {
    Game_Action game_action;
    initialize_game_action_as__apply_energy_damage_to__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            p_energy_damaging_specifier);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__increase_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    Game_Action game_action;
    initialize_game_action_as__increase_sustenance_of__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            kind_of_sustenance,
            change_in__sustenance);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__decrease_sustenance_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        enum Sustenance_Kind kind_of_sustenance,
        Sustenance__u8 change_in__sustenance) {
    Game_Action game_action;
    initialize_game_action_as__decrease_sustenance_of__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            kind_of_sustenance,
            change_in__sustenance);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__increase_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    Game_Action game_action;
    initialize_game_action_as__increase_homeostasis_of__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            change_in__homeostasis);
    invoke_game_action(
            p_game, &game_action);
}

void invoke_action__decrease_homeostasis_of__entity(
        Game *p_game,
        Entity *p_entity_source,
        Entity *p_entity_target,
        Quantity__u8 change_in__homeostasis) {
    Game_Action game_action;
    initialize_game_action_as__decrease_homeostasis_of__entity(
            &game_action, 
            p_entity_source, 
            p_entity_target, 
            change_in__homeostasis);
    invoke_game_action(
            p_game, &game_action);
}

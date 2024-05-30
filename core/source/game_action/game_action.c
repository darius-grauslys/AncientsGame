#include "defines.h"
#include <game_action/game_action.h>

///
/// Sends a Game_Action which applies velocity.
///
void apply_velocity_to__entity(
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
void set_velocity_of__entity(
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

#include "defines.h"
#include "game_action/game_action.h"
#include "vectors.h"
#include <entity/handlers/ai/ai_handler__dummy.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <entity/humanoid.h>
#include <rendering/animate_humanoid.h>

void m_handler_for__ai_dummy(
        Entity *p_this_dummy,
        Game *p_game) {
    int32_t random__result =
        get_humanoid__direction(p_this_dummy);

    if (p_game->tick__timer_u32.remaining__u32 % 20 == 0) {
        srand(p_game->tick__timer_u32.remaining__u32 + (int32_t)p_this_dummy);
        random__result = rand() & DIRECTION__ANY;
        if ((abs(rand()) % 100) < 60) { random__result = DIRECTION__ANY; }
        srand(p_game->world.world_parameters.seed__current_random);
    }

    switch (random__result) {
        default:
        case DIRECTION__ANY:
            invoke_action__set_velocity_of__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4_with__3i32(0, 0, 0));
            animate_humanoid__idle(p_this_dummy);
            return;
        case DIRECTION__NORTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, 0, 
                        0, ENTITY_VELOCITY__PLAYER, 
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER, 
                        0, 0,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__SOUTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, 0, 
                        0, -ENTITY_VELOCITY__PLAYER, 
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER, 
                        0, 0,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__NORTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__SOUTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__SOUTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
        case DIRECTION__NORTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_dummy);
            break;
    }
    set_humanoid__direction(p_this_dummy, random__result);
}

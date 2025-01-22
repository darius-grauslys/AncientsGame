#include "defines.h"
#include "game_action/game_action.h"
#include "vectors.h"
#include <entity/handlers/ai/ai_handler__dummy.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <entity/humanoid.h>
#include <rendering/animate_humanoid.h>
#include <random.h>

void m_entity_ai_handler__dummy(
        Entity *p_this_dummy,
        Game *p_game) {
    int32_t random__result =
        get_humanoid__direction(p_this_dummy);

    if (p_game->tick__timer_u32.remaining__u32 % 20 == 0) {
        random__result =
            get_psuedo_random__direction_u8__non_intrusively_with__seed(
                    &p_game->world.repeatable_pseudo_random,
                    p_game->tick__timer_u32.remaining__u32
                        + (int32_t)p_this_dummy);
        if ((abs(rand()) % 100) < 60) { random__result = DIRECTION__ANY; }
    }

    switch (random__result) {
        default:
        case DIRECTION__ANY:
            invoke_action__set_velocity_of__entity(
                    p_game,
                    p_this_dummy,
                    get_vector__3i32F4_using__i32(0, 0, 0));
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

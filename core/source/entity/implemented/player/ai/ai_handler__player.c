#include "defines.h"
#include "defines_weak.h"
#include "game_action/game_action.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/implemented/tool.h"
#include "inventory/item_stack.h"
#include "platform.h"
#include "raycast/ray.h"
#include "serialization/serialized_field.h"
#include "timer.h"
#include "vectors.h"
#include "world/chunk_vectors.h"
#include "world/chunk_manager.h"
#include "world/tile_vectors.h"
#include "world/world.h"
#include <entity/implemented/player/ai/ai_handler__player.h>
#include <entity/handlers/ai/ai_handler__dummy.h>
#include <input/input.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <rendering/animate_humanoid.h>
#include <entity/humanoid.h>
#include <game_util.h>

#include <world/chunk_manager.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <game.h>

#include <degree.h>
#include <debug/debug.h>

void m_entity_ai_handler__player(
        Entity *p_this_player,
        Game *p_game) {

    Input *p_input = &p_game->input;
    if (is_input__none_held(p_input)) {
        return;
    }

    switch (get_animation_kind_from__sprite_wrapper(
                get_p_sprite_wrapper_from__entity(p_this_player))) {
        default:
            break;
        case Sprite_Animation_Kind__Humanoid__Die:
        case Sprite_Animation_Kind__Humanoid__Hurt:
        case Sprite_Animation_Kind__Humanoid__Use:
            return;
    }

    Direction__u8 direction__new =
        DIRECTION__NONE;

    if (is_input__forward_held(p_input)) {
        direction__new |= DIRECTION__NORTH;
    }
    if (is_input__right_held(p_input)) {
        direction__new |= DIRECTION__EAST;
    }
    if (is_input__backward_held(p_input)) {
        direction__new |= DIRECTION__SOUTH;
    }
    if (is_input__left_held(p_input)) {
        direction__new |= DIRECTION__WEST;
    }

    if (is_input__consume_released(p_input)) {
        print_log__global(p_game, "Hello World!\n");
    }
    if (is_input__examine_released(p_input)) {
        // TODO: on player_ai loop, we should check if the front tile_vector
        //       is interactable, and if it is, put a (X) sprite above it.
        Tile_Vector__3i32 tile_vector__3i32 =
            get_tile_vector_thats__infront_of_this__entity(
                    p_this_player);

        poll_tile_for__interaction(
                p_game, 
                p_this_player,
                tile_vector__3i32);
    } 
    if (is_input__use_secondary_released(p_input)) {
        // TODO:    this will become running?
        //          I think there will be no running
        //          there will just be mounts, and B will
        //          become use secondary
    } 
    if (is_input__use_released(p_input)) {
        humanoid__use(
                p_game,
                p_this_player);
        return;
    }
    if (is_input__lockon_released(p_input)) {
        Item *p_item =
            &p_this_player
            ->equipment
            .item_stack__main_hand.item;
        if (is_item_tool_mode__combat(
                    p_item)) {
            set_item_tool_mode(
                    p_item, Tool_Mode__Labor);
        } else {
            humanoid__tool_mode(
                    p_game, 
                    p_this_player);
        }
    }

    switch (direction__new) {
        default:
            // animate_humanoid__idle(p_this_player);
            return;
        case DIRECTION__NORTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, 0,
                        0, ENTITY_VELOCITY__PLAYER,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER,
                        0, 0,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, 0,
                        0, -ENTITY_VELOCITY__PLAYER,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER,
                        0, 0,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__NORTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__NORTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0, -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0, 0));
            animate_humanoid__walk(p_this_player);
            break;
    }
    play_audio_of__entity_footstep(
            p_game, 
            p_this_player);
    set_humanoid__direction(p_this_player, direction__new);
}

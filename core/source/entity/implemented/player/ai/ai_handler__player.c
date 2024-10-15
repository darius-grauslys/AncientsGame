#include "defines.h"
#include "defines_weak.h"
#include "game_action/game_action.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
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
        for (i32 y=-3;y<4;y++) {
            for (i32 x=-3;x<4;x++) {
                Vector__3i32F4 player_vector__3i32F4 =
                    p_this_player
                    ->hitbox.position__3i32F4;
                player_vector__3i32F4.x__i32F4 += i32_to__i32F4(x << 3);
                player_vector__3i32F4.y__i32F4 += i32_to__i32F4(y << 3);

                Tile *p_tile =
                    get_p_tile_from__chunk_manager_with__3i32F4(
                            get_p_chunk_manager_from__game(p_game), 
                            player_vector__3i32F4);

                if (!p_tile) {
                    continue;
                }
                Tile_Vector__3i32 tv =
                        vector_3i32F4_to__tile_vector(
                            player_vector__3i32F4);
                if (is_tile__container(p_tile)) {
                    Identifier__u32 uuid_of__container =
                        get_uuid_for__container(tv);

                    Serialized_Field s_inventory__container;
                    initialize_serialized_field_as__unlinked(
                            &s_inventory__container, 
                            uuid_of__container);

                    if (!resolve_s_inventory_ptr_to__inventory_manager(
                            get_p_inventory_manager_from__game(p_game),
                            &s_inventory__container)) {
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Wall__Gold;
                        PLATFORM_update_chunks(
                                get_p_PLATFORM_gfx_context_from__game(p_game), 
                                get_p_chunk_manager_from__game(p_game));
                        continue;
                    }

                    for (Index__u8 index_of__item_stack = 0;
                            index_of__item_stack < 4;
                            index_of__item_stack++) {
                        Item_Stack *p_item_stack =
                            get_p_item_stack_from__inventory_by__index(
                                s_inventory__container.p_serialized_field__inventory, 
                                index_of__item_stack);
                        debug_info("item: %d",
                                p_item_stack->item.the_kind_of_item__this_item_is);
                    }

                    p_this_player
                        ->s_humanoid__container_ptr =
                        s_inventory__container;

                    PLATFORM_open_ui(
                            p_game,
                            UI_Window_Kind__Trade);
                }
            }
        }
    } 
    if (is_input__use_secondary_released(p_input)) {
    } 
    if (is_input__use_released(p_input)) {
        if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__game(p_game),
                &p_this_player
                ->s_humanoid__inventory_ptr)) {
            return;
        }

        for (i32 y=-3;y<4;y++) {
            for (i32 x=-3;x<4;x++) {
                Vector__3i32F4 player_vector__3i32F4 =
                    p_this_player
                    ->hitbox.position__3i32F4;
                player_vector__3i32F4.x__i32F4 += i32_to__i32F4(x << 3);
                player_vector__3i32F4.y__i32F4 += i32_to__i32F4(y << 3);

                Tile *p_tile =
                    get_p_tile_from__chunk_manager_with__3i32F4(
                            get_p_chunk_manager_from__game(p_game), 
                            player_vector__3i32F4);

                if (!p_tile) {
                    continue;
                }
                Tile_Vector__3i32 tv =
                        vector_3i32F4_to__tile_vector(
                            player_vector__3i32F4);
                if (is_tile__container(p_tile)) {
                    Identifier__u32 uuid_of__container =
                        get_uuid_for__container(tv);

                    Serialized_Field s_inventory__container;
                    initialize_serialized_field_as__unlinked(
                            &s_inventory__container, 
                            uuid_of__container);

                    if (!resolve_s_inventory_ptr_to__inventory_manager(
                            get_p_inventory_manager_from__game(p_game),
                            &s_inventory__container)) {
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Wall__Gold;
                        PLATFORM_update_chunks(
                                get_p_PLATFORM_gfx_context_from__game(p_game), 
                                get_p_chunk_manager_from__game(p_game));
                        continue;
                    }

                    Item_Stack *p_item_stack =
                        get_p_item_stack_from__inventory_by__index(
                            s_inventory__container.p_serialized_field__inventory, 
                            0);
                    Item_Stack *p_item_stack__player =
                        get_p_item_stack_from__inventory_by__index(
                            p_this_player
                            ->s_humanoid__inventory_ptr
                            .p_serialized_field__inventory, 
                            0);
                    debug_info("swapping: %d",
                            p_item_stack->item.the_kind_of_item__this_item_is);
                    resolve_item_stack__merge_or_swap(
                            p_item_stack, 
                            p_item_stack__player);

                    p_this_player
                        ->s_humanoid__container_ptr =
                        s_inventory__container;

                    PLATFORM_open_ui(
                            p_game,
                            UI_Window_Kind__Trade);
                }
            }
        }

        humanoid__use(
                p_game,
                p_this_player);
        return;
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

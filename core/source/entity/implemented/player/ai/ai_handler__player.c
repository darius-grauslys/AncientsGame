#include "defines.h"
#include "defines_weak.h"
#include "game_action/game_action.h"
#include "raycast/ray.h"
#include "vectors.h"
#include "world/chunk_vectors.h"
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

enum Use_Mode {
    Use_Mode__Place_Wall,
    Use_Mode__Place_Ground,
    Use_Mode__Remove_Wall
};

enum Tile_Kind kind_of_tile =
    Tile_Kind__Oak_Wood;
enum Use_Mode mode_of_use =
    Use_Mode__Place_Wall;

void m_entity_ai_handler__player(
        Entity *p_this_player,
        Game *p_game) {

    Input *p_input = &p_game->input;
    if (is_input__none_held(p_input)) {
        return;
    }

    Direction__u8 direction__old =
        get_humanoid__direction(p_this_player);
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

    int32_t x = 
        get_x_i32_from__entity(p_this_player);
    int32_t y = 
        get_y_i32_from__entity(p_this_player);
    if (direction__old & DIRECTION__NORTH) {
        y += 32;
    }
    if (direction__old & DIRECTION__SOUTH) {
        y -= 32;
    }
    if (direction__old & DIRECTION__EAST) {
        x += 32;
    }
    if (direction__old & DIRECTION__WEST) {
        x -= 32;
    }

    if (is_input__game_settings_released(p_input)) {
        invoke_action__allocate_entity(
                p_game,
                Entity_Kind__Skeleton,
                get_vector__3i32F4_using__i32(x, y, 0));
    } 
    if (is_input__examine_released(p_input)) {
        mode_of_use++;
        switch(mode_of_use) {
            default:
                mode_of_use = Use_Mode__Place_Wall;
            case Use_Mode__Place_Wall:
                debug_info("Use_Mode__Place_Wall");
                break;
            case Use_Mode__Place_Ground:
                debug_info("Use_Mode__Place_Ground");
                break;
            case Use_Mode__Remove_Wall:
                debug_info("Use_Mode__Remove_Wall");
                break;
        }
    } 
    if (is_input__use_secondary_released(p_input)) {
        kind_of_tile++;
        switch(kind_of_tile) {
            default:
                kind_of_tile = Tile_Kind__Oak_Wood;
            case Tile_Kind__Oak_Wood:
                debug_info("Tile_Kind__Oak_Wood");
                break;
            case Tile_Kind__Stone_Brick:
                debug_info("Tile_Kind__Stone_Brick");
                break;
            case Tile_Kind__Gold:
                debug_info("Tile_Kind__Gold");
                break;
            case Tile_Kind__Iron:
                debug_info("Tile_Kind__Iron");
                break;
            case Tile_Kind__Diamond:
                debug_info("Tile_Kind__Diamond");
                break;
            case Tile_Kind__Amethyst:
                debug_info("Tile_Kind__Amethyst");
                break;
            case Tile_Kind__Sandstone:
                debug_info("Tile_Kind__Sandstone");
                break;
            case Tile_Kind__Stone:
                debug_info("Tile_Kind__Stone");
                break;
            case Tile_Kind__Dirt:
                debug_info("Tile_Kind__Dirt");
                break;
            case Tile_Kind__Sand:
                debug_info("Tile_Kind__Sand");
                break;
        }
    } 
    if (is_input__use_released(p_input)) {
        Vector__3i32F4 origin = get_vector__3i32F4_using__i32(0, 0, 0);
        Degree__u8 angle_of__ray =
            get_angle_between__vectors_3i32F4(
                    &p_this_player->hitbox.position__3i32F4, 
                    &origin);
        Ray__3i32F8 ray = get_ray(
                p_this_player->hitbox.position__3i32F4, 
                angle_of__ray); 

        while (is_p_ray_within__length_i32F4(
                    &ray, i32_to__i32F4(1 << 3))) {
            step_p_ray_until__next_tile(&ray);
        }
        debug_info("angle_of__ray: %d/255", angle_of__ray);
        while (is_p_ray_within__length_i32F4(
                    &ray, i32_to__i32F4(8 << 3))) {
            step_p_ray_until__next_tile(&ray);
            Vector__3i32F4 tile_pos = 
                vector_3i32F8_to__vector_3i32F4(
                        ray.ray_current_vector__3i32F8);
            Chunk *p_chunk =
                get_p_chunk_from__chunk_manager_using__i32(
                        &p_game->world.chunk_manager,
                        get_chunk_x_i32_from__vector_3i32F4(tile_pos),
                        get_chunk_y_i32_from__vector_3i32F4(tile_pos),
                        0);

            if (p_chunk) {
                Tile *p_tile =
                    //TODO: consolidate these bit manips
                    get_p_tile_from__chunk_using__u8(
                            p_chunk,
                            get_tile_x_u8_from__vector_3i32F4(tile_pos),
                            get_tile_y_u8_from__vector_3i32F4(tile_pos),
                            0);
                switch(mode_of_use) {
                    default:
                    case Use_Mode__Place_Wall:
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            get_tile_cover_wall_for__tile_kind(kind_of_tile);
                        set_tile__is_unpassable(p_tile, true);
                        break;
                    case Use_Mode__Place_Ground:
                        p_tile->the_kind_of_tile__this_tile_is =
                            kind_of_tile;
                        break;
                    case Use_Mode__Remove_Wall:
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__None;
                        set_tile__is_unpassable(p_tile, false);
                        break;
                }
            }

        }

        PLATFORM_update_chunks(
                get_p_PLATFORM_gfx_context_from__game(p_game),
                get_p_chunk_manager_from__game(p_game));

        animate_humanoid__use(p_this_player);
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
    set_humanoid__direction(p_this_player, direction__new);
}

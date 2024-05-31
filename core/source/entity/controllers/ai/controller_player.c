#include "defines.h"
#include "game_action/game_action.h"
#include "world/world.h"
#include <entity/controllers/ai/controller_player.h>
#include <input/input.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <entity/controllers/ai/controller_dummy.h>
#include <rendering/animate_humanoid.h>
#include <entity/humanoid.h>

#include <world/chunk_manager.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <game.h>

enum Use_Mode {
    Use_Mode__Place_Wall,
    Use_Mode__Place_Ground,
    Use_Mode__Remove_Wall
};

bool toggle = false;
enum Tile_Kind kind_of_tile =
    Tile_Kind__Oak_Wood;
enum Use_Mode mode_of_use =
    Use_Mode__Place_Wall;

void m_handler_for__ai_player(
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

    int32_t 
        x = get_global_x_from__hitbox(&p_this_player->hitbox), 
          y = get_global_y_from__hitbox(&p_this_player->hitbox);
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

    goto set_direction;
    if (is_input__game_settings_held(p_input) && !toggle) {
        toggle = true;
        Entity *p_skeleton = add_entity_to__world(
                &p_game->world,
                Entity_Kind__Skeleton,
                get_vector__3i32F4(x, y, 0));

        set_entity__ai_handler(
                p_skeleton, 
                m_handler_for__ai_dummy);
    } else if (is_input__examine_held(p_input) && !toggle) {
        toggle = true;
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
    } else if (is_input__use_secondary_held(p_input) && !toggle) {
        toggle = true;
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
    } else if (is_input__use_held(p_input) && !toggle) {
        toggle = true;

        Chunk *p_chunk =
            get_chunk_ptr_from__chunk_manager(
                    &p_game->world.chunk_manager,
                    x >> 6,
                    y >> 6,
                    0);

        if (p_chunk) {
            Tile *p_tile =
                //TODO: consolidate these bit manips
                get_tile_ptr_from__chunk(
                        p_chunk,
                        (x >> 3) & ((1 << 3) - 1),
                        (y >> 3) & ((1 << 3) - 1),
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

            PLATFORM_update_chunks(
                    &p_game->gfx_context,
                    &p_game->world.chunk_manager);
        }

        animate_humanoid__use(p_this_player);
        return;
    } else if (!is_input__game_settings_held(p_input)
            && !is_input__use_held(p_input)
            && !is_input__use_secondary_held(p_input)
            && !is_input__examine_held(p_input)) {
        toggle = false;
    }

set_direction:
    switch (direction__new) {
        default:
            // animate_humanoid__idle(p_this_player);
            return;
        case DIRECTION__NORTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0,
                        ENTITY_VELOCITY__PLAYER,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        ENTITY_VELOCITY__PLAYER,
                        0,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        0,
                        -ENTITY_VELOCITY__PLAYER,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        -ENTITY_VELOCITY__PLAYER,
                        0,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__NORTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH_EAST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__SOUTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
        case DIRECTION__NORTH_WEST:
            invoke_action__apply_velocity_to__entity(
                    p_game,
                    p_this_player,
                    get_vector__3i32F4(
                        -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        ENTITY_VELOCITY__PLAYER_DIAGONAL,
                        0));
            animate_humanoid__walk(p_this_player);
            break;
    }
    set_humanoid__direction(p_this_player, direction__new);
}

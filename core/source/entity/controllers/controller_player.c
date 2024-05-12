#include <entity/controllers/controller_player.h>
#include <input/input.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <entity/controllers/controller_dummy.h>
#include <entity/controllers/humanoid_animation_handler.h>

#include <world/chunk.h>
#include <world/tile.h>

bool toggle = false;

void m_controller_for__player(
        Entity *this_player,
        Game *game) {

    if (is_input__none(game)) {
        return;
    }

    Direction direction__new =
        DIRECTION__NONE;

    if (is_input__forward(game)) {
        direction__new |= DIRECTION__NORTH;
    }
    if (is_input__right(game)) {
        direction__new |= DIRECTION__EAST;
    }
    if (is_input__backwards(game)) {
        direction__new |= DIRECTION__SOUTH;
    }
    if (is_input__left(game)) {
        direction__new |= DIRECTION__WEST;
    }

    int32_t 
        x = get_global_x_from__hitbox(&this_player->hitbox), 
          y = get_global_y_from__hitbox(&this_player->hitbox);
    if (get_entity__direction(this_player) & DIRECTION__NORTH) {
        y += 32;
    }
    if (get_entity__direction(this_player) & DIRECTION__SOUTH) {
        y -= 32;
    }
    if (get_entity__direction(this_player) & DIRECTION__EAST) {
        x += 32;
    }
    if (get_entity__direction(this_player) & DIRECTION__WEST) {
        x -= 32;
    }

    if (is_input__game_settings(game) && !toggle) {
        toggle = true;
        Entity *skeleton = get_new__entity(
                game,
                Entity_Kind__Skeleton,
                x, y, 0);

        set_entity__controller(
                skeleton, 
                m_controller_for__dummy);
    } else if (is_input__use(game) && !toggle) {
        toggle = true;

        Chunk *chunk =
            get_chunk_from__chunk_manager(
                    &game->world.chunk_manager,
                    x >> 6,
                    y >> 6,
                    0);

        debug_info("chunk place: %d, %d",
                    x >> 6,
                    y >> 6);
        debug_info("place: %d, %d",
                    (x >> 3) & ((1 << 3) - 1),
                    (y >> 3) & ((1 << 3) - 1));
        if (chunk) {
            Tile *tile =
                get_tile_from__chunk(
                        chunk,
                        (x >> 3) & ((1 << 3) - 1),
                        (y >> 3) & ((1 << 3) - 1),
                        0);
            tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Plant;
            tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Dirt
                ;
            set_tile__is_unpassable(tile, true);

            PLATFORM_update_chunks(
                    &game->gfx_context,
                    &game->world.chunk_manager);
        }

    } else if (!is_input__game_settings(game)
            && !is_input__use(game)) {
        toggle = false;
    }

    switch (direction__new) {
        default:
            return;
        case DIRECTION__NORTH:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    0, 
                    ENTITY_VELOCITY__PLAYER,
                    0);
            animate_humanoid__walk(this_player);
            break;
        case DIRECTION__EAST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    ENTITY_VELOCITY__PLAYER,
                    0, 0);
            break;
        case DIRECTION__SOUTH:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    0,
                    -ENTITY_VELOCITY__PLAYER,
                    0);
            animate_humanoid__walk(this_player);
            break;
        case DIRECTION__WEST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    -ENTITY_VELOCITY__PLAYER,
                    0, 0);
            break;
        case DIRECTION__NORTH_EAST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL, 
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    0);
            animate_humanoid__walk(this_player);
            break;
        case DIRECTION__SOUTH_EAST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    0);
            animate_humanoid__walk(this_player);
            break;
        case DIRECTION__SOUTH_WEST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    0);
            animate_humanoid__walk(this_player);
            break;
        case DIRECTION__NORTH_WEST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    0);
            animate_humanoid__walk(this_player);
            break;
    }
    set_entity__direction(this_player, direction__new);
}

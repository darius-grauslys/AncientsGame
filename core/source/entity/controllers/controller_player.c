#include <entity/controllers/controller_player.h>
#include <input/input.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>

void m_controller_for__player(
        Entity *this_player,
        Game *game) {

    if (is_input__none(game)) {
        return;
    }

    bool is_player__moving =
        is_entity__moving(this_player);

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

    switch (direction__new) {
        default:
            if (is_player__moving)
                set_entity_as__moving(
                        this_player,
                        false,
                        Sprite_Animation_Kind__Idle);
            return;
        case DIRECTION__NORTH:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    0, 
                    ENTITY_VELOCITY__PLAYER,
                    0);
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
            break;
        case DIRECTION__SOUTH_EAST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    0);
            break;
        case DIRECTION__SOUTH_WEST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    0);
            break;
        case DIRECTION__NORTH_WEST:
            apply_velocity_to__hitbox(
                    &this_player->hitbox,
                    -(ENTITY_VELOCITY__PLAYER_DIAGONAL),
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    0);
            break;
    }
    set_entity__direction(this_player, direction__new);
    if (!is_player__moving)
        set_entity_as__moving(
                this_player,
                true,
                Sprite_Animation_Kind__Idle);
}

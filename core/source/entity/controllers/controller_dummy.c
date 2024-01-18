#include <entity/controllers/controller_dummy.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>

void m_controller_for__dummy(
        Entity *this_dummy,
        Game *game) {

    int32_t random__result =
        get_entity__direction(this_dummy);

    bool is_dummy__moving =
        is_entity__moving(this_dummy);

    if (game->tick % 50 == 0) {
        srand(game->tick + (int32_t)this_dummy);
        random__result = rand() & DIRECTION__ANY;
        srand(game->world.world_params.seed__current_random);
    }

    switch (random__result) {
        default:
            set_entity_as__moving(
                    this_dummy,
                    false,
                    Sprite_Animation_Kind__Idle);
            return;
        case DIRECTION__NORTH:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    0, ENTITY_VELOCITY__PLAYER,
                    0);
            break;
        case DIRECTION__EAST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER,
                    0, 0);
            break;
        case DIRECTION__SOUTH:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    0, -ENTITY_VELOCITY__PLAYER,
                    0);
            break;
        case DIRECTION__WEST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER,
                    0, 0);
            break;
        case DIRECTION__NORTH_EAST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL, 0);
            break;
        case DIRECTION__SOUTH_EAST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL, 0);
            break;
        case DIRECTION__SOUTH_WEST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL, 0);
            break;
        case DIRECTION__NORTH_WEST:
            apply_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL, 0);
            break;
    }
    set_entity__direction(this_dummy, random__result);
    if (!is_dummy__moving)
        set_entity_as__moving(
                this_dummy,
                true,
                Sprite_Animation_Kind__Idle);
}

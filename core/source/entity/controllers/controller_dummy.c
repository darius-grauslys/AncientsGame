#include <entity/controllers/controller_dummy.h>
#include <entity/entity.h>
#include <collisions/hitbox_aabb.h>
#include <entity/humanoid.h>
#include <rendering/animate_humanoid.h>

void m_controller_for__dummy(
        Entity *this_dummy,
        Game *game) {
    int32_t random__result =
        get_humanoid__direction(this_dummy);

    if (game->tick__timer_u32 % 20 == 0) {
        srand(game->tick__timer_u32 + (int32_t)this_dummy);
        random__result = rand() & DIRECTION__ANY;
        if ((abs(rand()) % 100) < 60) { random__result = DIRECTION__ANY; }
        srand(game->world.world_parameters.seed__current_random);
    }

    switch (random__result) {
        default:
        case DIRECTION__ANY:
            set_x_velocity_to__hitbox(&this_dummy->hitbox, 0);
            set_y_velocity_to__hitbox(&this_dummy->hitbox, 0);
            set_z_velocity_to__hitbox(&this_dummy->hitbox, 0);
            animate_humanoid__idle(this_dummy);
            return;
        case DIRECTION__NORTH:
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__EAST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__SOUTH:
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__WEST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__NORTH_EAST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL);
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__SOUTH_EAST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL);
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__SOUTH_WEST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL);
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL);
            animate_humanoid__walk(this_dummy);
            break;
        case DIRECTION__NORTH_WEST:
            apply_x_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    -ENTITY_VELOCITY__PLAYER_DIAGONAL);
            apply_y_velocity_to__hitbox(
                    &this_dummy->hitbox,
                    ENTITY_VELOCITY__PLAYER_DIAGONAL);
            animate_humanoid__walk(this_dummy);
            break;
    }
    set_humanoid__direction(this_dummy, random__result);
}

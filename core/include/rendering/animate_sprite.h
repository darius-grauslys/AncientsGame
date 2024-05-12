#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include <defines.h>

static uint32_t inline get_sprite_frame (
        uint32_t col, uint32_t row,
        uint32_t cols_per_row) {
    return
        col
        + (row * cols_per_row);
}

static uint32_t inline get_animation_frame_offset_for__direction(
        Direction direction,
        uint32_t cols_per_row) {
    switch (direction) {
        default:
        case DIRECTION__EAST:
        case DIRECTION__WEST:
            return get_sprite_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING,
                    cols_per_row);
        case DIRECTION__SOUTH:
            return get_sprite_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING,
                    cols_per_row);
        case DIRECTION__NORTH:
            return get_sprite_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING,
                    cols_per_row);
    }
}

///
/// Updates the sprite_wrapper.frame value.
///
void animate_sprite__humanoid(Entity *entity);

uint32_t get_start_frame__of_animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

void set_sprite__animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

///
/// Performs the necessary graphical changes needed
/// to reflect the entity's sprite_wrapper.frame value.
///
void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper);

#endif

#include <rendering/animate_sprite.h>
#include <entity/entity.h>
#include <debug/debug.h>

uint32_t get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row) {
    switch (direction) {
        default:
        case DIRECTION__EAST:
        case DIRECTION__WEST:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING,
                    cols_per_row);
        case DIRECTION__SOUTH:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING,
                    cols_per_row);
        case DIRECTION__NORTH:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING,
                    cols_per_row);
    }
}

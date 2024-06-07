#ifndef COLLIDABLE_ENTITY_HANDERS_H
#define COLLIDABLE_ENTITY_HANDERS_H

#include <defines.h>

void m_entity_collision_handler__default(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction__u8 direction_of_collision);

void m_entity_tile_collision_handler__default(
        Entity *entity_collision_source,
        Tile *tile_collided,
        Signed_Index__i32 x_collision__i32,
        Signed_Index__i32 y_collision__i32,
        Direction__u8 direction_of__tile_collision);

#endif

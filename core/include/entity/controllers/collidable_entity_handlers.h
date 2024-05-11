#ifndef COLLIDABLE_ENTITY_HANDERS_H
#define COLLIDABLE_ENTITY_HANDERS_H

#include <defines.h>

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction direction_of_collision);

void m_entity_tile_collision_handler(
        Entity *entity_collision_source,
        Tile *tile_collided);

#endif

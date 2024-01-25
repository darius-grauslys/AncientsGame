#ifndef COLLIDABLE_ENTITY_HANDERS_H
#define COLLIDABLE_ENTITY_HANDERS_H

#include <defines.h>

void m_entity_chunk_transition_handler(
        Entity *this_entity,
        Game *game,
        int32_t old_x__chunk,
        int32_t old_y__chunk);

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction direction_of_collision);

#endif

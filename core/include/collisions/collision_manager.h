#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

///
/// We take Game as an argument here since the
/// Collision_Manager wants to interact with
/// both the Entity_Manager, as well as the
/// Chunk_Manager.
///
void poll_collision_mannager(
        Game *game,
        Entity *entity,
        f_entity_collision collision_handler);

#endif

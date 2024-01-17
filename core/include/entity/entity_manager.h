#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <defines.h>

///
/// Return nullptr (0) if fails to get new entity.
///
Entity *get_new_player(Entity_Manager* manager);
Entity *get_new_entity(Entity_Manager* manager,
        enum Entity_Kind kind_of_entity);
void release_entity__silently(Entity_Manager* manager, Entity* entity);

#endif

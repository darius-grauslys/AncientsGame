#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <defines.h>

void init_entity_manager(Entity_Manager *entity_manager);

///
/// Return nullptr (0) if fails to get new entity.
///
Entity *get_new__player(Entity_Manager* manager,
        bool is_local_player);
Entity *get_new__entity(Entity_Manager* manager,
        enum Entity_Kind kind_of_entity);
void release_entity__silently(Entity_Manager* manager, Entity* entity);

#endif

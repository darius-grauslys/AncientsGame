#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <defines.h>

typedef struct Entity_Manager_t {

} Entity_Manager;

///
/// Return nullptr (0) if fails to get new entity.
///
Entity *get_new_entity(Entity_Manger* manager);
void release_entity(Entity_Manager* manager, Entity* entity);

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include <defines.h>

///
/// Here we define the entity super struct. It has everything we could need
/// for an entity, even if some of the things are not used.
///

typedef struct Entity_t {
    m_init_entity       init_handler;
    m_update_entity     update_handler;
    m_render_entity     render_handler;
    m_dispose_entity    dispose_handler;
} Entity;

#endif

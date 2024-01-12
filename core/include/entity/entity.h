#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <defines.h>

///
/// Here we define the entity super struct. It has everything we could need
/// for an entity, even if some of the things are not used.
///

typedef struct Entity_t {
    Sprite_Wrapper          sprite_wrapper;
    m_init_entity           init_handler;
    m_update_entity         update_handler;
    m_render_entity         render_handler;
    m_dispose_entity        dispose_handler;
    enum Entity_Kind        the_kind_of_entity__this_entity_is;
    union {
        Armor_Properties    armor_properties;
    };
} Entity;

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity);

void init_entity(Entity *entity, enum Entity_Kind kind_of_entity);

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification);

#endif

#include "defines_weak.h"
#include <entity/humanoid.h>
#include <entity/entity.h>
#include <inventory/inventory.h>

void initialize_entity_as__humanoid(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height) {
    initialize_entity(
            p_entity, 
            kind_of_entity, 
            position__3i32F4, 
            width, 
            height);
#warning TODO: impl armor init and homeo
}

bool is_entity_a__humanoid(Entity *entity) {
    switch (entity->the_kind_of_entity__this_entity_is) {
        default:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            return true;
    }
}

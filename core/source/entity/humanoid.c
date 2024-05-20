#include <entity/humanoid.h>

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

#include <entity/entity.h>
#include <rendering/render_entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>

void animate_entity(Entity *entity) {
    switch (entity->the_kind_of_entity__this_entity_is) {
        default:
            debug_error("Missing animation implementation for given entity kind.");
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            uint32_t frame = entity->sprite_wrapper.frame;
            animate_sprite__humanoid(entity);
            break;
    }
}

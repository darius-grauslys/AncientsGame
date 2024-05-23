#ifndef HUMANOID_H
#define HUMANOID_H

#include <defines.h>

bool is_entity_a__humanoid(Entity *entity);
    
static void inline set_humanoid__direction(
        Entity *humanoid,
        Direction__u8 direction) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return;
    }
#endif
    humanoid->direction = direction;
}

static Direction__u8 inline get_humanoid__direction(
        Entity *humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return DIRECTION__NONE;
    }
#endif
    return humanoid->direction;
}

#endif

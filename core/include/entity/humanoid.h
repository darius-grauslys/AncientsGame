#ifndef HUMANOID_H
#define HUMANOID_H

#include <defines.h>

bool is_entity_a__humanoid(Entity *entity);
    
//TODO: this should be an entity thing
//      not a humanoid thing.
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

static bool inline is_humanoid__undead(
        Entity *humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return false;
    }
#endif
    return (bool)(humanoid->humanoid_flags 
            & HUMANOID_FLAG__IS_UNDEAD);
}

static bool inline does_humanoid_have__divine_providence(
        Entity *p_humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(p_humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                p_humanoid);
        return false;
    }
#endif
    return (bool)(p_humanoid->humanoid_flags 
            & HUMANOID_FLAG__HAS_DIVINE_PROVIDENCE);
}

#endif

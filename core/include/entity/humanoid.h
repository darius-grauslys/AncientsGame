#ifndef HUMANOID_H
#define HUMANOID_H

#include "defines_weak.h"
#include "entity/entity.h"
#include "rendering/animate_sprite.h"
#include <defines.h>

void initialize_entity_as__humanoid(
        Game *p_game,
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height);

void humanoid__use(
        Game *p_game,
        Entity *p_humanoid);

void humanoid__tool_mode(
        Game *p_game,
        Entity *p_humanoid);

bool is_entity_a__humanoid(Entity *entity);

bool is_humanoid__dead(Entity *p_humanoid);

/// 
/// WARNING: this is never guaranteed to resolve.
/// Always check for a returned nullptr.
///
Inventory *resolve_p_inventory_of__humanoid(
        Game *p_game,
        Entity *p_humanoid);
    
//TODO: this should be an entity thing
//      not a humanoid thing.
static void inline set_humanoid__direction(
        Entity *p_humanoid,
        Direction__u8 direction) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(p_humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                p_humanoid);
        return;
    }
#endif
    p_humanoid->direction = direction;
    set_animation__direction(
            get_p_sprite_wrapper_from__entity(p_humanoid), 
            direction);
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

void humanoid__add_item_to__inventory(
        Game *p_game,
        Entity *p_entity,
        Item item,
        Quantity__u32 quantity_of__items,
        Quantity__u32 max_quantity_of__items);

void humanoid__remove_quantity_of__item_kinds_from__inventory(
        Game *p_game,
        Entity *p_entity,
        Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items);

/// 
/// First removes items from offhand then inventory.
///
void humanoid__remove_quantity_of__item_kinds_from__posessions(
        Game *p_game,
        Entity *p_entity,
        Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items);

#endif

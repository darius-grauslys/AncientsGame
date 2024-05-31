#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>
#include <rendering/animate_entity.h>
#include <collisions/hitbox_aabb.h>

#include <debug/debug.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity_kind_have__armor.");
            return false;
        case Entity_Kind__Zombie:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool can_entity__move(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity__move.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool is_entity__humanoid(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    is_entity__humanoid.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

void init_entity(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity) {
    p_entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    p_entity->hitbox.chunk_index__3i32.x__i32 =
        p_entity->hitbox.position__3i32F4.x__i32F4 = 0;
    p_entity->hitbox.chunk_index__3i32.y__i32 =
        p_entity->hitbox.position__3i32F4.y__i32F4 = 0;
    p_entity->hitbox.chunk_index__3i32.z__i32 =
        p_entity->hitbox.position__3i32F4.z__i32F4 = 0;

    p_entity->m_dispose_handler = 0;
    p_entity->m_controller_handler = 0;
    p_entity->m_collision_handler = 0;
    p_entity->m_tile_collision_handler = 0;

    set_entity__enabled(p_entity);
    set_entity__is_updating_position(p_entity);
    set_entity__is_updating_graphics(p_entity);

    init_sprite_wrapper_for__entity(
            p_entity);
}

void set_entity__armor(Entity *p_entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    p_entity->armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    p_entity->armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
}

bool commit_entity_velocity(
        Entity *p_entity,
        int32_t *old_x__chunk,
        int32_t *old_y__chunk) {
    *old_x__chunk = p_entity->hitbox.chunk_index__3i32.x__i32;
    *old_y__chunk = p_entity->hitbox.chunk_index__3i32.y__i32;

    commit_hitbox_velocity(&p_entity->hitbox);

    if (*old_x__chunk != p_entity->hitbox.chunk_index__3i32.x__i32 
            || *old_y__chunk
            != p_entity->hitbox.chunk_index__3i32.y__i32) {
        return true;
    }
    return false;
}

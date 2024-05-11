#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <defines.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity);
bool can_entity__move(enum Entity_Kind kind_of_entity);

bool is_entity__humanoid(enum Entity_Kind kind_of_entity);

static bool inline is_entity__enabled(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_ENABLED;
}
static bool inline is_entity_not__updating_position(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_NOT_UPDATING_POSITION;
}
static bool inline is_entity_not__updating_graphics(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_NOT_UPDATING_GRAPHICS;
}
static bool inline is_entity__collidable(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_COLLIDING;
}
static bool inline is_entity__unloaded(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_UNLOADED;
}
static bool inline is_entity__hidden(Entity *entity) {
    return entity->entity_flags &
        ENTITY_FLAG__IS_HIDDEN;
}

static void inline set_entity__enabled(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_ENABLED;
}
static void inline set_entity__is_updating_position(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_NOT_UPDATING_POSITION;
}
static void inline set_entity__is_updating_graphics(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_NOT_UPDATING_GRAPHICS;
}
static void inline set_entity__collidable(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_COLLIDING;
}
static void inline set_entity_as__loaded(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_UNLOADED;
}
static void inline set_entity_as__hidden(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_HIDDEN;
}

static void inline set_entity__disabled(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_ENABLED;
}
static void inline set_entity__is_not_updating_position(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_NOT_UPDATING_POSITION;
}
static void inline set_entity__is_not_updating_graphics(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_NOT_UPDATING_GRAPHICS;
}
static void inline set_entity__uncollidable(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_COLLIDING;
}
static void inline set_entity_as__unloaded(Entity *entity) {
    entity->entity_flags |= ENTITY_FLAG__IS_UNLOADED;
}
static void inline set_entity_as__visible(Entity *entity) {
    entity->entity_flags &= ~ENTITY_FLAG__IS_HIDDEN;
}

static void inline set_entity__controller(
        Entity *entity,
        m_entity_controller controller) {
    entity->controller_handler = controller;
    if (!controller) {
        set_entity__collidable(entity);
    } else {
        set_entity__uncollidable(entity);
    }
}

static void inline set_entity__disposer(
        Entity *entity,
        m_dispose_entity disposer) {
    entity->dispose_handler = disposer;
}

static void inline set_entity__collider(
        Entity *entity,
        m_entity_collision collision_handler) {
    entity->collision_handler = collision_handler;
}

static void inline set_entity__tile_collider(
        Entity *entity,
        m_entity_tile_collision collision_handler) {
    entity->tile_collision_handler = collision_handler;
}

void init_entity(Entity *entity, enum Entity_Kind kind_of_entity);

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification);

void set_entity__direction(Entity *entity,
        Direction direction);

Direction get_entity__direction(Entity *entity);

bool is_entity__moving(Entity *entity);

void set_entity_as__moving(Entity *entity, 
        bool state_of_movement,
        enum Sprite_Animation_Kind fallback_animation);

/// 
/// DO NOT CALL THIS!
/// TODO: make internal headers.
///
/// This will commit hitbox velocity
/// and return true if a chunk transition
/// has occured.
///
bool commit_entity_velocity(
        Entity *entity,
        int32_t *old_x__chunk,
        int32_t *old_y__chunk);

#endif

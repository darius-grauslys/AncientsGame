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

static void inline set_entity__chunk_transitioner(
        Entity *entity,
        m_entity_chunk_transitioner chunk_transitioner) {
    entity->chunk_transition_handler = chunk_transitioner;
}

static void inline set_entity__collider(
        Entity *entity,
        m_entity_collision collision_handler) {
    entity->collision_handler = collision_handler;
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
/// Apply a velocity, and if the entity
/// undergoes a chunk transition, reflect
/// that in it's chunk_transition callback method.
///
void apply_velocity_to__entity(
        Game *game,
        Entity *entity,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity);

#endif

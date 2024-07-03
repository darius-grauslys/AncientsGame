#ifndef ENTITY_H
#define ENTITY_H

#include "collisions/hitbox_aabb.h"
#include "defines_weak.h"
#include "vectors.h"
#include <stdbool.h>
#include <defines.h>

static inline
Vector__3i32 get_vector_3i32_from__entity(
        Entity *p_entity) {
    return vector_3i32F4_to__vector_3i32(p_entity->hitbox.position__3i32F4);
}

static i32F4 inline get_x_i32F4_from__entity(
        Entity *p_entity) {
    return get_x_i32F4_from__hitbox(&p_entity->hitbox);
}

static i32F4 inline get_y_i32F4_from__entity(
        Entity *p_entity) {
    return get_y_i32F4_from__hitbox(&p_entity->hitbox);
}

static i32F4 inline get_z_i32F4_from__entity(
        Entity *p_entity) {
    return get_z_i32F4_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_x_i32_from__entity(
        Entity *p_entity) {
    return get_x_i32_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_y_i32_from__entity(
        Entity *p_entity) {
    return get_y_i32_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_z_i32_from__entity(
        Entity *p_entity) {
    return get_z_i32_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_chunk_x_i32_from__entity(
        Entity *p_entity) {
    return get_chunk_x_i32_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_chunk_y_i32_from__entity(
        Entity *p_entity) {
    return get_chunk_y_i32_from__hitbox(&p_entity->hitbox);
}

static Signed_Index__i32 inline get_chunk_z_i32_from__entity(
        Entity *p_entity) {
    return get_chunk_z_i32_from__hitbox(&p_entity->hitbox);
}

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

static void inline set_entity__ai_handler(
        Entity *p_entity,
        m_Entity_AI_Handler m_ai_handler) {
    p_entity->m_entity_ai_handler = m_ai_handler;
}

static void inline set_entity__body_handler(
        Entity *p_entity,
        m_Entity_Body_Handler m_body_handler) {
    p_entity->m_entity_body_handler = m_body_handler;
}

static void inline set_entity__disposer(
        Entity *p_entity,
        m_Entity_Dispose_Handler m_disposer) {
    p_entity->m_entity_dispose_handler = m_disposer;
}

static void inline set_entity__collider(
        Entity *p_entity,
        m_Entity_Collision_Handler m_collision_handler) {
    p_entity->m_entity_collision_handler = m_collision_handler;
    if (!m_collision_handler) {
        set_entity__collidable(p_entity);
    } else {
        set_entity__uncollidable(p_entity);
    }
}

static void inline set_entity__tile_collider(
        Entity *p_entity,
        m_Entity_Tile_Collision_Handler m_collision_handler) {
    p_entity->m_entity_tile_collision_handler = m_collision_handler;
}

static void inline set_entity__animator(
        Entity *p_entity,
        m_Entity_Animation_Handler m_animation_handler) {
    p_entity->m_entity_animation_handler = m_animation_handler;
}

void initialize_entity(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height);

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification);

bool is_entity__moving(Entity *entity);

void set_entity_as__moving(Entity *entity, 
        bool state_of_movement,
        enum Sprite_Animation_Kind fallback_animation);

#endif

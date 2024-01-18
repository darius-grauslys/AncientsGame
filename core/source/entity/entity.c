#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>
#include <rendering/animate_entity.h>

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

void init_entity(Entity *entity, enum Entity_Kind kind_of_entity) {
    entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    entity->x__chunk =
        entity->x = 0;
    entity->y__chunk =
        entity->y = 0;
    entity->z__chunk =
        entity->z = 0;

    set_entity__enabled(entity);
    set_entity__is_updating_position(entity);
    set_entity__is_updating_graphics(entity);

    init_sprite_wrapper(
            &entity->sprite_wrapper,
            entity);
}

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    entity->armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    entity->armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
    set_entity_animation(entity,
            entity->sprite_wrapper.the_kind_of_animation__this_sprite_has);
}

void set_entity__direction(Entity *entity,
        Direction direction) {
    if (entity->sprite_wrapper.direction == direction)
        return;
    entity->sprite_wrapper.direction = direction;
    set_entity_animation(entity, 
            entity->sprite_wrapper.the_kind_of_animation__this_sprite_has);
}

Direction get_entity__direction(Entity *entity) {
    return entity->sprite_wrapper.direction;
}

bool is_entity__moving(Entity *entity) {
    if (!can_entity__move(entity->the_kind_of_entity__this_entity_is)) {
        return false;
    }

    if (is_entity__humanoid(entity->the_kind_of_entity__this_entity_is)) {
        return
            entity->sprite_wrapper.the_kind_of_animation__this_sprite_has
            == Sprite_Animation_Kind__Humanoid__Walk;
    }

    debug_warning("unhandled case in: is_entity__moving.");

    return false;
}

void set_entity_as__moving(Entity *entity, 
        bool state_of_movement,
        enum Sprite_Animation_Kind fallback_animation) {
    if (!can_entity__move(entity->the_kind_of_entity__this_entity_is)) {
        debug_warning("illegal call to set_entity_as__moving.");
        return;
    }

    if (is_entity__humanoid(entity->the_kind_of_entity__this_entity_is)) {
        if (state_of_movement) {
            set_entity_animation(
                    entity,
                    Sprite_Animation_Kind__Humanoid__Walk);
        } else {
            set_entity_animation(
                    entity,
                    Sprite_Animation_Kind__Idle);
        }
        return;
    }

    debug_warning("unhandled case in: set_entity_as__moving");
}

void apply_velocity_to__entity(Entity *entity,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity) {

    int32_t dx, dy, dz;

    dx = ((entity->x + x__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (entity->x >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dy = ((entity->y + y__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (entity->y >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dz = ((entity->z + z__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (entity->z >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    entity->x += x__velocity
        - (dx << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    entity->y += y__velocity
        - (dy << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    entity->z += z__velocity
        - (dz << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    entity->x__chunk += dx;
    entity->y__chunk += dy;
    entity->z__chunk += dz;
}

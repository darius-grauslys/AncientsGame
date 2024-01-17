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

    debug_warning("init_entity is not complete.");

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
    set_animation__of_entity(entity,
            entity->sprite_wrapper.the_kind_of_animation__this_sprite_has);
}

void set_entity__direction(Entity *entity,
        Direction direction) {
    if (entity->sprite_wrapper.direction == direction)
        return;
    entity->x__velocity_accumilator = 0;
    entity->y__velocity_accumilator = 0;
    entity->z__velocity_accumilator = 0;
    entity->sprite_wrapper.direction = direction;
    set_animation__of_entity(entity, 
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
            set_animation__of_entity(
                    entity,
                    Sprite_Animation_Kind__Humanoid__Walk);
        } else {
            set_animation__of_entity(
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

    entity->x__velocity_accumilator
        += x__velocity;
    entity->y__velocity_accumilator
        += y__velocity;
    entity->z__velocity_accumilator
        += z__velocity;

    int32_t dx, dy, dz;
    dx = entity->x__velocity_accumilator >>
        ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE;
    dy = entity->y__velocity_accumilator >>
        ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE;
    dz = entity->z__velocity_accumilator >>
        ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE;

    entity->x += dx;
    entity->y += dy;
    entity->z += dz;

    if (dx > 0 || dx < 0)
        entity->x__velocity_accumilator =
            entity->x__velocity_accumilator
            % (1 << ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE);
    if (dy > 0 || dy < 0)
        entity->y__velocity_accumilator =
            entity->y__velocity_accumilator
            % (1 << ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE);
    if (dz > 0 || dz < 0)
        entity->z__velocity_accumilator =
            entity->z__velocity_accumilator
            % (1 << ENTITY_VELOCITY_ACUMMILATOR__BIT_SIZE);
}

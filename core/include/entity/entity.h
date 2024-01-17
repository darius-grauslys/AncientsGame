#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <defines.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity);
bool can_entity__move(enum Entity_Kind kind_of_entity);

bool is_entity__humanoid(enum Entity_Kind kind_of_entity);

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

void apply_velocity_to__entity(Entity *entity,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity);

#endif

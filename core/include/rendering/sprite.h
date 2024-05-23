#ifndef SPRITE_H
#define SPRITE_H

#include <defines.h>

static void inline init_sprite_wrapper(
        Sprite_Wrapper *sprite_wrapper,
        Texture_Flags texture_flags_for__sprite) {
    PLATFORM_init_sprite(
            &sprite_wrapper->sprite,
            texture_flags_for__sprite,
            false);
    sprite_wrapper->direction =
        DIRECTION__EAST;
    sprite_wrapper->
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Idle;

    sprite_wrapper->
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Idle;
    
    sprite_wrapper->
        frame__initial = 0;
    sprite_wrapper->
        frame = 0;
    sprite_wrapper->
        frame__final = 1;
}

static void inline init_sprite_wrapper_for__entity(
        Entity *entity) {
    PLATFORM_init_sprite_for__entity(
            entity);
    Sprite_Wrapper *sprite_wrapper =
        &entity->sprite_wrapper;
    sprite_wrapper->direction =
        DIRECTION__EAST;
    sprite_wrapper->
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Idle;

    sprite_wrapper->
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Idle;
    
    sprite_wrapper->
        frame__initial = 0;
    sprite_wrapper->
        frame = 0;
    sprite_wrapper->
        frame__final = 1;
}

#endif

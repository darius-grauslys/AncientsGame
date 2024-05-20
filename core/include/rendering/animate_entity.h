#ifndef RENDER_ENTITY_H
#define RENDER_ENTITY_H

#include <rendering/animate_sprite.h>
#include <defines.h>

static void inline poll_entity_animation__transition(
        Entity *entity,
        f_sprite_frame_lookup inital_frame__lookup,
        f_sprite_frame_lookup final_frame__lookup,
        bool force) {
    if (force || is_animation__in_transition(entity->sprite_wrapper)) {
        entity->sprite_wrapper.the_kind_of_animation__this_sprite_has =
            entity->sprite_wrapper.the_kind_of_animation__thats_upcomming;

        entity->sprite_wrapper.the_kind_of_animation__thats_upcomming =
            Sprite_Animation_Kind__None;

        entity->sprite_wrapper.frame = 
            entity->sprite_wrapper.frame__initial = 
            inital_frame__lookup(entity,
                    entity->sprite_wrapper
                    .the_kind_of_animation__this_sprite_has);
        entity->sprite_wrapper.frame__final =
            final_frame__lookup(entity,
                    entity->sprite_wrapper
                    .the_kind_of_animation__this_sprite_has);
        return;
    }
    if (is_animation__exceeded(entity->sprite_wrapper)) {
        entity->sprite_wrapper.frame =
            entity->sprite_wrapper.frame__initial;
        return;
    }
}

#endif

#include <entity/entity.h>
#include <rendering/animate_entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>

void poll_entity_animation__transition(
        Entity *p_entity,
        f_Sprite_Frame_Lookup f_inital_frame__lookup,
        f_Sprite_Frame_Lookup f_final_frame__lookup,
        bool force) {
    if (force || is_animation__in_transition(p_entity->sprite_wrapper)) {
        p_entity->sprite_wrapper.the_kind_of_animation__this_sprite_has =
            p_entity->sprite_wrapper.the_kind_of_animation__thats_upcomming;

        p_entity->sprite_wrapper.the_kind_of_animation__thats_upcomming =
            Sprite_Animation_Kind__None;

        p_entity->sprite_wrapper.frame = 
            p_entity->sprite_wrapper.frame__initial = 
            f_inital_frame__lookup(p_entity,
                    p_entity->sprite_wrapper
                    .the_kind_of_animation__this_sprite_has);
        p_entity->sprite_wrapper.frame__final =
            f_final_frame__lookup(p_entity,
                    p_entity->sprite_wrapper
                    .the_kind_of_animation__this_sprite_has);
        return;
    }
    if (is_animation__finished(p_entity->sprite_wrapper)) {
        p_entity->sprite_wrapper.frame =
            p_entity->sprite_wrapper.frame__initial;
        return;
    }
}


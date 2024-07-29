#include "defines_weak.h"
#include "entity/entity.h"
#include "platform.h"
#include "rendering/animate_sprite.h"
#include <entity/handlers/animation/animation_handler__humanoid.h>
#include <rendering/animate_humanoid.h>
#include <rendering/animate_entity.h>
#include <numerics.h>

void m_entity_animation_handler__humanoid(
        Entity *p_humanoid) {
    Sprite_Wrapper *p_sprite_wrapper = 
        get_p_sprite_wrapper_from__entity(
                p_humanoid);

    bool requires_direction_update = 
        p_sprite_wrapper->direction
        != p_sprite_wrapper->direction__requested
        ;

    if (requires_direction_update) {
        p_sprite_wrapper->direction =
            p_sprite_wrapper->direction__requested
            ;
        set_animation_for__humanoid_with__timer_modification(
                p_humanoid, 
                get_animation_kind_from__sprite_wrapper(p_sprite_wrapper),
                true);
    }
    
    if (poll_animation(p_sprite_wrapper)) {
        switch (get_animation_kind_from__sprite_wrapper(
                    p_sprite_wrapper)) {
            default:
                animate_humanoid__idle(p_humanoid);
                break;
            case Sprite_Animation_Kind__Humanoid__Die:
            case Sprite_Animation_Kind__Idle:
                break;
        }
        return;
    }

    if (!(get_time_elapsed_from__timer_u32(
                &p_sprite_wrapper->animation_timer__u32)
            & ANIMATION_BIT_MASK__TICK_RATE)) {
        p_sprite_wrapper->frame__current =
            add_u8__clamped(
                    p_sprite_wrapper->frame__current, 
                    1, 
                    p_sprite_wrapper->frame__final);
        PLATFORM_update_sprite_gfx__to_current_frame(
                get_p_sprite_wrapper_from__entity(p_humanoid));
    }
}

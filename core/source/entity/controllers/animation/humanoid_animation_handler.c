#include <entity/controllers/animation/humanoid_animation_handler.h>
#include <rendering/animate_humanoid.h>
#include <rendering/animate_entity.h>

void m_humanoid_animation_handler(Entity *entity, Timer__u32 *p_timer) {
    Quantity__u32 animation_duration =
        f_get_animation_duration_for__humanoid_animation(
                entity,
                entity->sprite_wrapper
                .the_kind_of_animation__this_sprite_has);

    if (p_timer->remaining__u32 % animation_duration) {
        return;
    }

    entity->sprite_wrapper.frame++;

    poll_humanoid_animation__transition(entity);

    PLATFORM_update_sprite_gfx__to_current_frame(
            &entity->sprite_wrapper);
}

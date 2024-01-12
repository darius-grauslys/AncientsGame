#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include <defines.h>

///
/// Updates the sprite_wrapper.frame value.
///
void animate_sprite__humanoid(Entity *entity);

uint32_t get_start_frame__of_animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

void set_sprite__animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

///
/// Performs the necessary graphical changes needed
/// to reflect the entity's sprite_wrapper.frame value.
///
void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper);

#endif

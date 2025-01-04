#include "debug/debug.h"
#include "defines_weak.h"
#include <rendering/sprite.h>
#include <defines.h>

void initialize_sprite_wrapper(
        Sprite_Wrapper *sprite_wrapper,
        Texture_Flags texture_flags_for__sprite) {
    sprite_wrapper->p_sprite = 0;
    sprite_wrapper->direction =
        DIRECTION__EAST;
    sprite_wrapper->
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Idle;
    
    sprite_wrapper->
        frame__initial = 0;
    sprite_wrapper->
        frame__current = 0;
    sprite_wrapper->
        frame__final = 1;
}

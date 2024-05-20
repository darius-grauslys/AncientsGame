#include <rendering/sprite.h>
#include <defines.h>

void init_sprite_wrapper(Sprite_Wrapper *sprite_wrapper,
        enum Entity_Kind entity_kind) {
    PLATFORM_init_sprite(&sprite_wrapper->sprite,
            entity_kind);
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

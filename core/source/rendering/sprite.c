#include <rendering/sprite.h>
#include <defines.h>

void init_sprite_wrapper(Sprite_Wrapper *sprite_wrapper,
        Entity *entity) {
    PLATFORM_init_sprite(&sprite_wrapper->sprite,
            entity);
    sprite_wrapper->direction =
        DIRECTION__EAST;
    sprite_wrapper->
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Idle;
}

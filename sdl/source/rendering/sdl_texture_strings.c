#include "defines_weak.h"
#include <rendering/sdl_texture_strings.h>
#include <defines.h>

SDL_Texture_String__Const SDL_texture_string__player =
    "player.png";

SDL_Texture_String__Const 
*SDL_get_texture_string_from__sprite_allocation_specification(
        Sprite_Allocation_Specification *p_sprite_allocation_specification) {
    switch (p_sprite_allocation_specification
            ->the_kind_of__sprite_allocation) {
        default:
            debug_error("SDL_get_texture_string_from__sprite_allocation_specification, unsupported type.");
            return 0;
        case Sprite_Allocation_Kind__Entity:
            switch (p_sprite_allocation_specification
                    ->the_kind_of__entity_this__sprite_is) {
                default:
                    debug_error("SDL_get_texture_string_from__sprite_allocation_specification, unsupported type.");
                    return 0;
                case Entity_Kind__Player:
                    return &SDL_texture_string__player;
            }
            break;
    }
}

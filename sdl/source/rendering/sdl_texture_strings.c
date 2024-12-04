#include "defines_weak.h"
#include <rendering/sdl_texture_strings.h>
#include <defines.h>

SDL_Texture_String__Const SDL_texture_string__tilesheet_cover =
    "tilesheet_cover.png";
SDL_Texture_String__Const SDL_texture_string__tilesheet_ground =
    "tilesheet_ground.png";

SDL_Texture_String__Const SDL_texture_string__tilesheet_ui =
    "_ui_tileset_default.png";

SDL_Texture_String__Const SDL_texture_string__items =
    "items.png";
SDL_Texture_String__Const SDL_texture_string__player =
    "player.png";
SDL_Texture_String__Const SDL_texture_string__skeleton =
    "skeleton.png";

SDL_Texture_String__Const SDL_texture_string__ui_sprites__8x8 =
    "ui_sprites__8x8.png";
SDL_Texture_String__Const SDL_texture_string__ui_sprites__16x16 =
    "ui_sprites__16x16.png";
SDL_Texture_String__Const SDL_texture_string__ui_sprites__32x32 =
    "ui_sprites__32x32.png";

// TODO: the behavior below should be auto-gen'd

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
                case Entity_Kind__Skeleton:
                    return &SDL_texture_string__skeleton;
            }
            break;
        case Sprite_Allocation_Kind__Item:
            return &SDL_texture_string__items;
        case Sprite_Allocation_Kind__UI:
            ;
            enum UI_Sprite_Kind the_kind_of__ui_sprite =
                p_sprite_allocation_specification
                ->the_kind_of__ui__this_sprite_is;
            if (the_kind_of__ui_sprite
                    < UI_Sprite_Kind__8x8) {
                return &SDL_texture_string__ui_sprites__8x8;
            }
            if (the_kind_of__ui_sprite
                    < UI_Sprite_Kind__16x16) {
                return &SDL_texture_string__ui_sprites__16x16;
            }
            if (the_kind_of__ui_sprite
                    >= UI_Sprite_Kind__32x32) {
                debug_error("SDL_get_texture_string_from__sprite_allocation_specification, unsupported ui_sprite.");
                return 0;
            }
            return &SDL_texture_string__ui_sprites__32x32;
    }
}

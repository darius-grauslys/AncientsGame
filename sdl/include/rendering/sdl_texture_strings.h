#ifndef SDL_TEXTURE_STRINGS_H
#define SDL_TEXTURE_STRINGS_H

#include "defines_weak.h"
#include <sdl_defines.h>

// TODO: auto-gen this file.

extern SDL_Texture_String__Const SDL_texture_string__tilesheet_cover;
extern SDL_Texture_String__Const SDL_texture_string__tilesheet_ground;

extern SDL_Texture_String__Const SDL_texture_string__tilesheet_ui;

extern SDL_Texture_String__Const SDL_texture_string__player;
extern SDL_Texture_String__Const SDL_texture_string__skeleton;

SDL_Texture_String__Const 
*SDL_get_texture_string_from__sprite_allocation_specification(
        Sprite_Allocation_Specification *p_sprite_allocation_specification);

#endif

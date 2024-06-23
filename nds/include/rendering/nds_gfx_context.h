#ifndef NDS_GFX_CONTEXT_H
#define NDS_GFX_CONTEXT_H

#include "defines_weak.h"
#include <defines.h>

void NDS_initialize_gfx_for__main_background();

void NDS_initialize_gfx_for__sub_background();

void NDS_initialize_gfx_for__main_sprites();

void NDS_initialize_gfx_for__sub_sprites();

void NDS_load_sprite_palletes();

void NDS_initialize_gfx_for__main_menu(
        PLATFORM_Gfx_Context *gfx_context);

void NDS_initialize_gfx_for__world(
        PLATFORM_Gfx_Context *gfx_context);

void NDS_initialize_gfx_for__ui(
        PLATFORM_Gfx_Context *gfx_context);

#endif

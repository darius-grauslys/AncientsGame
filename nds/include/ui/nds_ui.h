#ifndef NDS_UI_H
#define NDS_UI_H

#include "defines_weak.h"
#include <defines.h>

void NDS_set_ui_background_to__equip(
        PLATFORM_Gfx_Context *p_gfx_context);
void NDS_set_ui_background_to__ground(
        PLATFORM_Gfx_Context *p_gfx_context);
void NDS_set_ui_background_to__work(
        PLATFORM_Gfx_Context *p_gfx_context);

void NDS_set_ui_background_to__menu_main(
        PLATFORM_Gfx_Context *p_gfx_context);
void NDS_set_ui_background_to__menu_single_player(
        PLATFORM_Gfx_Context *p_gfx_context);
void NDS_set_ui_background_to__menu_multiplayer(
        PLATFORM_Gfx_Context *p_gfx_context);
void NDS_set_ui_background_to__menu_settings(
        PLATFORM_Gfx_Context *p_gfx_context);

void NDS_set_ui_element_size_using__sprite_size(
        UI_Element *p_ui_element,
        SpriteSize sprite_size);

#endif

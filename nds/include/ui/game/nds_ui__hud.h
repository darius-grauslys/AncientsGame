#ifndef NDS_UI__HUD_H
#define NDS_UI__HUD_H

#include "defines_weak.h"
#include "nds_defines.h"
#include <rendering/nds_background.h>

void NDS_update_ui_for__hud(
        PLATFORM_Gfx_Context *p_gfx_context,
        Scene *p_scene,
        Entity *p_player);

void NDS_put_hud_onto__background(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        NDS_Background *p_NDS_background);

#endif

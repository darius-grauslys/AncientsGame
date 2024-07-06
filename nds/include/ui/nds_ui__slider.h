#ifndef NDS_UI__SLIDER_H
#define NDS_UI__SLIDER_H

#include "defines_weak.h"
#include "ui/ui_slider.h"
#include <defines.h>
#include <nds_defines.h>

void m_NDS_ui_slider__dragged_handler_for__backgrounds(
        UI_Element *p_this_draggable,
        Game *p_game);

static inline
void NDS_allocate_sprite_for__ui_slider(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        UI_Element *p_NDS_ui_slider) {
    allocate_sprite_for__ui_slider(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
            ->graphics_window__sub, 
            p_NDS_ui_slider);
}

#endif

#ifndef NDS_GFX_WINDOW_H
#define NDS_GFX_WINDOW_H

#include "defines_weak.h"
#include "nds_defines.h"
#include "rendering/nds_background.h"

void NDS_initialize_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        NDS_Background *p_NDS_background_associated_to__this_window,
        OamState *p_oam_state);

static inline
bool NDS_is_PLATFORM_gfx_window_associated_with_a__background(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return (bool)p_PLATFORM_gfx_window
        ->p_NDS_background_associated_to__this_window
        ;
}

static inline
NDS_Background *NDS_get_p_background_of__PLATFORM_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->p_NDS_background_associated_to__this_window
        ;
}

static inline
u32 NDS_get_background_priortiy_of__PLATFORM_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    if (NDS_is_PLATFORM_gfx_window_associated_with_a__background(
                p_PLATFORM_gfx_window)) {
        return NDS_get_background__priority(
                NDS_get_p_background_of__PLATFORM_gfx_window(
                    p_PLATFORM_gfx_window)); 
    }

    return 0;
}

#endif

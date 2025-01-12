#ifndef GFX_CONTEXT_H
#define GFX_CONTEXT_H

#include "defines.h"
#include "defines_weak.h"

void initialize_gfx_context(
        Gfx_Context *p_gfx_context,
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

static inline
PLATFORM_Gfx_Context *get_p_PLATFORM_gfx_context_from__gfx_context(
        Gfx_Context *p_gfx_context) {
    return p_gfx_context->p_PLATFORM_gfx_context;
}

static inline
Aliased_Texture_Manager *get_p_aliased_texture_manager_from__gfx_context(
        Gfx_Context *p_gfx_context) {
    return &p_gfx_context->aliased_texture_manager;
}

static inline
UI_Context *get_p_ui_context_from__gfx_context(
        Gfx_Context *p_gfx_context) {
    return &p_gfx_context->ui_context;
}

static inline
UI_Tile_Map_Manager *get_p_ui_tile_map_manager_from__gfx_context(
        Gfx_Context *p_gfx_context) {
    return &p_gfx_context->ui_tile_map_manager;
}

static inline
Sprite_Gfx_Allocation_Manager 
*get_p_ui_sprite_gfx_allocation_manager_from__gfx_context(
        Gfx_Context *p_gfx_context) {
    return &p_gfx_context->sprite_gfx_allocation_manager;
}

#endif

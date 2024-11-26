#ifndef GFX_CONTEXT_H
#define GFX_CONTEXT_H

#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "nds_defines.h"

static inline
NDS_Texture_Manager *NDS_get_p_texture_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context
        ->NDS_texture_manager;
}

static inline
enum UI_Window_Kind get_the_kind_of__active_ui_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return p_PLATFORM_gfx_context->the_kind_of__active_ui_window;
}

static inline
PLATFORM_Graphics_Window *NDS_get_graphics_window__main_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context
        ->graphics_window__main;
}

static inline
PLATFORM_Graphics_Window *NDS_get_graphics_window__sub_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context
        ->graphics_window__sub;
}

void NDS_initialize_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

static inline
void NDS_register_sprite_gfx_allocator_for__items(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler) {
    p_PLATFORM_gfx_context
        ->f_sprite_gfx_allocator__handler_for__items = 
            f_sprite_gfx_allocator__handler;
}

static inline
void NDS_register_sprite_gfx_allocator_for__ui(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler) {
    p_PLATFORM_gfx_context
        ->f_sprite_gfx_allocator__handler_for__ui = 
            f_sprite_gfx_allocator__handler;
}

static inline
void NDS_register_sprite_gfx_allocator_for__entity(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Entity_Kind the_kind_of__entity,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler) {
#ifndef NDEBUG
    if (Entity_Kind__Unknown <= the_kind_of__entity) {
        debug_abort("NDS_register_sprite_gfx_allocator_for__entity, unknown entity kind: %d",
                the_kind_of__entity);
        debug_warning("Did you add this entity kind after Entity_Kind__Unknown?");
        return;
    }
#endif
    p_PLATFORM_gfx_context
        ->F_sprite_gfx_allocator__lookup_table_for__entities[
            the_kind_of__entity] = f_sprite_gfx_allocator__handler;
}

static inline
void NDS_register_sprite_gfx_allocator_for__particle(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Entity_Kind the_kind_of__entity,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator__handler) {
#warning impl particles
    debug_abort("NDS_register_sprite_gfx_allocator_for__particle, not implemented.");
}

static inline
void NDS_initialize_sprite_pallete(
        NDS_Sprite_Pallete *p_NDS_sprite_pallete,
        const uint16_t *p_sprite_pallete,
        Index__u8 pallete_slot,
        Quantity__u32 pallete_length) {
    p_NDS_sprite_pallete->p_pallete =
        p_sprite_pallete;
    p_NDS_sprite_pallete->pallete_slot =
        pallete_slot;
    p_NDS_sprite_pallete->pallete_length =
        pallete_length;
}

void NDS_set_video_modes_to__MODE_0_2D(void);
void NDS_set_vram_for__backgrounds_on__main(void);
void NDS_set_vram_for__backgrounds_on__sub(void);
void NDS_set_vram_and__oam_for__sprites_on__main(void);
void NDS_set_vram_and__oam_for__sprites_on__sub(void);
void NDS_load_sprite_palletes(
        NDS_Sprite_Pallete *p_NDS_sprite_palletes,
        Quantity__u32 quantity_of__sprite_palletes,
        bool for_main_or_sub);
void NDS_load_sprite_palletes__default_into__vram(void);
void NDS_initialize_gfx_for__ui(
        PLATFORM_Gfx_Context *gfx_context);
void NDS_initialize_gfx_for__world(
        PLATFORM_Gfx_Context *gfx_context);

static inline
NDS_Sprite_Manager *NDS_get_p_NDS_sprite_manager_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        &p_PLATFORM_gfx_context->nds_sprite_manager;
}

static inline
UI_Manager *NDS_get_p_ui_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        &p_PLATFORM_gfx_context
        ->NDS_ui_manager;
}

#endif

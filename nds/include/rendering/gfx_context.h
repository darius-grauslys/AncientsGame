#ifndef GFX_CONTEXT_H
#define GFX_CONTEXT_H

#include "defines_weak.h"
#include "nds_defines.h"
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

#endif

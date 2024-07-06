#include "debug/nds_debug.h"
#include "defines_weak.h"
#include "nds/arm9/background.h"
#include "nds/arm9/video.h"
#include "nds/dma.h"
#include "rendering/nds_sprite.h"
#include "rendering/nds_sprite_manager.h"
#include "rendering/sprite.h"
#include "rendering/texture.h"
#include "timer.h"
#include <defines.h>
#include <nds_defines.h>
#include <rendering/gfx_context.h>
#include <world/tile.h>

#include <rendering/nds_background.h>
#include <rendering/gfx_context.h>

#include <assets/world/GFX_world.h>
#include <assets/world/tiles.h>
#include <assets/ui/default/GFX_default.h>

#include <assets/entities/entity_sprite__16x16/GFX_entity_sprite__16x16.h>
#include <assets/entities/entity_sprite__8x8/GFX_entity_sprite__8x8.h>

#include <assets/entities/entity_sprite__16x16/player.h>
#include <assets/entities/entity_sprite__16x16/skeleton.h>
#include <assets/entities/entity_sprite__16x16/zombie.h>

PLATFORM_Gfx_Context _NDS_gfx_context;

static inline
void NDS_initialize_backgrounds(
        NDS_Backgrounds a_NDS_backgrounds) {
    for (Index__u8 index_of__background = 0;
            index_of__background 
            < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index_of__background++) {
        NDS_initialize_background(
                &a_NDS_backgrounds[index_of__background],
                index_of__background);
    }
}

void NDS_initialize_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

    NDS_initialize_backgrounds(
            p_PLATFORM_gfx_context
            ->backgrounds__main);
    NDS_initialize_backgrounds(
            p_PLATFORM_gfx_context
            ->backgrounds__sub);

    p_PLATFORM_gfx_context
        ->graphics_window__main = (PLATFORM_Graphics_Window){
            p_PLATFORM_gfx_context,
            &oamMain
        };
    p_PLATFORM_gfx_context
        ->graphics_window__sub = (PLATFORM_Graphics_Window){
            p_PLATFORM_gfx_context,
            &oamSub
        };

    initialize_sprite_gfx_allocator__lookup_table_for__entities(
            p_PLATFORM_gfx_context
            ->F_sprite_gfx_allocator__lookup_table_for__entities);

    initialize_sprite_gfx_allocator__lookup_table_for__particles(
            p_PLATFORM_gfx_context
            ->F_sprite_gfx_allocator__lookup_table_for__particles);

#warning impl, but not here, after initializer is called.
    p_PLATFORM_gfx_context
        ->f_sprite_gfx_allocator__handler_for__items =
        f_sprite_gfx_allocator__handler__default;
}

PLATFORM_Graphics_Window 
*PLATFORM_get_p_graphics_window_with__graphics_window_kind(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Graphics_Window_Kind the_kind_of__graphics_window,
        Identifier__u32 identifier_of__graphics_window) {
    switch (the_kind_of__graphics_window) {
        default:
            return &p_PLATFORM_gfx_context->graphics_window__main;
        case Graphics_Window_Kind__UI:
            return &p_PLATFORM_gfx_context->graphics_window__sub;
    }
}

PLATFORM_Gfx_Context *PLATFORM_get_p_gfx_context_from__graphics_window(
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    return p_PLATFORM_graphics_window
        ->p_PLATFORM_gfx_context;
}

void NDS_set_video_modes_to__MODE_0_2D(void) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
}

void NDS_set_vram_for__backgrounds_on__main(void) {
    vramSetBankA(VRAM_A_MAIN_BG);
}

void NDS_set_vram_for__backgrounds_on__sub(void) {
    vramSetBankC(VRAM_C_SUB_BG);
    bgExtPaletteEnableSub();
}

void NDS_set_vram_and__oam_for__sprites_on__main(void) {
    vramSetBankB(VRAM_B_MAIN_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_256, true);
}

void NDS_set_vram_and__oam_for__sprites_on__sub(void) {
    vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamSub, SpriteMapping_1D_256, true);
}

void NDS_load_sprite_palletes_into__vram(
        NDS_Sprite_Pallete *p_NDS_sprite_palletes,
        Quantity__u32 quantity_of__sprite_palletes,
        bool for_main_or_sub) {
    if (for_main_or_sub) {
        goto main;
    }
	vramSetBankI(VRAM_I_LCD);

    for (Index__u32 index_of__sprite_pallete = 0;
            index_of__sprite_pallete < quantity_of__sprite_palletes;
            index_of__sprite_pallete++) {
        const uint16_t *p_pallete =
            p_NDS_sprite_palletes[index_of__sprite_pallete].p_pallete;
        Index__u8 index_of__pallete_slot =
            p_NDS_sprite_palletes[index_of__sprite_pallete].pallete_slot;
        Quantity__u32 pallete_length =
            p_NDS_sprite_palletes[index_of__sprite_pallete].pallete_length;

        dmaCopy(p_pallete, 
                VRAM_I_EXT_SPR_PALETTE[index_of__pallete_slot],
                pallete_length);
    }

	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
    return;

main:
	vramSetBankF(VRAM_F_LCD);

    for (Index__u32 index_of__sprite_pallete = 0;
            index_of__sprite_pallete < quantity_of__sprite_palletes;
            index_of__sprite_pallete++) {
        const uint16_t *p_pallete =
            p_NDS_sprite_palletes[index_of__sprite_pallete].p_pallete;
        Index__u8 index_of__pallete_slot =
            p_NDS_sprite_palletes[index_of__sprite_pallete].pallete_slot;
        Quantity__u32 pallete_length =
            p_NDS_sprite_palletes[index_of__sprite_pallete].pallete_length;

        dmaCopy(p_pallete, 
                VRAM_F_EXT_SPR_PALETTE[index_of__pallete_slot],
                pallete_length);
    }

	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
}

void NDS_load_sprite_palletes__default_into__vram(void) {
    NDS_Sprite_Pallete entity_sprite_palletes[2];

    NDS_initialize_sprite_pallete(
            &entity_sprite_palletes[NDS_PALLETE_SLOT__0], 
            GFX_entity_sprite__8x8Pal, 
            NDS_PALLETE_SLOT__0,
            GFX_entity_sprite__8x8PalLen);
    NDS_initialize_sprite_pallete(
            &entity_sprite_palletes[NDS_PALLETE_SLOT__1], 
            GFX_entity_sprite__16x16Pal, 
            NDS_PALLETE_SLOT__1, 
            GFX_entity_sprite__16x16PalLen);

    NDS_load_sprite_palletes_into__vram(
            entity_sprite_palletes, 
            NDS_SPRITE_PALLETE_QUANTITY_OF_FOR__DEFAULT,
            true    // load onto main
            );
    NDS_load_sprite_palletes_into__vram(
            entity_sprite_palletes, 
            NDS_SPRITE_PALLETE_QUANTITY_OF_FOR__DEFAULT,
            false   // load onto main
            );
}

void NDS_initialize_gfx_for__world(
        PLATFORM_Gfx_Context *gfx_context) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

    NDS_set_vram_for__backgrounds_on__main();
    NDS_set_vram_for__backgrounds_on__sub();
    NDS_set_vram_and__oam_for__sprites_on__main();
    NDS_set_vram_and__oam_for__sprites_on__sub();
    NDS_load_sprite_palletes__default_into__vram();

    NDS_initialize_background_for__world_ground(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__GROUND]);
    NDS_initialize_background_for__world_wall_upper(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_LOWER]);
    NDS_initialize_background_for__world_wall_lower(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_UPPER]);

	dmaCopy(GFX_worldTiles, 
            gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__GROUND]
            .gfx_tileset, GFX_worldTilesLen);
	dmaCopy(GFX_worldPal, BG_PALETTE, GFX_worldPalLen);

	dmaCopy(tilesMap,
            gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__GROUND]
            .gfx_map, 
            tilesMapLen);
	dmaCopy(tilesMap, 
            gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_LOWER]
            .gfx_map,
            tilesMapLen);
	dmaCopy(tilesMap, 
            gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_UPPER]
            .gfx_map,
            tilesMapLen);

    NDS_set_background_priority(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_LOWER], 
            0);
    NDS_set_background_priority(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__WALL_UPPER], 
            1);
    NDS_set_background_priority(
            &gfx_context->backgrounds__main[
                NDS_BACKGROUND_SLOT__GAME__GROUND], 
            2);
}

#warning this should be replaced with NDS_open_ui(...);
//          maybe NDS_initialize_ui(...) for a UI_Window_Kind.
void NDS_initialize_gfx_for__ui(
        PLATFORM_Gfx_Context *gfx_context) {
    // NDS_initialize_background_ui(
    //         &gfx_context->backgrounds__sub[0]);
    // NDS_initialize_background_ui(
    //         &gfx_context->backgrounds__sub[1]);

	// dmaCopy(GFX_defaultTiles, 
    //         gfx_context->backgrounds__sub[0]
    //         .gfx_tileset, GFX_defaultTilesLen);
	// dmaCopy(GFX_defaultTiles, 
    //         gfx_context->backgrounds__sub[1]
    //         .gfx_tileset, GFX_defaultTilesLen);
	// dmaCopy(GFX_defaultPal, BG_PALETTE_SUB, GFX_defaultPalLen);

    // NDS_set_background_priority(
    //         &gfx_context->backgrounds__sub[0], 
    //         1);
    // NDS_set_background_priority(
    //         &gfx_context->backgrounds__sub[1], 
    //         2);
}

Quantity__u32 NDS_get_quantity_of__allocated_background_slots(
        NDS_Backgrounds nds_backgrounds) {
    Quantity__u32 quantity_of__allocated_background_slots = 0;
    for (Index__u8 index_of__background = 0;
            index_of__background
            < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index_of__background++) {
        if (nds_backgrounds[index_of__background]
                .gfx_tileset) {
            quantity_of__allocated_background_slots++;
        }
    }

    return quantity_of__allocated_background_slots;
}

Quantity__u32 PLATFORM_get_max_quantity_of__allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    Texture_Flags render_method_flags =
        get_texture_flags__rendering_method(texture_flags);

    switch (render_method_flags) {
        default:
            return 0;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN:
            return NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB:
            return NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_MAIN:
            return NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_SUB:
            return NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
    }
}

Quantity__u32 PLATFORM_get_quantity_of__available_allocations_for__texture_flags(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    Texture_Flags render_method_flags =
        get_texture_flags__rendering_method(texture_flags);

    switch (render_method_flags) {
        default:
            return 0;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN:
            return 
                NDS_get_quantity_of__available_sprite_allocations_on__oam_main(
                        NDS_get_p_NDS_sprite_manager_from__gfx_context(
                            p_PLATFORM_gfx_context));
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB:
            return 
                NDS_get_quantity_of__available_sprite_allocations_on__oam_sub(
                        NDS_get_p_NDS_sprite_manager_from__gfx_context(
                            p_PLATFORM_gfx_context));
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_MAIN:
            return 
                NDS_get_quantity_of__allocated_background_slots(
                        p_PLATFORM_gfx_context
                        ->backgrounds__main);
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_SUB:
            return 
                NDS_get_quantity_of__allocated_background_slots(
                        p_PLATFORM_gfx_context
                        ->backgrounds__sub);
    }
}

bool PLATFORM_has_support_for__texture_flag__render_method(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    switch (get_texture_flags__rendering_method(texture_flags)) {
        default:
            return false;
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_MAIN:
        case NDS_TEXTURE_FLAG__RENDER_METHOD__OAM_SUB:
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_MAIN:
        case NDS_TEXTURE_FLAG__RENDER_METHOD__BACKGROUND_SUB:
            return true;
    }
}

Quantity__u32 PLATFORM_get_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        NDS_get_quantity_of__allocated_sprites(
                NDS_get_p_NDS_sprite_manager_from__gfx_context(
                    p_PLATFORM_gfx_context));
}

Quantity__u32 PLATFORM_get_max_quantity_of__allocated_sprites(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        NDS_QUANTITY_OF__SPRITES_IN__OAM_ENGINE 
        << 2
        ;
}

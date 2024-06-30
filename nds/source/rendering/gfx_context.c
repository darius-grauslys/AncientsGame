#include "debug/nds_debug.h"
#include "defines_weak.h"
#include "nds/arm9/video.h"
#include "nds/dma.h"
#include "rendering/nds_sprite.h"
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

void PLATFORM_initialize_gfx_context(PLATFORM_Gfx_Context *gfx_context) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

    for (Index__u8 index_of__background = 0;
            index_of__background < NDS_BACKGROUND_QUANTITY_OF__MAIN;
            index_of__background++) {
        NDS_initialize_background(
                &gfx_context
                ->backgrounds__main[index_of__background],
                index_of__background);
    }
    for (Index__u8 index_of__background = 0;
            index_of__background < NDS_BACKGROUND_QUANTITY_OF__SUB;
            index_of__background++) {
        NDS_initialize_background(
                &gfx_context
                ->backgrounds__sub[index_of__background],
                index_of__background);
    }
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

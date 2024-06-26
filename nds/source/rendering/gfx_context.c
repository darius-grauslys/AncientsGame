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
                ->backgrounds__main[index_of__background]);
    }
    for (Index__u8 index_of__background = 0;
            index_of__background < NDS_BACKGROUND_QUANTITY_OF__SUB;
            index_of__background++) {
        NDS_initialize_background(
                &gfx_context
                ->backgrounds__sub[index_of__background]);
    }
}

void PLATFORM_open_ui(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum UI_Window_Kind the_kind_of__ui_window_to__open) {
    switch (the_kind_of__ui_window_to__open) {
        default:
            debug_error("PLATFORM_open_ui, unsupported UI_Window_Kind.");
            break;
#warning impl
    }
}

void NDS_set_video_modes_to__MODE_0_2D(void) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
}

void NDS_initialize_backgrounds_for__main(void) {
    vramSetBankA(VRAM_A_MAIN_BG);
}

void NDS_initialize_backgrounds_for__sub(void) {
    vramSetBankC(VRAM_C_SUB_BG);
}

void NDS_initialize_sprites_for__main(void) {
    vramSetBankB(VRAM_B_MAIN_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_256, true);
}

void NDS_initialize_sprites_for__sub(void) {
    vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamSub, SpriteMapping_1D_256, true);
}

void NDS_load_sprite_palletes(
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
            p_NDS_sprite_palletes->pallete_slot;
        Quantity__u32 pallete_length =
            p_NDS_sprite_palletes->pallete_length;

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
            p_NDS_sprite_palletes->pallete_slot;
        Quantity__u32 pallete_length =
            p_NDS_sprite_palletes->pallete_length;

        dmaCopy(p_pallete, 
                VRAM_F_EXT_SPR_PALETTE[index_of__pallete_slot],
                pallete_length);
    }

	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
}

void NDS_load_default__sprite_palletes(void) {
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

    NDS_load_sprite_palletes(
            entity_sprite_palletes, 
            NDS_SPRITE_PALLETE_QUANTITY_OF_FOR__DEFAULT,
            true    // load onto main
            );
}

void NDS_initialize_gfx_for__world(
        PLATFORM_Gfx_Context *gfx_context) {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

    NDS_initialize_backgrounds_for__main();
    NDS_initialize_backgrounds_for__sub();
    NDS_initialize_sprites_for__main();
    NDS_initialize_sprites_for__sub();
    NDS_load_default__sprite_palletes();

    NDS_initialize_background_ground__for_game(
            &gfx_context->backgrounds__main[0]);
    NDS_initialize_background_ground__sprite_cover__for_game(
            &gfx_context->backgrounds__main[1]);
    NDS_initialize_background_ground__overlay__for_game(
            &gfx_context->backgrounds__main[2]);

	dmaCopy(GFX_worldTiles, 
            gfx_context->backgrounds__main[0]
            .gfx_tileset, GFX_worldTilesLen);
	dmaCopy(GFX_worldPal, BG_PALETTE, GFX_worldPalLen);

	dmaCopy(tilesMap,
            gfx_context->backgrounds__main[0]
            .gfx_map, 
            tilesMapLen);
	dmaCopy(tilesMap, 
            gfx_context->backgrounds__main[1]
            .gfx_map,
            tilesMapLen);
	dmaCopy(tilesMap, 
            gfx_context->backgrounds__main[2]
            .gfx_map,
            tilesMapLen);

    NDS_set_background_priority(
            &gfx_context->backgrounds__main[1], 
            0);
    NDS_set_background_priority(
            &gfx_context->backgrounds__main[2], 
            1);
    NDS_set_background_priority(
            &gfx_context->backgrounds__main[0], 
            2);
}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *p_gfx_context,
        Chunk_Manager *p_chunk_manager) {
    TileMapEntry16 *p_sprite_cover_tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[1]
                .background_index);
    TileMapEntry16 *p_overlay_tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[2]
                .background_index);
    TileMapEntry16 *p_background_tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[0]
                .background_index);
    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_current_sub__chunk_map_node;

    for (uint8_t y=0; y < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            y++) {
        p_current_sub__chunk_map_node =
            p_current__chunk_map_node;
        for (uint8_t x=0; x < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
                x++) {
            //TODO: consolidate this to a helper
            uint32_t x__index =
                ((p_current_sub__chunk_map_node->p_chunk__here
                  ->x__signed_index_i32
                  % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
                 + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
                % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            uint32_t y__index =
                ((p_current_sub__chunk_map_node->p_chunk__here
                  ->y__signed_index_i32
                  % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
                 + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
                % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;

            //TODO: im am using magic numbers here atm.

            // Everything is based on the implementation of
            // TileMapEntry16 of background.h in the arm9
            // folder of libnds.
            for (Index__u8 y=0;y<8;y++) {
                for (Index__u8 x=0;x<8;x++) {
                    Quantity__u32 background_tile_index = 
                        y * 32 + x;
                    background_tile_index += 
                        (x__index % 4) * 8;
                    background_tile_index +=
                        (y__index % 4) * 8 * 32;
                    if (x__index >= 4)
                        background_tile_index += 32 * 32;
                    if (y__index >= 4)
                        background_tile_index += 32 * 32 * 2;
                    TileMapEntry16 *p_tile_entry =
                        &p_background_tile_map[background_tile_index];
                    TileMapEntry16 *p_tile_cover_entry =
                        &p_overlay_tile_map[background_tile_index];
                    TileMapEntry16 *p_tile_sprite_cover_entry =
                        &p_sprite_cover_tile_map[background_tile_index];
                    Local_Tile_Vector__3u8 local_tile_vector = {x, y, 0};
                    Tile_Render_Result render_result =
                        get_tile_render_result(
                                p_current_sub__chunk_map_node,
                                local_tile_vector);
                    *(uint16_t*)p_tile_entry = 
                        render_result.tile_index__ground;
                    *(uint16_t*)p_tile_cover_entry = 
                        render_result.tile_index__cover;
                    *(uint16_t*)p_tile_sprite_cover_entry = 
                        render_result.tile_index__sprite_cover;
                }
            }

            p_current_sub__chunk_map_node =
                p_current_sub__chunk_map_node->p_east__chunk_map_node;
        }
        p_current__chunk_map_node =
            p_current__chunk_map_node->p_south__chunk_map_node;
    }
}

void NDS_initialize_gfx_for__ui(
        PLATFORM_Gfx_Context *gfx_context) {
    NDS_initialize_background_ui(
            &gfx_context->backgrounds__sub[0],
            0);
    NDS_initialize_background_ui(
            &gfx_context->backgrounds__sub[1],
            1);

	dmaCopy(GFX_defaultTiles, 
            gfx_context->backgrounds__sub[0]
            .gfx_tileset, GFX_defaultTilesLen);
	dmaCopy(GFX_defaultTiles, 
            gfx_context->backgrounds__sub[1]
            .gfx_tileset, GFX_defaultTilesLen);
	dmaCopy(GFX_defaultPal, BG_PALETTE_SUB, GFX_defaultPalLen);

    NDS_set_background_priority(
            &gfx_context->backgrounds__sub[0], 
            1);
    NDS_set_background_priority(
            &gfx_context->backgrounds__sub[1], 
            2);
}

#include <defines.h>
#include <nds_defines.h>
#include <rendering/gfx_context.h>
#include <world/tile.h>

#include <assets/tiles.h>

#include <assets/entities/player.h>
#include <assets/entities/skeleton.h>
#include <assets/entities/zombie.h>

void PLATFORM_init_gfx_context(PLATFORM_Gfx_Context *gfx_context) {
    // NDS_init_background(&gfx_context->background_ground__back_buffer);
    // NDS_init_background(&gfx_context->background_ground__overlay);
    NDS_init_background(&gfx_context->background_ground__front_buffer);
    // NDS_init_background(&gfx_context->background_extra);
    gfx_context->active_background_ground__buffer =
        &gfx_context->background_ground__front_buffer;
}

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__menu(PLATFORM_Gfx_Context *gfx_context) {

}
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__game(PLATFORM_Gfx_Context *gfx_context) {
    //TODO: settle on better video modes
    videoSetMode(MODE_0_2D);
	// set the sub background up for text display (we could just print to one
	// of the main display text backgrounds just as easily
	videoSetModeSub(MODE_0_2D); //sub bg 0 will be used to print text

    // vramSetBankA(VRAM_A_MAIN_BG);
    // vramSetBankC(VRAM_C_SUB_BG);

	// vramSetPrimaryBanks(
    //         VRAM_A_MAIN_SPRITE,
    //         VRAM_B_MAIN_SPRITE, 
    //         VRAM_C_SUB_BG, 
    //         VRAM_D_MAIN_BG);

	vramSetPrimaryBanks(
            VRAM_A_MAIN_BG,
            VRAM_B_MAIN_SPRITE, 
            VRAM_C_SUB_BG, 
            VRAM_D_SUB_SPRITE);

	vramSetBankF(VRAM_F_LCD);

	dmaCopy(playerPal, 
            VRAM_F_EXT_SPR_PALETTE[SPRITE_PALETTE__PLAYER], 
            playerPalLen);
	dmaCopy(skeletonPal, 
            VRAM_F_EXT_SPR_PALETTE[SPRITE_PALETTE__SKELETON], 
            skeletonPalLen);
	dmaCopy(zombiePal, 
            VRAM_F_EXT_SPR_PALETTE[SPRITE_PALETTE__ZOMBIE], 
            zombiePalLen);

	// set vram to ex palette
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

#ifndef NDEBUG
	consoleDemoInit();
#endif

    NDS_init_background_ground__back_buffer__for_game(
            &gfx_context->background_ground__back_buffer);
    NDS_init_background_ground__front_buffer__for_game(
            &gfx_context->background_ground__front_buffer);
    NDS_init_background_ground__overlay__for_game(
            &gfx_context->background_ground__overlay);

	dmaCopy(tilesTiles, 
            gfx_context->background_ground__overlay
            .gfx_tileset, tilesTilesLen);
	dmaCopy(tilesTiles, 
            gfx_context->background_ground__back_buffer
            .gfx_tileset, tilesTilesLen);
	dmaCopy(tilesTiles, 
            gfx_context->background_ground__front_buffer
            .gfx_tileset, tilesTilesLen);
	dmaCopy(tilesPal, BG_PALETTE, tilesPalLen);

	dmaCopy(tilesMap,
                gfx_context->background_ground__back_buffer
                .gfx_map, 
                tilesMapLen);
	dmaCopy(tilesMap,
                gfx_context->background_ground__front_buffer
                .gfx_map,
                tilesMapLen);
	dmaCopy(tilesMap, 
                gfx_context->background_ground__overlay
                .gfx_map,
                tilesMapLen);

    NDS_set_background_priority(
            &gfx_context->background_ground__overlay, 
            1);
    NDS_set_background_priority(
            &gfx_context->background_ground__back_buffer, 
            2);
    NDS_set_background_priority(
            &gfx_context->background_ground__front_buffer, 
            3);

    // vramSetBankE(VRAM_E_LCD); // for main engine
    // vramSetBankH(VRAM_H_LCD); // for sub engine

    // // copy palettes to extended palette area
    // // there are 16 256-color palettes per bg
    // // use '-mp #' to make grit use # for the slot number
    // // we used '-mp 12' for drunkenlogo for demonstrative purposes
    // dmaCopy(tilesPal,  &VRAM_E_EXT_PALETTE[0][0],  tilesPalLen);  // bg 0, slot 0

    // // map vram banks to extended palettes
    // // http://mtheall.com/banks.html#A=MBG0&C=MBG2&E=BGEPAL&H=SBGEPAL
    // vramSetBankE(VRAM_E_BG_EXT_PALETTE);     // for main engine
    // vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE); // for sub engine

	oamInit(&oamMain, SpriteMapping_1D_256, true);
	oamInit(&oamSub, SpriteMapping_1D_256, true);
}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager) {
    TileMapEntry16 *overlay_tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(gfx_context
                ->background_ground__overlay
                .background_index);
    TileMapEntry16 *background_tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(gfx_context
                ->active_background_ground__buffer
                ->background_index);
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->chunk_map_node__most_north_western;
    Chunk_Manager__Chunk_Map_Node *current_sub__chunk_map_node;

    for (uint8_t y=0; y < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            y++) {
        current_sub__chunk_map_node =
            current__chunk_map_node;
        for (uint8_t x=0; x < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
                x++) {
            uint32_t x__index =
                ((current_sub__chunk_map_node->chunk__here->x
                  % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
                 + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
                % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            uint32_t y__index =
                ((current_sub__chunk_map_node->chunk__here->y
                  % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
                 + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
                % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;

            Chunk *chunk__here =
                current_sub__chunk_map_node->chunk__here;

            //TODO: im am using magic numbers here atm.

            // Everything is based on the implementation of
            // TileMapEntry16 of background.h in the arm9
            // folder of libnds.
            for (int y=0;y<8;y++) {
                for (int x=0;x<8;x++) {
                    uint32_t background_tile_index = 
                        y * 32 + x;
                    background_tile_index += 
                        (x__index % 4) * 8;
                    background_tile_index +=
                        (y__index % 4) * 8 * 32;
                    if (x__index >= 4)
                        background_tile_index += 32 * 32;
                    if (y__index >= 4)
                        background_tile_index += 32 * 32 * 2;
                    Tile *tile = &chunk__here->tiles[y * 8 + x];
                    TileMapEntry16 *tile_entry =
                        &background_tile_map[background_tile_index];
                    TileMapEntry16 *tile_cover_entry =
                        &overlay_tile_map[background_tile_index];
                    uint16_t background_value =
                        (get_tile_texture_sheet_index(tile) + 1)
                        & ((1 << 10)-1);
                    uint16_t overlay_value = 0;
                    if (tile->the_kind_of_tile_cover__this_tile_has
                            != Tile_Cover_Kind__None) {
                        overlay_value = 
                            (get_tile_cover_texture_sheet_index(tile))
                             & ((1 << 10)-1);
                    } 
                    if (is_tile__stairs(tile)) {
                        background_value |= 
                            does_tile__stair_direction__require_hflip(tile)
                            << 11;
                        background_value |= 
                            does_tile__stair_direction__require_vflip(tile)
                            << 10;
                    }
                    *(uint16_t*)tile_entry = background_value;
                    *(uint16_t*)tile_cover_entry = overlay_value;
                }
            }

            current_sub__chunk_map_node =
                current_sub__chunk_map_node->chunk_map_node__east;
        }
        current__chunk_map_node =
            current__chunk_map_node->chunk_map_node__south;
    }
}

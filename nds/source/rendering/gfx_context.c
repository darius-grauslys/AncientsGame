#include <defines.h>
#include <nds_defines.h>
#include <rendering/gfx_context.h>
#include <world/tile.h>

#include <assets/tiles.h>

void PLATFORM_init_gfx_context(PLATFORM_Gfx_Context *gfx_context) {
    NDS_init_background(&gfx_context->background_ground__back_buffer);
    NDS_init_background(&gfx_context->background_ground__front_buffer);
    NDS_init_background(&gfx_context->background_ground__overlay);
    NDS_init_background(&gfx_context->background_extra);
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

    // // enable extended palettes
    // bgExtPaletteEnable();
    // bgExtPaletteEnableSub();

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

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);
}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager) {
    //TODO: we are currently just rendering a single chunk.
    uint16_t *background_tile_map =
        bgGetMapPtr(gfx_context->active_background_ground__buffer
                ->background_index);

    //TODO: im am using magic numbers here atm.
    for (int y=0;y<8;y++) {
        for (int x=0;x<8;x++) {
            background_tile_map[y * 32 + x] =
                get_tile_texture_sheet_index(
                    &chunk_manager->chunk.tiles[y * 8 + x]) + 1;
        }
    }
}

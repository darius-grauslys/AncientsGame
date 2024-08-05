#include "defines.h"
#include "defines_weak.h"
#include "nds_defines.h"
#include "nds/arm9/background.h"
#include "platform_defines.h"
#include <rendering/render_chunk.h>
#include <rendering/render_tile.h>
#include <world/chunk.h>
#include <world/tile.h>

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk) {
}

void NDS_render_chunk(
        Signed_Index__i32 x__chunk_index_i32,
        Signed_Index__i32 y__chunk_index_i32,
        TileMapEntry16 *p_background__ground,
        TileMapEntry16 *p_background__wall_lower,
        TileMapEntry16 *p_background__wall_upper,
        Chunk_Manager__Chunk_Map_Node *p_current_sub__chunk_map_node) {

    // normalize chunk indicies:
    uint32_t x__chunk_index_u32 =
        ((x__chunk_index_i32
          % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
         + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
        % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    uint32_t y__chunk_index_u32 =
        (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS
         - (y__chunk_index_i32
          % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS))
        % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;

            //TODO: im am using magic numbers here atm.

            // Everything is based on the implementation of
            // TileMapEntry16 of background.h in the arm9
            // folder of libnds.
    Quantity__u32 index_offset_of__chunk_in__background = 0;

    index_offset_of__chunk_in__background +=
        (x__chunk_index_u32 % 4) * 8;
    index_offset_of__chunk_in__background +=
        (y__chunk_index_u32 % 4) * 8 * 32;
    if (x__chunk_index_u32 >= 4)
        index_offset_of__chunk_in__background += 32 * 32;
    if (y__chunk_index_u32 >= 4)
        index_offset_of__chunk_in__background += 32 * 32 * 2;

    for (Index__u8 y=0;y<8;y++) {
        for (Index__u8 x=0;x<8;x++) {
            Quantity__u32 background_tile_index = 
                index_offset_of__chunk_in__background
                + (7-y) * 32 + x;

            TileMapEntry16 *p_tile_entry =
                &p_background__ground[background_tile_index];
            TileMapEntry16 *p_tile_cover_entry =
                &p_background__wall_upper[background_tile_index];
            TileMapEntry16 *p_tile_sprite_cover_entry =
                &p_background__wall_lower[background_tile_index];

            Local_Tile_Vector__3u8 local_tile_vector = {
                x, 
                (7-y), 0};
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
}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *p_gfx_context,
        Chunk_Manager *p_chunk_manager) {
    TileMapEntry16 *p_background__wall_lower =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[
                    NDS_BACKGROUND_SLOT__GAME__WALL_LOWER]
                .background_index_from__hardware);
    TileMapEntry16 *p_background__wall_upper =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[
                    NDS_BACKGROUND_SLOT__GAME__WALL_UPPER]
                .background_index_from__hardware);
    TileMapEntry16 *p_background__ground =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__main[
                    NDS_BACKGROUND_SLOT__GAME__GROUND]
                .background_index_from__hardware);
    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_current_sub__chunk_map_node;

    for (uint8_t y=0; 
            y 
            < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            y++) {
        p_current_sub__chunk_map_node =
            p_current__chunk_map_node;
        for (uint8_t x=0; 
                x 
                < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
                x++) {
            //TODO: consolidate this to a helper
            Signed_Index__i32 x__index =
                p_current_sub__chunk_map_node
                    ->position_of__chunk_3i32
                    .x__i32;
            Signed_Index__i32 y__index =
                p_current_sub__chunk_map_node
                    ->position_of__chunk_3i32
                    .y__i32;

            NDS_render_chunk(
                    x__index,
                    y__index,
                    p_background__ground,
                    p_background__wall_lower,
                    p_background__wall_upper,
                    p_current_sub__chunk_map_node);

            p_current_sub__chunk_map_node =
                p_current_sub__chunk_map_node->p_east__chunk_map_node;
        }
        p_current__chunk_map_node =
            p_current__chunk_map_node->p_south__chunk_map_node;
    }
}


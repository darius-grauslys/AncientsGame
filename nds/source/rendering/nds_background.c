#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/background.h"
#include "nds_defines.h"
#include "rendering/texture.h"
#include "rendering/nds_texture.h"
#include "scene/scene_manager.h"
#include <rendering/nds_background.h>

void NDS_initialize_background(
        NDS_Background *background,
        Signed_Index__i8 background_index_for__initializer) {
    background->background_index_from__initializer = 
        background_index_for__initializer;
    NDS_initialize_texture_as__deallocated(
            background->p_PLATFORM_texture__background);
    NDS_initialize_texture_as__deallocated(
            background->p_PLATFORM_texture__background_reserved);
    background->background_index_from__hardware = -1;
    background->gfx_map = 0;
    background->gfx_tileset = 0;
    background->background__scroll_x =
        background->background__scroll_y = 0;
    background->priority = 0;
    background->tile_base =
        background->map_base = 0;
}

void NDS_initialize_background_for__world_ground(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 0;
    background->tile_base = 8;
    NDS_initialize_texture_as__deallocated(
            background->p_PLATFORM_texture__background_reserved);
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);

    NDS_initialize_texture(
            background->p_PLATFORM_texture__background, 
            0, 
            background->gfx_tileset, 
            0,
            0, 
            TEXTURE_FLAG__SIZE_512x512, 
            0, 
            NDS_Texture_Kind__Background);
}

void NDS_initialize_background_for__world_wall_lower(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 4;
    background->tile_base = 12;
    NDS_initialize_texture_as__deallocated(
            background->p_PLATFORM_texture__background_reserved);
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);

    NDS_initialize_texture(
            background->p_PLATFORM_texture__background, 
            0, 
            background->gfx_tileset, 
            0,
            0, 
            TEXTURE_FLAG__SIZE_512x512, 
            0, 
            NDS_Texture_Kind__Background);
}

void NDS_initialize_background_for__world_wall_upper(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 8;
    background->tile_base = 12;
    NDS_initialize_texture_as__deallocated(
            background->p_PLATFORM_texture__background_reserved);
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);

    NDS_initialize_texture(
            background->p_PLATFORM_texture__background, 
            0, 
            background->gfx_tileset, 
            0,
            0, 
            TEXTURE_FLAG__SIZE_512x512, 
            0, 
            NDS_Texture_Kind__Background);
}

void NDS_initialize_background_with__allocation_specification(
        NDS_Background *p_background,
        NDS_Background_Allocation_Specification
            *p_background_allocation_specification) {
    Signed_Index__i8 layer =
        p_background_allocation_specification
        ->background_slot;
    p_background->background_index_from__initializer =
        p_background_allocation_specification
        ->background_slot;

    p_background->quantity_of__tiles_allocated =
        p_background_allocation_specification
        ->length_of__p_gfx_background >> 6;
    p_background->quantity_of__tiles_allocated_in__reserve =
        p_background_allocation_specification
        ->length_of__p_gfx_background__reservation >> 6;

    p_background->quantity_of__map_entries_allocated =
        p_background_allocation_specification
        ->length_of__p_map_background >> 6;
    p_background->quantity_of__map_entries_allocated_in__reserve =
        p_background_allocation_specification
        ->length_of__p_map_background__reservation >> 6;
    
    p_background->quantity_of__pallete_colors_allocated =
        p_background_allocation_specification
        ->length_of__p_pal_background >> 1;
    p_background->quantity_of__pallete_colors_allocated_in__reserve =
        p_background_allocation_specification
        ->length_of__p_pal_background__reservation >> 1;

    switch (p_background_allocation_specification
            ->the_kind_of__background_allocation) {
        default:
            p_background->map_base = layer;
            p_background->tile_base = 1;
            p_background->background_index_from__hardware =
                bgInitSub(
                        layer,
                        BgType_Text8bpp, 
                        BgSize_T_256x256, 
                        p_background->map_base, 
                        p_background->tile_base);
            break;
        case NDS_UI_Background_Allocation_Kind__Typer:
            p_background->map_base = layer;
            p_background->tile_base = 5;
            p_background->background_index_from__hardware =
                bgInitSub(
                        layer,
                        BgType_Text8bpp, 
                        BgSize_T_256x256, 
                        p_background->map_base, 
                        p_background->tile_base);
            break;
        case NDS_UI_Background_Allocation_Kind__Log_Lower:
        case NDS_UI_Background_Allocation_Kind__Log_Upper:
            p_background->map_base = layer * 2;
            p_background->tile_base = layer * 2;
            p_background->background_index_from__hardware =
                bgInitSub(
                        layer, 
                        BgType_Text8bpp, 
                        BgSize_T_256x512, 
                        p_background->map_base, 
                        p_background->tile_base);
            break;
    }

    p_background->gfx_map = 
        bgGetMapPtr(p_background->background_index_from__hardware);
    p_background->gfx_tileset = 
        bgGetGfxPtr(p_background->background_index_from__hardware);

    NDS_initialize_texture(
            p_background->p_PLATFORM_texture__background, 
            0, 
            p_background->gfx_tileset, 
            0,
            0, 
            p_background_allocation_specification
                ->background_texture_flags,
            0, 
            NDS_Texture_Kind__Background);

    NDS_initialize_texture(
            p_background->p_PLATFORM_texture__background_reserved, 
            0, 
            p_background->gfx_tileset
            + (p_background->quantity_of__tiles_allocated << 5),
            0,
            0, 
            TEXTURE_FLAGS__NONE, 
            0, 
            NDS_Texture_Kind__Background);

    p_background->starting_position__3i32 =
        p_background_allocation_specification
        ->starting_position__3i32;
    p_background->current_position__3i32 =
        p_background->starting_position__3i32;
    p_background->spanning_scroll_lengths__3i32 =
        p_background_allocation_specification
        ->spanning_scroll_lengths__3i32;
    bgSetScroll(
            p_background->background_index_from__hardware,
            p_background_allocation_specification
            ->starting_position__3i32.x__i32, 
            p_background_allocation_specification
            ->starting_position__3i32.x__i32);
}

void NDS_set_background_priority(
        NDS_Background *background,
        uint32_t priority) {
    background->priority = priority;
	bgSetPriority(background->background_index_from__hardware, priority);
}

bool NDS_copy_tiles_into__reserved_tiles_of__background(
        NDS_Background *p_NDS_background,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height) {
    width >>= 3;
    height >>= 3;

    if (width * height >
            p_NDS_background
            ->quantity_of__tiles_allocated_in__reserve)
        return false;

    x >>= 3;
    y >>= 3;

    Quantity__u16 background_width =
                p_NDS_background
                ->p_PLATFORM_texture__background_reserved
                ->width >> 3;
    Quantity__u16 background_height =
                p_NDS_background
                ->p_PLATFORM_texture__background_reserved
                ->height >> 3;

    Index__u16 index_of__reserved_tile =
        p_NDS_background
        ->quantity_of__tiles_allocated;
    for (Index__u16 y__tile = y;
            y__tile < background_height
            && y__tile < y + height;
            y__tile++) {
        for (Index__u16 x__tile = x;
                x__tile < background_width
                && x__tile < x + width;
                x__tile++) {
            Index__u16 index_of__map_tile =
                p_NDS_background
                    ->gfx_map[x__tile + y__tile * background_width];
            dmaCopy(
                    &p_NDS_background
                        ->gfx_tileset[index_of__map_tile << 5],
                    &p_NDS_background
                        ->gfx_tileset[(index_of__reserved_tile++) << 5],
                    8 * 8);
        }
    }

    p_NDS_background
        ->p_PLATFORM_texture__background_reserved
        ->width = width << 3;
    p_NDS_background
        ->p_PLATFORM_texture__background_reserved
        ->height = height << 3;
    return true;
}

void NDS_point_tile_entries_to__reserved_tiles_in__background(
        NDS_Background *p_NDS_background,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height) {
    x >>= 3;
    y >>= 3;

    Quantity__u16 background_width =
                p_NDS_background
                ->p_PLATFORM_texture__background
                ->width >> 3;
    Quantity__u16 background_height =
                p_NDS_background
                ->p_PLATFORM_texture__background
                ->height >> 3;

    width >>= 3;
    height >>= 3;

    Index__u16 index_of__reserved_tiles =
        p_NDS_background
        ->quantity_of__tiles_allocated;
    for (Index__u16 y__tile = y;
            y__tile < background_height
            && y__tile < y + height;
            y__tile++) {
        for (Index__u16 x__tile = x;
                x__tile < background_width
                && x__tile < x + width;
                x__tile++) {
            p_NDS_background
                ->gfx_map[x__tile + y__tile * background_width] =
                    index_of__reserved_tiles++;
        }
    }

    p_NDS_background
        ->p_PLATFORM_texture__background_reserved
        ->width = width << 3;
    p_NDS_background
        ->p_PLATFORM_texture__background_reserved
        ->height = height << 3;
}

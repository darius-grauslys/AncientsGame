#include "nds/arm9/sprite.h"
#include <nds.h>
#include <ui/nds_ui.h>
#include <assets/ui/default/ui_tileset_default.h>

void NDS_set_ui_to__debug(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_tileset_defaultMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_tileset_defaultMapLen);
	dmaCopy(ui_tileset_defaultMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_tileset_defaultMapLen);
}

void NDS_set_ui_element_size_using__sprite_size(
        UI_Element *p_ui_element,
        SpriteSize sprite_size) {
    switch (sprite_size) {
        default:
            break;
        case SpriteSize_8x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_8x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_8x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                8;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_16x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_16x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_16x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                16;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_32x8:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                8;
            break;
        case SpriteSize_32x16:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                16;
            break;
        case SpriteSize_32x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_32x64:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                32;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                64;
            break;
        case SpriteSize_64x32:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                64;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                32;
            break;
        case SpriteSize_64x64:
            p_ui_element
                ->ui_bounding_box__aabb
                .width__quantity_u32 =
                64;
            p_ui_element
                ->ui_bounding_box__aabb
                .height__quantity_u32 =
                64;
            break;
    }
}

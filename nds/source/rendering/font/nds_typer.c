#include "nds/dma.h"
#include "rendering/nds_background.h"
#include "rendering/nds_texture.h"
#include "rendering/texture.h"
#include "vectors.h"
#include <platform.h>
#include <nds_defines.h>
#include <rendering/font/typer.h>

void PLATFORM_put_char_in__typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Typer *p_typer,
        unsigned char letter) {
    Font_Letter *p_font_letter =
        get_p_font_letter_from__typer(
                p_typer, letter);

    if (!poll_typer_for__cursor_wrapping(
            p_typer,
            p_font_letter)) {
        return;
    }

    u32 width_in__tiles =
        (p_typer
        ->p_PLATFORM_texture__typer_target
        ->width) >> 3;

    u32 x__cursor =
        get_x_i32_from__vector_3i32(
                p_typer->cursor_position__3i32);
    u32 y__cursor =
        get_y_i32_from__vector_3i32(
                p_typer->cursor_position__3i32);

    const uint16_t *p_src;
    uint16_t *p_dest;

    p_src =
        (const uint16_t*)p_typer
        ->p_font
        ->p_PLATFORM_texture_of__font
        ->gfx__readonly;
    p_dest =
        (uint16_t*)p_typer
        ->p_PLATFORM_texture__typer_target
        ->gfx;

    for (Index__u32 y__source_pixel = 0;
            y__source_pixel < p_font_letter->height_of__font_letter;
            y__source_pixel++) {
        for (Index__u32 x__source_pixel = 0;
                x__source_pixel < p_font_letter->width_of__font_letter;
                x__source_pixel+=2) {
            u32 index_of__source_pixel_in__font_tile = 
                (x__source_pixel >> 1)
                + (y__source_pixel << 2)
                ;
            u32 index_of__source_pixel_in__font =
                index_of__source_pixel_in__font_tile
                + ((p_font_letter->index_of__character__in_font + 1)
                << 5)
                ;

            u32 x__target_pixel =
                NDS_get_tile_pixel_x_from__i32(
                        x__source_pixel
                        + x__cursor
                        + p_font_letter
                            ->x__offset_of__font_letter);
            u32 y__target_pixel =
                NDS_get_tile_pixel_y_from__i32(
                        y__source_pixel
                        + y__cursor
                        + p_font_letter
                            ->y__offset_of__font_letter);
            u32 x__target_tile =
                (x__source_pixel
                 + x__cursor
                 + p_font_letter
                    ->x__offset_of__font_letter) >> 3;
            u32 y__target_tile =
                (y__source_pixel
                 + y__cursor
                 + p_font_letter
                    ->y__offset_of__font_letter) >> 3;

            u32 index_of__pixel_in__target_tile_8x8 =
                (x__target_pixel >> 1)
                + (y__target_pixel << 2)
                ;

            u32 index_of__tile_pixel__in_target =
                index_of__pixel_in__target_tile_8x8
                + ((x__target_tile) << 5)
                + ((y__target_tile) << 5)
                * width_in__tiles
                ;

            dmaCopy(
                    &p_src[index_of__source_pixel_in__font],
                    &p_dest[index_of__tile_pixel__in_target],
                    2);

            //p_dest[index_of__tile_pixel__in_target] = font_pixel;
        }
    }

    move_typer_cursor(
            p_typer, 
            p_font_letter);
}

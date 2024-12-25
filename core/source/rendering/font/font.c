#include "defines.h"
#include <rendering/font/font.h>
#include <rendering/font/font_letter.h>

void initialize_font__letter(
        Font_Letter *p_font_letter,
        Quantity__u8 width_of__font_letter,
        Quantity__u8 height_of__font_letter,
        Quantity__u8 x__offset_of__font_letter,
        Quantity__u8 y__offset_of__font_letter,
        Index__u16 index_of__character__in_font) {
    p_font_letter->width_of__font_letter =
        width_of__font_letter;
    p_font_letter->height_of__font_letter =
        height_of__font_letter;
    p_font_letter->x__offset_of__font_letter =
        x__offset_of__font_letter;
    p_font_letter->y__offset_of__font_letter =
        y__offset_of__font_letter;
    p_font_letter->index_of__character__in_font =
        index_of__character__in_font;
}

static inline
Font_Letter *get_p_font_letter_by__index_from__font(
        Font *p_font,
        Index__u32 index_of__font_letter) {
#ifndef NDEBUG
    if (FONT_LETTER_MAX_QUANTITY_OF
            <= index_of__font_letter) {
        debug_error("get_p_font_letter_by__index_from__font, index out of bounds: %d/%d",
                index_of__font_letter,
                FONT_LETTER_MAX_QUANTITY_OF);
        return 0;
    }
#endif

    return &p_font->font_lookup_table[index_of__font_letter];
}

void initialize_font(Font *p_font) {
    p_font->max_width_of__font_letter = 0;
    p_font->max_height_of__font_letter = 0;
    p_font->p_PLATFORM_texture_of__font = 0;
    p_font->font_flags = FONT_FLAGS__NONE;
    for (Index__u32 index_of__font_letter = 0;
            index_of__font_letter
            < FONT_LETTER_MAX_QUANTITY_OF;
            index_of__font_letter++) {
        Font_Letter *p_font_letter =
            get_p_font_letter_by__index_from__font(
                    p_font, 
                    index_of__font_letter);
        initialize_font__letter(
                p_font_letter, 
                0, 
                0, 
                0, 
                0, 
                0);
    }
}

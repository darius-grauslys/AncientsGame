#ifndef FONT_H
#define FONT_H

#include <defines.h>

void initialize_font__letter(
        Font_Letter *p_font_letter,
        Quantity__u8 width_of__font_letter,
        Quantity__u8 height_of__font_letter,
        Quantity__u8 x__offset_of__font_letter,
        Quantity__u8 y__offset_of__font_letter,
        Index__u16 index_of__character__in_font);

void initialize_font(Font *p_font);

static inline
Font_Letter *get_p_font_letter_from__font(
        Font *p_font,
        unsigned char letter) {
    return &p_font->font_lookup_table[letter];
}

static inline
bool is_font__allocated(Font *p_font) {
    return p_font->font_flags
        & FONT_FLAG__IS_ALLOCATED;
}

static inline
void set_font_as__deallocated(Font *p_font) {
    p_font->font_flags &=
        ~FONT_FLAG__IS_ALLOCATED;
}

static inline
void set_font_as__allocated(Font *p_font) {
    p_font->font_flags |=
        FONT_FLAG__IS_ALLOCATED;
}

#endif

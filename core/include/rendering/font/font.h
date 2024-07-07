#ifndef FONT_H
#define FONT_H

#include <defines.h>

static inline
Font_Letter *get_p_font_letter_from__font(
        Font *p_font,
        unsigned char letter) {
    return &p_font->font_lookup_table[letter];
}

#endif

#ifndef FONT_LETTER_H
#define FONT_LETTER_H

#include <defines.h>

#define DECLARE_FONT_LETTER(letter, width, height, x__offset, y__offset) \
    (Font_Letter){ width & MASK(4), \
        height & MASK(4), \
        (x__offset & MASK(4)), \
        (y__offset & MASK(4)), \
        letter }

#endif

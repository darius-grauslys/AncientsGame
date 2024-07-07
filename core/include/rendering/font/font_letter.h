#ifndef FONT_LETTER_H
#define FONT_LETTER_H

#include <defines.h>

#define DECLARE_FONT_LETTER(letter, width, height) \
    (Font_Letter){ ((width & MASK(4)) << 4) |\
        (height & MASK(4)), \
        letter }

#endif

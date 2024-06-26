#ifndef NDS_DEFINES_H
#define NDS_DEFINES_H

#include "defines_weak.h"
#define NDS_SPRITE_PALLETE__8x8 0
#define NDS_SPRITE_PALLETE__16x16 1

#define NDS_BACKGROUND_QUANTITY_OF__MAIN    4
#define NDS_BACKGROUND_QUANTITY_OF__SUB     4

typedef struct NDS_Sprite_Pallete_t {
    const uint16_t *p_pallete;
    Index__u8 pallete_slot;
    Quantity__u32 pallete_length;
} NDS_Sprite_Pallete;

#define NDS_PALLETE_SLOT__0 0
#define NDS_PALLETE_SLOT__1 1

#define NDS_SPRITE_PALLETE_QUANTITY_OF_FOR__DEFAULT 2

#endif

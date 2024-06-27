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

#define NDS_BACKGROUND_SLOT__GAME__GROUND 0
#define NDS_BACKGROUND_SLOT__GAME__WALL_UPPER 1
#define NDS_BACKGROUND_SLOT__GAME__WALL_LOWER 2

///
/// For hud, and UI that resides above ui_sprites
///
#define NDS_BACKGROUND_SLOT__UI__BASE 0

///
/// For UI that resides beneath ui_sprites, but doesn't scroll.
///
#define NDS_BACKGROUND_SLOT__UI__SUB_BASE 1

///
/// For UI that involves constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_UPPER 2

///
/// For UI that extends constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_LOWER 3

///
/// For UI that requires scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL 2

///
/// For a separate UI background that also needs scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL_SECONDARY 3

///
/// The only background slot available for the typer background.
///
#define NDS_BACKGROUND_SLOT__UI__TYPER 1

#endif

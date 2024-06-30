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

#define NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE 4

enum NDS_UI_Background_Allocation_Kind {
    NDS_UI_Background_Allocation_Kind__None=0,
    NDS_UI_Background_Allocation_Kind__Base,
    NDS_UI_Background_Allocation_Kind__Sub_Base,
    NDS_UI_Background_Allocation_Kind__Log_Upper,
    NDS_UI_Background_Allocation_Kind__Log_Lower,
    NDS_UI_Background_Allocation_Kind__Scroll,
    NDS_UI_Background_Allocation_Kind__Scroll_Secondary,
    NDS_UI_Background_Allocation_Kind__Typer,
};

typedef struct NDS_Background_Allocation_Specification_t {
    enum NDS_UI_Background_Allocation_Kind the_kind_of__ui_background_allocation;
    Index__u8 background_slot;

    const unsigned int *p_gfx_background;
    const uint16_t *p_map_background;
    Quantity__u32 length_of__p_background_gfx;
    Quantity__u32 length_of__p_background_map;
    Index__u8 priority_of__background;
} NDS_Background_Allocation_Specification;

typedef struct NDS_Background_Engine_Allocation_Context_t {
    NDS_Background_Allocation_Specification
        nds_background_allocation_specifications[
            NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE];
    //TODO: We will MOST likely need to make
    //extended background palletes a thing.
    const uint16_t *pal_background;
    Quantity__u16 length_of__background_pal;
} NDS_Background_Engine_Allocation_Context;

///
/// For hud, and specifies an unused background
///
#define NDS_BACKGROUND_SLOT__UI__NONE 0
#define NDS_BACKGROUND_PRIORITY__UI__NONE 0

///
/// For hud, and UI that resides above ui_sprites
///
#define NDS_BACKGROUND_SLOT__UI__BASE 0
#define NDS_BACKGROUND_PRIORITY__UI__BASE 2

///
/// For UI that resides beneath ui_sprites, but doesn't scroll.
///
#define NDS_BACKGROUND_SLOT__UI__SUB_BASE 1
#define NDS_BACKGROUND_PRIORITY__UI__SUB_BASE 1

///
/// For UI that involves constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_UPPER 2
#define NDS_BACKGROUND_PRIORITY__UI__LOG_UPPER 0

///
/// For UI that extends constantly changing text.
///
#define NDS_BACKGROUND_SLOT__UI__LOG_LOWER 3
#define NDS_BACKGROUND_PRIORITY__UI__LOG_LOWER 0

///
/// For UI that requires scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL 2
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL 0

///
/// For a separate UI background that also needs scrolling.
///
#define NDS_BACKGROUND_SLOT__UI__SCROLL_SECONDARY 3
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL_SECONDARY 0

///
/// The only background slot available for the typer background.
///
#define NDS_BACKGROUND_SLOT__UI__TYPER 1
#define NDS_BACKGROUND_PRIORITY__UI__SCROLL_TYPER 0

#endif

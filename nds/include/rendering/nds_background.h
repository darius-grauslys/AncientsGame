#ifndef NDS_BACKGROUND_H
#define NDS_BACKGROUND_H

#include "defines.h"
#include "defines_weak.h"
#include <nds_defines.h>

void NDS_initialize_background(
        NDS_Background *background,
        Signed_Index__i8 background_index_for__initializer);

void NDS_initialize_background_for__world_ground(
        NDS_Background *background);

void NDS_initialize_background_for__world_wall_lower(
        NDS_Background *background);

void NDS_initialize_background_for__world_wall_upper(
        NDS_Background *background);

void NDS_initialize_background_with__allocation_specification(
        NDS_Background *p_background,
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification);

void NDS_set_background_priority(
        NDS_Background *background,
        uint32_t priority);

static inline
bool NDS_does_background_have__enough_tiles_in__reserve(
        NDS_Background *p_NDS_background,
        Quantity__u16 quantity_of__tiles_to_reserve) {
    return p_NDS_background->quantity_of__tiles_allocated_in__reserve
        <= quantity_of__tiles_to_reserve;
}

bool NDS_copy_tiles_into__reserved_tiles_of__background(
        NDS_Background *p_NDS_background,
        i32 x, i32 y,
        Quantity__u32 width,
        Quantity__u32 height);

static inline
uint16_t *NDS_get_reserved_tile_as__p_u16_from__background(
        NDS_Background *p_NDS_background,
        i32 x, i32 y,
        Quantity__u32 width) {
    return &p_NDS_background
        ->gfx_tileset[x + y * width +
        p_NDS_background->quantity_of__tiles_allocated];
}


static inline
i32 NDS_get_tile_x_from__i32(i32 x__i32) {
    return (x__i32 >> 3) + (bool)(x__i32 & MASK(3));
}

static inline
i32 NDS_get_tile_y_from__i32(i32 y__i32) {
    return (y__i32 >> 3) + (bool)(y__i32 & MASK(3));
}

static inline
i32 NDS_get_tile_pixel_x_from__i32(i32 x__i32) {
    return (x__i32 & MASK(3));
}

static inline
i32 NDS_get_tile_pixel_y_from__i32(i32 y__i32) {
    return (y__i32 & MASK(3));
}

static inline
void NDS_set_scrolling_starting_position_3i32_of__background(
        NDS_Background *p_NDS_background,
        Vector__3i32 starting_position__3i32) {
    p_NDS_background->starting_position__3i32 =
        starting_position__3i32;
}

static inline
void NDS_set_spanning_scroll_lengths_3i32_of__background(
        NDS_Background *p_NDS_background,
        Vector__3i32 spanning_scroll_lengths__3i32) {
    p_NDS_background->spanning_scroll_lengths__3i32 =
        spanning_scroll_lengths__3i32;
}

#endif

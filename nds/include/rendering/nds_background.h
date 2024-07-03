#ifndef NDS_BACKGROUND_H
#define NDS_BACKGROUND_H

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

#ifndef NDS_BACKGROUND_ALLOCATION_SPECIFICATION_H
#define NDS_BACKGROUND_ALLOCATION_SPECIFICATION_H

#include "defines_weak.h"
#include "nds_defines.h"

extern const NDS_Background_Allocation_Specification
        nds_background_allocation_specification__none;

void NDS_initialize_background_allocation_specification(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        enum NDS_Background_Allocation_Kind the_kind_of__background_allocation,
        Texture_Flags backgrond_texture_flags,
        Index__u8 background_slot,
        Vector__3i32 starting_position__3i32,
        Vector__3i32 spanning_length__3i32,
        const unsigned int *p_gfx_background,
        Quantity__u32 length_of__p_background_gfx,
        const uint16_t *p_map_background,
        Quantity__u32 length_of__p_background_map,
        const uint16_t *p_pal_background,
        Quantity__u32 length_of__p_background_pal,
        Index__u8 priority);

///
// Use this initializer if later on additional graphics, map tiles
// and or pallete colors are needed. Example: Typer.c typing onto
// background graphics.
///
void NDS_initialize_background_allocation_specification_with__reservations(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        enum NDS_Background_Allocation_Kind the_kind_of__background_allocation,
        Texture_Flags backgrond_texture_flags,
        Index__u8 background_slot,
        Vector__3i32 starting_position__3i32,
        Vector__3i32 spanning_length__3i32,
        const unsigned int *p_gfx_background,
        Quantity__u32 length_of__p_gfx_background,
        Quantity__u32 length_of__p_gfx_background__reservation,
        const uint16_t *p_map_background,
        Quantity__u32 length_of__p_map_background,
        Quantity__u32 length_of__p_map_background__reservation,
        const uint16_t *p_pal_background,
        Quantity__u32 length_of__p_pal_background,
        Quantity__u32 length_of__p_pal_background__reservation,
        Index__u8 priority);

#endif

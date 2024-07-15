#include "defines_weak.h"
#include "numerics.h"
#include "vectors.h"
#include <rendering/nds_background_allocation_specification.h>

const NDS_Background_Allocation_Specification
        nds_background_allocation_specification__none = {
            VECTOR__OUT_OF_BOUNDS,
            VECTOR__OUT_OF_BOUNDS,
            NDS_UI_Background_Allocation_Kind__None, 0,
            0, 0, 0, 0, 0, 0, 0
        };

void NDS_initialize_background_allocation_specification(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        enum NDS_Background_Allocation_Kind the_kind_of__background_allocation,
        Texture_Flags background_texture_flags,
        Index__u8 background_slot,
        Vector__3i32 starting_position__3i32,
        Vector__3i32 spanning_length__3i32,
        const unsigned int *p_gfx_background,
        Quantity__u32 length_of__p_gfx_background,
        const uint16_t *p_map_background,
        Quantity__u32 length_of__p_map_background,
        const uint16_t *p_pal_background,
        Quantity__u32 length_of__p_pal_background,
        Index__u8 priority) {

    clamp__p_u8(&priority, 0, 3);
    p_NDS_background_allocation_specification
        ->the_kind_of__background_allocation =
        the_kind_of__background_allocation;
    p_NDS_background_allocation_specification
        ->background_texture_flags =
        background_texture_flags;
    p_NDS_background_allocation_specification
        ->background_slot = background_slot;
    p_NDS_background_allocation_specification
        ->starting_position__3i32 =
        starting_position__3i32;
    p_NDS_background_allocation_specification
        ->spanning_scroll_lengths__3i32 =
        spanning_length__3i32;

    p_NDS_background_allocation_specification
        ->p_gfx_background = p_gfx_background;
    p_NDS_background_allocation_specification
        ->length_of__p_gfx_background = 
        length_of__p_gfx_background;
    p_NDS_background_allocation_specification
        ->p_map_background = p_map_background;
    p_NDS_background_allocation_specification
        ->length_of__p_map_background = 
        length_of__p_map_background;
    p_NDS_background_allocation_specification
        ->p_pal_background = p_pal_background;
    p_NDS_background_allocation_specification
        ->length_of__p_pal_background = 
        length_of__p_pal_background;
    p_NDS_background_allocation_specification
        ->priority_of__background = priority;

    p_NDS_background_allocation_specification
        ->length_of__p_gfx_background__reservation = 0;
    p_NDS_background_allocation_specification
        ->length_of__p_map_background__reservation = 0;
    p_NDS_background_allocation_specification
        ->length_of__p_pal_background__reservation = 0;
}

void NDS_initialize_background_allocation_specification_with__reservations(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        enum NDS_Background_Allocation_Kind the_kind_of__background_allocation,
        Texture_Flags background_texture_flags,
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
        Index__u8 priority) {

    NDS_initialize_background_allocation_specification(
            p_NDS_background_allocation_specification, 
            the_kind_of__background_allocation, 
            background_texture_flags,
            background_slot, 
            starting_position__3i32,
            spanning_length__3i32,
            p_gfx_background, 
            length_of__p_gfx_background, 
            p_map_background, 
            length_of__p_map_background, 
            p_pal_background, 
            length_of__p_pal_background, 
            priority);

    p_NDS_background_allocation_specification
        ->length_of__p_gfx_background__reservation =
        length_of__p_gfx_background__reservation;
    p_NDS_background_allocation_specification
        ->length_of__p_map_background__reservation =
        length_of__p_map_background__reservation;
    p_NDS_background_allocation_specification
        ->length_of__p_pal_background__reservation =
        length_of__p_pal_background__reservation;
}

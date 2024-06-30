#include "defines_weak.h"
#include "numerics.h"
#include <rendering/nds_background_allocation_specification.h>

const NDS_Background_Allocation_Specification
        nds_background_allocation_specification__none = {
            NDS_UI_Background_Allocation_Kind__None, 0,
            0, 0, 0, 0, 0, 0, 0
        };

void NDS_initialize_background_allocation_specification(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        enum NDS_Background_Allocation_Kind the_kind_of__background_allocation,
        Index__u8 background_slot,
        const unsigned int *p_gfx_background,
        Quantity__u32 length_of__p_background_gfx,
        const uint16_t *p_map_background,
        Quantity__u32 length_of__p_background_map,
        const uint16_t *p_pal_background,
        Quantity__u32 length_of__p_background_pal,
        Index__u8 priority) {
    clamp__p_u8(&priority, 0, 3);
    p_NDS_background_allocation_specification
        ->the_kind_of__background_allocation =
        the_kind_of__background_allocation;
    p_NDS_background_allocation_specification
        ->background_slot = background_slot;
    p_NDS_background_allocation_specification
        ->p_gfx_background = p_gfx_background;
    p_NDS_background_allocation_specification
        ->length_of__p_background_gfx = length_of__p_background_gfx;
    p_NDS_background_allocation_specification
        ->p_map_background = p_map_background;
    p_NDS_background_allocation_specification
        ->length_of__p_background_map = length_of__p_background_map;
    p_NDS_background_allocation_specification
        ->p_pal_background = p_pal_background;
    p_NDS_background_allocation_specification
        ->length_of__p_background_pal = length_of__p_background_pal;
    p_NDS_background_allocation_specification
        ->priority_of__background = priority;
}

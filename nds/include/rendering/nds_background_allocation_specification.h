#ifndef NDS_BACKGROUND_ALLOCATION_SPECIFICATION_H
#define NDS_BACKGROUND_ALLOCATION_SPECIFICATION_H

#include "defines_weak.h"
#include "nds_defines.h"

extern const NDS_Background_Allocation_Specification
        nds_background_allocation_specification__none;

void NDS_initialize_background_allocation_specification(
        NDS_Background_Allocation_Specification
            *p_NDS_background_allocation_specification,
        Index__u8 background_slot,
        const unsigned int *p_gfx_background,
        Quantity__u32 length_of__p_background_gfx,
        const uint16_t *p_map_background,
        Quantity__u32 length_of__p_background_map,
        Index__u8 priority);

#endif

#ifndef NDS_BACKGROUND_H
#define NDS_BACKGROUND_H

#include "defines_weak.h"
#include <defines.h>

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

#endif

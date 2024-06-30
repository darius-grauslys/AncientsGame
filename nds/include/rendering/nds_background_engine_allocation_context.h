#ifndef NDS_BACKGROUND_ENGINE_ALLOCATION_CONTEXT_H
#define NDS_BACKGROUND_ENGINE_ALLOCATION_CONTEXT_H

#include "defines_weak.h"
#include <nds_defines.h>

bool NDS_does_NOT_bg_alloc_spec_share__palette_with__another_bg_alloc_spec(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context);

bool NDS_does_NOT_bg_alloc_spec_have_shared_map_offset(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context);

bool NDS_does_NOT_bg_alloc_spec__shared_tileset_offset(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context);

void NDS_initialize_background_engine_allocation_context(
        NDS_Background_Engine_Allocation_Context
            *p_NDS_background_engine_allocation_context,
        enum UI_Window_Kind the_kind_of__ui_window_to__allocate_for);

#endif

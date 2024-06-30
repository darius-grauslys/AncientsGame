#ifndef NDS_BACKGROUND_ENGINE_ALLOCATION_CONTEXT_H
#define NDS_BACKGROUND_ENGINE_ALLOCATION_CONTEXT_H

#include "defines_weak.h"
#include <nds_defines.h>

void NDS_initialize_background_engine_allocation_context(
        NDS_Background_Engine_Allocation_Context
            *p_NDS_background_engine_allocation_context,
        enum UI_Window_Kind the_kind_of__ui_window_to__allocate_for);

#endif

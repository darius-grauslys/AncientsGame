#ifndef NDS_UI__LOG_H
#define NDS_UI__LOG_H

#include "defines_weak.h"
#include <defines.h>

void NDS_initialize_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

///
/// Only invoke this if there is a new message
/// and do so prior to flushing the message.
///
void NDS_update_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Log *p_log);

void NDS_clear_log(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

#endif

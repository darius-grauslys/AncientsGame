#ifndef NDS_UI__TYPER_H
#define NDS_UI__TYPER_H

#include "defines_weak.h"
#include <defines.h>

void NDS_initialize_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

void NDS_update_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Log *p_log);

void NDS_clear_typer(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

#endif

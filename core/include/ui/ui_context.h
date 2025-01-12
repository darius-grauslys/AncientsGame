#ifndef UI_CONTEXT_H
#define UI_CONTEXT_H

#include "defines.h"

void initialize_ui_context(UI_Context *p_ui_context);

void register_ui_window_into__ui_context(
        UI_Context *p_ui_context,
        UI_Window_Record *p_ui_window_record,
        Graphics_Window_Kind the_kind_of__window);

Graphics_Window *open_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        Graphics_Window_Kind the_kind_of__window_to__open);

void close_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        Graphics_Window_Kind the_kind_of__window_to__close);

#endif

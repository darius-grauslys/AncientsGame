#ifndef UI_CONTEXT_H
#define UI_CONTEXT_H

#include "defines.h"

void initialize_ui_context(UI_Context *p_ui_context);

void register_ui_window__loader_into__ui_context(
        UI_Context *p_ui_context,
        f_UI_Window__Load f_ui_window__load,
        Graphics_Window_Kind the_kind_of__window);

void register_ui_window__closer_into__ui_context(
        UI_Context *p_ui_context,
        f_UI_Window__Close f_ui_window__close,
        Graphics_Window_Kind the_kind_of__window);

Graphics_Window *open_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        World *p_world,
        Graphics_Window_Kind the_kind_of__window_to__open);

void close_ui(
        Gfx_Context *p_gfx_context,
        UI_Manager *p_ui_manager,
        World *p_world,
        Graphics_Window_Kind the_kind_of__window_to__close);

#endif

#ifndef GRAPHICS_WINDOW_MANAGER_H
#define GRAPHICS_WINDOW_MANAGER_H

#include "defines.h"
#include "defines_weak.h"

void initialize_graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager);

bool allocate_graphics_window_with__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window__Wrapper *p_graphics_window__wrapper);

void set_graphics_window_as__parent_to__this_graphics_window(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window__Wrapper *p_graphics_window__wrapper__parent,
        Graphics_Window__Wrapper *p_graphics_window__wrapper__child);

void release_graphics_window_from__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window__Wrapper *p_graphics_window__wrapper);

bool get_graphics_windows_from__graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window__Wrapper *p_graphics_window__wrapper,
        Quantity__u8 max_quantity_of__windows,
        Graphics_Window_Kind the_kind_of__graphics_window);

#endif

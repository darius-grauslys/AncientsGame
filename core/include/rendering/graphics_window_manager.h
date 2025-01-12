#ifndef GRAPHICS_WINDOW_MANAGER_H
#define GRAPHICS_WINDOW_MANAGER_H

#include "defines.h"
#include "defines_weak.h"

void initialize_graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager);

Graphics_Window *allocate_graphics_window_with__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window_Manager *p_graphics_window_manager,
        Texture_Flags texture_flags_for__gfx_window);

void set_graphics_window_as__parent_to__this_graphics_window(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window *p_graphics_window__parent,
        Graphics_Window *p_graphics_window__child);

void release_graphics_window_from__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_graphics_window);

Quantity__u8 get_graphics_windows_from__graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window **p_ptr_array__graphics_windows,
        Quantity__u8 max_quantity_of__windows,
        Graphics_Window_Kind the_kind_of__graphics_window);

#endif

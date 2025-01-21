#include "rendering/graphics_window_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/graphics_window.h"
#include "util/bitmap/bitmap.h"

static inline
Graphics_Window *get_p_graphics_window_by__index_from__manager(
        Graphics_Window_Manager *p_graphics_window_manager,
        Index__u32 index_of__graphics_window) {
    if (MAX_QUANTITY_OF__GRAPHICS_WINDOWS <=
            index_of__graphics_window) {
        debug_error("get_p_graphics_window_by__index_from__manager, index out of range: %d/%d",
                index_of__graphics_window,
                MAX_QUANTITY_OF__GRAPHICS_WINDOWS);
        return 0;
    }
    return &p_graphics_window_manager->graphics_windows[
        index_of__graphics_window];
}

void initialize_graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager) {
    for(Index__u32 index_of__graphics_window = 0;
            index_of__graphics_window
            < MAX_QUANTITY_OF__GRAPHICS_WINDOWS;
            index_of__graphics_window++) {
        Graphics_Window *p_graphics_window =
            get_p_graphics_window_by__index_from__manager(
                    p_graphics_window_manager, 
                    index_of__graphics_window);
        initialize_graphics_window(
                p_graphics_window);
    }
}

Graphics_Window *allocate_graphics_window_with__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window_Manager *p_graphics_window_manager,
        Texture_Flags texture_flags_for__gfx_window) {
    Graphics_Window *p_graphics_window__available = 0;

    for (Index__u32 index_of__graphics_window = 0;
            index_of__graphics_window
            < MAX_QUANTITY_OF__GRAPHICS_WINDOWS;
            index_of__graphics_window++) {
        Graphics_Window *p_graphics_window =
            get_p_graphics_window_by__index_from__manager(
                    p_graphics_window_manager, 
                    index_of__graphics_window);

        if (is_graphics_window__allocated(p_graphics_window))
            continue;

        p_graphics_window__available = p_graphics_window;
        break;
    }

    if (!p_graphics_window__available) {
        debug_error("allocate_graphics_window_with__graphics_window_manager, graphics window limit reached.");
        return 0;
    }

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
        PLATFORM_allocate_gfx_window(
                p_gfx_context, 
                texture_flags_for__gfx_window);

    if (!p_PLATFORM_gfx_window) {
        debug_error("allocate_graphics_window_with__graphics_window_manager, failed to allocate PLATFORM_gfx_window.");
        return 0;
    }

    p_graphics_window__available
        ->p_PLATFORM_gfx_window = 
        p_PLATFORM_gfx_window;

    return p_graphics_window__available;
}

static inline
bool is_graphics_window_kind_NOT_in__bounds(
        Graphics_Window_Kind the_kind_of__graphics_window) {
    bool failure = the_kind_of__graphics_window
            >= Graphics_Window_Kind__Unknown;
    if (failure) {
        debug_error("is_graphics_window_kind_NOT_in__bounds, the_kind_of__graphics_window_to__allocate out of range: %d/%d.",
                the_kind_of__graphics_window,
                Graphics_Window_Kind__Unknown);
    }
    return failure;
}

static inline
bool is_graphics_window_NOT_from__this_graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window *p_graphics_window) {
    Index__u32 index = p_graphics_window - p_graphics_window_manager->graphics_windows;

    bool failure = index >= MAX_QUANTITY_OF__GRAPHICS_WINDOWS;

    if (failure) {
        debug_error("is_graphics_window_NOT_from__this_graphics_window_manager, provided graphics_window is not from this graphics_window_manager.");
    }

    return failure;
}

void set_graphics_window_as__parent_to__this_graphics_window(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window *p_graphics_window__parent,
        Graphics_Window *p_graphics_window__child) {
    if (is_graphics_window_NOT_from__this_graphics_window_manager(
                p_graphics_window_manager, 
                p_graphics_window__child)) {
        debug_error("set_graphics_window_as__parent_to__this_graphics_window, p_graphics_window__child is not from this graphics_window_manager.");
        return;
    }
    if (is_graphics_window_NOT_from__this_graphics_window_manager(
                p_graphics_window_manager, 
                p_graphics_window__parent)) {
        debug_error("set_graphics_window_as__parent_to__this_graphics_window, p_graphics_window__parent is not from this graphics_window_manager.");
        return;
    }

    if (is_graphics_window_possessing__a_child(
                p_graphics_window__parent)) {
        debug_error("set_graphics_window_as__parent_to__this_graphics_window, parent already possesses a child.");
        return;
    }

    for (Index__u32 index_of__graphics_window = 0;
            index_of__graphics_window
            < MAX_QUANTITY_OF__GRAPHICS_WINDOWS;
            index_of__graphics_window++) {
        Graphics_Window *p_graphics_window =
            get_p_graphics_window_by__index_from__manager(
                    p_graphics_window_manager, 
                    index_of__graphics_window);

        if (is_graphics_window_a__child_of__this_graphics_window(
                    p_graphics_window__child, 
                    p_graphics_window__parent)) {
            debug_error("set_graphics_window_as__parent_to__this_graphics_window, child is already assigned to another parent.");
            return;
        }
    }

    p_graphics_window__parent->p_child__graphics_window =
        p_graphics_window__child;
}

void release_graphics_window_from__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_graphics_window) {
    if (is_graphics_window_possessing__a_child(
                p_graphics_window)) {
        release_graphics_window_from__graphics_window_manager(
                p_gfx_context, 
                p_graphics_window);
    }
    
    PLATFORM_release_gfx_window(
            p_gfx_context, 
            p_graphics_window);
    initialize_graphics_window(
            p_graphics_window);
}

Quantity__u8 get_graphics_windows_from__graphics_window_manager(
        Graphics_Window_Manager *p_graphics_window_manager,
        Graphics_Window **p_ptr_array__graphics_windows,
        Quantity__u8 max_quantity_of__windows,
        Graphics_Window_Kind the_kind_of__graphics_window) {
    Index__u8 index_of__gfx_window_in__ptr_array = 0;
    if (!max_quantity_of__windows)
        return 0;
    for (Index__u32 index_of__graphics_window = 0;
            index_of__graphics_window
            < MAX_QUANTITY_OF__GRAPHICS_WINDOWS;
            index_of__graphics_window++) {
        Graphics_Window *p_graphics_window =
            get_p_graphics_window_by__index_from__manager(
                    p_graphics_window_manager, 
                    index_of__graphics_window);

        if (!is_graphics_window_of__this_kind(
                    p_graphics_window, 
                    the_kind_of__graphics_window)) {
            continue;
        }

        p_ptr_array__graphics_windows[
            index_of__gfx_window_in__ptr_array++] =
            p_graphics_window;

        if (index_of__gfx_window_in__ptr_array
                >= max_quantity_of__windows) {
            return index_of__graphics_window;
        }
    }
    
    return index_of__gfx_window_in__ptr_array;
}

void render_graphic_windows_in__graphics_window_manager(
        Gfx_Context *p_gfx_context,
        Graphics_Window_Manager *p_graphics_window__manager,
        World *p_world) {
    BITMAP(bitmap__gfx_windows__visited, MAX_QUANTITY_OF__GRAPHICS_WINDOWS);
    memset(
            bitmap__gfx_windows__visited, 
            0, 
            sizeof(bitmap__gfx_windows__visited));

    for (Index__u32 index_of__graphics_window = 0;
            index_of__graphics_window 
            < MAX_QUANTITY_OF__GRAPHICS_WINDOWS;
            index_of__graphics_window++) {
        Graphics_Window *p_gfx_window =
            get_p_graphics_window_by__index_from__manager(
                    p_graphics_window__manager, 
                    index_of__graphics_window);
        if (!is_graphics_window__allocated(
                    p_gfx_window)) {
            continue;
        }
        if (is_bit_set_in__bitmap(
                    bitmap__gfx_windows__visited, 
                    MAX_QUANTITY_OF__GRAPHICS_WINDOWS, 
                    index_of__graphics_window)) {
            continue;
        }

        PLATFORM_render_gfx_window(
                p_gfx_context, 
                p_gfx_window, 
                0, 
                p_world);

        if (is_graphics_window_possessing__a_child(
                    p_gfx_window)) {
            set_bit_in__bitmap(
                    bitmap__gfx_windows__visited, 
                    MAX_QUANTITY_OF__GRAPHICS_WINDOWS, 
                    p_gfx_window->p_child__graphics_window
                    - p_graphics_window__manager->graphics_windows, 
                    true);
            PLATFORM_render_gfx_window(
                    p_gfx_context, 
                    p_gfx_window->p_child__graphics_window, 
                    p_gfx_window, 
                    p_world);
        }
    }
}

#include "rendering/sdl_gfx_window_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/texture.h"
#include "sdl_defines.h"
#include "ui/ui_manager.h"
#include "ui/ui_tile_map.h"
#include "ui/ui_tile_map_manager.h"
#include "vectors.h"

static inline
PLATFORM_Graphics_Window *SDL_get_p_PLATFORM_gfx_window_by__index_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager,
        Index__u32 index_of__gfx_window) {
#ifndef NDEBUG
    if (index_of__gfx_window
            >= PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF) {
        debug_error("SDL_get_p_PLATFORM_gfx_window_by__type_from__manager, index out of bounds.");
        return 0;
    }
#endif

    return &p_SDL_gfx_window_manager
        ->SDL_gfx_windows[index_of__gfx_window];
}

void SDL_initialize_gfx_window_manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager) {
    for (Index__u32 index_of__gfx_window = 0;
            index_of__gfx_window
            < PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF;
            index_of__gfx_window++) {
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
            SDL_get_p_PLATFORM_gfx_window_by__index_from__manager(
                    p_SDL_gfx_window_manager, 
                    index_of__gfx_window);

        SDL_initialize_gfx_window_as__deallocated(
                p_PLATFORM_gfx_window);
    }
}

PLATFORM_Graphics_Window *SDL_allocate_PLATFORM_gfx_window_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager) {
    for (Index__u32 index_of__gfx_window = 0;
            index_of__gfx_window
            < PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF;
            index_of__gfx_window++) {
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
            SDL_get_p_PLATFORM_gfx_window_by__index_from__manager(
                    p_SDL_gfx_window_manager, 
                    index_of__gfx_window);

        if (SDL_is_gfx_window__allocated(
                    p_PLATFORM_gfx_window)) {
            continue;
        }

        SDL_set_gfx_window_as__allocated(
                p_PLATFORM_gfx_window);

        return p_PLATFORM_gfx_window;
    }

    return 0;
}

void SDL_release_PLATFORM_gfx_window_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
#ifndef NDEBUG
    uint index = p_PLATFORM_gfx_window
        - p_SDL_gfx_window_manager->SDL_gfx_windows
        ;
    if (index 
            >= PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF) {
        debug_error("SDL_release_PLATFORM_gfx_window_from__manager, p_PLATFORM_gfx_window was not allocated by this manager.");
        return;
    }
#endif

    SDL_initialize_gfx_window_as__deallocated(
            p_PLATFORM_gfx_window);
}

// TODO: move alloc/release into a manager, and take
// that mngr as a pointer parameter
PLATFORM_Graphics_Window *SDL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {

    f_SDL_Allocate_Gfx_Window f_SDL_allocate_gfx_window =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_allocate_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_allocate_gfx_window, f_SDL_allocate_gfx_window == 0.");
        return 0;
    }
#endif

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
        SDL_allocate_PLATFORM_gfx_window_from__manager(
                SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context));

    if (!p_PLATFORM_gfx_window) {
        debug_error("SDL_allocate_gfx_window, failed to allocate window from manager. Is the manager full?");
        return 0;
    }

    SDL_initialize_gfx_window(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_gfx_window, 
            UI_Window_Kind__Unknown, 
            VECTOR__3i32F4__0_0_0);

    f_SDL_allocate_gfx_window(
            p_PLATFORM_gfx_context,
            p_PLATFORM_gfx_window,
            p_texture_allocation_specification);

    // TODO:    maybe we can do this better, issue being is what if
    //          we change the engine profile such that these cases no longer hold?
    switch (get_texture_size_from__texture_allocation_specification(
                p_texture_allocation_specification)) {
        default:
            debug_error("SDL_allocate_gfx_window, unknown texture size.");
            break;
        case TEXTURE_FLAG__SIZE_8x8:
        case TEXTURE_FLAG__SIZE_8x16:
        case TEXTURE_FLAG__SIZE_8x32:
        case TEXTURE_FLAG__SIZE_16x8:
        case TEXTURE_FLAG__SIZE_16x16:
        case TEXTURE_FLAG__SIZE_16x32:
        case TEXTURE_FLAG__SIZE_32x16:
        case TEXTURE_FLAG__SIZE_32x32:
        case TEXTURE_FLAG__SIZE_32x64:
        case TEXTURE_FLAG__SIZE_64x64:
            p_PLATFORM_gfx_window
                ->SDL_graphics_window__ui_tile_map__wrapper =
                allocate_ui_tile_map_with__ui_tile_map_manager(
                        SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
                            p_PLATFORM_gfx_context), 
                        UI_Tile_Map_Size__Small);
            break;
        case TEXTURE_FLAG__SIZE_128x128:
            p_PLATFORM_gfx_window
                ->SDL_graphics_window__ui_tile_map__wrapper =
                allocate_ui_tile_map_with__ui_tile_map_manager(
                        SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
                            p_PLATFORM_gfx_context), 
                        UI_Tile_Map_Size__Medium);
            break;
        case TEXTURE_FLAG__SIZE_256x256:
        case TEXTURE_FLAG__SIZE_256x512:
        case TEXTURE_FLAG__SIZE_512x256:
        case TEXTURE_FLAG__SIZE_512x512:
            p_PLATFORM_gfx_window
                ->SDL_graphics_window__ui_tile_map__wrapper =
                allocate_ui_tile_map_with__ui_tile_map_manager(
                        SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
                            p_PLATFORM_gfx_context), 
                        UI_Tile_Map_Size__Large);
            break;
    }

    Texture_Flags texture_flags =
        get_texture_flags_from__texture_allocation_specification(
                p_texture_allocation_specification);

    set_ui_tile_map__wrapper__utilized_size(
            &p_PLATFORM_gfx_window
            ->SDL_graphics_window__ui_tile_map__wrapper, 
            get_length_of__texture_flag__width(
                texture_flags)
            / TILE_WIDTH__IN_PIXELS, 
            get_length_of__texture_flag__height(
                texture_flags)
            / TILE_WIDTH__IN_PIXELS);

    debug_info(">> SIZE: %d, %d",
            get_length_of__texture_flag__width(
                texture_flags)
            / TILE_WIDTH__IN_PIXELS, 
            get_length_of__texture_flag__height(
                texture_flags)
            / TILE_WIDTH__IN_PIXELS);

    return p_PLATFORM_gfx_window;
}

void SDL_release_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context = 
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    f_SDL_Release_Gfx_Window f_SDL_release_gfx_window =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_release_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_release_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_release_gfx_window, f_SDL_release_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_release_gfx_window(
            p_PLATFORM_gfx_context,
            p_PLATFORM_gfx_window);

    release_ui_tile_map_with__ui_tile_map_manager(
            SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context), 
            p_PLATFORM_gfx_window
            ->SDL_graphics_window__ui_tile_map__wrapper);

    release_all__ui_elements_from__ui_manager(
            PLATFORM_get_p_ui_manager_from__gfx_window(
                p_PLATFORM_gfx_window), 
            p_game);

    SDL_release_PLATFORM_gfx_window_from__manager(
            SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context), 
            p_PLATFORM_gfx_window);
}

Signed_Quantity__i32 SDL_get_p_PLATFORM_gfx_windows_by__type_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager,
        UI_Window_Kind the_kind_of__window_to__get,
        PLATFORM_Graphics_Window **p_PLATFORM_gfx_windows,
        Quantity__u32 size_of__ptr_buffer) {
    Signed_Quantity__i32 quantity_of__gfx_windows = 0;
    memset(
            p_PLATFORM_gfx_windows,
            0,
            sizeof(PLATFORM_Graphics_Window*)
            * size_of__ptr_buffer);
    for (Index__u32 index_of__gfx_window = 0;
            index_of__gfx_window
            < PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF;
            index_of__gfx_window++) {
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
            SDL_get_p_PLATFORM_gfx_window_by__index_from__manager(
                    p_SDL_gfx_window_manager, 
                    index_of__gfx_window);

        if (!SDL_is_gfx_window__allocated(
                    p_PLATFORM_gfx_window)) {
            continue;
        }

        if (!SDL_is_gfx_window_of__this_ui_window_kind(
                    p_PLATFORM_gfx_window, 
                    the_kind_of__window_to__get)
            && the_kind_of__window_to__get
            != UI_Window_Kind__Unknown) {
            continue;
        }

        if (quantity_of__gfx_windows
                >= size_of__ptr_buffer) {
            return -1;
        }

        p_PLATFORM_gfx_windows[
            quantity_of__gfx_windows] =
                p_PLATFORM_gfx_window;
        quantity_of__gfx_windows++;
    }

    return quantity_of__gfx_windows;
}

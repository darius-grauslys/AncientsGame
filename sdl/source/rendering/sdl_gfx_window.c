#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_sprite.h"
#include "rendering/texture.h"
#include "sdl_defines.h"
#include "ui/ui_tile_map_manager.h"
#include <rendering/sdl_gfx_window.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        UI_Window_Kind the_kind_of__ui_window) {
    p_PLATFORM_gfx_window
        ->p_PLATFORM_gfx_context =
        p_PLATFORM_gfx_context
        ;
    // TODO: initialize texture as deallocated
    p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__data = 0;
    p_PLATFORM_gfx_window
        ->is_allocated = false;
    p_PLATFORM_gfx_window
        ->the_kind_of__ui_window =
        the_kind_of__ui_window;
}

// TODO: move alloc/release into a manager, and take
// that mngr as a pointer parameter
void SDL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
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
        return;
    }
#endif

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
        case TEXTURE_FLAG__SIZE_256x256:
            p_PLATFORM_gfx_window
                ->SDL_graphics_window__ui_tile_map__wrapper =
                allocate_ui_tile_map_with__ui_tile_map_manager(
                        SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
                            p_PLATFORM_gfx_context), 
                        UI_Tile_Map_Size__Medium);
            break;
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
}

void SDL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {

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
}

void SDL_compose_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    f_SDL_Compose_Gfx_Window f_SDL_compose_gfx_window =
        get_p_PLATFORM_gfx_context_from__game(
                p_game)
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_compose_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_compose_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_compose_gfx_window, f_SDL_render_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_compose_gfx_window(
            p_game,
            p_PLATFORM_gfx_window);
}

void SDL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {

    f_SDL_Render_Gfx_Window f_SDL_render_gfx_window =
        get_p_PLATFORM_gfx_context_from__game(
                p_game)
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_render_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_render_gfx_window, f_SDL_render_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_render_gfx_window(
            p_game,
            p_PLATFORM_gfx_window);
}

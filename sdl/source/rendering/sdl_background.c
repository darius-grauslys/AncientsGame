#include "rendering/sdl_background.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "rendering/texture.h"
#include "assets/ui/default/ui_map_inventory_column.h"

PLATFORM_Graphics_Window *SDL_allocate_background_as__PLATFORM_Gfx_Window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__parent,
        SDL_Background_Kind the_kind_of__background,
        Vector__3i32 origin_of__window) {
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__child = 0;
    switch (the_kind_of__background) {
        case SDL_Background_Kind__Inventory_Column__Small:
        case SDL_Background_Kind__Equipment:
        case SDL_Background_Kind__Equipment_Divider:
        default:
            debug_error("SDL_allocate_background_as__PLATFORM_Gfx_Window, unsupported background type.");
            return 0;
        case SDL_Background_Kind__Inventory_Column:
            ;
            Texture_Allocation_Specification texture_alloc_spec;
            initialize_texture_allocation_specification(
                    &texture_alloc_spec, 
                    TEXTURE_FLAG__SIZE_256x256, 
                    p_PLATFORM_gfx_window__parent);
            p_PLATFORM_gfx_window__child =
                SDL_allocate_gfx_window(
                        get_p_PLATFORM_gfx_context_from__game(p_game), 
                        0,
                        &texture_alloc_spec);
            UI_Tile_Map__Wrapper ui_tile_map__wrapper =
                PLATFORM_get_tile_map__wrapper_from__gfx_window(
                        p_PLATFORM_gfx_window__child);
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_inventory_columnMap,
                    ui_map_inventory_columnMapLen);
            return p_PLATFORM_gfx_window__child;
    }
}

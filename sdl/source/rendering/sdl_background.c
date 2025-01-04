#include "rendering/sdl_background.h"
#include "assets/ui/default/ui_map_station.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "rendering/texture.h"
#include "assets/ui/default/ui_map_inventory_column.h"
#include "assets/ui/default/ui_map_short_inventory_column.h"
#include "assets/ui/default/ui_map_station_items.h"
#include "assets/ui/default/ui_map_equipment.h"

PLATFORM_Graphics_Window *SDL_allocate_background_as__PLATFORM_Gfx_Window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__parent,
        SDL_Background_Kind the_kind_of__background,
        Vector__3i32 origin_of__window) {
    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__child = 0;
    UI_Tile_Map__Wrapper ui_tile_map__wrapper;
    switch (the_kind_of__background) {
        case SDL_Background_Kind__Equipment_Divider:
        default:
            debug_error("SDL_allocate_background_as__PLATFORM_Gfx_Window, unsupported background type.");
            return 0;
        case SDL_Background_Kind__Inventory_Column:
            p_PLATFORM_gfx_window__child =
                SDL_allocate_gfx_window(
                        get_p_PLATFORM_gfx_context_from__game(p_game), 
                        0,
                        TEXTURE_FLAG__SIZE_256x256);
            ui_tile_map__wrapper =
                PLATFORM_get_tile_map__wrapper_from__gfx_window(
                        p_PLATFORM_gfx_window__child);
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_inventory_columnMap,
                    ui_map_inventory_columnMapLen);
            return p_PLATFORM_gfx_window__child;
        case SDL_Background_Kind__Equipment:
            p_PLATFORM_gfx_window__child =
                SDL_allocate_gfx_window(
                        get_p_PLATFORM_gfx_context_from__game(p_game), 
                        0,
                        TEXTURE_FLAG__SIZE_256x256);
            ui_tile_map__wrapper =
                PLATFORM_get_tile_map__wrapper_from__gfx_window(
                        p_PLATFORM_gfx_window__child);
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_equipmentMap,
                    ui_map_equipmentMapLen);
            return p_PLATFORM_gfx_window__child;
        case SDL_Background_Kind__Inventory_Column__Small:
            p_PLATFORM_gfx_window__child =
                SDL_allocate_gfx_window(
                        get_p_PLATFORM_gfx_context_from__game(p_game), 
                        0,
                        TEXTURE_FLAG__SIZE_256x256);
            ui_tile_map__wrapper =
                PLATFORM_get_tile_map__wrapper_from__gfx_window(
                        p_PLATFORM_gfx_window__child);
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_short_inventory_columnMap,
                    ui_map_short_inventory_columnMapLen);
            return p_PLATFORM_gfx_window__child;
        case SDL_Background_Kind__Station_Items:
            p_PLATFORM_gfx_window__child =
                SDL_allocate_gfx_window(
                        get_p_PLATFORM_gfx_context_from__game(p_game), 
                        0,
                        TEXTURE_FLAG__SIZE_256x256);
            ui_tile_map__wrapper =
                PLATFORM_get_tile_map__wrapper_from__gfx_window(
                        p_PLATFORM_gfx_window__child);
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_station_itemsMap,
                    ui_map_station_itemsMapLen);
            return p_PLATFORM_gfx_window__child;
            break;
    }
}

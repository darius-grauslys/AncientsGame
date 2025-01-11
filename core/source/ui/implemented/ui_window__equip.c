#include "ui/implemented/ui_window__equip.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/texture_strings.h"
#include "ui/ui_tile_map.h"
#include "ui/ui_tile_map_manager.h"

#include "assets/ui/default/ui_map_equip.h"

bool f_ui_window__load__equip(
        Gfx_Context *p_gfx_context,
        Graphics_Window_Kind the_kind_of__window) {
    PLATFORM_Texture *p_PLATFORM_texture_of__ui_sheet =
        get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__gfx_context(p_gfx_context), 
                name_of__texture__tilesheet_ui__c_str);

    if (!p_PLATFORM_texture_of__ui_sheet) {
        debug_error("f_ui_window__load__equip, failed to get ui texture sheet.");
        return false;
    }

    Graphics_Window__Wrapper gfx_window__wrapper;
    bool success_of__gfx_window__allocation = 
        allocate_graphics_window_with__graphics_window_manager(
            p_gfx_context, 
            &gfx_window__wrapper);

    if (!success_of__gfx_window__allocation) {
        debug_error("f_ui_window__load__equip, failed to allocate gfx_window.");
        return false;
    }

    UI_Tile_Map__Wrapper ui_tile_map__wrapper;
    initialize_ui_tile_map__wrapper(
            &ui_tile_map__wrapper,
            (UI_Tile_Raw*)ui_map_equipMap,
            256,
            256,
            UI_Tile_Map_Size__Large
            );

    PLATFORM_render_ui_tile_map__wrapper_to__gfx_window(
            get_p_PLATFORM_gfx_context_from__gfx_context(p_gfx_context), 
            gfx_window__wrapper.p_PLATFORM_gfx_window, 
            p_PLATFORM_texture_of__ui_sheet, 
            &ui_tile_map__wrapper);

    // TODO: allocate and load other windows
    // TODO: load ui

    return true;
}

void register_ui_window__equip(Gfx_Context *p_gfx_context) {
}

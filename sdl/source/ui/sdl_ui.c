#include "ui/sdl_ui.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/station_inventory_map.h"
#include "platform.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "rendering/texture.h"
#include "serialization/serialized_field.h"
#include "ui/game/sdl_ui_window__game__equip.h"
#include "ui/game/sdl_ui_window__game__trade.h"
#include "ui/game/sdl_ui_window__game__station.h"
#include "ui/sdl_ui__background.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_inventory_equipment.h"
#include "ui/ui_inventory_station.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "assets/ui/default/ui_map_trade.h"
#include "assets/ui/default/ui_map_equip.h"
#include "assets/ui/default/ui_map_station.h"

///
/// Opens the specified UI. Depending on the backend this
/// might close all other UI's.
///
void PLATFORM_open_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open,
        Game_Action *p_game_action) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    Texture_Allocation_Specification texture_alloc_spec;

    initialize_texture_allocation_specification(
            &texture_alloc_spec, 
            TEXTURE_FLAG__SIZE_256x256, 
            SDL_get_main_graphics_window_from__gfx_context(
                p_PLATFORM_gfx_context));

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__ui =
        SDL_allocate_gfx_window(
                p_PLATFORM_gfx_context, 
                0,
                &texture_alloc_spec);

    if (!p_PLATFORM_gfx_window__ui) {
        debug_error("SDL::PLATFORM_open_ui, failed to open ui.");
        return;
    }

    UI_Tile_Map__Wrapper ui_tile_map__wrapper =
        p_PLATFORM_gfx_window__ui
        ->SDL_graphics_window__ui_tile_map__wrapper;

    UI_Manager *p_ui_manager =
        PLATFORM_get_p_ui_manager_from__gfx_window(
                p_PLATFORM_gfx_window__ui);

    Entity *p_entity__local_player =
        get_p_local_player_from__game(p_game);

    switch (the_kind_of__ui_window_to__open) {
        default:
        case UI_Window_Kind__Idle:
            break;
        case UI_Window_Kind__Equip:
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_equipMap,
                    sizeof(ui_map_equipMap));
            SDL_allocate_ui_for__sdl_ui_window__game__equip(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_manager);

            UI_Element *p_ui_element__inventory_column__equip =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_14);

            UI_Element *p_ui_element__equipment_column__equip =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_8);

            if (!p_entity__local_player) {
                debug_error("SDL::PLATFORM_open_ui, fail to get local player.");
                return;
            }
            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        &p_entity__local_player->s_humanoid__inventory_ptr)) {
                debug_error("SDL::PLATFORM_open_ui, fail to get inventory of local player.");
                return;
            }

            Inventory *p_inventory__equip = 
                p_entity__local_player
                ->s_humanoid__inventory_ptr
                .p_serialized_field__inventory
                ;

            allocate_ui_inventory_column_into__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_element__inventory_column__equip, 
                    p_inventory__equip);

            allocate_ui_equipment_into__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_element__equipment_column__equip, 
                    &p_entity__local_player->equipment);
            break;
        case UI_Window_Kind__Trade:
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_tradeMap,
                    sizeof(ui_map_tradeMap));
            SDL_allocate_ui_for__sdl_ui_window__game__trade(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_manager);

            UI_Element *p_ui_element__inventory_column__container__trade =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__LEFT_8);

            UI_Element *p_ui_element__inventory_column__player__trade =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__RIGHT_62);

            if (!p_entity__local_player) {
                debug_error("SDL::PLATFORM_open_ui, fail to get local player.");
                return;
            }
            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        &p_entity__local_player->s_humanoid__inventory_ptr)) {
                debug_error("SDL::PLATFORM_open_ui, fail to get inventory of local player.");
                return;
            }

            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        &p_entity__local_player->s_humanoid__container_ptr)) {
                debug_error("SDL::PLATFORM_open_ui, fail to get inventory of trade container.");
                return;
            }

            Inventory *p_inventory__trade = 
                p_entity__local_player
                ->s_humanoid__inventory_ptr
                .p_serialized_field__inventory
                ;

            Inventory *p_inventory__container__trade = 
                p_entity__local_player
                ->s_humanoid__container_ptr
                .p_serialized_field__inventory
                ;

            allocate_ui_inventory_column_into__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_element__inventory_column__player__trade, 
                    p_inventory__trade);

            allocate_ui_inventory_column_into__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_element__inventory_column__container__trade, 
                    p_inventory__container__trade);
            break;
        case UI_Window_Kind__Station:
            memcpy(
                    ui_tile_map__wrapper.p_ui_tile_data,
                    ui_map_stationMap,
                    sizeof(ui_map_stationMap));
            SDL_allocate_ui_for__sdl_ui_window__game__station(
                    p_game, 
                    p_PLATFORM_gfx_window__ui, 
                    p_ui_manager);

            if (!p_entity__local_player)
                return;
            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        &p_entity__local_player->s_humanoid__inventory_ptr)) {
                return;
            }
            if (!resolve_s_inventory_ptr_to__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        &p_entity__local_player->s_humanoid__container_ptr)) {
                return;
            }

            Inventory *p_inventory__player = 
                p_entity__local_player
                ->s_humanoid__inventory_ptr
                .p_serialized_field__inventory
                ;

            Tile_Vector__3i32 tile_vector_of__station__3i32 =
                p_game_action
                ->game_action__container__tile_vector_3i32
                ;

            Serialized_Field s_station_inventory;
            initialize_serialized_field_as__unlinked(
                    &s_station_inventory, 
                    get_uuid_for__container(
                        tile_vector_of__station__3i32));

            Inventory *p_inventory__station = 
                resolve_s_inventory(
                        p_game,
                        &s_station_inventory);

            if (!p_inventory__station) {
                PLATFORM_open_ui(
                        p_game,
                        UI_Window_Kind__Idle,
                        0);
                return;
            }

            Station_Inventory_Map station_inventory_map;
            map_station_inventory(
                    p_inventory__station, 
                    &station_inventory_map);

            UI_Element *p_ui_element__inventory_column__player__station =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11);

            allocate_ui_inventory_column_into__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui,
                    p_ui_element__inventory_column__player__station, 
                    p_inventory__player);

            // load station items:

            UI_Element *p_ui_element__inventory_slot__requirements =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__STATION_P_REQUIREMENTS_7);

            UI_Element *p_ui_element__inventory_slot__recipe_and_tools =
                get_p_ui_element_by__index_from__ui_manager(
                        p_ui_manager,
                        SDL_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4);

            allocate_ui_station_inventory_for__ui_element_container(
                    p_game, 
                    p_PLATFORM_gfx_window__ui,
                    &station_inventory_map, 
                    p_ui_element__inventory_slot__requirements, 
                    p_ui_element__inventory_slot__recipe_and_tools);
            break;
    }

    SDL_compose_gfx_window(
            p_game,
            p_PLATFORM_gfx_window__ui);

    debug_info("SDL::PLATFORM_open_ui, ui opened.");
}

void PLATFORM_refresh_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open) {
    // TODO: impl
}

void PLATFORM_update_ui(
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    PLATFORM_Graphics_Window *ptr_array_of__gfx_windows[
        PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF];

    Signed_Quantity__i32 quantity_of__windows =
        SDL_get_p_PLATFORM_gfx_windows_by__type_from__manager(
                SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                UI_Window_Kind__Unknown, 
                ptr_array_of__gfx_windows, 
                PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF);

    if (!quantity_of__windows)
        return;

    for (Index__u32 index_of__gfx_window = 0;
            index_of__gfx_window
            < PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF
            && index_of__gfx_window
            < quantity_of__windows;
            index_of__gfx_window++) {
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window =
            ptr_array_of__gfx_windows[
            index_of__gfx_window];
        if (!SDL_is_gfx_window__allocated(
                    p_PLATFORM_gfx_window)) {
            continue;
        }

        // TODO: allow ui_elements to flag the gfx_window as having
        // it's tile_map modified, and if so, recomposite the window.
        poll_ui_manager__update(
                SDL_get_p_ui_manager_from__PLATFORM_gfx_window(
                    p_PLATFORM_gfx_window),
                p_game);
        SDL_compose_gfx_window(
                p_game,
                p_PLATFORM_gfx_window);
        SDL_render_gfx_window(
                p_game, 
                p_PLATFORM_gfx_window);
        return; // TODO:    remove, and also only render/update windows
                //          allocate as stand-alone windows, and not
                //          sub-windows.
    }
}

///
/// Closes the specified UI. Depending on the backend this
/// might cause a UI window to open. For example, on NDS
/// this will close the specified UI Window, and transition
/// to the UI Idle window.
///
void PLATFORM_close_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__close) {
    //TODO: prop impl, with ui window manager

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window;
    if (!SDL_get_p_PLATFORM_gfx_windows_by__type_from__manager(
                SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context), 
                the_kind_of__ui_window_to__close, 
                &p_PLATFORM_gfx_window, 
                1)) {
        return;
    }

    SDL_release_gfx_window(
            p_game, 
            p_PLATFORM_gfx_window);

    debug_info("SDL::PLATFORM_open_ui, ui closed.");
}

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void) {
    // TODO: impl
    return UI_Window_Kind__None;
}

Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer) {
    // TODO: impl
    return 0;
}

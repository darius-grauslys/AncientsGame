#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/station_inventory_map.h"
#include "serialization/serialized_field.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/ui_element.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_inventory_station.h"
#include "ui/ui_manager.h"
#include <ui/nds_ui__station.h>
#include <ui/game/nds_ui_window__game__station.h>
#include <nds_defines.h>
#include "nds_game.h"

void NDS_open_ui__station(
        Game *p_game,
        Game_Action *p_game_action) {
    UI_Manager *p_ui_manager =
        NDS_get_p_ui_manager_from__game(
                p_game);
    NDS_allocate_ui_for__nds_ui_window__game__station(
            p_game,
            p_ui_manager);

    Entity *p_entity__local_player =
        get_p_local_player_from__game(p_game);

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

    UI_Element *p_ui_element__inventory_column__player =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11);

    allocate_ui_inventory_column_into__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            p_ui_element__inventory_column__player, 
            p_inventory__player);

    // load station items:

    UI_Element *p_ui_element__inventory_slot__requirements =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__STATION_P_REQUIREMENTS_7);

    UI_Element *p_ui_element__inventory_slot__recipe_and_tools =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4);

    allocate_ui_station_inventory_for__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            &station_inventory_map, 
            p_ui_element__inventory_slot__requirements, 
            p_ui_element__inventory_slot__recipe_and_tools);
}

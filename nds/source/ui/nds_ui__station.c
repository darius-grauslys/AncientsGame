#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/station_inventory_map.h"
#include "serialization/serialized_field.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/ui_element.h"
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

    NDS_load_ui_inventory_column_for__inventory(
            p_game,
            p_ui_element__inventory_column__player,
            p_inventory__player);

    // load station items:

    Index__u32 index_of__inventory_column_slot = 0;

    PLATFORM_Graphics_Window *p_graphics_window =
        &get_p_PLATFORM_gfx_context_from__game(p_game)
        ->graphics_window__sub;

    UI_Element *p_ui_element__current_inventory_slot =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__STATION_P_REQUIREMENTS_7);

    do {
        Item_Stack *p_item_stack =
            &station_inventory_map
            .p_item_stack__required_items[
                index_of__inventory_column_slot];
        NDS_load_ui_item_stack(
                p_game, 
                p_graphics_window, 
                p_ui_manager,
                p_item_stack, 
                p_ui_element__current_inventory_slot);
    } while (iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot
            && index_of__inventory_column_slot++
            < ITEM_REQUIREMENT_MAX_QUANTITY_OF);

    p_ui_element__current_inventory_slot =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4);

    NDS_load_ui_item_stack(
            p_game, 
            p_graphics_window, 
            p_ui_manager,
            station_inventory_map
            .p_item_stack__recipe, 
            p_ui_element__current_inventory_slot);
    if (!iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot) {
        return;
    }
    NDS_load_ui_item_stack(
            p_game, 
            p_graphics_window, 
            p_ui_manager,
            station_inventory_map
            .p_item_stack__tool_one, 
            p_ui_element__current_inventory_slot);
    if (!iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot) {
        return;
    }
    NDS_load_ui_item_stack(
            p_game, 
            p_graphics_window, 
            p_ui_manager,
            station_inventory_map
            .p_item_stack__tool_two, 
            p_ui_element__current_inventory_slot);
}

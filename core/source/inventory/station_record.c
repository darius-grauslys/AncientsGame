#include "defines.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "inventory/item_recipe.h"
#include "inventory/item_recipe_record.h"
#include "inventory/item_stack.h"
#include <inventory/station_inventory_map.h>
#include <inventory/station_record.h>
#include <inventory/item_recipe_manager.h>

void initialize_station_record(
        Station_Record *p_station_record,
        f_Station_Handler__Use f_station_handler__use,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required) {
    p_station_record->f_station_handler__use =
        f_station_handler__use;
    p_station_record->first_required__tool =
        the_first_kind_of__tool_required;
    p_station_record->second_required__tool =
        the_second_kind_of__tool_required;
}

bool f_station_handler__use__empty(
        Game *p_game,
        Entity *p_entity__user,
        Inventory *p_station__inventory) {
    print_log__system(
            p_game, 
            "This station lacks usable tools.");
    return false;
}

bool f_station_handler__use__default(
        Game *p_game,
        Entity *p_entity__user,
        Inventory *p_station__inventory) {

    Inventory *p_inventory__entity =
        resolve_s_inventory(
                p_game,
                &p_entity__user->s_humanoid__inventory_ptr);

    if (!p_inventory__entity) {
        return false;
    }

    Station_Inventory_Map station_inventory_map;
    map_station_inventory(
            p_station__inventory, 
            &station_inventory_map);

    if (is_p_item_stack__empty(
                station_inventory_map
                .p_item_stack__recipe)) {
        return false;
    }

    bool is_crafting__successful =
        make_item_with__this_inventory(
                get_p_item_recipe_manager_from__game(p_game), 
                p_inventory__entity, 
                get_item_kind_of__station_recipe(
                    &station_inventory_map), 
                get_item_recipe_flags_of__station_recipe(
                    &station_inventory_map));

    if (is_crafting__successful) {
#warning NEED TO IMPL
        // PLATFORM_refresh_ui(
        //         p_game, 
        //         UI_Window_Kind__Equip);
        // PLATFORM_refresh_ui(
        //         p_game, 
        //         UI_Window_Kind__Trade);
        // PLATFORM_refresh_ui(
        //         p_game, 
        //         UI_Window_Kind__Station);
    }

    return is_crafting__successful;
}

#include "game.h"
#include "inventory/inventory_manager.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/ui_manager.h"
#include <ui/nds_ui__station.h>
#include <ui/game/nds_ui_window__game__station.h>

void NDS_open_ui__station(
        Game *p_game) {
    NDS_allocate_ui_for__nds_ui_window__game__station(p_game);

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

    // Inventory *p_inventory__container = 
    //     p_entity__local_player
    //     ->s_humanoid__container_ptr
    //     .p_serialized_field__inventory
    //     ;

    UI_Element *p_ui_element__inventory_column__player =
        get_p_ui_element_by__index_from__ui_manager(
                get_p_ui_manager_from__game(p_game), 
                NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11);

    NDS_load_ui_inventory_column_for__inventory(
            p_game,
            p_ui_element__inventory_column__player,
            p_inventory__player);
}

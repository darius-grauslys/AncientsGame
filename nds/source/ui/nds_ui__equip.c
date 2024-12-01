#include "ui/nds_ui__equip.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "ui/game/nds_ui_window__game__equip.h"
#include "ui/nds_ui__equipment.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_inventory_equipment.h"
#include "ui/ui_manager.h"
#include "nds_game.h"

void NDS_open_ui__equip(
        Game *p_game) {
    UI_Manager *p_ui_manager =
            NDS_get_p_ui_manager_from__game(
                p_game);

    NDS_allocate_ui_for__nds_ui_window__game__equip(
            p_game,
            p_ui_manager);

    Entity *p_entity__local_player =
        get_p_local_player_from__game(p_game);

    if (!p_entity__local_player) {
        debug_error("NDS::NDS_open_ui__equip, fail to get local player.");
        return;
    }
    if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__game(p_game), 
                &p_entity__local_player->s_humanoid__inventory_ptr)) {
        debug_error("NDS::NDS_open_ui__equip, fail to get inventory of local player.");
        return;
    }

    Inventory *p_inventory = 
        p_entity__local_player
        ->s_humanoid__inventory_ptr
        .p_serialized_field__inventory
        ;

    UI_Element *p_ui_element__inventory_column =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13);

    UI_Element *p_ui_element__equipment_column =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                NDS_UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7);

    allocate_ui_inventory_column_into__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            p_ui_element__inventory_column, 
            p_inventory);

    allocate_ui_equipment_into__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            p_ui_element__equipment_column, 
            &p_entity__local_player->equipment);
}

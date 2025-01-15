#include "ui/implemented/ui_gfx_window__load__trade.h"
#include "inventory/inventory_manager.h"
#include "ui/implemented/generated/game/ui_window__game__trade.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_manager.h"
#include "world/world.h"

bool f_ui_window_load__trade(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager) {

    Entity *p_entity__local_player =
        get_p_local_player_from__world(p_world);

    if (!p_entity__local_player)
        return false;
    if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__world(p_world), 
                &p_entity__local_player->s_humanoid__inventory_ptr)) {
        return false;
    }
    if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__world(p_world), 
                &p_entity__local_player->s_humanoid__container_ptr)) {
        return false;
    }

    Inventory *p_inventory__player = 
        p_entity__local_player
        ->s_humanoid__inventory_ptr
        .p_serialized_field__inventory
        ;

    Inventory *p_inventory__container = 
        p_entity__local_player
        ->s_humanoid__container_ptr
        .p_serialized_field__inventory
        ;

    allocate_ui_for__ui_window__game__trade(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_manager);

    UI_Element *p_ui_element__inventory_column__player =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager, 
                UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__RIGHT_62);

    allocate_ui_inventory_column_into__ui_element_container(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_element__inventory_column__player, 
            p_inventory__player);

    UI_Element *p_ui_element__inventory_column__container =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager, 
                UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__LEFT_8);

    allocate_ui_inventory_column_into__ui_element_container(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_element__inventory_column__container, 
            p_inventory__container);

    return true;
}

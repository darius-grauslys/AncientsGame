#include "ui/implemented/ui_gfx_window__load__equip.h"
#include "inventory/inventory_manager.h"
#include "ui/implemented/generated/game/ui_window__game__equip.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_inventory_equipment.h"
#include "ui/ui_manager.h"
#include "world/world.h"

bool f_ui_window_load__equip(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager) {
    Entity *p_entity__local_player =
        get_p_local_player_from__world(p_world);

    if (!p_entity__local_player) {
        debug_error("NDS::NDS_open_ui__equip, fail to get local player.");
        return false;
    }
    if (!resolve_s_inventory_ptr_to__inventory_manager(
                get_p_inventory_manager_from__world(p_world), 
                &p_entity__local_player->s_humanoid__inventory_ptr)) {
        debug_error("NDS::NDS_open_ui__equip, fail to get inventory of local player.");
        return false;
    }

    Inventory *p_inventory = 
        p_entity__local_player
        ->s_humanoid__inventory_ptr
        .p_serialized_field__inventory
        ;

    allocate_ui_for__ui_window__game__equip(
            p_gfx_context, 
            p_gfx_window, 
            p_world,
            p_ui_manager);

    UI_Element *p_ui_element__inventory_column =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13);

    UI_Element *p_ui_element__equipment_column =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager,
                UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7);

    allocate_ui_inventory_column_into__ui_element_container(
            p_gfx_context,
            p_gfx_window,
            p_world,
            p_ui_manager,
            p_ui_element__inventory_column, 
            p_inventory);

    allocate_ui_equipment_into__ui_element_container(
            p_gfx_context,
            p_gfx_window,
            p_world,
            p_ui_manager,
            p_ui_element__equipment_column, 
            &p_entity__local_player->equipment);
    return true;
}

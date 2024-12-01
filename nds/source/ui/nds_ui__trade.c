#include "ui/nds_ui__trade.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "platform.h"
#include "ui/game/nds_ui_window__game__trade.h"
#include "ui/nds_ui__equipment.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "nds_game.h"

void NDS_open_ui__trade(
        Game *p_game,
        Game_Action *p_game_action) {
    UI_Manager *p_ui_manager =
        NDS_get_p_ui_manager_from__game(
                p_game);
    NDS_allocate_ui_for__nds_ui_window__game__trade(
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

    Inventory *p_inventory__container = 
        p_entity__local_player
        ->s_humanoid__container_ptr
        .p_serialized_field__inventory
        ;

    UI_Element *p_ui_element__inventory_column__player =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager, 
                NDS_UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__RIGHT_62);

    allocate_ui_inventory_column_into__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            p_ui_element__inventory_column__player, 
            p_inventory__player);

    UI_Element *p_ui_element__inventory_column__container =
        get_p_ui_element_by__index_from__ui_manager(
                p_ui_manager, 
                NDS_UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__LEFT_8);

    allocate_ui_inventory_column_into__ui_element_container(
            p_game, 
            &get_p_PLATFORM_gfx_context_from__game(p_game)
            ->graphics_windows__sub[1], 
            p_ui_element__inventory_column__container, 
            p_inventory__container);
}

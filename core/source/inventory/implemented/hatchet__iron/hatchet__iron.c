#include "inventory/implemented/hatchet__iron/hatchet__iron.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "inventory/implemented/tool.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"
#include "platform.h"
#include "world/chunk_manager.h"
#include "world/chunk_vectors.h"

void register_into__item_manager__hatchet__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Hatchet__Iron, 
            get_item(
                Item_Kind__Hatchet__Iron, 
                ITEM_USAGE_FLAG__IS_LABOR
                | ITEM_USAGE_FLAG__IS_LABOR__SECONDARY
                | ITEM_USAGE_FLAG__IS_COMBAT,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(4), 
                m_item_use_handler__hatchet__iron, 
                0, 
                0));
}

void m_item_use_handler__hatchet__iron(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
    if (is_item_tool_mode_a__combat_mode(p_item_self)) {
        m_item_use_handler__weapon(
                p_item_self, 
                p_entity_user, 
                p_game_action, 
                p_game);
        return;
    }

    use_tool__harvest_tree(
            p_game, 
            p_entity_user);
}

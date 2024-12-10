#include "inventory/implemented/pickaxe__iron/pickaxe__iron.h"
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

void register_into__item_manager__pickaxe__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pickaxe__Iron, 
            get_tool(
                Item_Kind__Pickaxe__Iron, 
                ITEM_USAGE_FLAG__IS_LABOR
                | ITEM_USAGE_FLAG__IS_LABOR__SECONDARY
                | ITEM_USAGE_FLAG__IS_COMBAT,
                i32_to__i32F20(4), 
                Tool_Kind__Pickaxe, 
                m_item_use_handler__harvest, 
                0, 
                0));
}

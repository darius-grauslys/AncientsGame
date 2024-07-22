#include "inventory/implemented/battleaxe__iron/battleaxe__iron.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__battle_axe__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Battleaxe__Iron, 
            get_weapon(
                Item_Kind__Battleaxe__Iron, 
                i32_to__i32F20(12), 
                HEARTS_DAMAGING_FLAG__IS_SLASHING, 
                9));
}

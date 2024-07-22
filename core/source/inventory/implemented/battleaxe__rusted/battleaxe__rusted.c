#include "inventory/implemented/battleaxe__rusted/battleaxe__rusted.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__battle_axe__rusted_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Battleaxe__Rusted, 
            get_weapon(
                Item_Kind__Battleaxe__Rusted, 
                i32_to__i32F20(16), 
                HEARTS_DAMAGING_FLAG__IS_SLASHING, 
                8));
}

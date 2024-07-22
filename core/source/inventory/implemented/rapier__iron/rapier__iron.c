#include "inventory/implemented/rapier__iron/rapier__iron.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__rapier__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Rapier__Iron, 
            get_weapon(
                Item_Kind__Rapier__Iron, 
                i32_to__i32F20(6), 
                HEARTS_DAMAGING_FLAG__IS_SLASHING, 
                6));
}

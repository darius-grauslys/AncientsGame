#include "inventory/implemented/rapier__steel/rapier__steel.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__rapier__steel_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Rapier__Steel, 
            get_weapon(
                Item_Kind__Rapier__Steel, 
                i32_to__i32F20(5), 
                HEARTS_DAMAGING_FLAG__IS_SLASHING, 
                15));
}

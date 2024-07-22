#include "inventory/implemented/sword__steel__order/sword__steel__order.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__sword__steel__order_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Sword__Steel__Order, 
            get_weapon(
                Item_Kind__Sword__Steel__Order, 
                i32_to__i32F20(6), 
                HEARTS_DAMAGING_FLAG__IS_ORDER, 
                16));
}

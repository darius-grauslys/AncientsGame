#include "inventory/implemented/dagger__steel__order/dagger__steel__order.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__dagger__steel__order_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Dagger__Steel__Order, 
            get_weapon(
                Item_Kind__Dagger__Steel__Order, 
                i32_to__i32F20(3), 
                HEARTS_DAMAGING_FLAG__IS_ORDER, 
                13));
}

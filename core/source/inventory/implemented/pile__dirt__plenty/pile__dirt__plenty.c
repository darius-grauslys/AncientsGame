#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__dirt__plenty/pile__dirt__plenty.h>

void register_into__item_manager__pile__dirt__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Dirt__Plenty, 
            get_item(
                Item_Kind__Pile__Dirt__Plenty, 
                ITEM_USAGE_FLAGS__NONE,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(300), 
                0, 
                0, 
                0));
}

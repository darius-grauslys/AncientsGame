#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__wood__plenty/pile__wood__plenty.h>

void register_into__item_manager__pile__wood__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Wood__Plenty, 
            get_item(
                Item_Kind__Pile__Wood__Plenty, 
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(180), 
                0, 
                0, 
                0));
}

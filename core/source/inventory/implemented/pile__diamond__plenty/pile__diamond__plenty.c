#include "defines.h"
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__diamond__plenty/pile__diamond__plenty.h>

void register_into__item_manager__pile__diamond__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Diamond__Plenty, 
            get_item(
                Item_Kind__Pile__Diamond__Plenty, 
                ITEM_USAGE_FLAGS__NONE,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(80), 
                0, 
                0, 
                0));
}

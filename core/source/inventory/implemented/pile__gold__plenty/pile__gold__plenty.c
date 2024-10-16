#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__gold__plenty/pile__gold__plenty.h>

void register_into__item_manager__pile__gold__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Gold__Plenty, 
            get_item(
                Item_Kind__Pile__Gold__Plenty, 
                ITEM_USAGE_FLAGS__NONE,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(1000), 
                0, 
                0, 
                0));
}

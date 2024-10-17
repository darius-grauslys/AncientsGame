#include <inventory/implemented/door__amethyst/door__amethyst.h>
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"

void register_into__item_manager__door__amethyst_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Door__Amethyst, 
            get_item(
                Item_Kind__Door__Amethyst, 
                ITEM_USAGE_FLAGS__NONE,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(200), 
                0, 
                0, 
                0));
}


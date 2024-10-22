#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include <inventory/implemented/item_recipe/item_recipe.h>

void register_into__item_manager__item_recipe_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Item_Recipe, 
            get_item(
                Item_Kind__Item_Recipe, 
                ITEM_USAGE_FLAGS__NONE,
                ITEM_FILTER_FLAGS__NONE, 
                (i32F20)BIT(18), 
                0, 
                0, 
                0));
}

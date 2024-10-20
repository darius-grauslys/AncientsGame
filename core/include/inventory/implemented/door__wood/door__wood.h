#ifndef DOOR__WOOD_H
#define DOOR__WOOD_H

#include "defines_weak.h"
#include "inventory/item_recipe.h"
#include <defines.h>

void register_into__item_manager__door__wood_into__item_manager(
        Item_Manager *p_item_manager);

void register_into__recipe_manager__door__wood(
        Item_Recipe_Manager *p_item_recipe_manager);

static inline
Item get_item_recipe_for__door__wood(void) {
    return get_item_recipe(
            Item_Kind__Door__Wood,
            ITEM_RECIPE_FLAGS__NONE,
            Station_Kind__Carpentry);
}


#endif

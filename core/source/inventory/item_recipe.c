#include "defines.h"
#include "defines_weak.h"
#include "inventory/item.h"
#include <inventory/item_recipe.h>

void initialize_item_as__item_recipe(
        Item *p_item,
        Item_Kind the_kind_of__item_produced,
        Item_Recipe_Flags item_recipe_flags,
        Station_Kind the_kind_of__station_required) {
    *p_item =
        get_item(
                Item_Kind__Item_Recipe, 
                ITEM_USAGE_FLAGS__NONE, 
                ITEM_FILTER_FLAGS__NONE, 
                (i32F20)BIT(18), 
                0, 
                0, 
                0);
    p_item->the_kind_of_item__this_recipe_produces =
        the_kind_of__item_produced;
    p_item->item_recipe_flags =
        item_recipe_flags;
    p_item->the_kind_of__station_required =
        the_kind_of__station_required;
}


#ifndef ITEM_RECIPE_H
#define ITEM_RECIPE_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item_recipe_as__deallocated(
        Item_Recipe *p_item_recipe);

void initialize_item_recipe(
        Item_Recipe *p_item_recipe,
        Item_Kind the_kind_of__item_this__recipe_makes,
        Quantity__u32 the_quantity_of__items_this__recipe_makes);

///
/// Returns false if fails to add requirement.
/// Likely due to the recipe already possessing the
/// maximum amount of permitted requirements.
///
bool add_item_recipe_requirement(
        Item_Recipe *p_item_recipe,
        Item_Kind the_kind_of__item_that_is__required,
        Quantity__u32 the_quantity_of__items_required);

bool is_inventory_capable_of__making_this_item(
        Inventory *p_inventory,
        Item_Recipe *p_item_recipe);

static inline
bool is_item_recipe_for__this_item(
        Item_Recipe *p_item_recipe,
        Item_Kind the_kind_of__item) {
    return p_item_recipe->the_kind_of__item_this__recipe_makes
        == the_kind_of__item;
}

static inline
bool is_item_recipe__allocated(
        Item_Recipe *p_item_recipe) {
    return p_item_recipe
        ->the_kind_of__item_this__recipe_makes
        != Item_Kind__None;
}

#endif

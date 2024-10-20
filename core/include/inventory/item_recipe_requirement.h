#ifndef ITEM_RECIPE_REQUIREMENT_H
#define ITEM_RECIPE_REQUIREMENT_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item_recipe_requirement_as__unused(
        Item_Recipe_Requirement *p_item_recipe_requirement);

Item_Recipe_Requirement get_item_recipe_requirement(
        Item_Kind the_kind_of__item_required,
        Quantity__u32 the_quantity_of__items_required);

void initialize_item_recipe_requirement(
        Item_Recipe_Requirement *p_item_recipe_requirement,
        Item_Kind the_kind_of__item_that_is__required,
        Quantity__u32 the_quantity_of__items_required);

bool is_inventory_capable_of__meeting_item_recipe_requirement(
        Inventory *p_inventory,
        Item_Recipe_Requirement *p_item_recipe_requirement,
        bool is_requirement__halved);

static inline
bool is_item_recipe_requirement__used(
        Item_Recipe_Requirement *p_item_recipe_requirement) {
    return p_item_recipe_requirement
        ->the_kind_of__item_that_is__required
        != Item_Kind__None;
}

#endif

#ifndef ITEM_RECIPE_RECORD_H
#define ITEM_RECIPE_RECORD_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item_recipe_record_as__deallocated(
        Item_Recipe_Record *p_item_recipe);

void initialize_item_recipe_record(
        Item_Recipe_Record *p_item_recipe,
        Item_Kind the_kind_of__item_this__recipe_makes,
        Quantity__u32 the_quantity_of__items_this__recipe_makes);

Item_Recipe_Record get_item_recipe_record(
        Item_Kind the_kind_of__item_produced,
        Quantity__u32 the_quantity__produced,
        Item_Recipe_Requirement requirements[ITEM_REQUIREMENT_MAX_QUANTITY_OF]);

///
/// Returns false if fails to add requirement.
/// Likely due to the recipe already possessing the
/// maximum amount of permitted requirements.
///
bool add_item_recipe_requirement_to__item_recipe_record(
        Item_Recipe_Record *p_item_recipe,
        Item_Kind the_kind_of__item_that_is__required,
        Quantity__u32 the_quantity_of__items_required);

bool is_inventory_capable_of__making_this_item(
        Inventory *p_inventory,
        Item_Recipe_Record *p_item_recipe,
        Item_Recipe_Flags item_recipe_flags);

static inline
bool is_item_recipe_record_for__this_item(
        Item_Recipe_Record *p_item_recipe,
        Item_Kind the_kind_of__item) {
    return p_item_recipe->the_kind_of__item_this__recipe_makes
        == the_kind_of__item;
}

static inline
bool is_item_recipe_record__allocated(
        Item_Recipe_Record *p_item_recipe) {
    return p_item_recipe
        ->the_kind_of__item_this__recipe_makes
        != Item_Kind__None;
}

#endif

#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "inventory/item_recipe_requirement.h"
#include <inventory/item_recipe.h>

void initialize_item_recipe_as__deallocated(
        Item_Recipe *p_item_recipe) {
    p_item_recipe->the_kind_of__item_this__recipe_makes =
        Item_Kind__None;
    p_item_recipe->the_quantity_of__items_this__recipe_makes =
        0;
    
    for (Index__u32 index_of__requirement = 0;
            index_of__requirement < ITEM_REQUIREMENT_MAX_QUANTITY_OF;
            index_of__requirement++) {
        Item_Recipe_Requirement *p_item_recipe_requirement =
            &p_item_recipe->requirements[index_of__requirement];

        initialize_item_recipe_requirement_as__unused(
                p_item_recipe_requirement);
    }
}

void initialize_item_recipe(
        Item_Recipe *p_item_recipe,
        Item_Kind the_kind_of__item_this__recipe_makes,
        Quantity__u32 the_quantity_of__items_this__recipe_makes) {
    p_item_recipe->the_kind_of__item_this__recipe_makes =
        the_kind_of__item_this__recipe_makes;
    p_item_recipe->the_quantity_of__items_this__recipe_makes =
        the_quantity_of__items_this__recipe_makes;
}

///
/// Returns false if fails to add requirement.
/// Likely due to the recipe already possessing the
/// maximum amount of permitted requirements.
///
bool add_item_recipe_requirement(
        Item_Recipe *p_item_recipe,
        Item_Kind the_kind_of__item_that_is__required,
        Quantity__u32 the_quantity_of__items_required) {
    for (Index__u32 index_of__requirement = 0;
            index_of__requirement < ITEM_REQUIREMENT_MAX_QUANTITY_OF;
            index_of__requirement++) {
        Item_Recipe_Requirement *p_item_recipe_requirement =
            &p_item_recipe
            ->requirements[index_of__requirement];

        if (is_item_recipe_requirement__used(
                    p_item_recipe_requirement)) {
            continue;
        }

        initialize_item_recipe_requirement(
                p_item_recipe_requirement,
                the_kind_of__item_that_is__required,
                the_quantity_of__items_required);

        return true;
    }

    return false;
}

bool is_inventory_capable_of__making_this_item(
        Inventory *p_inventory,
        Item_Recipe *p_item_recipe) {
    for (Index__u32 index_of__requirement = 0;
            index_of__requirement < ITEM_REQUIREMENT_MAX_QUANTITY_OF;
            index_of__requirement++) {
        Item_Recipe_Requirement *p_item_recipe_requirement =
            &p_item_recipe
            ->requirements[index_of__requirement];

        if (!is_item_recipe_requirement__used(
                    p_item_recipe_requirement)) {
            return true;
        }

        if (!is_inventory_capable_of__meeting_item_recipe_requirement(
                p_inventory, 
                p_item_recipe_requirement)) {
            return true;
        }
    }

    return true;
}

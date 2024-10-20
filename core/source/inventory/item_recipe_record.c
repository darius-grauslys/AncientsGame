#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "inventory/item_recipe.h"
#include "inventory/item_recipe_requirement.h"
#include <inventory/item_recipe_record.h>

void initialize_item_recipe_record_as__deallocated(
        Item_Recipe_Record *p_item_recipe) {
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

Item_Recipe_Record get_item_recipe_record(
        Item_Kind the_kind_of__item_produced,
        Quantity__u32 the_quantity__produced,
        Item_Recipe_Requirement requirements[ITEM_REQUIREMENT_MAX_QUANTITY_OF]) {
    Item_Recipe_Record item_recipe_record;
    item_recipe_record.the_kind_of__item_this__recipe_makes =
        the_kind_of__item_produced;
    item_recipe_record.the_quantity_of__items_this__recipe_makes =
        the_quantity__produced;

    for (Index__u32 index_of__requirement = 0;
            index_of__requirement
            < ITEM_REQUIREMENT_MAX_QUANTITY_OF;
            index_of__requirement++) {
        item_recipe_record.requirements[index_of__requirement] =
            requirements[index_of__requirement];
    }

    return item_recipe_record;
}


void initialize_item_recipe_record(
        Item_Recipe_Record *p_item_recipe,
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
bool add_item_recipe_requirement_to__item_recipe_record(
        Item_Recipe_Record *p_item_recipe,
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
        Item_Recipe_Record *p_item_recipe,
        Item_Recipe_Flags item_recipe_flags) {
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
                p_item_recipe_requirement,
                is_nth_requirement_of__item_recipe__efficent(
                    item_recipe_flags, 
                    index_of__requirement))) {
            return true;
        }
    }

    return true;
}

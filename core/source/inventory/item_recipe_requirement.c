#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include <inventory/item_recipe_requirement.h>

void initialize_item_recipe_requirement_as__unused(
        Item_Recipe_Requirement *p_item_recipe_requirement) {
    p_item_recipe_requirement->the_kind_of__item_that_is__required =
        Item_Kind__None;
    p_item_recipe_requirement->the_quantity_of__items_required =
        0;
}

Item_Recipe_Requirement get_item_recipe_requirement(
        Item_Kind the_kind_of__item_required,
        Quantity__u32 the_quantity_of__items_required) {
    return (Item_Recipe_Requirement){
        the_kind_of__item_required,
        the_quantity_of__items_required
    };
}

void initialize_item_recipe_requirement(
        Item_Recipe_Requirement *p_item_recipe_requirement,
        Item_Kind the_kind_of__item_that_is__required,
        Quantity__u32 the_quantity_of__items_required) {
    p_item_recipe_requirement->the_kind_of__item_that_is__required =
        the_kind_of__item_that_is__required;
    p_item_recipe_requirement->the_quantity_of__items_required =
        the_quantity_of__items_required;
}

bool is_inventory_capable_of__meeting_item_recipe_requirement(
        Inventory *p_inventory,
        Item_Recipe_Requirement *p_item_recipe_requirement,
        bool is_requirement__halved) {
    Quantity__u32 quantity_of__items =
        p_item_recipe_requirement
        ->the_quantity_of__items_required;
    if (is_requirement__halved) {
        quantity_of__items >>= 1;
    }
    return
        does_inventory_have_this_many_of__item_kind(
                p_inventory, 
                p_item_recipe_requirement
                ->the_kind_of__item_that_is__required, 
                quantity_of__items);
}

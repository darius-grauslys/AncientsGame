#include "defines.h"
#include "defines_weak.h"
#include "inventory/implemented/door__wood/door__wood.h"
#include "inventory/inventory.h"
#include "inventory/item_recipe.h"
#include "inventory/item_recipe_record.h"
#include "inventory/item_recipe_requirement.h"
#include <inventory/item_recipe_manager.h>

bool is_item_kind__illegal_for__item_recipe_manager(
        Item_Kind the_kind_of__item) {
    return the_kind_of__item
            >= Item_Kind__Unknown
            || the_kind_of__item
            <= Item_Kind__None
            ;
}

static inline
Item_Recipe_Record *get_p_item_recipe_from__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager,
        Item_Kind the_kind_of__item) {
    return &p_item_recipe_manager
        ->recipes[the_kind_of__item - 1];
}

void initialize_item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager) {
    for (Index__u32 index_of__item_recipe = 0;
            index_of__item_recipe < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item_recipe++) {
        Item_Recipe_Record *p_item_recipe =
            &p_item_recipe_manager
            ->recipes[index_of__item_recipe];

        initialize_item_recipe_record_as__deallocated(
                p_item_recipe);
    }
}

///
/// TODO: currently, there is only one way to make
/// each item.
///
void register_item_recipe_into__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager,
        Item_Recipe_Record item_recipe) {
    if (is_item_kind__illegal_for__item_recipe_manager(
                item_recipe
                .the_kind_of__item_this__recipe_makes)) {
        debug_error("register_item_recipe_into__item_recipe_manager, illegal item_kind: %d", item_recipe.the_kind_of__item_this__recipe_makes);
        return;
    }

    p_item_recipe_manager->recipes[
        item_recipe
            .the_kind_of__item_this__recipe_makes - 1] =
            item_recipe;
}

bool is_inventory_capable_of__making_this_item_in__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager,
        Inventory *p_inventory,
        Item_Kind the_kind_of__item,
        Item_Recipe_Flags item_recipe_flags) {
    if (is_item_kind__illegal_for__item_recipe_manager(
                the_kind_of__item)) {
        debug_error("is_inventory_capable_of__making_this_item_in__item_recipe_manager, illegal item_kind: %d", the_kind_of__item);
        return false;
    }

    Item_Recipe_Record *p_item_recipe =
        get_p_item_recipe_from__item_recipe_manager(
                p_item_recipe_manager, 
                the_kind_of__item);

    return is_inventory_capable_of__making_this_item(
            p_inventory, 
            p_item_recipe,
            item_recipe_flags);
}

bool make_item_with__this_inventory(
        Item_Recipe_Manager *p_item_recipe_manager,
        Inventory *p_inventory,
        Item_Kind the_kind_of__item,
        Item_Recipe_Flags item_recipe_flags) {
    if (!is_item__craftable(
                p_item_recipe_manager, 
                the_kind_of__item)) {
        return false;
    }
    if (!is_inventory_capable_of__making_this_item_in__item_recipe_manager(
                p_item_recipe_manager, 
                p_inventory, 
                the_kind_of__item,
                item_recipe_flags)) {
        return false;
    }

    Item_Recipe_Record *p_item_recipe =
        get_p_item_recipe_from__item_recipe_manager(
                p_item_recipe_manager, 
                the_kind_of__item);

    // Remove the used items.
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

        Quantity__u32 quantity_of__items_to__remove =
            p_item_recipe_requirement
            ->the_quantity_of__items_required;

        if (is_nth_requirement_of__item_recipe__efficent(
                    item_recipe_flags, 
                    index_of__requirement)) {
            quantity_of__items_to__remove >>= 1;
        }

        remove_this_many_item_kinds_from__inventory(
                p_inventory, 
                p_item_recipe_requirement
                ->the_kind_of__item_that_is__required, 
                quantity_of__items_to__remove);
    }

    return true;
}

bool is_item__craftable(
        Item_Recipe_Manager *p_item_recipe_manager,
        Item_Kind the_kind_of__item) {
    return 
        !is_item_kind__illegal_for__item_recipe_manager(
                the_kind_of__item)
        && get_p_item_recipe_from__item_recipe_manager(
                p_item_recipe_manager, 
                the_kind_of__item)
        ->the_kind_of__item_this__recipe_makes
        != Item_Kind__None;
}

void register_core_item_recipes_into__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager) { 
    register_into__recipe_manager__door__wood(
            p_item_recipe_manager);
}

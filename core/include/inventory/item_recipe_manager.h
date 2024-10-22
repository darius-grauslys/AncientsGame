#ifndef ITEM_RECIPE_MANAGER_H
#define ITEM_RECIPE_MANAGER_H

#include <defines.h>

void initialize_item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager);

///
/// TODO: currently, there is only one way to make
/// each item.
///
void register_item_recipe_into__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager,
        Item_Recipe_Record item_recipe);

bool is_inventory_capable_of__making_this_item_in__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager,
        Inventory *p_inventory,
        Item_Kind the_kind_of__item,
        Item_Recipe_Flags item_recipe_flags);

bool make_item_with__this_inventory(
        Item_Recipe_Manager *p_item_recipe_manager,
        Inventory *p_inventory,
        Item_Kind the_kind_of__item,
        Item_Recipe_Flags item_recipe_flags);

bool is_item__craftable(
        Item_Recipe_Manager *p_item_recipe_manager,
        Item_Kind the_kind_of__item);

void register_core_item_recipes_into__item_recipe_manager(
        Item_Recipe_Manager *p_item_recipe_manager);

#endif

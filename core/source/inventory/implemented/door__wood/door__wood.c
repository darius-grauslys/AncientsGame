#include <inventory/implemented/door__wood/door__wood.h>
#include <inventory/implemented/building_material.h>
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/item_recipe.h"
#include "inventory/item_recipe_manager.h"
#include "inventory/item_recipe_record.h"
#include "inventory/item_recipe_requirement.h"
#include "numerics.h"

void register_into__item_manager__door__wood_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Door__Wood, 
            get_building_material(
                Item_Kind__Door__Wood, 
                i32_to__i32F20(80), 
                Tile_Kind__None,
                Tile_Cover_Kind__Door__Horizontal__Wood));
}

void register_into__recipe_manager__door__wood(
        Item_Recipe_Manager *p_item_recipe_manager) {
    Item_Recipe_Requirement requirements[
        ITEM_REQUIREMENT_MAX_QUANTITY_OF] = {
        get_item_recipe_requirement(
                Item_Kind__Pile__Wood__Plenty, 
                1),
        get_item_recipe_requirement(
                Item_Kind__None, 
                0),
        get_item_recipe_requirement(
                Item_Kind__None, 
                0),
        get_item_recipe_requirement(
                Item_Kind__None, 
                0),
    };
    register_item_recipe_into__item_recipe_manager(
            p_item_recipe_manager, 
            get_item_recipe_record(
                Item_Kind__Door__Wood, 
                1, 
                requirements));
}

#include <inventory/implemented/door__amethyst/door__amethyst.h>
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/building_material.h>

void register_into__item_manager__door__amethyst_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Door__Amethyst, 
            get_building_material(
                Item_Kind__Door__Amethyst, 
                i32_to__i32F20(80), 
                Tile_Kind__None,
                Tile_Cover_Kind__Door__Horizontal__Amethyst));
}


#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__sand__plenty/pile__sand__plenty.h>
#include <inventory/implemented/building_material.h>

void register_into__item_manager__pile__sand__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Sand__Plenty, 
            get_building_material(
                Item_Kind__Pile__Sand__Plenty, 
                i32_to__i32F20(80), 
                Tile_Kind__Sand,
                Tile_Cover_Kind__Wall__Sand));
}

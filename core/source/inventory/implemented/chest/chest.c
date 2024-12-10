#include "inventory/implemented/chest/chest.h"
#include "defines_weak.h"
#include "inventory/implemented/building_material.h"
#include "inventory/item_manager.h"
#include "numerics.h"

void register_into__item_manager__chest_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Chest, 
            get_building_material(
                Item_Kind__Chest, 
                i32_to__i32F20(80), 
                Tile_Kind__None,
                Tile_Cover_Kind__Chest__Single));
}

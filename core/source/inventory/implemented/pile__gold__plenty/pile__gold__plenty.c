#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/pile__gold__plenty/pile__gold__plenty.h>
#include <inventory/implemented/building_material.h>

void register_into__item_manager__pile__gold__plenty_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Pile__Gold__Plenty, 
            get_building_material(
                Item_Kind__Pile__Gold__Plenty, 
                i32_to__i32F20(80), 
                Tile_Kind__Gold,
                Tile_Cover_Kind__Wall__Gold));
}

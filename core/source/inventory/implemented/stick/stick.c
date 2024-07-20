#include "inventory/implemented/stick/stick.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/implemented/weapon.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"

void register_into__item_manager__stick(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Stick, 
            get_weapon(
                Item_Kind__Stick,
                1<< 16,
                HEARTS_DAMAGING_FLAG__IS_BLUDGEONING,
                2));
}


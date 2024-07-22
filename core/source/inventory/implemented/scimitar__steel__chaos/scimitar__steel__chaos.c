#include "inventory/implemented/scimitar__steel__chaos/scimitar__steel__chaos.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"

void register_into__item_manager__scimitar__steel__chaos_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Scimitar__Steel__Chaos, 
            get_weapon(
                Item_Kind__Scimitar__Steel__Chaos, 
                i32_to__i32F20(7), 
                HEARTS_DAMAGING_FLAG__IS_CURSING
                | HEARTS_DAMAGING_FLAG__IS_CHAOS, 
                17));
}

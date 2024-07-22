#include "inventory/implemented/armor__steel__chaos/armor__steel__chaos.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/implemented/armor.h"
#include "inventory/item_manager.h"
#include "numerics.h"

void register_into__item_manager__armor_steel__chaos(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Armor__Steel__Chaos,
            get_armor(
                Item_Kind__Armor__Steel__Chaos, 
                i32F4_to__i32F20(22), 
                HEARTS_DAMAGING_FLAG__IS_SLASHING
                | HEARTS_DAMAGING_FLAG__IS_BLUDGEONING
                | HEARTS_DAMAGING_FLAG__IS_PIERCING
                | HEARTS_DAMAGING_FLAG__IS_ORDER, 
                6,
                m_item_equip_handler__armor_steel__chaos));
}

bool m_item_equip_handler__armor_steel__chaos(
        Item *p_this_armor_steel__chaos,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game) {
    if (the_kind_of__slot
            != Entity_Equipment_Slot_Kind__Armor)
        return false;

    p_entity_user->humanoid__armor_properties
        .the_kind_of_armor__this_armor_is =
        Entity_Armor_Kind__Steel;
    p_entity_user->humanoid__armor_properties
        .the_kind_of_modification__this_armor_has =
        Entity_Armor_Modification_Kind__Amethyst;
    return true;
}

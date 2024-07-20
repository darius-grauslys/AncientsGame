#include "inventory/implemented/armor__iron/armor__iron.h"
#include "defines.h"
#include "defines_weak.h"
#include "inventory/handlers/armor/armor.h"
#include "inventory/item_manager.h"
#include "numerics.h"

void register_into__item_manager__armor_iron(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Armor__Iron, 
            ITEM_FILTER_FLAG__ARMOR, 
            i32_to__i32F20(4), 
            0, 
            m_item_protect_handler__armor_iron, 
            m_item_equip_handler__armor_iron, 
            m_item_unequip_handler__armor__default);
}

void m_item_protect_handler__armor_iron(
        Item *p_this_armor_iron,
        Entity *p_entity_user,
        Game *p_game,
        Hearts_Damaging_Specifier *p_hearts_damage) {
    p_hearts_damage->quantity_of__damage =
        subtract_u16__no_overflow(
                p_hearts_damage->quantity_of__damage, 
                1);
}

bool m_item_equip_handler__armor_iron(
        Item *p_this_armor_iron,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game) {
    if (the_kind_of__slot
            != Entity_Equipment_Slot_Kind__Armor)
        return false;

    p_entity_user->humanoid__armor_properties
        .the_kind_of_armor__this_armor_is =
        Entity_Armor_Kind__Iron;
    p_entity_user->humanoid__armor_properties
        .the_kind_of_modification__this_armor_has =
        Entity_Armor_Modification_Kind__None;
    return true;
}

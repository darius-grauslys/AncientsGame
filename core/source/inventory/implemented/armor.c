#include "inventory/implemented/armor.h"
#include "defines.h"
#include "defines_weak.h"
#include "game_action/game_action.h"
#include "inventory/item.h"
#include "numerics.h"

void initialize_item_as__armor(
        Item *p_item__armor,
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags damage_type,
        Quantity__u8 quantity_of__damage,
        m_Item_Equip_Event m_item_equip_handler) {
    initialize_item(
            p_item__armor,
            the_kind_of__item,
            ITEM_USAGE_FLAGS__NONE,
            ITEM_FILTER_FLAG__INTERACTABLE,
            weight_of_each__item,
            m_item_use_handler__armor,
            m_item_equip_handler, 
            m_item_unequip_handler__armor__default);
    p_item__armor->armor__resistances =
        damage_type;
    p_item__armor->armor__quantity_of__protection_u8 =
        quantity_of__damage;
}

void m_item_use_handler__armor(
        Item *p_item_self, 
        Entity *p_entity_user, 
        Game_Action *p_game_action,
        Game *p_game) {
    switch (get_the_kind_of__game_action(p_game_action)) {
        default:
            return;
        case Game_Action_Kind__Entity__Health__Apply_Damage:
            break;
    }

    Hearts_Damaging_Specifier *p_damage_spec =
        &p_game_action->hearts_damaging_specifier;

    Quantity__u16 quantity_of__damage = 
        p_damage_spec->quantity_of__damage;

    if (p_damage_spec->hearts_damaging__flags
            & p_item_self->armor__resistances) {
        quantity_of__damage =
            r_bitshift_u16__clamped(
                    quantity_of__damage, 1, 1);
    }
    p_damage_spec->quantity_of__damage =
        subtract_u16__no_overflow(
                quantity_of__damage, 
                p_item_self->armor__quantity_of__protection_u8);
}

bool m_item_unequip_handler__armor__default(
        Item *p_this_armor_cloth,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game) {
    p_entity_user->humanoid__armor_properties
        .the_kind_of_armor__this_armor_is =
        Entity_Armor_Kind__None;
    p_entity_user->humanoid__armor_properties
        .the_kind_of_modification__this_armor_has =
        Entity_Armor_Modification_Kind__None;
    return true;
}

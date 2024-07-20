#ifndef ARMOR_H
#define ARMOR_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item_as__armor(
        Item *p_item__armor,
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags resistance_type,
        Quantity__u8 quantity_of__protection,
        m_Item_Equip_Event m_item_equip_handler);

static inline
Item get_armor(
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags resistance_type,
        Quantity__u8 quantity_of__protection,
        m_Item_Equip_Event m_item_equip_handler) {
    Item armor;
    initialize_item_as__armor(
            &armor, 
            the_kind_of__item,
            weight_of_each__item, 
            resistance_type, 
            quantity_of__protection,
            m_item_equip_handler);
    return armor;
}

void m_item_use_handler__armor(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game);

bool m_item_unequip_handler__armor__default(
        Item *p_this_armor_cloth,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game);

static inline
bool does_armor__resist_chaos(
        Item *p_item_armor) {
    return p_item_armor->armor__resistances
        & HEARTS_DAMAGING_FLAG__IS_CHAOS
        ;
}

static inline
bool does_armor__resist_order(
        Item *p_item_armor) {
    return p_item_armor->armor__resistances
        & HEARTS_DAMAGING_FLAG__IS_ORDER
        ;
}

#endif

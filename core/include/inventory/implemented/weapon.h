#ifndef WEAPON_H
#define WEAPON_H

#include "defines_weak.h"
#include <defines.h>

void initialize_item_as__weapon(
        Item *p_item__weapon,
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags damage_type,
        Quantity__u8 quantity_of__damage);

static inline
Item get_weapon(
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Hearts_Damaging_Flags damage_type,
        Quantity__u8 quantity_of__damage) {
    Item weapon;
    initialize_item_as__weapon(
            &weapon, 
            the_kind_of__item,
            weight_of_each__item, 
            damage_type, 
            quantity_of__damage);
    return weapon;
}

void m_item_use_handler__weapon(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game);

#endif

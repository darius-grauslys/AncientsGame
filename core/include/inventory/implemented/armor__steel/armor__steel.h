#ifndef ARMOR_STEEL_H
#define ARMOR_STEEL_H

#include "defines_weak.h"
#include <defines.h>

void register_into__item_manager__armor_steel(
        Item_Manager *p_item_manager);

void m_item_protect_handler__armor_steel(
        Item *p_this_armor_steel,
        Entity *p_entity_user,
        Game *p_game,
        Hearts_Damaging_Specifier *p_hearts_damage);

bool m_item_equip_handler__armor_steel(
        Item *p_this_armor_steel,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game);

#endif

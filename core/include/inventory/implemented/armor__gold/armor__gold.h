#ifndef ARMOR_GOLD_H
#define ARMOR_GOLD_H

#include "defines_weak.h"
#include <defines.h>

void register_into__item_manager__armor_gold(
        Item_Manager *p_item_manager);

bool m_item_equip_handler__armor_gold(
        Item *p_this_armor_gold,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game);

#endif

#ifndef ARMOR_STEEL__ORDER_H
#define ARMOR_STEEL__ORDER_H

#include "defines_weak.h"
#include <defines.h>

void register_into__item_manager__armor_steel__order(
        Item_Manager *p_item_manager);

bool m_item_equip_handler__armor_steel__order(
        Item *p_this_armor_steel__order,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game);

#endif

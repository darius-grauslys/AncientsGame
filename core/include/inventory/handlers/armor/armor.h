#ifndef ARMOR_H
#define ARMOR_H

#include "defines.h"

bool m_item_unequip_handler__armor__default(
        Item *p_this_armor_cloth,
        Entity *p_entity_user,
        enum Entity_Equipment_Slot_Kind the_kind_of__slot,
        Game *p_game);

#endif

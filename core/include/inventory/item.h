#ifndef ITEM_H
#define ITEM_H

#include <defines.h>

typedef struct Item_t {
    m_item_use      use_handler;
    m_item_equip    equip_handler;
    m_item_unequip  unequip_handler;
} Item;

void offset_item_durability(Item* item, int offset);
void set_item_durability(Item* item, int value);

#endif

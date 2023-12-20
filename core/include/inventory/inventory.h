#ifndef INVENTORY_H
#define INVENTORY_H

#include <defines.h>

typedef struct Inventory_t {

} Inventory;

void add_item_to_inventory(Inventory* inventory, Item* item);
void remove_item_from_inventory(Inventory *inventory, Item* item);

#endif

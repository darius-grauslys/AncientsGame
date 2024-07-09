#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_inventory_manager(
        Inventory_Manager *p_inventory_manager);

Inventory *allocate_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager);

void release_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Inventory *p_inventory);

Inventory *get_p_inventory_by__identifier_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Identifier__u32 identifier_for__inventory);

#endif

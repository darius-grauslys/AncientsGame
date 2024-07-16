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

static inline
Inventory *get_p_inventory_by__index_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Index__u32 index_of__inventory) {
    return &p_inventory_manager->inventories[index_of__inventory];
}

bool resolve_s_inventory_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Inventory_Ptr *s_inventory_ptr);

bool resolve_s_item_stack_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Item_Stack_Ptr *s_item_stack_ptr);

#endif
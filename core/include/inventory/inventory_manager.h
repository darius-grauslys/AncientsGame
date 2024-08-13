#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_inventory_manager(
        Inventory_Manager *p_inventory_manager);

Inventory *allocate_p_inventory_using__this_uuid_in__inventory_manager(
        Inventory_Manager *p_inventory_manager, 
        Identifier__u32 uuid);

Inventory *allocate_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager);

void release_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Inventory *p_inventory);

Inventory *get_p_inventory_by__identifier_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Identifier__u32 identifier_for__inventory);

///
/// This will truncate the chunk_vector to
/// fit inside it's region 
/// mod (2^REGION__WIDTH__BIT_SHIFT)
/// mod (2^REGION__HEIGHT__BIT_SHIFT)
///
typedef void (*f_Foreach_Inventory_Container)(
        Game *p_game,
        Inventory *p_inventory,
        Inventory_Manager *p_inventory_manager,
        void *p_data);
void foreach_p_inventory_container_in__chunk_vector(
        Inventory_Manager *p_inventory_manager,
        Chunk_Vector__3i32 chunk_vector__3i32,
        f_Foreach_Inventory_Container f_callback,
        Game *p_game,
        void *p_data);

static inline
Inventory *get_p_inventory_for__entity_by__index_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Index__u32 index_of__inventory) {
    return &p_inventory_manager->inventories_for__entities[index_of__inventory];
}

static inline
Inventory *get_p_inventory_for__container_by__index_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Index__u32 index_of__inventory) {
    return &p_inventory_manager->inventories_for__containers[
        index_of__inventory];
}

bool resolve_s_inventory_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Inventory_Ptr *s_inventory_ptr);

bool resolve_s_item_stack_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Item_Stack_Ptr *s_item_stack_ptr);

#endif

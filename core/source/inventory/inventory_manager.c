#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "serialization/identifiers.h"
#include <inventory/inventory_manager.h>

void initialize_inventory_manager(
        Inventory_Manager *p_inventory_manager) {
    for (Index__u32 index_of__inventory = 0;
            index_of__inventory
            < INVENTORY_MAX_QUANTITY_OF;
            index_of__inventory++) {
        Inventory *p_inventory =
            get_p_inventory_by__index_in__inventory_manager(
                    p_inventory_manager,
                    index_of__inventory);
        initialize_inventory_as__empty(
                p_inventory);
    }
}

Inventory *allocate_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager) {
    Inventory *p_inventory =
        (Inventory*)get_next_available_p_serialization_header(
                (Serialization_Header*)p_inventory_manager->inventories, 
                INVENTORY_MAX_QUANTITY_OF);

    if (!p_inventory)
        return 0;
}

void release_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Inventory *p_inventory) {
#ifndef NDEBUG
    if (p_inventory
            - p_inventory_manager->inventories
            >= INVENTORY_MAX_QUANTITY_OF) {
        debug_abort("release_p_inventory_in__inventory_manager, p_inventory: %p does not belong to this manager: %p.",
                p_inventory,
                p_inventory_manager);
        return;
    }
#endif
    initialize_inventory_as__empty(
            p_inventory);
    p_inventory_manager->quantity_of__active_inventories--;
}

Inventory *get_p_inventory_by__identifier_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Identifier__u32 identifier_for__inventory) {

}

bool resolve_s_inventory_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Inventory_Ptr *s_inventory_ptr) {
    Identifier__u32 inventory_identifier__u32 =
        merge_identifiers_u32(
                s_inventory_ptr->identifier_for__serialized_field, 
                INVENTORY_IDENTIFIER_BITS, 
                0);

    Serialized_Inventory_Ptr s_inventory_ptr__copy;
    initialize_serialized_field_as__unlinked(
            &s_inventory_ptr__copy, 
            inventory_identifier__u32);

    link_serialized_field(
            &s_inventory_ptr__copy, 
            (Serialization_Header*)p_inventory_manager->inventories, 
            p_inventory_manager->quantity_of__active_inventories);

    if (is_p_serialized_field__linked(
                &s_inventory_ptr__copy)) {
        s_inventory_ptr->p_serialized_field__inventory =
            s_inventory_ptr__copy.p_serialized_field__inventory;
        return true;
    }

    return false;
}

bool resolve_s_item_stack_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Item_Stack_Ptr *s_item_stack_ptr) {
    if (!is_p_serialized_field__linked(s_item_stack_ptr)) {
        Serialized_Inventory_Ptr *s_inventory_ptr = s_item_stack_ptr;
        resolve_s_inventory_ptr_to__inventory_manager(
                p_inventory_manager, 
                s_inventory_ptr);

        Identifier__u32 inventory_identifier__u32 =
            merge_identifiers_u32(
                    s_inventory_ptr->identifier_for__serialized_field,
                    INVENTORY_IDENTIFIER_BITS, 
                    s_item_stack_ptr->identifier_for__serialized_field);

        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory(
                    s_item_stack_ptr->p_serialized_field__inventory, 
                    inventory_identifier__u32);

        if (!p_item_stack)
            return false;

        s_item_stack_ptr->p_serialized_field__item_stack =
            p_item_stack;
        return true;
    }
    
    return false;
}
